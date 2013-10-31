#ifndef __game__Beam_h__
#define __game__Beam_h__

#include <zenilib.h>

#include "Game_Object.h"
#include "Model_Wrapper.h"

class Tower_Weapon;

class Beam : public Game_Object
{
public:
	Beam(std::weak_ptr<Tower_Weapon> owner_, std::weak_ptr<Game_Object> target_, float damage_, float range_);

	~Beam();

	void on_logic(float time_step) override;

	std::shared_ptr<Zeni::Model> getModel() const override {return model.getModel();};

private:
	static Model_Wrapper model;

	float range;

	float damage;
	float damageCap;
	float stacks;
	float stacksCap;

	std::weak_ptr<Tower_Weapon> owner;
	std::weak_ptr<Game_Object> target;

	Zeni::Point3f targetPos;

	void pointToTarget();

	Zeni::Sound_Source beamSoundSource;
};

#endif