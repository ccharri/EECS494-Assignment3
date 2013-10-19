#include "Tower_Base.h"

#include <algorithm>
#include "Tower_Section.h"

using namespace Zeni;
using namespace std;


Model_Wrapper Tower_Base::model = Model_Wrapper("models/Tower_Base.3ds");

Tower_Base::~Tower_Base() 
{

}

float Tower_Base::getNextSectionZ() const
{
	return segments.size();
}

void Tower_Base::pushSection(Tower_Section *section_)
{
	Point3f newPos(getPosition().x, getPosition().y, getNextSectionZ());
	section_->setPosition(newPos);
	segments.push_back(section_);
}

void Tower_Base::on_logic(float time_step)
{
	for_each(segments.begin(), segments.end(), [&](Tower_Section* section_) {
		section_->on_logic(time_step);
	});

}

void Tower_Base::render()
{
	getModel()->render();

	for_each(segments.begin(), segments.end(), [&](Tower_Section* section_) {
		section_->render();
	});
}