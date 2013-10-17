#include "Tower_Base.h"

#include "Tower_Section.h"

using namespace Zeni;
using namespace std;

void Tower_Base::pushSection(Tower_Section *section_)
{
	Point3f newPos(getPosition().x, getPosition().y, getNextSectionZ());
	section_->setPosition(newPos);
}