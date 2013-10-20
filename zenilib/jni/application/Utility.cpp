#include "Utility.h"

#include <math.h>
#include <algorithm>

#include "Constants.h"

using namespace Zeni;
using namespace std;
//
//Zeni::Quaternion quatBetweenPoints(const Zeni::Point3f& destination_, const Zeni::Point3f& origin_)
//{
//	double dx, dy, dz;
//	dx = destination_.x - origin_.x;
//	dy = destination_.y - origin_.y;
//	dz = destination_.z - origin_.z;
//
//	double yaw, pitch, roll;
//	yaw = atan2(dz, dx);
//	pitch = atan2(sqrt(dz*dz + dx*dx), dy) + Global::pi;
//	roll = 0;
//
//	return Quaternion(yaw, pitch, roll);
//}

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

shared_ptr<Game_Object> closestObject(const Zeni::Point3f& pos_, const vector<shared_ptr<Game_Object>>& objects_)
{
	return closestObjectMatching(pos_, objects_, [](shared_ptr<Game_Object> object) {return true;});
}
