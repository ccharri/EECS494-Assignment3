#ifndef __game__Enemy_Box_h__
#define __game__Enemy_Box_h__

#include <zenilib.h>
#include <memory>

#include "Enemy.h"
#include "Model_Wrapper.h"

class Enemy_Box : public Enemy {
public:
	Enemy_Box(Zeni::Point3f loc_, float speed_, float health_, Zeni::Vector3f size_ = Zeni::Vector3f(1,1,1), Zeni::Quaternion facing = Zeni::Quaternion()) : Enemy(loc_, size_, facing, speed_, health_) {};

	virtual std::shared_ptr<Zeni::Model> getModel() const override {return model.getModel();};

	~Enemy_Box() {};

private:
	static Model_Wrapper model;
};

Model_Wrapper Enemy_Box::model = Model_Wrapper("models/crate.3ds");

#endif