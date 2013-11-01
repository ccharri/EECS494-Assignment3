#include "Beam.h"

#include "Tower_Weapon.h"
#include "Tower_Section.h"
#include <Zeni/Sound_Buffer.h>

using namespace Zeni;
using namespace std;

Model_Wrapper Beam::model("models/laser.3ds");

Beam::Beam(std::weak_ptr<Tower_Weapon> owner_, std::weak_ptr<Game_Object> target_, float damage_, float range_) : 
	Game_Object(owner_.lock()->getSection()->getPosition()), 
	owner(owner_), target(target_), damage(damage_), damageCap(5 * damage_), stacks(0), stacksCap(7.0), range(range_),
	beamSoundSource(get_Sounds()["beam"], 1., 1., owner_.lock()->getSection()->getPosition(),Vector3f(),true)
{
	beamSoundSource.play();
	pointToTarget();
}

Beam::~Beam()
{
	beamSoundSource.stop();
}

void Beam::on_logic(float time_step)
{
	auto sowner = owner.lock();
	auto starget = target.lock();

	if(starget)
	{
		if(!sowner->canFire(starget))
		{
			sowner->removeProjectile(shared_from_this());
			return;
		}

		targetPos = starget->getPosition();
		starget->onDamage(damage * time_step);
	}
	else 
	{
		if(sowner)
		{
			sowner->removeProjectile(shared_from_this());
		}
		return;
	}

	damage+= damage*time_step;
	damage = damage > damageCap ? damageCap : damage;
	stacks+= time_step;
	stacks = stacks > stacksCap ? stacksCap : stacks;

	auto scale = getScale();
	float scalemult = 1 + stacks;
	setScale(Vector3f(scale.x,scalemult, scalemult));

	pointToTarget();
}

void Beam::pointToTarget()
{
	auto weapon = owner.lock();
	if(!weapon) return;

	float dist = Vector3f(targetPos - weapon->getSection()->getPosition()).magnitude();
	auto scale = getScale();
	setScale(Vector3f(dist, scale.y, scale.z));
	lookAt(targetPos);
}
