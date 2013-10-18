#ifndef __game__Utility_h__
#define __game__Utility_h__

#include <functional>
#include <vector>
#include <zenilib.h>
#include "Game_Object.h"

//Zeni::Quaternion createQuaternionBetweenTwoPoints(const Zeni::Point3f& destination_, const Zeni::Point3f& origin_);

float parabolicFallTime(float target_z_initial, float target_z_vel, float launch_z);
//NOTE: Returns a negative number if the fall is invalid

Game_Object* closestObject(const Zeni::Point3f& pos_, const std::vector<Game_Object*>& objects_);

//This has to be here cause of reasons
template <typename Func>
Game_Object* closestObjectMatching(const Zeni::Point3f& pos_, const std::vector<Game_Object*>& objects_, Func matchfunc)
{
	Game_Object* contender = nullptr;
	float lowestDistance = FLT_MAX;

	for_each(objects_.begin(), objects_.end(), [&](Game_Object* object) {
		float distance;

		if(matchfunc(object) && ((distance = Zeni::Vector3f(object->getPosition() - pos_).magnitude()) < lowestDistance))
		{
			contender = object;
			lowestDistance = distance;
		}
	});

	return contender;
}


#endif