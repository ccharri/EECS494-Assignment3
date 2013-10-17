#include "Tower_Base.h"


void Tower_Base::pushSection(Tower_Section *section_){
	Zeni::Point3f newPos(getPosition().x, getPosition().y, getNextSectionZ());
	section_->setPosition(newPos);
}