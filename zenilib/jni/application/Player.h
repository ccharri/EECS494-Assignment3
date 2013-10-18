#ifndef __game__Player_h__
#define __game__Player_h__

#include "Game_Object.h"

#include <vector>
#include <zenilib.h>

#include "Model_Wrapper.h"

class Player : public Game_Object
{
public:
	Player(Zeni::Point3f location_, Zeni::Vector3f size_, Zeni::Quaternion facing_);
	~Player();

	virtual Zeni::Model* getModel() override {return model.getModel();};

	void on_logic(float time_step) override;
	Zeni::Camera get_camera() const {return view;};

private:
	Zeni::Collision::Capsule collision_capsule;
	Zeni::Camera view;

	static Model_Wrapper model;

	float speed;
	bool moving;
};

#endif