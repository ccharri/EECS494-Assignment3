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

	virtual Zeni::Model* getModel() override {return model.getModel();};

	std::shared_ptr<Tower_Weapon> getWeapon() {return weapon;};
	void setWeapon(std::shared_ptr<Tower_Weapon> weapon_) {weapon = weapon_;};

	virtual float getPrimaryAttributeMax() const {return weapon->getCooldown();};
	virtual float getPrimaryAttributeCurrent() const {return weapon->getCooldownRemaining();};
	virtual Zeni::Color getPrimaryColor() const {return Zeni::Color(1.f, .5, .5, .5);};

	void updateCollider() {};

private:
	static Model_Wrapper model;

	std::shared_ptr<Tower_Weapon> weapon;
};

#endif