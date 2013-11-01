//
//  Loss_Screen.h
//  game
//
//  Created by Christopher Harris on 10/31/13.
//
//

#ifndef __game__Loss_Screen__
#define __game__Loss_Screen__

#include <iostream>
#include <zenilib.h>

class Loss_Screen : public Zeni::Widget_Gamestate
{
public:
    Loss_Screen() : Zeni::Widget_Gamestate(std::make_pair(Zeni::Point2f(Zeni::get_Video().get_viewport().first), Zeni::Point2f(Zeni::get_Video().get_viewport().second))), continueButton(), quitButton()
    {
        m_widgets.lend_Widget(continueButton);
        m_widgets.lend_Widget(quitButton);
    }
    
    ~Loss_Screen() {
        m_widgets.unlend_Widget(continueButton);
        m_widgets.unlend_Widget(quitButton);
    };
    
    void render() override
    {
        Zeni::Font &fr = Zeni::get_Fonts()["title"];
        fr.render_text("You Lose",
                       Zeni::Point2f(Zeni::Window::get_width()/2., (Zeni::Window::get_height() - fr.get_text_height())/2.),
                       Zeni::get_Colors()["title_text"],
                       Zeni::ZENI_CENTER);
    
        Zeni::Widget_Gamestate::render();
    }

private:
    
    class Continue_Button : public Zeni::Text_Button
    {
    public:
        Continue_Button(const Zeni::Point2f &upper_left_ = Zeni::Point2f(100, Zeni::Window::get_height()/2. - 75),
                        const Zeni::Point2f &lower_right_ = Zeni::Point2f(300, Zeni::Window::get_height()/2. + 75))
        : Zeni::Text_Button(upper_left_, lower_right_, "system_24_800x600", "Continue")
        {
            
        }
        
        void on_accept() override
        {
            Zeni::get_Game().pop_state();
        }
    } continueButton;
    
    class Quit_Button : public Zeni::Text_Button
    {
    public:
        Quit_Button(const Zeni::Point2f &upper_left_ = Zeni::Point2f(Zeni::Window::get_width() - 300, Zeni::Window::get_height()/2. - 75),
                    const Zeni::Point2f &lower_right_ = Zeni::Point2f(Zeni::Window::get_width()-100, Zeni::Window::get_height()/2. + 75))
        : Zeni::Text_Button(upper_left_, lower_right_, "system_24_800x600", "Quit")
        {
            
        }
        
        void on_accept() override
        {
            Zeni::get_Game().pop_state();
            Zeni::get_Game().pop_state();
        }
    } quitButton;
};

#endif /* defined(__game__Loss_Screen__) */
