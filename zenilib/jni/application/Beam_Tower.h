#ifndef __game__Beam_Tower_h__
#define __game__Beam_Tower_h__

#include <zenilib.h>
#include <memory>

#include "Tower_Weapon.h"

class Beam_Tower : public Tower_Weapon
{
public:
	Beam_Tower(std::weak_ptr<Tower_Section> owner_);

	~Beam_Tower();

	void on_logic(float time_step) override;

	bool canFire(std::shared_ptr<Game_Object> object) override;

	void fire() override;

	static int getCost() {return 125;};

private:

};

#endif