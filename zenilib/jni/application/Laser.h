#ifndef __game__Laser_h__
#define __game__Laser_h__

#include <zenilib.h>

#include "Model_Wrapper.h"
#include "Game_Object.h"

class Tower_Weapon;

class Laser : public Game_Object
{
public:
	Laser(std::weak_ptr<Tower_Weapon> owner_, std::weak_ptr<Game_Object> target_, float damage_, float duration_);

	std::shared_ptr<Zeni::Model> getModel() const override {return model.getModel();};

	void on_logic(float time_step) override;

private:
	static Model_Wrapper model;

	float timePassed;
	float duration;

	std::weak_ptr<Tower_Weapon> owner;
	std::weak_ptr<Game_Object> target;

	Zeni::Point3f targetPos;

	void pointToTarget();
};

#endif