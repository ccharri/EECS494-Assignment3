#include "Tower_Section.h"

#include "Tower_Weapon.h"
#include <algorithm>

using namespace Zeni;
using namespace std;

Tower_Section::Tower_Section(const Zeni::Point3f& position_, const Zeni::Vector3f& size_, const Zeni::Quaternion& facing_, Tower_Weapon* weapon_) : Game_Object(position_, size_, facing_),  weapon(weapon_) 
{
}


Tower_Section::~Tower_Section()
{
	delete weapon;
}

void Tower_Section::render() {
	auto projectiles = weapon->getProjectiles();

	for_each(projectiles.begin(), projectiles.end(), [&](Game_Object* object_)
	{
		object_->render();
	});
}

void Tower_Section::on_logic(float time_step)
{
	weapon->on_logic(time_step);

	//Weapon projectiles
	auto projectiles = weapon->getProjectiles();
	for_each(projectiles.begin(), projectiles.end(), [&](Game_Object* object_) {
			object_->on_logic(time_step);
	});
}