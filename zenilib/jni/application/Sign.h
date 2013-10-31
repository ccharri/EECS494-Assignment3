#ifndef __game__Sign_h__
#define __game__Sign_h__

#include <zenilib.h>
#include <memory>

#include "Model_Wrapper.h"
#include "Game_Object.h"

class Sign : public Game_Object
{
public:
	Sign(Zeni::Point3f location_, Zeni::Vector3f size_ = Zeni::Vector3f(), Zeni::Quaternion facing_ = Zeni::Quaternion()) 
		: Game_Object(location_, size_, facing_)
	{
		
	}
	~Sign(){};

	std::shared_ptr<Zeni::Model> getModel() const override {return model.getModel();}

private:
	static Model_Wrapper model;
};

#endif