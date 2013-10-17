#ifndef __game__Game_Object_h__
#define __game__Game_Object_h__

#include <zenilib.h>

class Game_Object {
public:
	Game_Object(Zeni::Point3f position_ = Zeni::Point3f(), Zeni::Vector3f size_ = Zeni::Vector3f(), Zeni::Quaternion facing_ = Zeni::Quaternion());

	virtual ~Game_Object() = 0;

	virtual void render();

	virtual void on_logic(float time_step);

	virtual bool collide(const Zeni::Collision::Capsule* collider_) {return false;};
	virtual bool collide(const Zeni::Collision::Infinite_Cylinder* collider_) {return false;};
	virtual bool collide(const Zeni::Collision::Line* collider_) {return false;};
	virtual bool collide(const Zeni::Collision::Line_Segment* collider_) {return false;};
	virtual bool collide(const Zeni::Collision::Parallelepiped* collider_) {return false;};
	virtual bool collide(const Zeni::Collision::Plane* collider_) {return false;};
	virtual bool collide(const Zeni::Collision::Ray* collider_) {return false;};
	virtual bool collide(const Zeni::Collision::Sphere* collider_) {return false;};

	Zeni::Point3f getPosition() const {return position;};

	//float getSpeed() const {return speed;};

	//float getMaxHealth() const {return health_max;};
	//float getCurrentHealth() const {return health_current;};

	//bool isAlive() const {return is_alive;};

	virtual Zeni::Model* getModel() = 0;
	//const Zeni::Collision::Capsule& getCollider() const {return collision_capsule;};

	float getKeyframe() const {return keyframe;};
	void setKeyframe(float keyframe_) {keyframe = keyframe_;};

	//virtual void onDamage(float damage);

private:
	Zeni::Point3f position;
	Zeni::Vector3f size;
	Zeni::Quaternion facing;

	//Zeni::Collision::Capsule collision_capsule;

	float keyframe;

	//float speed;

	//float health_max;
	//float health_current;
	//bool is_alive;

	//Zeni::Point3f destination;

	//void stop_Moving();
};

#endif