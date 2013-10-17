#include "Enemy.h"

using namespace Zeni;
using namespace std;

Enemy::Enemy(Zeni::Point3f location_, Zeni::Vector3f size_, Zeni::Quaternion facing, float speed_, float health_max_) : Game_Object(location_), speed(speed_), health_max(health_max_), health_current(health_max), moving(true), alive(true)
{

}

bool Enemy::collide(const Collision::Capsule* collider_) const
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Infinite_Cylinder* collider_) const
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Line* collider_) const
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Line_Segment* collider_) const
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Parallelepiped* collider_) const
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Plane* collider_) const
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Ray* collider_) const
{
	return collider_->intersects(collision_capsule);
}

bool Enemy::collide(const Collision::Sphere* collider_) const
{
	return collider_->intersects(collision_capsule);
}

void Enemy::on_logic(float time_step) 
{
	doMovement();
}

void Enemy::doMovement() {
	if(!moving) return;
	if(!alive) return;

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

void Enemy::onDamage(float damage)
{
	if((health_current -= damage) <= 0)
	{
		alive = false;
	}
}