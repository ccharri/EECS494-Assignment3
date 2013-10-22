#include "Rocket.h"

#include "Game_Level.h"
#include "Tower_Weapon.h"

using namespace Zeni;
using namespace std;

Model_Wrapper Rocket::model = Model_Wrapper("models/rocket.3ds");


Rocket::Rocket( std::weak_ptr<Tower_Weapon> owner_, std::weak_ptr<Game_Object> target_, float damage_, float speed_, Zeni::Point3f position_, Zeni::Vector3f size_, Zeni::Quaternion facing_, Zeni::Vector3f scale_)
	: Game_Object(position_, size_, facing_, scale_), owner(owner_), target(target_), damage(damage_), speed(speed_)
{
	auto tar = target.lock();

	if(tar)
		lookAt(tar->getPosition());
}

void Rocket::on_logic( float time_step )
{
	shared_ptr<Game_Object> tar = target.lock();

	if(!tar) explode();

	Vector3f vel = Vector3f(tar->getPosition() - getPosition()).normalized() * speed * time_step;

	if(Vector3f(tar->getPosition() - getPosition()).magnitude() <= vel.magnitude())
	{
		setPosition(tar->getPosition());
	}
	else
	{
		setPositionAndLookAt(getPosition() + vel, tar->getPosition());
	}

	if(tar->collide(&collider))
	{
		tar->onDamage(damage);
		explode();
	}

	Game_Object::on_logic(time_step);
}

void Rocket::updateCollider()
{
	collider = Collision::Capsule(getPosition(), getPosition() + (getFacing() * Vector3f(getSize().x, 0, 0)), getSize().y/2.);
}

void Rocket::explode()
{
	auto ownerptr = owner.lock();
	if(ownerptr)
	{
		ownerptr->removeProjectile(shared_from_this());
	}

	//Play sound effects, yada yada
}

