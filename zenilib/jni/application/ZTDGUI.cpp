#include "ZTDGUI.h"

#include "Game_Object.h"
#include "Game_Level.h"
#include "Play_State.h"
#include "Tower_Section.h"
#include "Tower_Weapon.h"
#include "Utility.h"

using namespace Zeni;
using namespace std;


ZTDGUI::ZTDGUI(Play_State* state_) : playState(state_), ignoreNextClick(false), renderTowerInfo(false)
{
	sellButton = new Sell_Button(this, nullptr, Point2f(25, Window::get_height()/2. - 50), Point2f(125, Window::get_height()/2. + 50));
}

ZTDGUI::~ZTDGUI()
{
	delete sellButton;
}

void ZTDGUI::on_key(const SDL_KeyboardEvent &event)
{

}

void ZTDGUI::on_mouse_button( const SDL_MouseButtonEvent &event )
{
	if(event.state == SDL_PRESSED)return;
    if(ignoreNextClick)
	{ 
		ignoreNextClick=false;
		playState->unlendWidget(*sellButton);
		return;
	}
    
	switch(event.button)
	{
		case 1:
		{
			auto prevSelect = selectedObj;
			selectedObj = findMousedTarget();

			auto prevSelectObj = prevSelect.lock();
			auto selectObj = selectedObj.lock();

			if(prevSelectObj)
			{
				//If there was an object selected before click, and still is one now
				if(selectObj)
				{
					//If different, deselect old, select new
					if(!(prevSelectObj == selectObj))
					{
						prevSelectObj->onDeselection(this);
						selectObj->onSelection(this);
					}
				}
				//Otherwise, we know there was previous, and is not now
				else
				{
					prevSelectObj->onDeselection(this);
				}
			}
			else {
				if(selectObj)
				{
					selectObj->onSelection(this);
				}
			}

			break;
		}
		case 3:
		{
			auto selectObj = selectedObj.lock();

			if(!selectObj) return;

			auto attackTargetWeak = findMousedTarget();
			auto attackTarget = attackTargetWeak.lock();

			if(!attackTarget) return;

			auto towerSegment = dynamic_pointer_cast<Tower_Section>(selectObj);

			if(!towerSegment) return;

			auto towerWeapon = towerSegment->getWeapon();
			if(towerWeapon->canFire(attackTarget))
			{
				towerWeapon->setTarget(attackTarget);
			}
		}
		default:
			break;
	}
}

void ZTDGUI::on_mouse_motion(const SDL_MouseMotionEvent &event)
{
	mousePos = Point2f(event.x, event.y);
}

void ZTDGUI::render()
{
	
	shared_ptr<Game_Object> highObj = highlightObj.lock();
	shared_ptr<Game_Object> targetObj = selectedObj.lock();
	shared_ptr<Game_Object> textObj = targetObj ? targetObj : highObj;

	renderPlayerAttributes(Point2f(10, 10));

	if(highObj)
	{
		Point3f screenPosProj = proj.project(highObj->getPosition());
		Point2f screenPos(screenPosProj.x, screenPosProj.y);
		Vector2f size(64, 64);
		render_image("selection", screenPos - size/2., screenPos + size/2.);
	}

	if(targetObj)
	{
		Point3f screenPosProj = proj.project(targetObj->getPosition());
		Point2f screenPos(screenPosProj.x, screenPosProj.y);
		Vector2f size(64, 64);
		render_image("selection", screenPos - size/2., screenPos + size/2., false, Color(1.f, 1.f, 0.f, 0.f));
	}

	if(textObj)
	{
		renderObjectAttributes(Point2f(500, 500), textObj);
	}
    
    if(renderTowerInfo)
    {
        renderTowerInformation(Point2f(10, Window::get_height()*.7));
    }
}

void ZTDGUI::on_logic(const Projector3D& projector_)
{
	proj = projector_;
	highlightObj = findMousedTarget();

	if(!selectedObj.lock())
	{
		playState->unlendWidget(*sellButton);
	}
}

void ZTDGUI::lendWidget(Zeni::Widget *widget_)
{
	playState->lendWidget(*widget_);
}

void ZTDGUI::unlendWidget(Zeni::Widget *widget_)
{
	playState->unlendWidget(*widget_);
}

void ZTDGUI::showSellButton(Tower_Section* section_)
{
	playState->lendWidget(*sellButton);
	sellButton->setOwner(section_);
}

void ZTDGUI::hideSellButton()
{
}

void ZTDGUI::sellButtonPressed(Tower_Section* section_)
{
	hideSellButton();
	section_->onSell();
}


