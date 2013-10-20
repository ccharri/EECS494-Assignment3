#ifndef __game__Utility_Templates_h__
#define __game__Utility_Templates_h__

#include "Game_Object.h"
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


#endif