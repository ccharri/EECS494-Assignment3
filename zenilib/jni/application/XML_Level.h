#ifndef __game__XML_Level_h__
#define __game__XML_Level_h__

#include "zenilib.h"

#include "Model_Wrapper.h"
#include "Game_Level.h"

class Enemy;

class XML_Level : public Game_Level
{
	enum Enemy_Type_e {BASIC};
	struct Wave
	{
		int total;
		int spawned;
		float duration;
		float time_start;
		
		float health;
		float speed;
		int height;
		int bounty;
		int lives;
		Zeni::Vector3f size;
		Enemy_Type_e type;

		std::shared_ptr<Model_Wrapper> model;
		float scaling;

		Wave(){spawned = 0; time_start = 0; health = 1; speed = 10;}

		bool canSpawn(float time_passed);
		bool isOver() {return total <= spawned;}
		Enemy* spawnEnemy();
	};
	struct Round
	{
		int num;
		int goldBonus;

		Round(){goldBonus = 0; num = 1;}

		std::vector<Wave> waves;
	};

public:
	XML_Level(std::string xml);
	
	Zeni::Model* getModel() override {return levelModel.getModel();}
	void on_logic(float time_step) override;
	bool isRoundOver();

private:
	int levelNum;
	std::string levelName;

	Model_Wrapper levelModel;

	std::vector<Round> rounds;
	int currentRound;
	float levelTime;

	void startRound();
	void endRound();

	std::string grabComment(const std::string &line);
	std::string grabValue(const std::string &line);
	Zeni::Point3f getPointFromValue(const std::string &value);
	Zeni::Vector3f getVectorFromValue(const std::string &value);
};

#endif