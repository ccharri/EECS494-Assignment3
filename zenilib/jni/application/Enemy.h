#ifndef __game__Enemy_h__
#define __game__Enemy_h__

#include "Game_Object.h"

#include <vector>
#include <zenilib.h>

class Enemy : public Game_Object
{
public:
	Enemy(Zeni::Point3f location_, Zeni::Vector3f size_, Zeni::Quaternion facing_, float speed_, float health_max_);

	~Enemy() = 0;

	virtual void on_logic(float time_step) override;

	void setDestination(std::vector<Zeni::Point3f>::const_iterator destination_) {destination = destination_;};
	void setEnd(std::vector<Zeni::Point3f>::const_iterator end_) {end = end_;};

	float getSpeed() const {return speed;};
	bool isMoving() const {return moving;};

	float getMaxHealth() const {return health_max;};
	float getCurrentHealth() const {return health_current;};

	bool isAlive() const {return alive;};

	bool collide(const Collision::Capsule* collider_);
	bool collide(const Collision::Infinite_Cylinder* collider_);
	bool collide(const Collision::Line* collider_);
	bool collide(const Collision::Line_Segment* collider_);
	bool collide(const Collision::Parallelepiped* collider_);
	bool collide(const Collision::Plane* collider_);
	bool collide(const Collision::Ray* collider_);
	bool collide(const Collision::Sphere* collider_);

	const Zeni::Collision::Capsule& getCollider() const {return collision_capsule;};

	virtual void onDamage(float damage);

	bool isTargetable() const override {return true;};

private:
	Zeni::Collision::Capsule collision_capsule;

	float speed;
	bool moving;

	float health_max;
	float health_current;
	bool alive;

	std::vector<Zeni::Point3f>::const_iterator destination;
	std::vector<Zeni::Point3f>::const_iterator end;

	void doMovement();
	void stopMoving();
};

#endif