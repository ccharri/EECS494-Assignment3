#include "Rock.h"

#include "Constants.h"

using namespace Zeni;
using namespace std;

Model_Wrapper Rock::model = Model_Wrapper("models/Boulder.3ds");

Rock::Rock(const Point3f& position_, const Vector3f &vel_, const float gravity, const Quaternion& facing_)	
		 : Physics_Object(position_, Vector3f(11,11,11), facing_, Vector3f(3.5, 3.5, 3.5))
{
	setVelocity(vel_);
	setAcceleration(Vector3f(0, 0, -gravity));
	updateCollider();
	
	//setRotation(Quaternion::Forward_Up(facing_ * Vector3f(1, 0, -20).normalized(), facing_ *Vector3f(0,0,1)));
}

void Rock::on_logic(float time_step)
{
	Physics_Object::on_logic(time_step);
	//TODO: Set rotation
}

void Rock::updateCollider()
{
	collider = Collision::Sphere(getPosition(), 2.f);
}
