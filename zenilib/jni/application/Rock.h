#ifndef __game__Rock_h__
#define __game__Rock_h__

#include "Physics_Object.h"
#include "Model_Wrapper.h"
#include <zenilib.h>

class Rock : public Physics_Object
{
public:
	Rock(const Zeni::Point3f& position_, const Zeni::Vector3f &vel, 
			 const Zeni::Quaternion& facing_ = Zeni::Quaternion());

	void on_logic(float time_step);
	void render() {model.getModel()->render();}
	Zeni::Model* getModel() {return model.getModel();}
	
private:
	Zeni::Vector3f size;
	static Model_Wrapper model;
	Zeni::Collision::Sphere collider;
};

#endif