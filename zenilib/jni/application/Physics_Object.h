#ifndef __game__Projectile_h__
#define __game__Projectile_h__

#include "Game_Object.h"
#include <zenilib.h>

class Physics_Object : public Game_Object
{
public:
	Physics_Object(const Zeni::Point3f& position_, const Zeni::Vector3f& size_, const Zeni::Quaternion& facing_ = Zeni::Quaternion());

	void setVelocity(Zeni::Vector3f vel_) {vel = vel_;}
	void setAcceleration(Zeni::Vector3f acc_) {acc = acc_;}
	void setRotation(Zeni::Quaternion rotation_) {rotation = rotation_;};
	Zeni::Vector3f getVelocity() {return vel;}
	Zeni::Vector3f getAcceleration() {return acc;}
	Zeni::Quaternion getRotation() {return rotation;};

	virtual void on_logic(float time_step) override;

private:
	Zeni::Vector3f vel;
	Zeni::Vector3f acc;
	Zeni::Quaternion rotation;
};

#endif