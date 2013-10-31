#ifndef __game__Tower_Section_h__
#define __game__Tower_Section_h__

#include <zenilib.h>
#include <memory>

#include "Model_Wrapper.h"
#include "Game_Object.h"
#include "Tower_Weapon.h"

class Tower_Base;

class Tower_Section : public Game_Object
{
public:
	Tower_Section(Tower_Base* base_, const Zeni::Point3f& position_ = Zeni::Point3f(), const Zeni::Vector3f& size_ = Zeni::Vector3f(7,7,10), const Zeni::Quaternion& facing_ = Zeni::Quaternion(), std::shared_ptr<Tower_Weapon> weapon_ = nullptr);

	virtual ~Tower_Section();

	virtual void on_logic(float time_step) override;
	virtual void render() override;
    
    bool collide(const Zeni::Collision::Capsule& collider_) const override;
	bool collide(const Zeni::Collision::Infinite_Cylinder& collider_) const override;
	bool collide(const Zeni::Collision::Line& collider_) const override;
	bool collide(const Zeni::Collision::Line_Segment& collider_) const override;
	bool collide(const Zeni::Collision::Parallelepiped& collider_) const override;
	bool collide(const Zeni::Collision::Plane& collider_) const override;
	bool collide(const Zeni::Collision::Ray& collider_) const override;
	bool collide(const Zeni::Collision::Sphere& collider_) const override;

	virtual std::shared_ptr<Zeni::Model> getModel() const override {return model.getModel();};

	std::shared_ptr<Tower_Section> getSectionSharedFromThis() {return std::static_pointer_cast<Tower_Section>(shared_from_this());};

	Tower_Base* getBase() const {return base;};

	std::shared_ptr<Tower_Weapon> getWeapon() {return weapon;};
	void setWeapon(std::shared_ptr<Tower_Weapon> weapon_) {weapon = weapon_;};

	virtual float getPrimaryAttributeMax() const {return weapon->getCooldown();};
	virtual float getPrimaryAttributeCurrent() const {return weapon->getCooldownRemaining();};
	virtual Zeni::Color getPrimaryColor() const {return Zeni::Color(1.f, .5, .5, .5);};
    
    virtual bool isTargetable() const override {return true;};

	virtual void onSelection(ZTDGUI* gui_);
	virtual void onDeselection(ZTDGUI* gui_);

	virtual void onSell();

	void updateCollider() override;

private:
	static Model_Wrapper model;

	Tower_Base* base;
    
    Zeni::Collision::Parallelepiped collider;

	std::shared_ptr<Tower_Weapon> weapon;

	std::vector<Zeni::Text_Button*> towerActionButtons;

	Zeni::Text_Button* sell_button;
};

#endif