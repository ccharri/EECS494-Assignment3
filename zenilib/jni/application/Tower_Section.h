#ifndef __game__Tower_Section_h__
#define __game__Tower_Section_h__

#include <zenilib.h>
#include <memory>

#include "Model_Wrapper.h"
#include "Game_Object.h"
#include "Tower_Weapon.h"

class Tower_Section : public Game_Object
{
public:
	Tower_Section(const Zeni::Point3f& position_, const Zeni::Vector3f& size_, const Zeni::Quaternion& facing_ = Zeni::Quaternion(), std::shared_ptr<Tower_Weapon> weapon_ = nullptr);

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

	std::shared_ptr<Tower_Weapon> getWeapon() {return weapon;};
	void setWeapon(std::shared_ptr<Tower_Weapon> weapon_) {weapon = weapon_;};

	virtual float getPrimaryAttributeMax() const {return weapon->getCooldown();};
	virtual float getPrimaryAttributeCurrent() const {return weapon->getCooldownRemaining();};
	virtual Zeni::Color getPrimaryColor() const {return Zeni::Color(1.f, .5, .5, .5);};
    
    virtual bool isTargetable() const override {return true;};

	void updateCollider() override;

private:
	static Model_Wrapper model;
    
    Zeni::Collision::Parallelepiped collider;

	std::shared_ptr<Tower_Weapon> weapon;
};

#endif