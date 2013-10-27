#ifndef __game__Game_Level_h__
#define __game__Game_Level_h__

#include <zenilib.h>
#include <memory>

class Game_Object;
class Player;
class Tower_Base;
class Enemy;

class Game_Level {
public:
	Game_Level();
	virtual ~Game_Level() = 0;

	virtual void render();

	virtual void on_logic(float time_step);

	void enemyLeaked(std::shared_ptr<Enemy> enemy);

	const std::vector<std::shared_ptr<Enemy> >& getEnemies() const {return enemies;};
    const std::vector<std::shared_ptr<Game_Object> > getEnemyObjs() const;
    void pushEnemy(std::shared_ptr<Enemy> enemy_) {enemies.push_back(enemy_);};
	void removeEnemy(std::shared_ptr<Enemy> enemy);

	const std::vector<std::shared_ptr<Tower_Base> >& getBases() const {return towerBases;};
    void pushBase(std::shared_ptr<Tower_Base> base_) {towerBases.push_back(base_);};
    std::vector<std::shared_ptr<Game_Object> > getTowerParts() const;

	std::vector<Zeni::Point3f>& getPath() {return enemy_path;};

	virtual std::shared_ptr<Zeni::Model> getModel() const = 0;

	virtual float getMaxDistance() {return 100.f;};

	// getters and setters
	virtual float getTimeUntilNextRound() const = 0;

	Player* getPlayer() const {return player;};
	void setPlayer(Player* player_) {player = player_;};

	static Game_Level* getCurrentLevel() {return currentLevel;};
	static void setCurrentLevel(Game_Level* level_) {if(currentLevel) delete currentLevel; currentLevel = level_;};

	int getLivesMax() const {return livesMax;};
	void setLivesMax(int i) { livesMax = i;};

	int getLivesRemaining() const {return livesRemaining;};
	void setLivesRemaining(int amount) {livesRemaining = amount;};

	int getGold() const {return gold;};
	void addGold(int amount) {gold += amount;};

	int getCurrentRound() {return currentRound;}
	void setCurrentRound(int i) {currentRound = i;}

	std::string getLevelName() {return name;}
	void setLevelName(std::string s) {name = s;}

private:
	static Game_Level* currentLevel;
	Player* player;

	int livesMax;
	int livesRemaining;
	int gold;

	std::vector<Zeni::Point3f> enemy_path;

	std::vector<std::shared_ptr<Enemy> > enemies;

	std::vector<std::shared_ptr<Tower_Base> > towerBases;

	
	int currentRound;
	std::string name;
};

#endif