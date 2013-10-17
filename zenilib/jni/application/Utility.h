#ifndef __game__Utiliy_h__
#define __game__Utiliy_h__

#include <vector>
#include <zenilib.h>

class Game_Object;

Game_Object* closestObject(const Zeni::Point3f& pos_, const std::vector<Game_Object*>& objects_);
Game_Object* closestObjectMatching(const Zeni::Point3f& pos_, const std::vector<Game_Object*>& objects_, bool (*matchfunc)(Game_Object*));

#endif