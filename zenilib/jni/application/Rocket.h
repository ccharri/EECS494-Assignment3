#ifndef __game__Rocket_h__
#define __game__Rocket_h__

#include <zenilib.h>

#include <memory>

#include "Game_Object.h"
#include "Model_Wrapper.h"

class Tower_Weapon;

class Rocket : public Game_Object {
public:
	Rocket::Rocket( std::weak_ptr<Tower_Weapon> owner_, std::weak_ptr<Game_Object> target_, float damage_, float speed_, Zeni::Point3f position_, Zeni::Vector3f size_ = Zeni::Vector3f(10,2,2), Zeni::Quaternion facing_ = Zeni::Quaternion(), Zeni::Vector3f scale_ = Zeni::Vector3f(1,1,1));

	virtual void on_logic( float time_step );

	virtual Zeni::Model* getModel() {return model.getModel();};

private:
	static Model_Wrapper model;

	Zeni::Collision::Capsule collider;

	std::weak_ptr<Tower_Weapon> owner;

	float damage;
	float speed;
	std::weak_ptr<Game_Object> target;

	void updateCollider();
	void explode();
};

#endif