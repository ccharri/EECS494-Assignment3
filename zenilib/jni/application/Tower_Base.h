#ifndef __game__Tower_Base_h__
#define __game__Tower_Base_h__

#include <zenilib.h>

#include <vector>

class Tower_Base{
public:
	Tower_Base(const Zeni::Point3f &position_)
	{
		
	}

	virtual void render() const;
	
	float getNextSegmentZ();
	void pushSegment();

	virtual ~Tower_Base() = 0

private:
	Zeni::Point3f position;
	Zeni::Vector3f size;
	Zeni::Quaternion facing;

	vector<Tower_Section*> segments;
}

#endif