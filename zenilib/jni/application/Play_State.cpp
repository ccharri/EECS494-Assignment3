#include "Play_State.h"

void Play_State::on_push() {
    Zeni::get_Window().set_mouse_state(Zeni::Window::MOUSE_RELATIVE);
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
        player.jump();
        player_moved = true;
      }
      break;

    default:
      Gamestate_Base::on_key(event);
      break;
  }
}

void Play_State::on_mouse_motion(const SDL_MouseMotionEvent &event) {
  player.adjust_pitch(event.yrel / 500.0f);
  player.turn_left_xy(-event.xrel / 500.0f);
}

void Play_State::perform_logic() {
  const Zeni::Time_HQ current_time = Zeni::get_Timer_HQ().get_time();
  float processing_time = float(current_time.get_seconds_since(time_passed));
  time_passed = current_time;

  /** Get forward and left vectors in the XY-plane **/
  const Zeni::Vector3f forward = player.get_camera().get_forward().get_ij().normalized();
  const Zeni::Vector3f left = player.get_camera().get_left().get_ij().normalized();

  /** Get velocity vector split into a number of axes **/
  const Zeni::Vector3f velocity = (m_controls.forward - m_controls.back) * 50.0f * forward
                          + (m_controls.left - m_controls.right) * 50.0f * left;
  const Zeni::Vector3f x_vel = velocity.get_i();
  const Zeni::Vector3f y_vel = velocity.get_j();
  Zeni::Vector3f z_vel = player.get_velocity().get_k();

  /** Bookkeeping for sound effects **/
  if(velocity.magnitude() != 0.0f)
    player_moved = true;

  /** Keep delays under control (if the program hangs for some time, we don't want to lose responsiveness) **/
  if(processing_time > 0.1f)
    processing_time = 0.1f;

  /** Physics processing loop**/
  for(float time_step = 0.05f; processing_time > 0.0f; processing_time -= time_step)
  {
    if(time_step > processing_time)
      time_step = processing_time;

    /** Gravity has its effect **/
    z_vel -= Zeni::Vector3f(0.0f, 0.0f, 50.0f * time_step);

    /** Try to move on each axis **/
    partial_step(time_step, x_vel);
    partial_step(time_step, y_vel);
    partial_step(time_step, z_vel);

    /** Keep player above ground; Bookkeeping for jumping controls **/
    const Zeni::Point3f &position = player.get_camera().position;
    if(position.z < 50.0f) {
      player.set_position(Zeni::Point3f(position.x, position.y, 50.0f));
      player.set_on_ground(true);
    }
  }
}

void Play_State::render() {
  Zeni::Video &vr = Zeni::get_Video();
  vr.set_3d(player.get_camera());

  //render call for level
}