weak_ptr<Game_Object> ZTDGUI::findMousedTarget()
{
	Point3f closeMouseScreenPos = proj.unproject(Point3f(mousePos.x, mousePos.y, 0));
	Point3f farMouseScreenPos = proj.unproject(Point3f(mousePos.x, mousePos.y, 1));

	Collision::Infinite_Cylinder mouseRay(closeMouseScreenPos, farMouseScreenPos, 1. );
    auto collidingObjects = findCollidingObjects(mouseRay, Game_Level::getCurrentLevel()->getTowerParts());
    auto collidedObject = closestObjectMatching(closeMouseScreenPos, collidingObjects, [&](shared_ptr<Game_Object> object_) {return object_->isTargetable();});;
    if(!collidedObject)
    {
        collidingObjects = findCollidingObjects(mouseRay, Game_Level::getCurrentLevel()->getEnemies());
        collidedObject = closestObjectMatching(closeMouseScreenPos, collidingObjects, [&](shared_ptr<Game_Object> object_) {return object_->isTargetable();});
    }
    
	return collidedObject;
}

void ZTDGUI::renderObjectAttributes(Point2f upperLeft, shared_ptr<Game_Object> textObj)
{
	Zeni::Font &fr = get_Fonts()["system_36_800x600"];
	Zeni::Font &detailfont = get_Fonts()["system_24_800x600"];

	fr.render_text(
		textObj->getName(),
		Point2f(Window::get_width()/2., 0),
		get_Colors()["title_text"],
		ZENI_CENTER);
		
	Color primColor = textObj->getPrimaryColor();
	float primMax = textObj->getPrimaryAttributeMax();
	float primCur = textObj->getPrimaryAttributeCurrent();
	float primWidth = 240;
	float primHeight = 40;
	Point2f ulp((Window::get_width() - primWidth)/2. ,fr.get_text_height());
	Point2f lrp((Window::get_width() - primWidth)/2. + (300 * primCur / primMax), fr.get_text_height() + primHeight);
	
	Vertex2f_Color ul, ll, lr, ur;
	ul = Vertex2f_Color(ulp, primColor);
	ll = Vertex2f_Color(ulp + Vector2f(0, primHeight), primColor);
	lr = Vertex2f_Color(lrp, primColor);
	ur = Vertex2f_Color(lrp - Vector2f(0, primHeight), primColor);
	Quadrilateral<Vertex2f_Color> primQuad(ul, ll, lr, ur);
		
	get_Video().render(primQuad);

	detailfont.render_text(
		ftoa(primCur, 3) + "/" + ftoa(primMax, 3),
		Point2f(Window::get_width()/2., (ulp.y + lrp.y)/2.),
		get_Colors()["title_text"],
		ZENI_CENTER
		);
}

void ZTDGUI::renderPlayerAttributes(Point2f upperLeft)
{
    Zeni::Font &super = get_Fonts()["title"];
	Zeni::Font &sub = get_Fonts()["system_24_800x600"];
    
	//renders gold, lives, level, and level name
	// render gold & lives
	Vector2f size(160, 5 * sub.get_text_height());
	render_image("selection", upperLeft, upperLeft+size);

	sub.render_text(
		String(Game_Level::getCurrentLevel()->getLevelName()),
		upperLeft + Point2f(20, 10),
		get_Colors()["title_text"],
		ZENI_LEFT);
	sub.render_text(
		String("Round: ") + String(to_string(Game_Level::getCurrentLevel()->getCurrentRound())),
		upperLeft + Point2f(20, 30),
		get_Colors()["title_text"],
		ZENI_LEFT);
	sub.render_text(
        String("Gold:  ") + String(to_string(Game_Level::getCurrentLevel()->getGold())),
		upperLeft + Point2f(20, 50),
		get_Colors()["title_text"],
		ZENI_LEFT);
	sub.render_text(
		String("Lives: ") + String(to_string(Game_Level::getCurrentLevel()->getLivesRemaining())),
		upperLeft + Point2f(20, 70),
		get_Colors()["title_text"],
		ZENI_LEFT);
	sub.render_text(
		String("Time:  ") + String(to_string(int(Game_Level::getCurrentLevel()->getTimeUntilNextRound()))),
		upperLeft + Point2f(20, 90),
		get_Colors()["title_text"],
		ZENI_LEFT);
}

void ZTDGUI::renderTowerInformation(Zeni::Point2f upperLeft)
{
    Zeni::Font &sub = get_Fonts()["system_24_800x600"];
    
    sub.render_text(towerDescription, upperLeft, get_Colors()["title_text"], ZENI_LEFT);
}
