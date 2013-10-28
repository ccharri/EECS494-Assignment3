#ifndef __game__ZTDGUI_h__
#define __game__ZTDGUI_h__

#include <zenilib.h>
#include <memory>

class Play_State;
class Game_Object;

class ZTDGUI
{
public:
	ZTDGUI(Play_State* state_) : playState(state_), ignoreNextClick(false) {};

	~ZTDGUI() {};

	void on_key(const SDL_KeyboardEvent &event);
	void on_mouse_button( const SDL_MouseButtonEvent &event);
	void on_mouse_motion(const SDL_MouseMotionEvent &event);
	void render();
	void on_logic(const Zeni::Projector3D& projector_);

	void lendWidget(Zeni::Widget &widget_);
	void unlendWidget(Zeni::Widget &widget_);

	const Play_State* const getState() const {return playState;};

	const Zeni::Point2f& getMousePos() const {return mousePos;};
    
    void markIgnoreNextClick() {ignoreNextClick = true;};

private:
	Zeni::Projector3D proj;
	Play_State* playState;

	std::weak_ptr<Game_Object> highlightObj;
	std::weak_ptr<Game_Object> selectedObj;

	std::weak_ptr<Game_Object> findMousedTarget();

	Zeni::Point2f mousePos;
    
    bool ignoreNextClick;

	void renderPlayerAttributes(Zeni::Point2f upperLeft);
};

#endif