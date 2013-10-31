#ifndef __game__XML_Level_h__
#define __game__XML_Level_h__

#include "zenilib.h"

#include "Model_Wrapper.h"
#include "Game_Level.h"

class Enemy;
class Ready_Button;

class XML_Level : public Game_Level
{
	enum Enemy_Type_e {BASIC};
	struct Wave
	{
		int total;
		int spawned;
		float duration;
		float time_start;
		
		Zeni::String name;
		float health;
		float speed;
		int height;
		int bounty;
		int lifeCost;
		Zeni::Vector3f size;
		Enemy_Type_e type;

    std::shared_ptr<Zeni::Model> model;
		float scaling;

		Wave() : spawned(0), time_start(0), health(1), speed(10) {}

		bool canSpawn(float time_passed);
		bool isOver() {return total <= spawned;}
        std::shared_ptr<Enemy> spawnEnemy();
	};
	struct Round
	{
		int num;
		int goldBonus;

		Round() :  num(1), goldBonus(0) {}

		std::vector<Wave> waves;
	};

public:
	XML_Level(std::string xml, Play_State* state_);
	~XML_Level();

	std::shared_ptr<Zeni::Model> getModel() const override {return levelModel.getModel();};
	
	float getTimeUntilNextRound() const;
	void setTimeUntilNextRound(float f);
	void on_logic(float time_step) override;
	bool isRoundOver();

private:
	int levelNum;

	static Model_Wrapper levelModel;

	std::vector<Round> rounds;
	float roundTime;
	
	Ready_Button *readyButton;

	Zeni::Chronometer<Zeni::Time> nextRoundTimer;
	bool waiting;
	float nextRoundStartTime;
	float roundGapTime;

	void startRound();
	void endRound();

	std::string grabComment(const std::string &line);
	std::string grabValue(const std::string &line);
	Zeni::Point3f getPointFromValue(const std::string &value);
	Zeni::Vector3f getVectorFromValue(const std::string &value);
};

class Ready_Button : public Zeni::Text_Button
{
public:
	Ready_Button(const Zeni::Point2f& upperLeft_, const Zeni::Point2f& lowerRight_) 
		: Zeni::Text_Button(upperLeft_, lowerRight_, "system_24_800x600", "Ready")
	{}
    
	void on_accept() override
	{
		Game_Level::getCurrentLevel()->setTimeUntilNextRound(0.5);
		Zeni::Text_Button::on_accept();
	}
    
    void on_hover() override{    
    }
};

#endif