#include "Tower_Section.h"

#include "Constants.h"
#include "Game_Level.h"
#include "Tower_Weapon.h"
#include "Tower_Base.h"
#include "Tower_Section.h"
#include "Play_State.h"
#include "ZTDGUI.h"

#include <algorithm>

using namespace Zeni;
using namespace std;

Model_Wrapper Tower_Section::model = Model_Wrapper("models/Tower_Section.3ds");

class Sell_Button : public Text_Button
{
public:
	Sell_Button(Tower_Section* owner_ = nullptr, const Point2f& upperLeft_ = Point2f() , const Point2f& lowerRight_ = Point2f()) : Text_Button(upperLeft_, lowerRight_, "system_36_800x600", String("Sell")), owner(owner_)
	{

	}

	void on_accept() override
	{
		owner->onDeselection(&Game_Level::getCurrentLevel()->getState()->getGUI());
		Game_Level::getCurrentLevel()->addGold(SELL_PERCENTAGE * owner->getWeapon()->getValue());
		owner->getBase()->removeSection(owner->getSectionSharedFromThis());
	}

	void on_hover() override
	{

	}

	void setOwner(Tower_Section* owner_){owner = owner_;};

private:
	Tower_Section* owner;
};

Sell_Button* sell_button = nullptr;

Tower_Section::Tower_Section(Tower_Base* base_, const Zeni::Point3f& position_, const Zeni::Vector3f& size_, const Zeni::Quaternion& facing_, shared_ptr<Tower_Weapon> weapon_) : Game_Object(position_, size_, facing_), base(base_), weapon(weapon_) 
{
    updateCollider();
}


Tower_Section::~Tower_Section()
{
}

void Tower_Section::render() {
	Game_Object::render();
	weapon->render();
}

void Tower_Section::on_logic(float time_step)
{
	weapon->on_logic(time_step);
}

void Tower_Section::onSelection(ZTDGUI* gui_)
{
	if(sell_button) delete sell_button;
	sell_button = new Sell_Button(this, Point2f(25, Window::get_height()/2. - 50), Point2f(175, Window::get_height()/2. + 50));
	//gui_->lendWidget(*sell_button);

	base->onSelection(gui_);
}

void Tower_Section::onDeselection(ZTDGUI* gui_)
{
	gui_->unlendWidget(*sell_button);

	base->onDeselection(gui_);
}

bool Tower_Section::collide(const Collision::Capsule& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Section::collide(const Collision::Infinite_Cylinder& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Section::collide(const Collision::Line& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Section::collide(const Collision::Line_Segment& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Section::collide(const Collision::Parallelepiped& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Section::collide(const Collision::Plane& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Section::collide(const Collision::Ray& collider_) const
{
    return collider.intersects(collider_);
}

bool Tower_Section::collide(const Collision::Sphere& collider_) const
{
    return collider.intersects(collider_);
}

void Tower_Section::updateCollider()
{
    Vector3f size = getSize();
    collider = Collision::Parallelepiped(getPosition() - Vector3f(size.x, size.y, 0)/2., Vector3f(size.x, 0, 0), Vector3f(0, size.y, 0), Vector3f(0, 0, size.z));
}