#ifndef __game__Laser_Turret_h__
#define __game__Laser_Turret_h__

#include <zenilib.h>
#include <memory>

#include "Tower_Weapon.h"

class Laser_Turret : public Tower_Weapon
{
public:
	Laser_Turret(std::weak_ptr<Tower_Section> owner_, float cooldown_ = 1.25f, float damage_ = 12.f, float range_ = 30.f);

	~Laser_Turret();

	void on_logic(float time_step) override;

	void fire() override;

	bool canFire(std::shared_ptr<Game_Object> object) override;

	static int getCost() {return 25;};

private:
	float damage;
	float range;
};

#endif