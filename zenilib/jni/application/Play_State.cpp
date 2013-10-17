#include "Play_State.h"

#include "Player.h"

Play_State::Play_State() {
	god_view_on = false;

}

void Play_State::on_push() {
    Zeni::get_Window().set_mouse_state(Zeni::Window::MOUSE_RELATIVE);
}

void Play_State::on_pop() {

}

void Play_State::on_key(const SDL_KeyboardEvent &event) {
  switch(event.keysym.sym) {
    case SDLK_w:
      movement_controls.forward = event.type == SDL_KEYDOWN; break;
    case SDLK_a:
      movement_controls.left = event.type == SDL_KEYDOWN; break;
    case SDLK_s:
      movement_controls.back = event.type == SDL_KEYDOWN; break;
    case SDLK_d:
      movement_controls.right = event.type == SDL_KEYDOWN; break;
    case SDLK_SPACE:
      if(event.type == SDL_KEYDOWN) {
        player_moved = true;
      }
      break;

    default:
      Gamestate_Base::on_key(event);
      break;
  }
}

void Play_State::on_mouse_motion(const SDL_MouseMotionEvent &event) {
  //TODO: Maybe add some crate code back into here from Crate_State.cpp
}


void Play_State::perform_logic() {
  const Zeni::Time_HQ current_time = Zeni::get_Timer_HQ().get_time();
  float processing_time = float(current_time.get_seconds_since(time_passed));
  time_passed = current_time;

  /** Keep delays under control (if the program hangs for some time, we don't want to lose responsiveness) **/
  if(processing_time > 0.1f)
    processing_time = 0.1f;

  //DOES: Physics loop
  for(float time_step = 0.05f; processing_time > 0.0f; processing_time -= time_step)
  {
    if(time_step > processing_time)
      time_step = processing_time;
  }
}

void Play_State::render() {
	//set up camera
  Zeni::Video &vr = Zeni::get_Video();
	if(god_view_on)
		vr.set_3d(god_view);
	else
		vr.set_3d(player.get_camera());

  //render call for level
}
