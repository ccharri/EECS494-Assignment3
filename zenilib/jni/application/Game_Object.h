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
	Zeni::Vector3f getSize() const {return size;};
	Zeni::Quaternion getFacing() const {return facing;};

	void setPosition(Zeni::Point3f position_) {position = position_;};
	void setSize(Zeni::Vector3f size_) {size = size_;};
	void setFacing(Zeni::Quaternion facing_) {facing = facing_;};

	virtual Zeni::Model* getModel() = 0;

	float getKeyframe() const {return keyframe;};
	void setKeyframe(float keyframe_) {keyframe = keyframe_;};
	
	virtual bool isTargetable() const {return false;};

private:
	Zeni::Point3f position;
	Zeni::Vector3f size;
	Zeni::Quaternion facing;

	float keyframe;
};

#endif