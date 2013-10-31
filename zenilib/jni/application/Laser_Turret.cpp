#include "Laser_Turret.h"

#include "Laser.h"
#include "Tower_Section.h"

using namespace Zeni;
using namespace std;

Laser_Turret::Laser_Turret(std::weak_ptr<Tower_Section> owner_, float cooldown_, float damage_, float range_) : Tower_Weapon(owner_, cooldown_), damage(damage_), range(range_)
{
	auto owner = owner_.lock();
    if(owner) owner->setName("Laser Turret");
	setValue(Laser_Turret::getCost());
}

Laser_Turret::~Laser_Turret()
{

}

void Laser_Turret::on_logic(float time_step)
{
	Tower_Weapon::on_logic(time_step);
}

void Laser_Turret::fire()
{
	shared_ptr<Game_Object> laser = shared_ptr<Game_Object>(new Laser(shared_from_this(), getTarget(), damage, .20));
	addProjectile(laser);

	Tower_Weapon::fire();
}

bool Laser_Turret::canFire(std::shared_ptr<Game_Object> object)
{
	if(!Tower_Weapon::canFire(object)) return false;

	if(Vector3f(object->getPosition() - getSection()->getPosition()).magnitude() > range) return false;

	return true;
}