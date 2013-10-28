#ifndef __game__Level_One_h__
#define __game__Level_One_h__

#include <zenilib.h>
#include <iostream>

#include "Game_Level.h"
#include "Model_Wrapper.h"

class Level_One : public Game_Level
{
public:
	Level_One(Play_State* state_) : Game_Level(state_) {
		std::vector<Zeni::Point3f>& path = getPath();
		path.push_back(Zeni::Point3f(-50, 50,0));
		path.push_back(Zeni::Point3f( 50, 50,0));
		path.push_back(Zeni::Point3f( 50,-50,0));
		path.push_back(Zeni::Point3f(-50,-50,0));
	};

	~Level_One() {};

	virtual std::shared_ptr<Zeni::Model> getModel() const override {return model.getModel();};

private:
	static Model_Wrapper model;
};

Model_Wrapper Level_One::model("models/Level1.3DS");

#endif