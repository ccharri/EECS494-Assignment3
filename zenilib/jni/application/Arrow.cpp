#include "Arrow.h"

#include <zenilib.h>
#include <memory>

#include "Sign.h"
#include "Game_Level.h"

Model_Wrapper Arrow::model = Model_Wrapper("models/arrow.3ds");

void Arrow::on_logic(float time_step)
{
	Enemy::on_logic(time_step);
	if(!moving)
	{
		moving = true;
		pathIndex = 0;
	}
	if(signTimer.seconds() - lastDrop > dropInterval)
	{
		Sign *s = new Sign(getPosition(), getSize(), getFacing());
		Game_Level::getCurrentLevel()->addSign(std::shared_ptr<Sign>(s));
		lastDrop = signTimer.seconds();
	}
}