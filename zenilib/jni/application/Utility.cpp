#include "Utility.h"

#include <algorithm>
#include <zenilib.h>

#include "Constants.h"
#include "Game_Object.h"

using namespace Zeni;
using namespace std;

float parabolicFallTime(float target_z_initial, float target_z_vel, float launch_z, float launch_z_vel)
{
	float a = -SPEED_OF_GRAVITY;
	float b = launch_z_vel - target_z_vel;
	float c = launch_z - target_z_initial;
	// no non-complex roots
	if(b*b - 4*a*c < 0)
		return -1;
	float t1 = (-b + sqrt(b*b - 4*a*c))/(2*a);
	float t2 = (-b - sqrt(b*b - 4*a*c))/(2*a);
	//NOTE: Assuming a remains negative, no more than one of these can be positive.
	return max(t1, t2);
}

Game_Object* closestObject(const Zeni::Point3f& pos_, const vector<Game_Object*>& objects_)
{
	return closestObjectMatching(pos_, objects_, [](Game_Object* object) {return true;});
}

Game_Object* closestObjectMatching(const Zeni::Point3f& pos_, const std::vector<Game_Object*>& objects_, bool (*matchfunc)(Game_Object*))
{
	Game_Object* contender = nullptr;
	float lowestDistance = FLT_MAX;

	for_each(objects_.begin(), objects_.end(), [&](Game_Object* object) {
		float distance;

		if(matchfunc(object) && ((distance = Vector3f(object->getPosition() - pos_).magnitude()) < lowestDistance))
		{
			contender = object;
			lowestDistance = distance;
		}
	});

	return contender;
}