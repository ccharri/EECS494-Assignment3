#include "Buzzsaw.h"

#include "Tower_Weapon.h"
#include "Tower_Section.h"

using namespace Zeni;
using namespace std;

Model_Wrapper Buzzsaw::model("models/buzzsaw.3ds");

Buzzsaw::Buzzsaw(std::weak_ptr<Tower_Weapon> owner_, std::weak_ptr<Game_Object> target_, float radius, float duration_, float radPerUpdate_) : Game_Object(owner_.lock()->getSection()->getPosition()), owner(owner_), spinTimer(0), duration(duration_), angle(0), radPerUpdate(radPerUpdate_)
{
	play_sound("saw", 1.f, 1.f, owner_.lock()->getSection()->getPosition());
	setScale(Vector3f(radius, radius, 1.));
}

void Buzzsaw::on_logic(float time_step)
{
	if((spinTimer += time_step) > duration)
	{
		auto weapon = owner.lock();
		if(!weapon) return;

		weapon->removeProjectile(shared_from_this());
		return;
	}

	setFacing(Quaternion(angle -= radPerUpdate, 0, 0));
}