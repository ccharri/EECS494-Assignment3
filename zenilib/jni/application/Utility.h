#ifndef __game__Utility_h__
#define __game__Utility_h__

#include <functional>
#include <vector>
#include <memory>
#include <zenilib.h>

#include "Utility_Templates.h"

class Game_Object;

float getTimeParabolic(const float velY, const float deltaY);
float getAngleParabolic(const Zeni::Point3f targetPos, const Zeni::Point3f launchPos, const float launchVel);
float getTimeIterativeParabolic(const Zeni::Point3f targetPos, const Zeni::Vector3f targetVel, const Zeni::Point3f launchPos, const float launchVel); 

std::shared_ptr<Game_Object> closestObject(const Zeni::Point3f& pos_, const std::vector<std::shared_ptr<Game_Object> >& objects_);


#endif