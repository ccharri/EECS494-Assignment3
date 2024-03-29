#ifndef __game__Rock_Dropper_h__
#define __game__Rock_Dropper_h__

#include <zenilib.h>
#include <memory>

#include "Tower_Weapon.h"

class Rock_Dropper : public Tower_Weapon{
public:
	Rock_Dropper(std::weak_ptr<Tower_Section> owner_, float cooldown_ = 2.f);

	~Rock_Dropper();

	float DAMAGE_PER_Z_VEL;
	float LAUNCH_VEL;
	float GRAVITY;

	bool canFire(std::shared_ptr<Game_Object> object) override;
	void fire() override;
	void on_logic(float time_step) override;
    
    Zeni::String getDescription() const override {return description;};
    static Zeni::String getGenericDescription() {return description;};
    
    static int getCost() {return 75;};

private:
	static Zeni::String description;
};

#endif