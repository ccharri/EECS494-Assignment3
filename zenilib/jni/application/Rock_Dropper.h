#ifndef __game__Rock_Dropper_h__
#define __game__Rock_Dropper_h__

#include "zenilib.h"
#include "Tower_Weapon.h"

class Rock_Dropper : public Tower_Weapon{
public:
	Rock_Dropper(Tower_Section* owner_, float cooldown_);

	~Rock_Dropper();

	float DAMAGE_PER_Z_VEL;
	float LAUNCH_VEL;

	bool canFire(Game_Object* object) override;
	void fire() override;
	void on_logic(float time_step) override;

private:
	
};

#endif