#ifndef __game__Basic_Enemy_h__
#define __game__Basic_Enemy_h__

#include <zenilib.h>

#include "Enemy.h"
#include "Model_Wrapper.h"

class Basic_Enemy : public Enemy {
public:
	Basic_Enemy(Zeni::Point3f loc_, float speed_, float health_, std::shared_ptr<Model_Wrapper> model_, 
							Zeni::Vector3f size_ = Zeni::Vector3f(1,1,1), Zeni::Quaternion facing = Zeni::Quaternion()) 
							: Enemy(loc_, size_, facing, speed_, health_) {model = model_;}

	virtual Zeni::Model* getModel() override {return model->getModel();}

	~Basic_Enemy() {};

private:
	std::shared_ptr<Model_Wrapper> model;
};


#endif