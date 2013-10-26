#ifndef __game__Arrow_h__
#define __game__Arrow_h__

#include <zenilib.h>
#include <memory>

#include "Enemy.h"
#include "Model_Wrapper.h"

class Arrow : public Enemy
{
public:
	Arrow(Zeni::Point3f location_, Zeni::Vector3f size_ = Zeni::Vector3f(), Zeni::Quaternion facing_ = Zeni::Quaternion(), float speed_ = 50) : Enemy(location_, size_, facing_, speed_, 0)
	{};

	~Arrow() {};

	virtual bool isTargetable() const override {return false;};

	virtual void on_logic(float time_step) override
	{
		Enemy::on_logic(time_step);
		if(!moving)
		{
			moving = true;
			pathIndex = 0;
		}
	}

	virtual std::shared_ptr<Zeni::Model> getModel() const override {return model.getModel();};

private:
	static Model_Wrapper model;
};

Model_Wrapper Arrow::model = Model_Wrapper("models/arrow.3ds");

#endif