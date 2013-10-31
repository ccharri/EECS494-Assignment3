#ifndef __game__ZTDGUI_h__
#define __game__ZTDGUI_h__

#include <zenilib.h>
#include <memory>

#include "Game_Level.h"

class Play_State;
class Game_Object;
class Sell_Button;
class Tower_Section;
class Ready_Button;

class ZTDGUI
{
public:
	ZTDGUI(Play_State* state_);

	~ZTDGUI();

	void on_key(const SDL_KeyboardEvent &event);
	void on_mouse_button( const SDL_MouseButtonEvent &event);
	void on_mouse_motion(const SDL_MouseMotionEvent &event);
	void render();
	void on_logic(const Zeni::Projector3D& projector_);

	void lendWidget(Zeni::Widget *widget_);
	void unlendWidget(Zeni::Widget *widget_);
	void showSellButton(Tower_Section* section_);
	void hideSellButton();
	void sellButtonPressed(Tower_Section* section_);

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
    
	Sell_Button* sellButton;

    bool ignoreNextClick;

	void renderObjectAttributes(Zeni::Point2f upperLeft, std::shared_ptr<Game_Object> textObj);
	void renderPlayerAttributes(Zeni::Point2f upperLeft);
};


class Sell_Button : public Zeni::Text_Button
{
public:
	Sell_Button(ZTDGUI* gui_, Tower_Section* owner_ = nullptr, const Zeni::Point2f& upperLeft_ = Zeni::Point2f() , const Zeni::Point2f& lowerRight_ = Zeni::Point2f()) : Zeni::Text_Button(upperLeft_, lowerRight_, "system_36_800x600", Zeni::String("Sell")), gui(gui_), owner(owner_)
	{

	}

	void on_accept() override
	{
		gui->sellButtonPressed(owner);
	}

	void on_hover() override
	{

	}

	void setOwner(Tower_Section* owner_) {owner = owner_;};

private:
	ZTDGUI* gui;
	Tower_Section* owner;
};

#endif