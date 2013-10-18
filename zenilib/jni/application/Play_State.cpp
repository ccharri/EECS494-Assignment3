#include "Play_State.h"

#include "Player.h"
#include "Game_Level.h"
#include "Level1.h"
#include "Enemy_Box.h"
#include "Tower_Base.h"
#include "Tower_Section.h"
#include "Rock_Dropper.h"

using namespace Zeni;
using namespace std;

Play_State::Play_State() /*: player(Player(Point3f(), Vector3f(), Quaternion()))*/ 
{
	god_view_on = true;
	god_view = Camera(Point3f(-60, 0, 40), Quaternion(0, (Global::pi_over_two/2.), 0), 10.0f, 1000.0f, Global::pi_over_two, 1.25f);

	worldLight = Light();

	Game_Level::setCurrentLevel(new Level_One());

	Game_Level::getCurrentLevel()->getEnemies().push_back(new Enemy_Box(Point3f(-50, -50, 0), Vector3f(), Quaternion(), 10., 100.));

	Tower_Base* centerBase = new Tower_Base(Point3f(0,0,0));
	Tower_Section* newSection = new Tower_Section(Point3f(), Vector3f());
	Rock_Dropper* dropper = new Rock_Dropper(newSection, 2.);
	newSection->setWeapon(dropper);
	centerBase->pushSection(newSection);

	Game_Level::getCurrentLevel()->getBases().push_back(centerBase);
	
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

	performMovement(time_step);

	Game_Level::getCurrentLevel()->on_logic(time_step);
  }
}

void Play_State::performMovement(float time_step)
{
	float speed = 20.f;
	float distance = speed * time_step;

	if(movement_controls.forward) {
		god_view.move_forward_xy(distance);
	}

	if(movement_controls.back) {
		god_view.move_forward_xy(-distance);
	}

	if(movement_controls.left)
	{
		god_view.move_left_xy(distance);
	}

	if(movement_controls.right)
	{
		god_view.move_left_xy(-distance);
	}
}

void Play_State::render() {
	//set up camera
  Zeni::Video &vr = Zeni::get_Video();
	if(god_view_on)
		vr.set_3d(god_view);
	//else
	//	vr.set_3d(player.get_camera());

  //render call for level
	Game_Level::getCurrentLevel()->render();
}
