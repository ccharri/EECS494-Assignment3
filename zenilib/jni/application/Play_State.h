#ifndef __game__Play_State_h__
#define __game__Play_State_h__

#include "zenilib.h"
#include <memory>
#include "ZTDGUI.h"
//#include "Player.h"

class Game_Object;

class Play_State : public Zeni::Gamestate_Base {
    struct Controls {
      Controls() : forward(false), left(false), back(false), right(false) {}

      bool forward;
      bool left;
      bool back;
      bool right;
    } movement_controls;

  public:
    Play_State();

    void on_push();
		void on_pop();
    void on_key(const SDL_KeyboardEvent &event);
    void on_mouse_motion(const SDL_MouseMotionEvent &event);
		void on_mouse_wheel(const SDL_MouseWheelEvent &event);

		int getGold() {return gold;}
		int incrementGold(int delta) {gold += delta;}
		int setGold(int amount) {gold = amount;}
		int getLives() {return lives;}
		int decrementLives(int delta) {lives -= delta;}
		int setLives(int amount) {lives = amount;}

    void perform_logic();

		void performMovement(float time_step);

    void render();

	virtual void on_mouse_button( const SDL_MouseButtonEvent &event );

  private:
		Zeni::Projector3D proj;

		Zeni::Light worldLight;
		Zeni::Light backLight;
		Zeni::Camera god_view;
		bool god_view_on;

		ZTDGUI gui;

		int gold;
		int lives;

		float time_since_last_spawn;

		//Player player;
		bool player_moved;

		Zeni::Time_HQ time_passed;
};

#endif