#include "Tower_Section.h"

#include "Tower_Weapon.h"
#include <algorithm>

using namespace Zeni;
using namespace std;

Model_Wrapper Tower_Section::model = Model_Wrapper("models/crate.3ds");

Tower_Section::Tower_Section(const Zeni::Point3f& position_, const Zeni::Vector3f& size_, const Zeni::Quaternion& facing_, shared_ptr<Tower_Weapon> weapon_) : Game_Object(position_, size_, facing_),  weapon(weapon_) 
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