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

	void setPath(std::vector<Zeni::Point3f>* path_) {path = path_;};

	float getSpeed() const {return speed;};
	bool isMoving() const {return moving;};

	float getMaxHealth() const {return health_max;};
	float getCurrentHealth() const {return health_current;};

	bool isAlive() const {return alive;};

	bool collide(const Zeni::Collision::Capsule* collider_) const;
	bool collide(const Zeni::Collision::Infinite_Cylinder* collider_) const;
	bool collide(const Zeni::Collision::Line* collider_) const;
	bool collide(const Zeni::Collision::Line_Segment* collider_) const;
	bool collide(const Zeni::Collision::Parallelepiped* collider_) const;
	bool collide(const Zeni::Collision::Plane* collider_) const;
	bool collide(const Zeni::Collision::Ray* collider_) const;
	bool collide(const Zeni::Collision::Sphere* collider_) const;

	const Zeni::Collision::Capsule& getCollider() const {return collision_capsule;};

	virtual void onDamage(float damage);

	bool isTargetable() const override {return isAlive();};

private:
	Zeni::Collision::Capsule collision_capsule;

	float speed;
	bool moving;

	float health_max;
	float health_current;
	bool alive;

	int pathIndex;
	std::vector<Zeni::Point3f>* path;

	void doMovement(float time_step);
	void stopMoving();
};

#endif