#include "Tower_Base.h"

#include <algorithm>
#include "Tower_Section.h"
#include "Rock_Dropper.h"
#include "Constants.h"
#include "ZTDGUI.h"

using namespace Zeni;
using namespace std;


Model_Wrapper Tower_Base::model = Model_Wrapper("models/Tower_Base.3ds");

class Dropper_Button : public Text_Button
{
public:
	Dropper_Button(Tower_Base* owner_, const Point2f& upperLeft_, const Point2f& lowerRight_) : Text_Button(upperLeft_, lowerRight_, "system_36_800x600", "Rock Dropper"), owner(owner_)
	{
	}

	void on_accept() override
	{
		shared_ptr<Tower_Section> dropperSection(new Tower_Section());
		shared_ptr<Tower_Weapon> dropperWeapon(new Rock_Dropper(dropperSection));
		dropperSection->setWeapon(dropperWeapon);
		owner->pushSection(dropperSection);
	}


private:
	Tower_Base* owner;
};

Tower_Base::Tower_Base(const Point3f &position_) : Game_Object(position_, Vector3f(20,20,1), Quaternion(), Vector3f(1,1,1))
{
    Vector3f size = getSize();
	collider = Collision::Parallelepiped(position_ - Vector3f(size.x, size.y, 0)/2., Vector3f(size.x, 0, 0), Vector3f(0, size.y, 0), Vector3f(0, 0, size.z));
    setName("Tower Base");

	Text_Button &dropperButton = Dropper_Button(this, Point2f(50, Window::get_height() - 100), Point2f(150, Window::get_height() - 50));
}

Tower_Base::~Tower_Base() 
{

}

float Tower_Base::getNextSectionZ() const
{
	return segments.size()*HEIGHT_INCREMENT + HEIGHT_INCREMENT*0.5;
}

void Tower_Base::pushSection(shared_ptr<Tower_Section> section_)
{
	Point3f newPos(getPosition().x, getPosition().y, getNextSectionZ());
	section_->setPosition(newPos);
	segments.push_back(section_);
}

void Tower_Base::on_logic(float time_step)
{
    Game_Object::on_logic(time_step);
    
	for_each(segments.begin(), segments.end(), [&](shared_ptr<Tower_Section> section_) {
		section_->on_logic(time_step);
	});
}

void Tower_Base::render()
{
	Game_Object::render();

	for_each(segments.begin(), segments.end(), [&](shared_ptr<Tower_Section> section_) {
		section_->render();
	});
}

void Tower_Base::onSelection(ZTDGUI* gui_)
{
	for_each(towerSegmentButtons.begin(), towerSegmentButtons.end(), [&](Text_Button &button_) {
		gui_->lendWidget(button_);
	});
}

void Tower_Base::onDeselection(ZTDGUI* gui_)
{
	for_each(towerSegmentButtons.begin(), towerSegmentButtons.end(), [&](Text_Button &button_) {
		gui_->unlendWidget(button_);
	});
}

bool Tower_Base::collide(const Collision::Capsule& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Base::collide(const Collision::Infinite_Cylinder& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Base::collide(const Collision::Line& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Base::collide(const Collision::Line_Segment& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Base::collide(const Collision::Parallelepiped& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Base::collide(const Collision::Plane& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Base::collide(const Collision::Ray& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Base::collide(const Collision::Sphere& collider_) const
{
    return collider.intersects(collider_);
}
