#ifndef __game__Utility_Templates_h__
#define __game__Utility_Templates_h__

#include "Game_Object.h"
#include <algorithm>
#include <memory>
#include <zenilib.h>

template <typename Func>
std::shared_ptr<Game_Object> closestObjectMatching(const Zeni::Point3f& pos_, const std::vector<std::shared_ptr<Game_Object> >& objects_, Func matchfunc)
{
	std::shared_ptr<Game_Object> contender = nullptr;
	float lowestDistance = FLT_MAX;

	for_each(objects_.begin(), objects_.end(), [&](std::shared_ptr<Game_Object> object) {
		float distance;

		if(matchfunc(object) && ((distance = Zeni::Vector3f(object->getPosition() - pos_).magnitude()) < lowestDistance))
		{
			contender = object;
			lowestDistance = distance;
		}
	});

	return contender;
}

template<typename collider>
std::vector<std::shared_ptr<Game_Object> > findCollidingObjects(const collider& collider_, const std::vector<std::shared_ptr<Game_Object> >& objects_)
{
	std::vector<std::shared_ptr<Game_Object> > r_vector;

	for_each(objects_.begin(), objects_.end(), [&](shared_ptr<Game_Object> object_) {
		if(object_ && object_->collide(collider_)) 
			r_vector.push_back(object_);
	});

	return r_vector;
}

#endif