#include "ZTDGUI.h"

#include "Game_Object.h"
#include "Game_Level.h"
#include "Utility.h"

using namespace Zeni;
using namespace std;

void ZTDGUI::on_key(const SDL_KeyboardEvent &event)
{

}

void ZTDGUI::on_mouse_button( const SDL_MouseButtonEvent &event )
{
	switch(event.button)
	{
		case 1:
			selectedObj = findMousedTarget();
			break;
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
		Zeni::Font &fr = get_Fonts()["title"];
		Zeni::Font &detailfont = get_Fonts()["system_36_800x600"];

		fr.render_text(
			textObj->getName(),
			Point2f(Window::get_width()/2., 0),
			get_Colors()["title_text"],
			ZENI_CENTER);
		
		Color primColor = textObj->getPrimaryColor();
		float primMax = textObj->getPrimaryAttributeMax();
		float primCur = textObj->getPrimaryAttributeCurrent();
		float primWidth = 300;
		float primHeight = 50;
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
}

void ZTDGUI::on_logic(const Projector3D& projector_)
{
	proj = projector_;
	highlightObj = findMousedTarget();
}

weak_ptr<Game_Object> ZTDGUI::findMousedTarget()
{
	Point3f closeMouseScreenPos = proj.unproject(Point3f(mousePos.x, mousePos.y, 0));
	Point3f farMouseScreenPos = proj.unproject(Point3f(mousePos.x, mousePos.y, 1));

	Collision::Infinite_Cylinder mouseRay(closeMouseScreenPos, farMouseScreenPos, 1. );
	auto collidingObjects = findCollidingObjects(mouseRay, Game_Level::getCurrentLevel()->getEnemies());
	return closestObjectMatching(closeMouseScreenPos, collidingObjects, [&](shared_ptr<Game_Object> object_) {return object_->isTargetable();});
}