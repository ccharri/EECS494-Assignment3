//
//  Win_Screen.c
//  game
//
//  Created by Christopher Harris on 10/31/13.
//
//

#ifndef __game__Win_Screen_h__
#define __game__Win_Screen_h__

#include <zenilib.h>

class Win_Screen : public Zeni::Widget_Gamestate
{
public:
    Win_Screen() : Zeni::Widget_Gamestate(std::make_pair(Zeni::Point2f(Zeni::get_Video().get_viewport().first), Zeni::Point2f(Zeni::get_Video().get_viewport().second))), quitButton()
    {
        m_widgets.lend_Widget(quitButton);
    }
    
    ~Win_Screen() {
        m_widgets.unlend_Widget(quitButton);
    };
    
    void render() override
    {
        Zeni::Font &fr = Zeni::get_Fonts()["title"];
        fr.render_text("You Win!",
                       Zeni::Point2f(Zeni::Window::get_width()/2., (Zeni::Window::get_height() - fr.get_text_height())/2.),
                       Zeni::get_Colors()["title_text"],
                       Zeni::ZENI_CENTER);
        
        Zeni::Widget_Gamestate::render();
    }
    
private:
    
    class Quit_Button : public Zeni::Text_Button
    {
    public:
        Quit_Button(const Zeni::Point2f &upper_left_ = Zeni::Point2f(Zeni::Window::get_width()/2. - 300, Zeni::Window::get_height()/2. + 75),
                    const Zeni::Point2f &lower_right_ = Zeni::Point2f(Zeni::Window::get_width()/2. + 300, Zeni::Window::get_height()/2. + 225))
        : Zeni::Text_Button(upper_left_, lower_right_, "system_24_800x600", "Exit")
        {
            
        }
        
        void on_accept() override
        {
            Zeni::get_Game().pop_state();
        }
    } quitButton;
};

#endif

