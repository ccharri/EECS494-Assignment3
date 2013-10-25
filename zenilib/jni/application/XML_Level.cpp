
#include "XML_Level.h"

#include "Tower_Base.h"
#include "Basic_Enemy.h"
#include <fstream>
#include <sstream>


using namespace std;
using namespace Zeni;

XML_Level::XML_Level(string xml) : levelModel("models/Crate.3ds")
{
	string line;
	ifstream in;
	in.open(xml);
	
	while(getline(in, line))
	{
		string comment = grabComment(line);
		string value = grabValue(line);

		if(comment == "level num")
			levelNum = atoi(value.c_str());
		else if(comment == "level name")
			levelName = value;
		else if(comment  == "level model")
			levelModel = Model_Wrapper(Zeni::String("models/" + value));
		else if(comment == "node")
			getPath().push_back(getPointFromValue(value));
		else if(comment == "base")
			getBases().push_back(make_shared<Tower_Base>(getPointFromValue(value)));
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
			rounds.back().waves.back().model = shared_ptr<Model_Wrapper>(new Model_Wrapper(Zeni::String("models/" + value)));
		else if(comment == "scaling")
			rounds.back().waves.back().scaling = float(atof(value.c_str()));
		else if(comment == "type")
		{
			if(value == "basic")
				rounds.back().waves.back().type = BASIC;
		}
		else if(comment == "bounty")
				rounds.back().waves.back().bounty = atoi(value.c_str());
		else if(comment == "lives")
				rounds.back().waves.back().lives = atoi(value.c_str());
	}
	in.close();
	currentRound = 0;
	levelTime = 0;
	startRound();

}


bool XML_Level::Wave::canSpawn(float time_passed)
{
	cout << "s: " << spawned << " d: " << duration << "t: " << total << endl;
	return (time_passed - time_start) >= (duration / (total - 1)) * spawned;
}

Enemy* XML_Level::Wave::spawnEnemy()
{
	Enemy *e;
	if(type == BASIC)
		e = new Basic_Enemy(Game_Level::getCurrentLevel()->getPath().front(), speed, health, model);
	e->setSize(size);
	e->setName(name);
	e->setBounty(bounty);
	e->setLeakAmount(lives);
	Game_Level::getCurrentLevel()->getEnemies().push_back(shared_ptr<Enemy>(e));
	spawned++;
	return e;
	
}

void XML_Level::startRound()
{
	//display any data
	//add in level gap/spending time
}

bool XML_Level::isRoundOver()
{
	cout << "num: " << getEnemies().size() << endl;
	if(getEnemies().size() == 0)
		return false;
	for(Wave &w : rounds[currentRound].waves)
		if(!w.isOver())
			return false;
	return true;
}

void XML_Level::endRound()
{
	//award bonus gold


}

void XML_Level::on_logic(float time_step)
{
	Game_Level::on_logic(time_step);
	levelTime += time_step;

	for(Wave &w : rounds[currentRound].waves)
		if(!w.isOver() && w.canSpawn(levelTime))
			w.spawnEnemy();
	
	if(isRoundOver())
	{
		cout << "round ended: " << currentRound << endl; 
		endRound();
		currentRound++;
		if(currentRound >= rounds.size())
		{
			currentRound--;
		}
		startRound();
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
	cout << value << endl;
	return Vector3f(x, y, z);
}