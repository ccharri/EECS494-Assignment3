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
