#ifndef __game__Buzzsaw_h__
#define __game__Buzzsaw_h__

#include <zenilib.h>

#include "Game_Object.h"
#include "Model_Wrapper.h"

class Tower_Weapon;

class Buzzsaw : public Game_Object
{
public:
	Buzzsaw(std::weak_ptr<Tower_Weapon> owner_, std::weak_ptr<Game_Object> target_, float radius, float duration_, float radPerUpdate_ = Zeni::Global::pi_over_two/3.);

	void on_logic(float time_step) override;

	std::shared_ptr<Zeni::Model> getModel() const override {return model.getModel();};

private:
	static Model_Wrapper model;

	std::weak_ptr<Tower_Weapon> owner;

	float spinTimer;
	float duration;
	
	float angle;
	float radPerUpdate;
};

#endif