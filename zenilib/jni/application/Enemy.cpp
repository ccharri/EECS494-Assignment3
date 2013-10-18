#include "Enemy.h"

#include "Game_Level.h"
#include "Utility.h"
#include <math.h>

using namespace Zeni;
using namespace std;

Quaternion createQuaternionBetweenTwoPoints(const Point3f& destination_, const Point3f& origin_)
{
	double dx, dy, dz;
	dx = destination_.x - origin_.x;
	dy = destination_.y - origin_.y;
	dz = destination_.z - origin_.z;

	double yaw, pitch, roll;
	yaw = atan2(dz, dx);
	pitch = atan2(sqrt(dz*dz + dx*dx), dy) + Global::pi;
	roll = 0;

	return Quaternion(yaw, pitch, roll);
}

Enemy::Enemy(Zeni::Point3f location_, Zeni::Vector3f size_, Zeni::Quaternion facing, float speed_, float health_max_) : Game_Object(location_), speed(speed_), health_max(health_max_), health_current(health_max), moving(true), alive(true), pathIndex(0), path(nullptr)
{
	path = &Game_Level::getCurrentLevel()->getPath();
}

Enemy::~Enemy() {};

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
	doMovement(time_step);
}

void Enemy::doMovement(float time_step) {
	if(!moving) return;
	if(!alive) return;

	if(pathIndex == path->size()) return;

	if(Vector3f((*path)[pathIndex] - getPosition()).magnitude() <= (getSpeed() * time_step)) {
		setPosition((*path)[pathIndex]);
		if(++pathIndex >= path->size()) stopMoving();
	}
	else {
		//It's either this
		//setFacing(Quaternion::Vector3f_to_Vector3f((*path)[pathIndex], getPosition()));
		//Or this
		//setFacing(Quaternion::Vector3f_to_Vector3f(Vector3f((*destination) - getPosition()), Quaternion);
		setFacing(createQuaternionBetweenTwoPoints((*path)[pathIndex], getPosition()));
		setPosition(getPosition() + Vector3f((*path)[pathIndex] - getPosition()).normalized() * (getSpeed() * time_step));
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