#include "Physics_Object.h"

#include <iostream>

using namespace Zeni;
using namespace std;

Physics_Object::Physics_Object(const Zeni::Point3f& position_, const Zeni::Vector3f& size_, const Zeni::Quaternion& facing_)
	: Game_Object(position_, size_, facing_)
{

}

void Physics_Object::on_logic(float time_step){
	cout << "Updating Physics Object" << endl;
	cout << "Acceleration = " << acc.x << ", " << acc.y << ", " << acc.z << endl;
	cout << "Velocity before = " << vel.x << ", " << vel.y << ", " << vel.z << endl;
	vel += acc * time_step;
	cout << "Velocity after = " << vel.x << ", " << vel.y << ", " << vel.z << endl;

	cout << "time_step = " << time_step << endl;
	cout << "Velocity increment = " << vel.x * time_step << ", " << vel.y * time_step << ", " << vel.z * time_step << endl;

	cout << "Prev Position = " << getPosition().x << ", " << getPosition().y << ", " << getPosition().z << endl;
	setPosition(getPosition() + vel * time_step);
	cout << "Next Position = " << getPosition().x << ", " << getPosition().y << ", " << getPosition().z << endl;

	Game_Object::on_logic(time_step);
}