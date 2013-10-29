#include "Play_State.h"

#include <memory>

#include "Player.h"
#include "Arrow.h"
#include "Game_Level.h"
#include "Level1.h"
#include "Enemy_Box.h"
#include "Tower_Base.h"
#include "Tower_Section.h"
#include "Rock_Dropper.h"
#include "Rocket_Launcher.h"
#include "Rock.h"
#include "Rocket.h"
#include "Utility.h"
#include "XML_Level.h"

using namespace Zeni;
using namespace std;

Play_State::Play_State() : Widget_Gamestate(make_pair(Point2f(get_Video().get_viewport().first), Point2f(get_Video().get_viewport().second))), gui(this) /*: player(Player(Point3f(), Vector3f(), Quaternion()))*/ 
{
	god_view_on = true;
	god_view = Camera(Point3f(-60, 0, 40), Quaternion(0, (Global::pi_over_two/2.), 0), 1.0f, 1000.0f, Global::pi_over_two, 1.f);
	
	worldLight = Light();
	worldLight.set_light_type(Zeni::LIGHT_DIRECTIONAL);
	worldLight.spot_direction = Vector3f(1, 1, -1);

	backLight = Light();
	backLight.set_light_type(Zeni::LIGHT_DIRECTIONAL);
	backLight.spot_direction = Vector3f(-1, -1, -1);
	backLight.ambient = Color(1., .4, .4, .4);
	backLight.diffuse = Color(1., .4, .4, .4);
	backLight.specular = Color(1., .4, .4, .4);

	get_Video().set_Light(0, worldLight);
	get_Video().set_Light(1, backLight);

	time_since_last_spawn = 0;

	Game_Level::setCurrentLevel(new XML_Level("levels/level1.level", this));
	Game_Level::getCurrentLevel()->pushEnemy(shared_ptr<Game_Object>(new Arrow(Point3f(-50., -50., 0.))));
}

void Play_State::on_push() {
	Zeni::get_Window().set_mouse_state(Zeni::Window::MOUSE_GRABBED);
}

void Play_State::on_pop() {

}

void Play_State::on_key(const SDL_KeyboardEvent &event) {
	gui.on_key(event);

  switch(event.keysym.sym) {
	case SDLK_e:
		movement_controls.rotateRight = event.type == SDL_KEYDOWN; break;
	case SDLK_q:
		movement_controls.rotateLeft = event.type == SDL_KEYDOWN; break;
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
		Widget_Gamestate::on_key(event);
      break;
  }
}

void Play_State::on_mouse_wheel(const SDL_MouseWheelEvent &event) {
	Widget_Gamestate::on_mouse_wheel(event);
	god_view.position += god_view.get_forward().normalized() * event.y;
}

void Play_State::on_mouse_motion(const SDL_MouseMotionEvent &event) {
	Widget_Gamestate::on_mouse_motion(event);
	gui.on_mouse_motion(event);
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

	time_since_last_spawn += time_step;

	performMovement(time_step);

	proj = Projector3D(god_view, get_Video().get_viewport());

	gui.on_logic(proj);

	/*
	if(time_since_last_spawn > 4.)
	{
		Game_Level::getCurrentLevel()->getEnemies().push_back(shared_ptr<Game_Object>(new Enemy_Box(Point3f(-50, -50, 0), 10., 100.)));
		time_since_last_spawn -= 4.f;
	}
	*/

	Game_Level::getCurrentLevel()->on_logic(time_step);
  }

  Widget_Gamestate::perform_logic();
}

void Play_State::performMovement(float time_step)
{
	float speed = 20.f;
	float distance = speed * time_step;
	float angularSpeed = 0.01;

	float mouseWindowPanBufferDistance = 40.f;

	Point2f mousePos = gui.getMousePos();

	if(mousePos.y <= mouseWindowPanBufferDistance){
		god_view.move_forward_xy((mouseWindowPanBufferDistance - mousePos.y) * time_step);
	}
	else if(movement_controls.forward) {
		god_view.move_forward_xy(distance);
	}

	if(mousePos.y >= (Window::get_height() - mouseWindowPanBufferDistance)){
		god_view.move_forward_xy(((Window::get_height() - mouseWindowPanBufferDistance) - mousePos.y) * time_step);
	}
	else if(movement_controls.back){
		god_view.move_forward_xy(-distance);
	}

	if(mousePos.x <= mouseWindowPanBufferDistance){
		god_view.move_left_xy((mouseWindowPanBufferDistance - mousePos.x) * time_step);
	}else if(movement_controls.left){
		god_view.move_left_xy(distance);
	}

	if(mousePos.x >= (Window::get_width() - mouseWindowPanBufferDistance)){
		god_view.move_left_xy(((Window::get_width() - mouseWindowPanBufferDistance)- mousePos.x) * time_step);
	}
	else if(movement_controls.right){
		god_view.move_left_xy(-distance);
	}

	if(movement_controls.rotateLeft || movement_controls.rotateRight){
		Vector3f d = (god_view.position.z / god_view.get_forward().z) * god_view.get_forward();
		float r = hypot(d.x, d.y);
		Point3f o(god_view.position.x - d.x, god_view.position.y - d.y, 0);
		float a = atan2(-god_view.get_forward().y, -god_view.get_forward().x) + 
					angularSpeed * (movement_controls.rotateRight - movement_controls.rotateLeft);
		god_view.position = Point3f(o.x + r*cos(a), o.y + r*sin(a), god_view.position.z);
		god_view.look_at(o);
	}
}

void Play_State::render() {
	Zeni::Video &vr = Zeni::get_Video();
	vr.set_lighting(true);
	Color UILight = vr.get_ambient_lighting();
	vr.set_ambient_lighting(Color(1.f,0.f,0.f,0.f));

	//set up camera
	if(god_view_on)
		vr.set_3d(god_view);

  //render call for level
	Game_Level::getCurrentLevel()->render();

	vr.set_lighting(false);
	vr.set_ambient_lighting(UILight);
    
	vr.set_2d();
	vr.clear_depth_buffer();

	gui.render();

	m_widgets.render();
}

void Play_State::on_mouse_button( const SDL_MouseButtonEvent &event )
{
	Widget_Gamestate::on_mouse_button(event);
	gui.on_mouse_button(event);
}
