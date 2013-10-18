#ifndef __game__Level_One_h_
#define __game__Level_One_h_

#include <zenilib.h>

#include "Game_Level.h"
#include "Model_Wrapper.h"

class Level_One : public Game_Level
{
public:
	Level_One() : Game_Level() {};

	~Level_One() {};

	virtual Zeni::Model* getModel() {return model.getModel();};

private:
	static Model_Wrapper model;
};

Model_Wrapper Level_One::model = Model_Wrapper("models/crate.3DS");

#endif