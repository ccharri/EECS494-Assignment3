#include "Tower_Base.h"

#include <algorithm>

#include "Game_Level.h"
#include "Play_State.h"
#include "Tower_Section.h"
#include "Buzzsaw_Tower.h"
#include "Rock_Dropper.h"
#include "Rocket_Launcher.h"
#include "Laser_Turret.h"
#include "Beam_Tower.h"
#include "Constants.h"
#include "ZTDGUI.h"

using namespace Zeni;
using namespace std;


Model_Wrapper Tower_Base::model = Model_Wrapper("models/Tower_Base.3ds");

class Buzzsaw_Button : public Text_Button
{
public:
	Buzzsaw_Button(Tower_Base* owner_, const Point2f& upperLeft_, const Point2f& lowerRight_) 
		: Text_Button(upperLeft_, lowerRight_, "system_24_800x600", String("Buzzsaw\n") + itoa(Buzzsaw_Tower::getCost())), owner(owner_)
	{
	}

	void on_accept() override{
        auto level = Game_Level::getCurrentLevel();
        level->getState()->getGUI().markIgnoreNextClick();
        
        if(level->getGold() < Buzzsaw_Tower::getCost()) return;
        
		shared_ptr<Tower_Section> dropperSection(new Tower_Section(owner));
		shared_ptr<Tower_Weapon> dropperWeapon(new Buzzsaw_Tower(dropperSection));
		dropperSection->setWeapon(dropperWeapon);
		owner->pushSection(dropperSection);
       
        level->removeGold(Buzzsaw_Tower::getCost());

		Text_Button::on_accept();
	}
    
    void on_hover() override {
        Game_Level::getCurrentLevel()->getState()->getGUI().markRenderTowerInfo(Buzzsaw_Tower::getGenericDescription());
	}
    
    void on_unhover() override {
        Game_Level::getCurrentLevel()->getState()->getGUI().stopRenderTowerInfo();
    }

private:
	Tower_Base* owner;
};

class Beam_Button : public Text_Button
{
public:
	Beam_Button(Tower_Base* owner_, const Point2f& upperLeft_, const Point2f& lowerRight_) 
		: Text_Button(upperLeft_, lowerRight_, "system_24_800x600", String("Beam Tower\n") + itoa(Beam_Tower::getCost())), owner(owner_)
	{
	}

	void on_accept() override
	{
        auto level = Game_Level::getCurrentLevel();
        level->getState()->getGUI().markIgnoreNextClick();
        
        if(level->getGold() < Beam_Tower::getCost()) return;
        
		shared_ptr<Tower_Section> dropperSection(new Tower_Section(owner));
		shared_ptr<Tower_Weapon> dropperWeapon(new Beam_Tower(dropperSection));
		dropperSection->setWeapon(dropperWeapon);
		owner->pushSection(dropperSection);
       
        level->removeGold(Beam_Tower::getCost());

		Text_Button::on_accept();
	}
    
    void on_hover() override {
        Game_Level::getCurrentLevel()->getState()->getGUI().markRenderTowerInfo(Beam_Tower::getGenericDescription());
	}
    
    void on_unhover() override {
        Game_Level::getCurrentLevel()->getState()->getGUI().stopRenderTowerInfo();
    }

private:
	Tower_Base* owner;
};

class Laser_Button : public Text_Button
{
public:
	Laser_Button(Tower_Base* owner_, const Point2f& upperLeft_, const Point2f& lowerRight_) 
		: Text_Button(upperLeft_, lowerRight_, "system_24_800x600", String("Laser Turret\n") + itoa(Laser_Turret::getCost())), owner(owner_)
	{
	}

	void on_accept() override
	{
        auto level = Game_Level::getCurrentLevel();
        level->getState()->getGUI().markIgnoreNextClick();
        
        if(level->getGold() < Laser_Turret::getCost()) return;
        
		shared_ptr<Tower_Section> dropperSection(new Tower_Section(owner));
		shared_ptr<Tower_Weapon> dropperWeapon(new Laser_Turret(dropperSection));
		dropperSection->setWeapon(dropperWeapon);
		owner->pushSection(dropperSection);
        
        level->removeGold(Laser_Turret::getCost());

		Text_Button::on_accept();
	}
    
    void on_hover() override {
        Game_Level::getCurrentLevel()->getState()->getGUI().markRenderTowerInfo(Laser_Turret::getGenericDescription());
	}
    
    void on_unhover() override {
        Game_Level::getCurrentLevel()->getState()->getGUI().stopRenderTowerInfo();
    }

private:
	Tower_Base* owner;
};

class Dropper_Button : public Text_Button
{
public:
	Dropper_Button(Tower_Base* owner_, const Point2f& upperLeft_, const Point2f& lowerRight_) 
		: Text_Button(upperLeft_, lowerRight_, "system_24_800x600", String("Rock Dropper\n") + itoa(Rock_Dropper::getCost())), owner(owner_)
	{    
	}

	void on_accept() override
	{
        auto level = Game_Level::getCurrentLevel();
        level->getState()->getGUI().markIgnoreNextClick();
        
        if(level->getGold() < Rock_Dropper::getCost()) return;
        
		shared_ptr<Tower_Section> dropperSection(new Tower_Section(owner));
		shared_ptr<Tower_Weapon> dropperWeapon(new Rock_Dropper(dropperSection));
		dropperSection->setWeapon(dropperWeapon);
		owner->pushSection(dropperSection);
        
        level->removeGold(Rock_Dropper::getCost());

		Text_Button::on_accept();
	}
    
