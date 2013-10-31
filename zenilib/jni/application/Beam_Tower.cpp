#include "Beam_Tower.h"

#include "Tower_Section.h"
#include "Beam.h"

using namespace Zeni;
using namespace std;

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

	if(getProjectiles().size()) return false;

	auto pos = getSection()->getPosition();
	auto tpos = object->getPosition();
	float deltaz = abs(pos.z - tpos.z);

	if(Vector3f(Point3f(pos.x, pos.y, tpos.z) - tpos).magnitude() > deltaz) return false;

	return true;
}

void Beam_Tower::fire()
{
	auto pos = getSection()->getPosition();
	auto tpos = getTarget()->getPosition();
	float deltaz = abs(pos.z - tpos.z);
	float dist = Vector3f(Point3f(pos.x, pos.y, tpos.z) - tpos).magnitude();
	shared_ptr<Game_Object> beam = shared_ptr<Game_Object>(new Beam(shared_from_this(), getTarget(), 2., dist));
	addProjectile(beam);
}