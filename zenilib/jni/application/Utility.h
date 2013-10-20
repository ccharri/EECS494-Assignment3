#ifndef __game__Utility_h__
#define __game__Utility_h__

#include <functional>
#include <vector>
#include <memory>
#include <zenilib.h>

#include "Utility_Templates.h"

class Game_Object;

Zeni::Quaternion quatBetweenPoints(const Zeni::Point3f& destination_, const Zeni::Point3f& origin_);

float parabolicFallTime(float target_z_initial, float target_z_vel, float launch_z);
//NOTE: Returns a negative number if the fall is invalid

std::shared_ptr<Game_Object> closestObject(const Zeni::Point3f& pos_, const std::vector<std::shared_ptr<Game_Object> >& objects_);

#endif