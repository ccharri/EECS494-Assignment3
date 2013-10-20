#ifndef __game__Tower_Base_h__
#define __game__Tower_Base_h__

#include <zenilib.h>

#include <vector>
#include <memory>

#include "Game_Object.h"
#include "Model_Wrapper.h"

class Tower_Section;

class Tower_Base : public Game_Object{
public:
	Tower_Base(const Zeni::Point3f &position_) : Game_Object(position_, Zeni::Vector3f(1,1,1), Zeni::Quaternion(), Zeni::Vector3f(1,1,1))
	{
		
	}

	void on_logic(float time_step) override;
	void render() override;

	virtual Zeni::Model* getModel() override {return model.getModel();};

	float getNextSectionZ() const;
	//DOES: Returns the would-be height of the next tower section. 
	//TODO: Replace 50 with segment height constant
	
	void pushSection(std::shared_ptr<Tower_Section> section_);
	// DOES: Takes the segment and changes its position to the top of the Tower_Base.

	const std::vector<std::shared_ptr<Tower_Section> >& getSegments() const {return segments;};
	virtual ~Tower_Base();

private:
	std::vector<std::shared_ptr<Tower_Section>> segments;

	static Model_Wrapper model;
};

#endif