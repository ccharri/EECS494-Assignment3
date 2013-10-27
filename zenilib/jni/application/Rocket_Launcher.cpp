#include "Rocket_Launcher.h"

#include "Rocket.h"
#include "Tower_Section.h"

using namespace Zeni;
using namespace std;

Rocket_Launcher::Rocket_Launcher( std::weak_ptr<Tower_Section> owner_, float cooldown_ ) : Tower_Weapon(owner_, cooldown_)
{
    auto owner = owner_.lock();
    if(owner) owner->setName("Rocket Launcher");
}


void Rocket_Launcher::on_logic( float time_step )
{
	Tower_Weapon::on_logic(time_step);
}


void Rocket_Launcher::fire()
{
	shared_ptr<Game_Object> rocket = shared_ptr<Game_Object>(new Rocket(shared_from_this(), getTarget(), 50., 60., getSection()->getPosition()));
	rocket->lookAt(getTarget()->getPosition());
	addProjectile(rocket);

	Tower_Weapon::fire();
}
