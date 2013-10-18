#ifndef __game__Tower_Weapon_h__
#define __game__Tower_Weapon_h__

#include <zenilib.h>

class Game_Object;
class Tower_Section;

class Tower_Weapon
{
public:
	Tower_Weapon(Tower_Section* owner_, float cooldown_);

	~Tower_Weapon();

	Tower_Section* getSection() const {return owner;};
	void setSection(Tower_Section* section_) {owner = section_;};

	Game_Object* getTarget() const {return target;};
	void setTarget(Game_Object* target_) {target = target_;};

	bool hasProjectiles() {return projectiles.empty();}
	void addProjectile(Game_Object *p) {projectiles.push_back(p);}

	virtual bool canFire(Game_Object* object);

	virtual void on_logic(float time_step);

	virtual void fire();

private:
	Tower_Section* owner;

	Game_Object* target;
	std::vector<Game_Object*> projectiles;

	Zeni::Chronometer<Zeni::Time> fireTimer;
	float cooldown;
	float last_fired_time;
};

#endif