/* This file is part of the Zenipex Library (zenilib).
 * Copyleft (C) 2011 Mitchell Keith Bloch (bazald).
 *
 * This source file is simply under the public domain.
 */

#include <zenilib.h>

#include "Play_State.h"

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Zeni;
//
//class Play_State : public Gamestate_Base {
//  Play_State(const Play_State &);
//  Play_State operator=(const Play_State &);
//
//public:
//  Play_State() {
//    set_pausable(true);
//  }
//
//private:
//  void on_push() {
//    get_Window().set_mouse_state(Window::MOUSE_HIDDEN);
//  }
//
//  void on_pop() {
//    get_Controllers().reset_vibration_all();
//  }
//
//  void on_cover() {
//    get_Controllers().reset_vibration_all();
//  }
//
//  void on_controller_button(const SDL_ControllerButtonEvent &event) {
//    if(event.button == SDL_CONTROLLER_BUTTON_BACK && event.state == SDL_PRESSED)
//      get_Game().push_Popup_Menu_State();
//  }
//};

class Instructions_State : public Widget_Gamestate {
  Instructions_State(const Instructions_State &);
  Instructions_State operator=(const Instructions_State &);

public:
  Instructions_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
  {
  }

private:
  void on_key(const SDL_KeyboardEvent &event) {
    if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
      get_Game().pop_state();
  }

  void render() {
    Widget_Gamestate::render();

    Zeni::Font &fr = get_Fonts()["system_24_800x600"];

    fr.render_text(
		Zeni::String("Your objective is to defend the homeland against waves of invading enemies\nwith the powers of physics!\n1. Build towers to attack enemies!\n2. Build towers on top of other towers to unleash their effects!\n3. Enemies will walk along the ground or sky in the sky: be prepared!\n\n-Alt+F4 to Quit\n-ESC to bring up menu\n-Click on a Tower Base to add Towers to it\n-Right click an enemy while having a tower selected to order it to attack that enemy!\n-Click on anything to view its attributes\n-Towers cost gold; survive to get more!\n\n-WASD or Mouse to move the camera\n-Mouse wheel to zoom\n-Q & E to rotate the camera"),
		Point2f(50.0f, 10.0f - 0.5f * fr.get_text_height()),
        get_Colors()["title_text"],
        ZENI_LEFT);
  }
};

class Bootstrap {
  class Gamestate_One_Initializer : public Gamestate_Zero_Initializer {
    virtual Gamestate_Base * operator()() {
      Window::set_title("ZTD");

      get_Controllers();
      get_Video();
      get_Textures();
      get_Fonts();
      get_Sounds();

      return new Title_State<Play_State, Instructions_State>("ZTD");
    }
  } m_goi;

public:
  Bootstrap() {
    g_gzi = &m_goi;
  }
} g_bootstrap;

int main(int argc, char **argv) {
  return zenilib_main(argc, argv);
}
