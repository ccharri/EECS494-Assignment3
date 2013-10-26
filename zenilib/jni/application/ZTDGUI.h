#ifndef __game__ZTDGUI_h__
#define __game__ZTDGUI_h__

#include <zenilib.h>
#include <memory>

class Game_Object;

class ZTDGUI
{
public:
	ZTDGUI() {};

	~ZTDGUI() {};

	void on_key(const SDL_KeyboardEvent &event);
	void on_mouse_button( const SDL_MouseButtonEvent &event);
	void on_mouse_motion(const SDL_MouseMotionEvent &event);
	void render();
	void on_logic(const Zeni::Projector3D& projector_);

	const Zeni::Point2f& getMousePos() const {return mousePos;};

private:
	Zeni::Projector3D proj;

	std::weak_ptr<Game_Object> highlightObj;
	std::weak_ptr<Game_Object> selectedObj;

	std::weak_ptr<Game_Object> findMousedTarget();

	Zeni::Point2f mousePos;

	void renderPlayerAttributes(Zeni::Point2f upperLeft);
};

#endif