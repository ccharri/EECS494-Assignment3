#ifndef __game__Tower_Base_h__
#define __game__Tower_Base_h__

#include <zenilib.h>

#include <vector>

#include "Game_Object.h"

class Tower_Section;

class Tower_Base : public Game_Object{
public:
	Tower_Base(const Zeni::Point3f &position_) : Game_Object(position_)
	{
		
	}

	virtual void on_logic(float time_step) override;

	virtual Zeni::Model* getModel() override;

	float getNextSegmentZ();
	void pushSegment(Tower_Section* segment_) {segments.push_back(segment_);};
	const vector<Tower_Section>& getSegments() {return segments;};

	virtual ~Tower_Base();

private:
	vector<Tower_Section*> segments;
}

#endif