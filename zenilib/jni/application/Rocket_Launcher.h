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
    
    
    static int getCost() {return 100;};

private:

};

#endif