#include "Physics_Object.h"

Physics_Object::Physics_Object(const Zeni::Point3f& position_, const Zeni::Vector3f& size_, const Zeni::Quaternion& facing_)
	: Game_Object(position_, size_, facing_)
{

}

void Physics_Object::on_logic(float time_step){
	setPosition(getPosition() + vel * time_step);
	vel += acc * time_step;
}