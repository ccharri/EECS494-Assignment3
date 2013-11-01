#include "Beam_Tower.h"

#include "Tower_Section.h"
#include "Beam.h"

using namespace Zeni;
using namespace std;

Zeni::String Beam_Tower::description = "Damage: 10 * 1.05 per second since activation.  Caps at 50 damage per second.\nCooldown: Continuous\nRange: Can only shoot within a 45 degree cone towards the ground.";

Beam_Tower::Beam_Tower(weak_ptr<Tower_Section> owner_) : Tower_Weapon(owner_, 0.0)
{
	auto owner = owner_.lock();
	if(owner) owner->setName("Beam Tower");
	setValue(Beam_Tower::getCost());
}

Beam_Tower::~Beam_Tower()
{
}

void Beam_Tower::on_logic(float time_step)
{
	Tower_Weapon::on_logic(time_step);
}

bool Beam_Tower::canFire(std::shared_ptr<Game_Object> object)
{
	if(!Tower_Weapon::canFire(object)) return false;

	auto pos = getSection()->getPosition();
	auto tpos = object->getPosition();
	float deltaz = abs(pos.z - tpos.z);

	if(Vector3f(Point3f(pos.x, pos.y, tpos.z) - tpos).magnitude() > deltaz) return false;

	return true;
}

void Beam_Tower::fire()
{
    if(getProjectiles().size()) return;
    
	auto pos = getSection()->getPosition();
	auto tpos = getTarget()->getPosition();
	float dist = Vector3f(Point3f(pos.x, pos.y, tpos.z) - tpos).magnitude();
	shared_ptr<Game_Object> beam = shared_ptr<Game_Object>(new Beam(shared_from_this(), getTarget(), 10., dist));
	addProjectile(beam);
}