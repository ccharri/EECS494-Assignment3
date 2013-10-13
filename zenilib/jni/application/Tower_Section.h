#ifndef __game__Tower_Section_h__
#define __game__Tower_Section_h__

#include <zenilib.h>

class Tower_Weapon;

class Tower_Section {
public:
	Tower_Section(const Zeni::Point3f& position_, const Zeni::Vector3f& size_, const Zeni::Quaternion& facing_ = Zeni::Quaternion(), Tower_Weapon * const weapon_ = nullptr);

	virtual ~Tower_Section()  = 0;

	virtual void render() const;

	virtual void on_logic(float time_step);

	Zeni::Point3f getPosition() const {return position;};
	Zeni::Vector3f getSize() const {return size;};
	Zeni::Quaternion getFacing() const {return facing;};

	void setSize(Zeni::Vector3f size_) {size = size_;};
	void setFacing(Zeni::Quaternion facing_) {facing = facing_;};

	Tower_Weapon* getWeapon() {return weapon;};
	void setWeapon(Tower_Weapon* weapon_) {weapon = weapon_};

private:
	Zeni::Point3f position;
	Zeni::Vector3f size;
	Zeni::Quaternion facing;

	Tower_Weapon* weapon;
};

#endif __game__Tower_Section_h__