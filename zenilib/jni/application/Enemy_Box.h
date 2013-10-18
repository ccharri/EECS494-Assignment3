#ifndef __game__Enemy_Box_h__
#define __game__Enemy_Box_h__

#include <zenilib.h>

#include "Enemy.h"
#include "Model_Wrapper.h"

class Enemy_Box : public Enemy {
public:
	Enemy_Box(Zeni::Point3f loc_, Zeni::Vector3f size_, Zeni::Quaternion facing, float speed_, float health_) : Enemy(loc_, size_, facing, speed_, health_) {};

	virtual Zeni::Model* getModel() override {return model.getModel();};

	~Enemy_Box() {};

private:
	static Model_Wrapper model;
};

Model_Wrapper Enemy_Box::model = Model_Wrapper("models/crate.3ds");

#endif