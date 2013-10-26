#include "Game_Object.h"

#include "Utility.h"
#include "Game_Level.h"

using namespace Zeni;
using namespace std;

Game_Object::Game_Object(Zeni::Point3f position_ /* = Zeni::Point3f() */, Zeni::Vector3f size_ /* = Zeni::Vector3f() */, Zeni::Quaternion facing_ /* = Zeni::Quaternion() */, Zeni::Vector3f scale_)  : name("Uninitialized"), position(position_), size(size_), facing(facing_), scale(scale_)
{
	updateCollider();
}

Game_Object::~Game_Object()
{
}

void Game_Object::render()
{
	shared_ptr<Model> model = getModel();

	model->set_keyframe(keyframe);
	model->set_rotate(facing);
	model->set_translate(position);
	model->set_scale(scale);
	model->render();
}

void Game_Object::on_logic(float time_step)
{
}

void Game_Object::lookAt(Zeni::Point3f pos_)
{
	setFacing(Quaternion::Forward_Up(Vector3f(pos_-getPosition()).normalized(), Vector3f(0,0,1)));
	updateCollider();
}