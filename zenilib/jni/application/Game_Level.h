#ifndef __game__Game_Level_h__
#define __game__Game_Level_h__

#include <zenilib.h>
#include <memory>

class Game_Object;
class Player;
class Tower_Base;

class Game_Level {
public:
	Game_Level();

	virtual ~Game_Level() = 0;

	virtual void render();

	virtual void on_logic(float time_step);

	std::vector<std::shared_ptr<Game_Object> >& getEnemies() {return enemies;};
	void removeEnemy(std::shared_ptr<Game_Object> enemy);

	std::vector<std::shared_ptr<Tower_Base> >& getBases() {return towerBases;};

	std::vector<Zeni::Point3f>& getPath() {return enemy_path;};

	Player* getPlayer() const {return player;};
	void setPlayer(Player* player_) {player = player_;};

	virtual Zeni::Model* getModel() = 0;

	virtual float getMaxDistance() {return 100.f;};

	static Game_Level* getCurrentLevel() {return currentLevel;};
	static void setCurrentLevel(Game_Level* level_) {if(currentLevel) delete currentLevel; currentLevel = level_;};

private:
	static Game_Level* currentLevel;

	Player* player;

	std::vector<Zeni::Point3f> enemy_path;

	std::vector<std::shared_ptr<Game_Object> > enemies;

	std::vector<std::shared_ptr<Tower_Base> > towerBases;
};

#endif