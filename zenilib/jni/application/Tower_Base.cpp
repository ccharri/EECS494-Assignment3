#include "Tower_Base.h"

#include <algorithm>
#include "Tower_Section.h"

using namespace Zeni;
using namespace std;


Model_Wrapper Tower_Base::model = Model_Wrapper("models/Tower_Base.3ds");

Tower_Base::~Tower_Base() 
{

}

float Tower_Base::getNextSectionZ() const
{
	return segments.size();
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
