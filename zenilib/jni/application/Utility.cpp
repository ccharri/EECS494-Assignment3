#include "Utility.h"

#include <algorithm>
#include <zenilib.h>

#include "Game_Object.h"

using namespace Zeni;
using namespace std;

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