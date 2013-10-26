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

	const std::vector<std::shared_ptr<Game_Object> >& getEnemies() const {return enemies;};
    void pushEnemy(std::shared_ptr<Game_Object> enemy_) {enemies.push_back(enemy_);};
	void removeEnemy(std::shared_ptr<Game_Object> enemy);

	const std::vector<std::shared_ptr<Tower_Base> >& getBases() const {return towerBases;};
    void pushBase(std::shared_ptr<Tower_Base> base_) {towerBases.push_back(base_);};
    std::vector<std::shared_ptr<Game_Object> > getTowerParts() const;

	std::vector<Zeni::Point3f>& getPath() {return enemy_path;};

	Player* getPlayer() const {return player;};
	void setPlayer(Player* player_) {player = player_;};

	int getLivesMax() const {return livesMax;};
	int getLivesRemaining() const {return livesRemaining;};
	void setLivesRemaining(int amount) {livesRemaining = amount;};

	int getGold() {return gold;};
	void setGold(int amount) {gold = amount;};

	void enemyLeaked(std::shared_ptr<Game_Object> enemy);

	virtual std::shared_ptr<Zeni::Model> getModel() const = 0;

	virtual float getMaxDistance() {return 100.f;};

	static Game_Level* getCurrentLevel() {return currentLevel;};
	static void setCurrentLevel(Game_Level* level_) {if(currentLevel) delete currentLevel; currentLevel = level_;};

private:
	static Game_Level* currentLevel;

	Player* player;

	int livesMax;
	int livesRemaining;
	int gold;

	std::vector<Zeni::Point3f> enemy_path;

	std::vector<std::shared_ptr<Game_Object> > enemies;

	std::vector<std::shared_ptr<Tower_Base> > towerBases;
};

#endif