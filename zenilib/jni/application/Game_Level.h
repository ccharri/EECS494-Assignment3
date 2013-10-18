#ifndef __game__Game_Level_h__
#define __game__Game_Level_h__

#include <zenilib.h>

class Game_Object;
class Player;
class Tower_Base;

class Game_Level {
public:
	Game_Level();

	virtual ~Game_Level() = 0;

	virtual void render();

	virtual void on_logic(float time_step);

	std::vector<Game_Object*>& getEnemies() {return enemies;};
	void removeEnemy(Game_Object* enemy);

	std::vector<Tower_Base*>& getBases() {return towerBases;};

	Player* getPlayer() const {return player;};
	void setPlayer(Player* player_) {player = player_;};

	virtual Zeni::Model* getModel() = 0;

	static Game_Level* getCurrentLevel() {return currentLevel;};
	static void setCurrentLevel(Game_Level* level_) {if(currentLevel) delete currentLevel; currentLevel = level_;};

private:
	static Game_Level* currentLevel;

	Player* player;

	std::vector<Zeni::Point3f> enemy_path;

	std::vector<Game_Object*> enemies;

	std::vector<Tower_Base*> towerBases;
};

#endif