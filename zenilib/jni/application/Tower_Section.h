#ifndef __game__Tower_Section_h__
#define __game__Tower_Section_h__

#include <zenilib.h>

#include "Model_Wrapper.h"
#include "Game_Object.h"

class Tower_Weapon;

class Tower_Section : public Game_Object 
{
public:
	Tower_Section(const Zeni::Point3f& position_, const Zeni::Vector3f& size_, const Zeni::Quaternion& facing_ = Zeni::Quaternion(), Tower_Weapon* weapon_ = nullptr);

	virtual ~Tower_Section();

	virtual void on_logic(float time_step) override;
	virtual void render() override;

	virtual Zeni::Model* getModel() override {return model.getModel();};

	Tower_Weapon* getWeapon() {return weapon;};
	void setWeapon(Tower_Weapon* weapon_) {weapon = weapon_;};

private:
	static Model_Wrapper model;

	Tower_Weapon* weapon;
};

#endif