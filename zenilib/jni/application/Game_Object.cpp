#include "Game_Object.h"

using namespace Zeni;
using namespace std;

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

void Game_Object::onDamage(float damage)
{
	if(!is_alive) return;

	health_current -= damage;

	if(health_current <= 0)
	{
		health_current = 0;
		is_alive = false;
	}
}

bool Game_Object::collide(const Collision::Capsule* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Game_Object::collide(const Collision::Infinite_Cylinder* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Game_Object::collide(const Collision::Line* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Game_Object::collide(const Collision::Line_Segment* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Game_Object::collide(const Collision::Parallelepiped* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Game_Object::collide(const Collision::Plane* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Game_Object::collide(const Collision::Ray* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Game_Object::collide(const Collision::Sphere* collider_)
{
	return collider_->intersects(collision_capsule);
}