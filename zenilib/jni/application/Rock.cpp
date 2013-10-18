#include "Rock.h"

#include "Constants.h"

Model_Wrapper Rock::model("models/spike_ball.3ds");

Rock::Rock(const Zeni::Point3f& position_, const Zeni::Vector3f &vel, const Zeni::Quaternion& facing_)	
		 : Physics_Object(position_, Zeni::Vector3f(), facing_)
{
	//setAcceleration(GRAVITY_VECTOR);
	setSize(Zeni::Vector3f(5, 5, 5));
}

void Rock::on_logic(float time_step)
{
	//TODO: Set rotation
}
