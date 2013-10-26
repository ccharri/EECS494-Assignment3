#ifndef __game__Basic_Enemy_h__
#define __game__Basic_Enemy_h__

#include <zenilib.h>

#include "Enemy.h"
#include "Model_Wrapper.h"

class Basic_Enemy : public Enemy {
public:
	Basic_Enemy(Zeni::Point3f loc_, float speed_, float health_, std::shared_ptr<Zeni::Model> model_,
							Zeni::Vector3f size_ = Zeni::Vector3f(1,1,1), Zeni::Quaternion facing_ = Zeni::Quaternion())
    : Enemy(loc_, size_, facing_, speed_, health_), model(model_)
    {
    }

    std::shared_ptr<Zeni::Model> getModel() const override {return model.getModel();}

	~Basic_Enemy() {};

private:
    Model_Wrapper model;
};


#endif