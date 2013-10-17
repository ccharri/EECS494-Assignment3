#ifndef __game__Player_h__
#define __game__Player_h__

#include "Game_Object.h"

#include <vector>
#include <zenilib.h>

class Player : public Game_Object
{
public:
	Player(Zeni::Point3f location_);

	~Player() = 0;

	void on_logic(float time_step);

private:
	Zeni::Collision::Capsule collision_capsule;

	float speed;
	bool moving;
};

#endif