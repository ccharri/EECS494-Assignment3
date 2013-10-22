#include "Enemy.h"

#include "Game_Level.h"
#include "Utility.h"
#include <math.h>

using namespace Zeni;
using namespace std;

Enemy::Enemy(Zeni::Point3f location_, Zeni::Vector3f size_, Zeni::Quaternion facing, float speed_, float health_max_) : Game_Object(location_), speed(speed_), health_max(health_max_), health_current(health_max), moving(true), alive(true), pathIndex(0), path(nullptr)
{
	path = &Game_Level::getCurrentLevel()->getPath();
	updateCollider();
}

Enemy::~Enemy() {};

bool Enemy::collide(const Collision::Capsule& collider_) const
{
	return collision_capsule.intersects(collider_);
}

bool Enemy::collide(const Collision::Infinite_Cylinder& collider_) const
{
	return collision_capsule.intersects(collider_);
}

bool Enemy::collide(const Collision::Line& collider_) const
{
	return collision_capsule.intersects(collider_);
}

bool Enemy::collide(const Collision::Line_Segment& collider_) const
{
	return collision_capsule.intersects(collider_);
}

bool Enemy::collide(const Collision::Parallelepiped& collider_) const
{
	return collision_capsule.intersects(collider_);
}

bool Enemy::collide(const Collision::Plane& collider_) const
{
	return collision_capsule.intersects(collider_);
}

bool Enemy::collide(const Collision::Ray& collider_) const
{
	return collision_capsule.intersects(collider_);
}

bool Enemy::collide(const Collision::Sphere& collider_) const
{
	return collision_capsule.intersects(collider_);
}

void Enemy::on_logic(float time_step) 
{
	doMovement(time_step);
}

void Enemy::doMovement(float time_step) {
	if(!moving) return;
	if(!alive) return;

	if(pathIndex == path->size()) return;

	Point3f next = (*path)[pathIndex];

	if(Vector3f(next - getPosition()).magnitude() <= (getSpeed() * time_step)) {
		setPosition(next);
		if(++pathIndex >= path->size()) stopMoving();
		lookAt((*path)[pathIndex]);
		Game_Level::getCurrentLevel()->enemyLeaked(shared_from_this());
	}
	else {
		//It's either this
		//setFacing(Quaternion::Vector3f_to_Vector3f((*path)[pathIndex], getPosition()));
		//Or this
		//setFacing(Quaternion::Vector3f_to_Vector3f(Vector3f((*destination) - getPosition()), Quaternion);
		setPosition(getPosition() + Vector3f(next - getPosition()).normalized() * (getSpeed() * time_step));
		lookAt(next);
	}
}

void Enemy::stopMoving() 
{
	moving = false;
}

void Enemy::updateCollider() 
{
	Point3f location = getPosition();
	Vector3f size = getSize();
	collision_capsule = Collision::Capsule(location, location + Vector3f(0,0, size.z), (size.x + size.y)/2. /2.);
}

void Enemy::onDamage(float damage)
{
	if((health_current -= damage) <= 0)
	{
		alive = false;
		Game_Level::getCurrentLevel()->removeEnemy(shared_from_this());
	}
}