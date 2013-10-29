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

	Zeni::Vector3f getVel() const;
	float getHeight() {return height;}
	void setHeight(float f){height = f;}
	
	float getSpeed() const {return speed;}
	bool isMoving() const {return moving;};

	float getMaxHealth() const {return health_max;};
	float getCurrentHealth() const {return health_current;};
	
	int leakAmount() const override {return lifeCost;}
	void setLeakAmount(int i){lifeCost = i;}
	int getBounty() {return bounty;}
	void setBounty(int i) {bounty = i;}

	bool isAlive() const {return alive;};

	bool collide(const Zeni::Collision::Capsule& collider_) const override;
	bool collide(const Zeni::Collision::Infinite_Cylinder& collider_) const override;
	bool collide(const Zeni::Collision::Line& collider_) const override;
	bool collide(const Zeni::Collision::Line_Segment& collider_) const override;
	bool collide(const Zeni::Collision::Parallelepiped& collider_) const override;
	bool collide(const Zeni::Collision::Plane& collider_) const override;
	bool collide(const Zeni::Collision::Ray& collider_) const override;
	bool collide(const Zeni::Collision::Sphere& collider_) const override;

	const Zeni::Collision::Capsule& getCollider() const {return collision_capsule;};

	virtual float getPrimaryAttributeMax() const {return health_max;};
	virtual float getPrimaryAttributeCurrent() const {return health_current;};
	virtual Zeni::Color getPrimaryColor() const {return Zeni::Color(1.0, (1.0 -(health_current / health_max)), health_current / health_max, 0.f);};

	virtual void onDamage(float damage) override;

	virtual bool isTargetable() const override {return isAlive();};
	virtual bool isAttackable() const {return isAlive();};

private:
	Zeni::Collision::Capsule collision_capsule;

protected:
	float speed;
	float height;
	bool moving;
private:
	float health_max;
	float health_current;
	bool alive;
	int bounty;
	int lifeCost;
protected:
	int pathIndex;
	std::vector<Zeni::Point3f>* path;
private:
	void updateCollider() override;
	void doMovement(float time_step);
	void stopMoving();
};

#endif