    void on_hover() override {
        Game_Level::getCurrentLevel()->getState()->getGUI().markRenderTowerInfo(Rock_Dropper::getGenericDescription());
	}
    
    void on_unhover() override {
        Game_Level::getCurrentLevel()->getState()->getGUI().stopRenderTowerInfo();
    }

private:
	Tower_Base* owner;
};

class Rocket_Button : public Text_Button
{
public:
	Rocket_Button(Tower_Base* owner_, const Point2f& upperLeft_, const Point2f& lowerRight_) 
		: Text_Button(upperLeft_, lowerRight_, "system_24_800x600", String("Rocket Launcher\n") + itoa(Rocket_Launcher::getCost())), owner(owner_)
	{
        
	}
    
	void on_accept() override
	{
        auto level = Game_Level::getCurrentLevel();
        level->getState()->getGUI().markIgnoreNextClick();
        
        if(level->getGold() < Rocket_Launcher::getCost()) return;
        
		shared_ptr<Tower_Section> rocketSection(new Tower_Section(owner));
		shared_ptr<Tower_Weapon> rocketWeapon(new Rocket_Launcher(rocketSection));
		rocketSection->setWeapon(rocketWeapon);
		owner->pushSection(rocketSection);
        
        level->removeGold(Rocket_Launcher::getCost());
        
		Text_Button::on_accept();
	}
    
    void on_hover() override {
        Game_Level::getCurrentLevel()->getState()->getGUI().markRenderTowerInfo(Rocket_Launcher::getGenericDescription());
	}
    
    void on_unhover() override {
        Game_Level::getCurrentLevel()->getState()->getGUI().stopRenderTowerInfo();
    }
    
private:
	Tower_Base* owner;
};

Tower_Base::Tower_Base(const Point3f &position_) : Game_Object(position_, Vector3f(15,15,1), Quaternion(), Vector3f(1,1,1))
{
    Vector3f size = getSize();
	collider = Collision::Parallelepiped(position_ - Vector3f(size.x, size.y, 0)/2., Vector3f(size.x, 0, 0), Vector3f(0, size.y, 0), Vector3f(0, 0, size.z));
    setName("Tower Base");
	
	float buttonWidth = 150;
	float buttonGap = 10;
	float buttonHeight = 100;
	float buttonHeightOffset = 20;

	Laser_Button *dropperButton = new Laser_Button(this, Point2f(buttonGap, Window::get_height() - buttonHeightOffset - buttonHeight), Point2f(buttonGap+buttonWidth, Window::get_height() - buttonHeightOffset));
    Buzzsaw_Button *rocketButton = new Buzzsaw_Button(this, Point2f(buttonGap*2 + buttonWidth, Window::get_height() - buttonHeightOffset - buttonHeight), Point2f(buttonGap*2 + buttonWidth*2, Window::get_height() - buttonHeightOffset));
	Rocket_Button *buzzsawButton = new Rocket_Button(this, Point2f(buttonGap*3+buttonWidth*2, Window::get_height() - buttonHeightOffset - buttonHeight), Point2f(buttonGap*3+buttonWidth*3, Window::get_height() - buttonHeightOffset));
	Dropper_Button *laserButton = new Dropper_Button(this, Point2f(buttonGap*4+buttonWidth*3, Window::get_height() - buttonHeightOffset - buttonHeight), Point2f(buttonGap*4+buttonWidth*4, Window::get_height() - buttonHeightOffset));
	Beam_Button *beamButton = new Beam_Button(this, Point2f(buttonGap*5 + buttonWidth*4, Window::get_height() - buttonHeightOffset - buttonHeight), Point2f(buttonGap*5 + buttonWidth*5, Window::get_height() - buttonHeightOffset));

	towerSegmentButtons.push_back(buzzsawButton);
	towerSegmentButtons.push_back(dropperButton);
    towerSegmentButtons.push_back(rocketButton);
	towerSegmentButtons.push_back(laserButton);
	towerSegmentButtons.push_back(beamButton);
}

Tower_Base::~Tower_Base() 
{
	for_each(towerSegmentButtons.begin(), towerSegmentButtons.end(), [&](Text_Button* button_) {delete button_;});
}

float Tower_Base::getNextSectionZ() const
{
	return getHeightForIndex(segments.size());
}

float Tower_Base::getHeightForIndex(int i_) const
{
	return i_*HEIGHT_INCREMENT + HEIGHT_INCREMENT*0.5 + getPosition().z;
}

void Tower_Base::pushSection(shared_ptr<Tower_Section> section_)
{
	Point3f newPos(getPosition().x, getPosition().y, getNextSectionZ());
	section_->setPosition(newPos);
	segments.push_back(section_);
}

void Tower_Base::removeSection(std::shared_ptr<Tower_Section> section_)
{
	auto it = find(segments.begin(), segments.end(), section_);
	if(it == segments.end()) return;

	segments.erase(it);
	
	int i = 0;
	for_each(segments.begin(), segments.end(), [&](shared_ptr<Tower_Section> section_) {
		auto pos = section_->getPosition();
		section_->setPosition(Point3f(pos.x, pos.y, getHeightForIndex(i++)));
	});
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
	for_each(towerSegmentButtons.begin(), towerSegmentButtons.end(), [&](Text_Button* button_) {
		gui_->lendWidget(button_);
	});
}

void Tower_Base::onDeselection(ZTDGUI* gui_)
{
	for_each(towerSegmentButtons.begin(), towerSegmentButtons.end(), [&](Text_Button* button_) {
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
