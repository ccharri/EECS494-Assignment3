#include "Play_State.h"

#include <memory>

#include "Player.h"
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

Play_State::Play_State() /*: player(Player(Point3f(), Vector3f(), Quaternion()))*/ 
{
	god_view_on = true;
	god_view = Camera(Point3f(-60, 0, 40), Quaternion(0, (Global::pi_over_two/2.), 0), 1.0f, 1000.0f, Global::pi_over_two, 1.25f);

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

	Game_Level::setCurrentLevel(new Level_One());

	Game_Level::getCurrentLevel()->getEnemies().push_back(shared_ptr<Game_Object>(new Enemy_Box(Point3f(-50, -50, 0), 10., 100.)));

	XML_Level fredrick(Zeni::String("levels/level1.xml"));

	shared_ptr<Tower_Base> centerBase = shared_ptr<Tower_Base>(new Tower_Base(Point3f(0,0,0)));
	shared_ptr<Tower_Section> newSection = shared_ptr<Tower_Section>(new Tower_Section(Point3f(), Vector3f()));
	shared_ptr<Tower_Weapon> dropper = shared_ptr<Tower_Weapon>(new Rock_Dropper(newSection, 2.));
	newSection->setWeapon(dropper);
	centerBase->pushSection(newSection);

	shared_ptr<Tower_Section> rocketSection = shared_ptr<Tower_Section>(new Tower_Section(Point3f(), Vector3f()));
	shared_ptr<Tower_Weapon> rocketLauncher = shared_ptr<Tower_Weapon>(new Rocket_Launcher(rocketSection, 2.5));
	rocketSection->setWeapon(rocketLauncher);
	centerBase->pushSection(rocketSection);

	Game_Level::getCurrentLevel()->getBases().push_back(centerBase);

	testNear = shared_ptr<Game_Object>(new Rock(Point3f(), Vector3f()));
	testFar = shared_ptr<Game_Object>(new Rocket(shared_ptr<Tower_Weapon>(nullptr), shared_ptr<Game_Object>(nullptr),0,0,Point3f()));
}

void Play_State::on_push() {
    //Zeni::get_Window().set_mouse_state(Zeni::Window::MOUSE_RELATIVE);
	Zeni::get_Window().set_mouse_state(Zeni::Window::MOUSE_GRABBED);
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

void Play_State::on_mouse_wheel(const SDL_MouseWheelEvent &event) {
	god_view.position += god_view.get_forward().normalized() * event.y;
}

void Play_State::on_mouse_motion(const SDL_MouseMotionEvent &event) {
	mousePos = Point2f(event.x, event.y);
	Gamestate_Base::on_mouse_motion(event);
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

	proj = Projector3D(god_view); 

	Point3f closeMouseScreenPos = proj.unproject(Point3f(mousePos.x, mousePos.y, .01));
	Point3f farMouseScreenPos = proj.unproject(Point3f(mousePos.x, mousePos.y, .02));

	//Vector3f rayDir = rayDirection(closeMouseScreenPos, farMouseScreenPos);
	
	Vector3f rayDir = Vector3f(farMouseScreenPos - closeMouseScreenPos).normalized();

	testNear->setPosition(closeMouseScreenPos);
	testFar->setPosition(farMouseScreenPos);
	testNear->setFacing(Quaternion::Forward_Up(rayDir, Vector3f(0,0,1)));
	testFar->setFacing(Quaternion::Forward_Up(rayDir, Vector3f(0,0,1)));

	Collision::Infinite_Cylinder mouseRay(closeMouseScreenPos, rayDir, 1. );
	auto collidingObjects = findCollidingObjects(mouseRay, Game_Level::getCurrentLevel()->getEnemies());
	mouseoverObj = closestObject(closeMouseScreenPos, collidingObjects);
	if(time_since_last_spawn > 4.)
	{
		Game_Level::getCurrentLevel()->getEnemies().push_back(shared_ptr<Game_Object>(new Enemy_Box(Point3f(-50, -50, 0), 10., 100.)));
		time_since_last_spawn -= 4.f;
	}

	Game_Level::getCurrentLevel()->on_logic(time_step);
  }
}

void Play_State::performMovement(float time_step)
{
	float speed = 20.f;
	float distance = speed * time_step;

	float mouseWindowPanBufferDistance = 40.f;

	if(mousePos.y <= mouseWindowPanBufferDistance)
	{
		god_view.move_forward_xy((mouseWindowPanBufferDistance - mousePos.y) * time_step);
	}
	else if(movement_controls.forward) {
		god_view.move_forward_xy(distance);
	}

	if(mousePos.y >= (Window::get_height() - mouseWindowPanBufferDistance))
	{
		god_view.move_forward_xy(((Window::get_height() - mouseWindowPanBufferDistance) - mousePos.y) * time_step);
	}
	else if(movement_controls.back) {
		god_view.move_forward_xy(-distance);
	}

	if(mousePos.x <= mouseWindowPanBufferDistance)
	{
		god_view.move_left_xy((mouseWindowPanBufferDistance - mousePos.x) * time_step);
	}
	else if(movement_controls.left)
	{
		god_view.move_left_xy(distance);
	}

	if(mousePos.x >= (Window::get_width() - mouseWindowPanBufferDistance))
	{
		god_view.move_left_xy(((Window::get_width() - mouseWindowPanBufferDistance)- mousePos.x) * time_step);
	}
	else if(movement_controls.right)
	{
		god_view.move_left_xy(-distance);
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

	//else
	//	vr.set_3d(player.get_camera());

  //render call for level
	Game_Level::getCurrentLevel()->render();

	vr.set_lighting(false);
	vr.set_ambient_lighting(UILight);

	testNear->render();
	testFar->render();

	vr.set_2d();

	shared_ptr<Game_Object> targetedObj = mouseoverObj.lock();

	if(targetedObj)
	{
		Zeni::Font &fr = get_Fonts()["title"];

		fr.render_text(
			targetedObj->getName(),
			Point2f(Window::get_width()/2., 0),
			get_Colors()["title_text"],
			ZENI_CENTER);
	}
}

void Play_State::on_mouse_button( const SDL_MouseButtonEvent &event )
{
	Gamestate_Base::on_mouse_button(event);
}

Zeni::Vector3f Play_State::rayDirection( Zeni::Point3f& nearClipP, Zeni::Point3f& farClipP ) const
{
	float dx, dy;
	auto viewMatrix = god_view.get_view_matrix();
	auto invViewMatrix = viewMatrix.inverted();
	float aspect = (float)Window::get_width() / (float)Window::get_height();

	dx = tanf(god_view.get_tunneled_fov_rad())*(mousePos.x/Window::get_width()/2. - 1.f)/aspect;
	dy = tanf(god_view.get_tunneled_fov_rad())*(1-0 - mousePos.y/Window::get_height()/2.);
	nearClipP = Vector3f(dx*god_view.get_tunneled_near_clip(), dy * god_view.get_tunneled_near_clip(), god_view.get_tunneled_near_clip());
	farClipP = Vector3f(dx*god_view.get_tunneled_far_clip(), dy*god_view.get_tunneled_far_clip(), god_view.get_tunneled_far_clip());
	nearClipP = invViewMatrix * nearClipP;
	farClipP = invViewMatrix * farClipP;

	return Vector3f(farClipP - nearClipP).normalized();
}
