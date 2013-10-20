#include "Tower_Section.h"

#include "Tower_Weapon.h"
#include <algorithm>

using namespace Zeni;
using namespace std;

Model_Wrapper Tower_Section::model = Model_Wrapper("models/crate.3ds");

Tower_Section::Tower_Section(const Zeni::Point3f& position_, const Zeni::Vector3f& size_, const Zeni::Quaternion& facing_, shared_ptr<Tower_Weapon> weapon_) : Game_Object(position_, size_, facing_),  weapon(weapon_) 
{
}


Tower_Section::~Tower_Section()
{
}

void Tower_Section::render() {
	Game_Object::render();
	weapon->render();
}

void Tower_Section::on_logic(float time_step)
{
	weapon->on_logic(time_step);
}