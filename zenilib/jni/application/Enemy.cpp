#include "Enemy.h"

using namespace Zeni;
using namespace std;

bool Enemy::collide(const Collision::Capsule* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Infinite_Cylinder* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Line* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Line_Segment* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Parallelepiped* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Plane* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Ray* collider_)
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Sphere* collider_)
{
	return collider_->intersects(collision_capsule);
}

void Enemy::on_logic(float time_step) 
{
	doMovement();
}

void Enemy::doMovement() {
	if(!moving) return;

	if(Vector3f((*destination) - getPosition()).magnitude() <= getSpeed()) {
		setPosition(*destination);
		if(++destination == end) stopMoving();
	}
	else {
		setPosition(Vector3f((*destination) - getPosition()).normalized() * getSpeed());
	}
}

void Enemy::stopMoving() 
{
	moving = false;
}