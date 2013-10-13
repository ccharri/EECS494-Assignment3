#include "Tower_Section.h"

using namespace Zeni;
using namespace std;

Tower_Section::Tower_Section(const Zeni::Point3f& position_, const Zeni::Vector3f& size_, const Zeni::Quaternion& facing_, Tower_Weapon * const weapon_) : position(position_), size(size_), facing(facing_), weapon(weapon_) 
{
}


Tower_Section::~Tower_Section()
{
	delete weapon;
}