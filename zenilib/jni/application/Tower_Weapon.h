#ifndef __game__Tower_Weapon_h__
#define __game__Tower_Weapon_h__

#include <zenilib.h>
#include <memory>

#include "Game_Object.h"

class Tower_Section;

class Tower_Weapon : public std::enable_shared_from_this<Tower_Weapon> /* : public Game_Object*/
{
public:
	Tower_Weapon(std::weak_ptr<Tower_Section> owner_, float cooldown_);

	~Tower_Weapon();

	std::shared_ptr<Tower_Section> getSection() const {return owner.lock();};
	void setSection(std::shared_ptr<Tower_Section> section_) {owner = section_;};

	std::shared_ptr<Game_Object> getTarget() const {return target.lock();};
	void setTarget(std::shared_ptr<Game_Object> target_) {target = target_;};

	bool hasProjectiles() {return projectiles.empty();}
	void addProjectile(std::shared_ptr<Game_Object> p) {projectiles.push_back(p);}
	std::vector<std::shared_ptr<Game_Object> >& getProjectiles() {return projectiles;};
	void removeProjectile(std::shared_ptr<Game_Object> projectile_);

	virtual bool canFire(std::shared_ptr<Game_Object> object);

	virtual float getCooldown() const {return cooldown;};
	virtual float getCooldownRemaining() const
    {
        float cd = (last_fired_time + cooldown) - fireTimer.seconds();
        return cd < 0 ? cooldown : cd;
    };

	virtual void on_logic(float time_step) /*override*/;
	virtual void render() /*override*/;

	virtual void fire();

private:
	std::weak_ptr<Tower_Section> owner;

	std::weak_ptr<Game_Object> target;
	std::vector<std::shared_ptr<Game_Object> > projectiles;

	Zeni::Chronometer<Zeni::Time> fireTimer;
	float cooldown;
	float last_fired_time;
};

#endif