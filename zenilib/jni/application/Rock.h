#ifndef __game__Rock_h__
#define __game__Rock_h__

#include "Physics_Object.h"
#include "Model_Wrapper.h"
#include "Constants.h"
#include <zenilib.h>
#include <memory>

class Rock : public Physics_Object
{
public:
	Rock(const Zeni::Point3f& position_, const Zeni::Vector3f &vel, const float gravity = SPEED_OF_GRAVITY,
			 const Zeni::Quaternion& facing_ = Zeni::Quaternion());

	void on_logic(float time_step);
    std::shared_ptr<Zeni::Model> getModel() const override {return model.getModel();}

	const Zeni::Collision::Sphere& getCollider() const {return collider;}; 
	
private:
	Zeni::Vector3f size;
	static Model_Wrapper model;
	Zeni::Collision::Sphere collider;

	void updateCollider() override;
};

#endif