#ifndef __game__Buzzsaw_Tower_h__
#define __game__Buzzsaw_Tower_h__

#include <zenilib.h>
#include <memory>

#include "Tower_Weapon.h"

class Buzzsaw_Tower : public Tower_Weapon{
public:
	Buzzsaw_Tower(std::weak_ptr<Tower_Section> owner_, float cooldown_ = 4.f);

	~Buzzsaw_Tower();

	float DAMAGE_PER_Z_VEL;
	float LAUNCH_VEL;
	float GRAVITY;

	bool canFire(std::shared_ptr<Game_Object> object) override;
	void fire() override;
	void on_logic(float time_step) override;
    
    static int getCost() {return 50;};

private:
	float RANGE;
	float DAMAGE;

	float timeSpinning;
	float timeCooling;
	bool spinning;
};

#endif