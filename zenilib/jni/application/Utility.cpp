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


float getTimeParabolic(float velY, float deltaY, const float g)
//NOTE: Returns a negative value if the parabolic can't work.
{
	float a = g;
	float b = velY;
	float c = deltaY;
	float det = b*b - 4*a*c;
	if(det < 0)
		return -1;
	float t1 = (-b + sqrt(det))/(2*a);
	float t2 = (-b - sqrt(det))/(2*a);
	if(t1 < 0)
		return t2;
	else if(t2 < 0)
		return t1;
	return min(t1, t2);
}

float getAngleParabolic(const Point3f targetPos, const Point3f launchPos, const float launchVel, const float g)
//NOTE: Returns a value between pi/2 and -pi/2. If no trajectory, returns 2pi.
{
	float d = hypot(targetPos.x - launchPos.x, targetPos.y - launchPos.y);
	float z = targetPos.z - launchPos.z;
	float v = launchVel;
	float det = v*v*v*v - g*(g*d*d + 2*z*v*v);
	if(det < 0)
		return 2*acos(1);
	float a1 = atan2(v*v + sqrt(det), g*d);
	float a2 = atan2(v*v - sqrt(det), g*d);
	return min(a2, a1);
}

float getTimeIterativeParabolic(const Point3f targetPos, const Vector3f targetVel, const Point3f launchPos, const float launchVel, const float g)
//NOTE: Returns a time, or -1 if there's no trajectory.
{
	Point3f iterativePos = targetPos;
	float error = 0, angle = 0, time = 0, deltaTime = 0;
	int i = 0;
	do
	{
		//this assumes that the correct direction is to increase the time it'll take.
		//maybe it should account for the possibility that a decrease will happen instead.
        angle = getAngleParabolic(iterativePos, launchPos, launchVel, g);
		if(angle == 2*acos(1))
			return -1;
        deltaTime = getTimeParabolic(sin(angle)*launchVel, iterativePos.z - launchPos.z, g) - time;
		if(time < 0)
			return -1;
		Point3f newPos = iterativePos + targetVel * deltaTime;
		time += deltaTime;
		error = pow(iterativePos.x - newPos.x, 2) + pow(iterativePos.y - newPos.y, 2) + pow(iterativePos.z - newPos.z, 2);
        iterativePos = newPos;
	}while(error > 0.5 && i++ < 4);
    
    return time;
}

shared_ptr<Game_Object> closestObject(const Zeni::Point3f& pos_, const vector<shared_ptr<Game_Object>>& objects_)
{
	return closestObjectMatching(pos_, objects_, [](shared_ptr<Game_Object> object) {return true;});
}
