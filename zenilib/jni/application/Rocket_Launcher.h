#ifndef __game__Rocket_Launcher_h__
#define __game__Rocket_Launcher_h__

#include <zenilib.h>
#include <memory>

#include "Tower_Weapon.h"

class Tower_Section;

class Rocket_Launcher : public Tower_Weapon
{
public:
	Rocket_Launcher(std::weak_ptr<Tower_Section> owner_, float cooldown_ = 2.5f);

	virtual void on_logic( float time_step );

	virtual void fire();
    
	virtual bool canFire(std::shared_ptr<Game_Object> object) override;
    
    Zeni::String getDescription() const override {return description;};
    static Zeni::String getGenericDescription() {return description;};
    
    static int getCost() {return 100;};

private:
    static Zeni::String description;
};

#endif