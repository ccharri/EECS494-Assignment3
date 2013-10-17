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

//void Game_Object::onDamage(float damage)
//{
//	if(!is_alive) return;
//
//	health_current -= damage;
//
//	if(health_current <= 0)
//	{
//		health_current = 0;
//		is_alive = false;
//	}
//}

