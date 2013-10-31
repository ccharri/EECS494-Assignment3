#ifndef __game__Game_Object_h__
#define __game__Game_Object_h__

#include <zenilib.h>
#include <memory>

class ZTDGUI;

class Game_Object : public std::enable_shared_from_this<Game_Object>
{
public:
	Game_Object(Zeni::Point3f position_ = Zeni::Point3f(), Zeni::Vector3f size_ = Zeni::Vector3f(), Zeni::Quaternion facing_ = Zeni::Quaternion(),
							Zeni::Vector3f scale_ = Zeni::Vector3f(1,1,1));

	virtual ~Game_Object() = 0;

	virtual void render();

	virtual void on_logic(float time_step);

	virtual bool collide(const Zeni::Collision::Capsule& collider_) const {return false;};
	virtual bool collide(const Zeni::Collision::Infinite_Cylinder& collider_) const {return false;};
	virtual bool collide(const Zeni::Collision::Line& collider_) const {return false;};
	virtual bool collide(const Zeni::Collision::Line_Segment& collider_) const {return false;};
	virtual bool collide(const Zeni::Collision::Parallelepiped& collider_) const {return false;};
	virtual bool collide(const Zeni::Collision::Plane& collider_) const {return false;};
	virtual bool collide(const Zeni::Collision::Ray& collider_) const {return false;};
	virtual bool collide(const Zeni::Collision::Sphere& collider_) const {return false;};

	Zeni::String getName() const {return name;};
	void setName(const Zeni::String& name_) {name = name_;};

	Zeni::Point3f getPosition() const {return position;};
	Zeni::Vector3f getSize() const {return size;};
	Zeni::Quaternion getFacing() const {return facing;};
	Zeni::Vector3f getScale() const {return scale;};

	virtual void setPosition(Zeni::Point3f position_) {position = position_; updateCollider();};
	virtual void setSize(Zeni::Vector3f size_) {size = size_;};
	virtual void setFacing(Zeni::Quaternion facing_) {facing = facing_;};
	virtual void setScale(Zeni::Vector3f scale_) {scale = scale_;};
	virtual void lookAt(Zeni::Point3f pos_);

	virtual void onSelection(ZTDGUI* gui_) {};
	virtual void onDeselection(ZTDGUI* gui_) {};

	virtual float getPrimaryAttributeMax() const {return 0;};
	virtual float getPrimaryAttributeCurrent() const {return 0;};
	virtual Zeni::Color getPrimaryColor() const {return Zeni::Color(0.f, 0.f, 0.f, 0.f);};

	virtual Zeni::Vector3f getVel() const {return Zeni::Vector3f(0,0,0);};
	float getSpeed() const {return getVel().magnitude();}

	//Quality of Life function for setting position AND facing BEFORE updating collider (for those objects with a collider based on rotation)
	virtual void setPositionAndLookAt(Zeni::Point3f position_, Zeni::Point3f lookPos_) {position = position_; lookAt(lookPos_);};

	virtual std::shared_ptr<Zeni::Model> getModel() const = 0;

	float getKeyframe() const {return keyframe;};
	void setKeyframe(float keyframe_) {keyframe = keyframe_;};
	
	virtual bool isTargetable() const {return false;};
	virtual bool isAttackable() const {return false;};

	virtual void onDamage(float damage) {};

	virtual int leakAmount() const {return 0;};

protected:
	virtual void updateCollider() {} ;
private:
	Zeni::Point3f position;
	Zeni::Vector3f size;
	Zeni::Quaternion facing;
	Zeni::Vector3f scale;

	Zeni::String name;

	float keyframe;
};

#endif