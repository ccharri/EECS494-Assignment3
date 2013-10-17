#ifndef __game__Play_State_h__
#define __game__Play_State_h__

#include "zenilib.h"
#include "Player.h"
#include "Game_Level.h"

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

    void perform_logic();

    void render();

  private:
		Zeni::Camera god_view;
		bool god_view_on;

		Player player;
    bool player_moved;

		Game_Level current_level;

		Zeni::Time_HQ time_passed;
};

#endif