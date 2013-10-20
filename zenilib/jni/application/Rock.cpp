#include "Rock.h"

#include "Constants.h"

using namespace Zeni;
using namespace std;

Model_Wrapper Rock::model("models/spike_ball.3ds");

Rock::Rock(const Point3f& position_, const Vector3f &vel_, const Quaternion& facing_)	
		 : Physics_Object(position_, Vector3f(), facing_)
{
	
	//setAcceleration(GRAVITY_VECTOR);
	//setSize(Zeni::Vector3f(5, 5, 5));
	setVelocity(vel_);
	setAcceleration(Vector3f(0,0,0));
}

void Rock::on_logic(float time_step)
{
	Physics_Object::on_logic(time_step);
	//TODO: Set rotation
}
