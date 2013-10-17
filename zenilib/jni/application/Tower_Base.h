#ifndef __game__Tower_Base_h__
#define __game__Tower_Base_h__

#include <zenilib.h>

#include <vector>

#include "Game_Object.h"
#include "Model_Wrapper.h"

class Tower_Section;

class Tower_Base : public Game_Object{
public:
	Tower_Base(const Zeni::Point3f &position_) : Game_Object(position_)
	{
		
	}

	void on_logic(float time_step) override;

	virtual Zeni::Model* getModel() override /*{return model.getModel();}*/;


	float getNextSectionZ(){return segments.size()*50} const;
	//DOES: Returns the would-be height of the next tower section. 
	//TODO: Replace 50 with segment height constant
	
	void pushSection(Tower_Section*);
	// DOES: Takes the segment and changes its position to the top of the Tower_Base.

	const vector<Tower_Section>& getSegments() const {return segments;};
	virtual ~Tower_Base();

private:
	vector<Tower_Section*> segments;

	//static Model_Wrapper model = Model_Wrapper(/* Insert model file location here */);
}

#endif