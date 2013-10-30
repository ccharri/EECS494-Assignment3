#include "Buzzsaw.h"

#include <stdio.h>

#include "Game_Level.h"
#include "Tower_Section.h"
#include "Utility.h"

using namespace std;
using namespace Zeni;

Buzzsaw::Buzzsaw(weak_ptr<Tower_Section> owner_, float cooldown_) : Tower_Weapon(owner_, cooldown_)
{
	DAMAGE = 15;
	RANGE = 20;
  
  auto owner = owner_.lock();
  if(owner) owner->setName("Buzzsaw");
  setValue(Buzzsaw::getCost());
}

Buzzsaw::~Buzzsaw() 
{

}

bool Buzzsaw::canFire(shared_ptr<Game_Object> object)
{
	if(!Tower_Weapon::canFire(object))
		return false;
	if((object->getPosition() - getSection()->getPosition()).magnitude() > RANGE)
		return false;
	return true;
}

void Buzzsaw::fire()
{
	Collision::Sphere saw(getSection()->getPosition(), RANGE);
	auto collidingEnemies = findCollidingObjects(saw, Game_Level::getCurrentLevel()->getEnemies());
	for_each(collidingEnemies.begin(), collidingEnemies.end(), [&](shared_ptr<Game_Object> enemy_) 
	{
		enemy_->onDamage(DAMAGE);
	});
	Tower_Weapon::fire();
}

void Buzzsaw::on_logic(float time_step)
{
	Tower_Weapon::on_logic(time_step);
}