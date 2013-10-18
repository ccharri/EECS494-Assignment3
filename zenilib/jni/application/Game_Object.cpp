#include "Game_Object.h"

using namespace Zeni;
using namespace std;

Game_Object::Game_Object(Zeni::Point3f position_ /* = Zeni::Point3f() */, Zeni::Vector3f size_ /* = Zeni::Vector3f() */, Zeni::Quaternion facing_ /* = Zeni::Quaternion() */)  : position(position_), size(size_), facing(facing_)
{

}

Game_Object::~Game_Object()
{
}

void Game_Object::render()
{
	Model* model = getModel();

	model->set_keyframe(keyframe);
	model->set_rotate(facing);
	model->set_translate(position);
	model->render();
}
