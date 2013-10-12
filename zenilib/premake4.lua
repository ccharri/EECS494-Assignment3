-- dofile "dev/os_copy.lua"

newoption {
   trigger     = "build",
   value       = "WHICH",
   description = "Choose which binaries to build",
   allowed = {
      { "all",   "game and all dependencies" },
      { "mine",  "game only (default)" }
   }
}

if not _OPTIONS["build"] then
   _OPTIONS["build"] = "mine"
end

newoption {
   trigger     = "dir",
   value       = "DIR",
   description = "Choose the build directory"
}

if not _OPTIONS["dir"] then
   _OPTIONS["dir"] = "build"
end

solution "zenilib"
  configurations { "Debug", "Release" }

  if os.get() == "windows" then
    defines { "_WINDOWS", "WIN32", "_CRT_SECURE_NO_DEPRECATE" }
    platforms { "x32", "x64" }
    TARGET_DIR = "bin"
  elseif os.get() == "macosx" then
    premake.gcc.cc = "clang"
    premake.gcc.cxx = "clang++"
    defines { "_MACOSX" }
    platforms { "native", "universal" }
    TARGET_DIR = "lib"
  else
    defines { "_LINUX" }
    platforms { "x32", "x64" }
    TARGET_DIR = "lib"
  end

  configuration "Debug*"
    defines { "_DEBUG", "DEBUG", "TEST_NASTY_CONDITIONS" }
    flags { "Symbols" }
    targetsuffix "_d"

  configuration "Release*"
    defines { "NDEBUG" }
    flags { "Optimize" }

  configuration { "Debug*", "x32" }
    targetdir(TARGET_DIR .. "/d32")
    libdirs { TARGET_DIR .. "/d32" }
  configuration { "Release*", "x32" }
    targetdir(TARGET_DIR .. "/x32")
    libdirs { TARGET_DIR .. "/x32" }
  configuration { "Debug*", "x64" }
    defines { "X64" }
    targetdir(TARGET_DIR .. "/d64")
    libdirs { TARGET_DIR .. "/d64" }
  configuration { "Release*", "x64" }
    defines { "X64" }
    targetdir(TARGET_DIR .. "/x64")
    libdirs { TARGET_DIR .. "/x64" }
  configuration { "macosx", "Debug*" }
    libdirs { TARGET_DIR .. "/univ_d" }
  configuration { "macosx", "Release*" }
    libdirs { TARGET_DIR .. "/univ" }

  configuration "*"
    defines { "DISABLE_CPP11", "GLEW_NO_GLU" }

  configuration "windows"
    defines { "ZLIB_DLL",
--              "GLAPI=extern",
              "OGG_DLL=__declspec(dllimport)",
              "VORBIS_DLL=__declspec(dllimport)",
              "VORBISFILE_DLL=__declspec(dllimport)",
              "LIB3DSAPI=__declspec(dllimport)",
              "TINYXML_DLL=__declspec(dllimport)",
              "TINYXML_EXT=extern",
              "ZENI_DLL=__declspec(dllimport)",
              "ZENI_EXT=extern",
              "ZENI_AUDIO_DLL=__declspec(dllimport)",
              "ZENI_AUDIO_EXT=extern",
              "ZENI_CORE_DLL=__declspec(dllimport)",
              "ZENI_CORE_EXT=extern",
              "ZENI_GRAPHICS_DLL=__declspec(dllimport)",
              "ZENI_GRAPHICS_EXT=extern",
              "ZENI_NET_DLL=__declspec(dllimport)",
              "ZENI_NET_EXT=extern",
              "ZENI_REST_DLL=__declspec(dllimport)",
              "ZENI_REST_EXT=extern" }
  configuration "not windows"
    defines { "OGG_DLL="           ,
              "VORBIS_DLL="        ,
              "VORBISFILE_DLL="    ,
              "DISABLE_DX9"       , "DISABLE_WGL"       ,
              "TINYXML_DLL="      , "TINYXML_EXT="      ,
              "ZENI_DLL="         , "ZENI_EXT="         ,
              "ZENI_AUDIO_DLL="   , "ZENI_AUDIO_EXT="   ,
              "ZENI_CORE_DLL="    , "ZENI_CORE_EXT="    ,
              "ZENI_GRAPHICS_DLL=", "ZENI_GRAPHICS_EXT=",
              "ZENI_NET_DLL="     , "ZENI_NET_EXT="     ,
              "ZENI_REST_DLL="    , "ZENI_REST_EXT=" }

  configuration "linux"
    linkoptions { "-Wl,-rpath,'$$ORIGIN'",
                  "-Wl,--hash-style=both" }
    links { "rt" }

  configuration "macosx"
    buildoptions { "-Qunused-arguments" }

  configuration "*"
    if _ACTION then
      location (_OPTIONS.dir .. "/" .. _ACTION)
    end

  include "jni/application"

  if _OPTIONS.build == "all" then
    include "jni/launcher"
    include "jni/external/lib3ds"
    include "jni/external/zlib"
    include "jni/external/libpng"
    include "jni/external/freetype2"
    include "jni/external/tinyxml"
    include "jni/external/angle"
    include "jni/external/glew"
    include "jni/external/libogg"
    include "jni/external/libvorbis"
    include "jni/external/sdl"
    include "jni/external/sdl_net"
    include "jni/external/zenilib/zeni"
    include "jni/external/zenilib/zeni_audio"
    include "jni/external/zenilib/zeni_core"
    include "jni/external/zenilib/zeni_graphics"
    include "jni/external/zenilib/zeni_net"
    include "jni/external/zenilib/zeni_rest"
  end
