
#include "XML_Level.h"

#include "Tower_Base.h"
#include "Basic_Enemy.h"
#include "Play_State.h"
#include <fstream>
#include <sstream>
#include <memory>


using namespace std;
using namespace Zeni;

Model_Wrapper XML_Level::levelModel("models/Crate.3ds");

XML_Level::XML_Level(string xml, Play_State* state_) : Game_Level(state_)
{
	string line;
	ifstream in;
	in.open(xml);
	
	readyButton = new Ready_Button(Point2f(20, 5 * 30), Point2f(160, 5 * 30 + 50));

	roundGapTime = 3;
	nextRoundTimer.start();
	
	while(getline(in, line))
	{
		string comment = grabComment(line);
		string value = grabValue(line);

		if(comment == "level num")
			levelNum = atoi(value.c_str());
		else if(comment == "level name")
			setLevelName(value);
		else if(comment  == "level model")
			levelModel = shared_ptr<Model>(new Model(Zeni::String("models/" + value)));
		else if("level lives" == comment)
		{
			setLivesMax(atoi(value.c_str()));
			setLivesRemaining(atoi(value.c_str()));
		}
		else if("round gap time" == comment)
			roundGapTime = atof(value.c_str());
		else if("initial gold" == comment)
			addGold(atoi(value.c_str()));
		else if(comment == "node")
			getPath().push_back(getPointFromValue(value));
		else if(comment == "base")
			pushBase(make_shared<Tower_Base>(getPointFromValue(value)));
		else if(comment == "round")
			rounds.emplace_back();
		else if(comment == "round num")
			rounds.back().num = atoi(value.c_str());
		else if(comment == "round bonus")
			rounds.back().goldBonus = atoi(value.c_str());
		else if(comment == "wave")
			rounds.back().waves.emplace_back();
		else if(comment == "total")
			rounds.back().waves.back().total = atoi(value.c_str());
		else if(comment == "duration")
			rounds.back().waves.back().duration = float(atof(value.c_str()));
		else if(comment == "time_start")
			rounds.back().waves.back().time_start = float(atof(value.c_str()));
		else if(comment == "name")
			rounds.back().waves.back().name = value;
		else if(comment == "health")
			rounds.back().waves.back().health = float(atof(value.c_str()));
		else if(comment == "speed")
			rounds.back().waves.back().speed = float(atof(value.c_str()));
		else if(comment == "size")
			rounds.back().waves.back().size = getVectorFromValue(value);
		else if(comment == "height")
			rounds.back().waves.back().height = atoi(value.c_str());
		else if(comment == "model")
			rounds.back().waves.back().model = shared_ptr<Zeni::Model>(new Model(Zeni::String("models/" + value)));
		else if(comment == "scaling")
			rounds.back().waves.back().scaling = float(atof(value.c_str()));
		else if(comment == "type")
		{
			if(value == "basic")
				rounds.back().waves.back().type = BASIC;
		}
		else if(comment == "bounty")
				rounds.back().waves.back().bounty = atoi(value.c_str());
		else if(comment == "life cost")
				rounds.back().waves.back().lifeCost = atoi(value.c_str());
	}
	in.close();
	setCurrentRound(0);
	startRound();
}

XML_Level::~XML_Level()
{
	delete readyButton;
}

bool XML_Level::Wave::canSpawn(float time_passed)
{
	return (time_passed - time_start) >= (duration / (total+1)) * spawned;
}

shared_ptr<Enemy> XML_Level::Wave::spawnEnemy()
{
	shared_ptr<Enemy> e;
	Point3f loc = Game_Level::getCurrentLevel()->getPath().front();
	loc.z += height;
	if(type == BASIC)
		e = shared_ptr<Enemy>(new Basic_Enemy(loc, speed, health, model));
	//other types
	e->setSize(size);
	e->setName(name);
	e->setBounty(bounty);
	e->setLeakAmount(lifeCost);
	e->setHeight(height);
	Game_Level::getCurrentLevel()->pushEnemy(e);
	spawned++;
	return e;
}

void XML_Level::startRound()
{
	roundTime = 0;
	waiting  = false;
	getState()->unlendWidget(*readyButton);
}

bool XML_Level::isRoundOver()
{
	if(getEnemies().size() != 0)
		return false;
	for(Wave &w : rounds[getCurrentRound()].waves)
		if(!w.isOver())
			return false;
	return true;
}

float XML_Level::getTimeUntilNextRound() const
{
	if(waiting == false)
		return 0;
	return nextRoundStartTime - nextRoundTimer.seconds();
}

void XML_Level::setTimeUntilNextRound(float f)
{
	nextRoundStartTime = nextRoundTimer.seconds() + f;
}

void XML_Level::endRound()
{
	//award bonus gold
	Game_Level::getCurrentLevel()->addGold(rounds[getCurrentRound()].goldBonus);
	waiting = true;
	getState()->lendWidget(*readyButton);
	nextRoundStartTime = roundGapTime + nextRoundTimer.seconds();
}

void XML_Level::on_logic(float time_step)
{
	Game_Level::on_logic(time_step);
	roundTime += time_step;

	if(isRoundOver())
	{
		endRound();
		setCurrentRound(getCurrentRound()+1);
		if(getCurrentRound() >= rounds.size())
		{
			//look, this line is totally stupid
			setCurrentRound(getCurrentRound()-1);
			//TODO: VICTORY CONDITION HERE
		}
	}
	if(waiting)
	{
		if(getTimeUntilNextRound() <= 0)
			startRound();
	}
	else
	{
		for(Wave &w : rounds[getCurrentRound()].waves)
		if(!w.isOver() && w.canSpawn(roundTime))
			w.spawnEnemy();
	}
}

string XML_Level::grabComment(const string &line)
{
	int start = line.find("<") + 1;
	int length = line.find(">") - line.find("<") - 1;
	return line.substr(start, length);
}
string XML_Level::grabValue(const string &line)
{
	// removes the comment
	int start = line.find("<");
	int end = line.find(">");
	string s = line.substr(0, start) + line.substr(end+1);
	// removes the whitespace
	size_t startPos = s.find_first_not_of(" \t\n");
	if(string::npos != startPos)
    s = s.substr(startPos);
	size_t endPos = s.find_last_not_of(" \t\n");
	if(string::npos != endPos)
    s = s.substr(0, endPos+1);
	return s;
}
Point3f XML_Level::getPointFromValue(const string &value)
{
	return Point3f(getVectorFromValue(value));
}
Vector3f XML_Level::getVectorFromValue(const string &value)
{
	int firstComma = value.find_first_of(',');
	int secondComma = value.find_last_of(',');
	float x = float(atof(value.substr(0, firstComma).c_str()));
	float y = float(atof(value.substr(firstComma+1, secondComma-firstComma).c_str()));
	float z = float(atof(value.substr(secondComma+1).c_str()));
	return Vector3f(x, y, z);
}