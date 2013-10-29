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
	Tower_Base(const Zeni::Point3f &position_);

	void on_logic(float time_step) override;
	void render() override;
    
    bool collide(const Zeni::Collision::Capsule& collider_) const override;
	bool collide(const Zeni::Collision::Infinite_Cylinder& collider_) const override;
	bool collide(const Zeni::Collision::Line& collider_) const override;
	bool collide(const Zeni::Collision::Line_Segment& collider_) const override;
	bool collide(const Zeni::Collision::Parallelepiped& collider_) const override;
	bool collide(const Zeni::Collision::Plane& collider_) const override;
	bool collide(const Zeni::Collision::Ray& collider_) const override;
	bool collide(const Zeni::Collision::Sphere& collider_) const override;

	virtual std::shared_ptr<Zeni::Model> getModel() const override {return model.getModel();};

	float getNextSectionZ() const;
	//DOES: Returns the would-be height of the next tower section. 
	//TODO: Replace 50 with segment height constant
	
	void pushSection(std::shared_ptr<Tower_Section> section_);
	// DOES: Takes the segment and changes its position to the top of the Tower_Base.
	void removeSection(std::shared_ptr<Tower_Section> section_);

	const std::vector<std::shared_ptr<Tower_Section> >& getSegments() const {return segments;};
    
	virtual void onSelection(ZTDGUI* gui_) override;
	virtual void onDeselection(ZTDGUI* gui_) override;

    virtual float getPrimaryAttributeMax() const {return segments.capacity();};
	virtual float getPrimaryAttributeCurrent() const {return segments.size();};
	virtual Zeni::Color getPrimaryColor() const {return Zeni::Color(1.f, .5, .5, .5);};
    
    virtual bool isTargetable() const override {return true;};
    
	virtual ~Tower_Base();

	void updateCollider() {};

private:
	std::vector<std::shared_ptr<Tower_Section> > segments;

	static Model_Wrapper model;
    
    Zeni::Collision::Parallelepiped collider;

	std::vector<Zeni::Text_Button*> towerSegmentButtons;

	float getHeightForIndex(int i_) const;
};

#endif