#include "Player.h"

using namespace Zeni;
using namespace std;

Model_Wrapper Player::model = Model_Wrapper("");

Player::Player(Point3f location_, Vector3f size_, Quaternion facing_) : Game_Object(location_, size_, facing_)
{

}

Player::~Player()
{

}

void Player::on_logic(float time_step)
{
	Game_Object::on_logic(time_step);
}