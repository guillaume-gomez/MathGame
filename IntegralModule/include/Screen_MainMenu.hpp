#ifndef SCREEN_MAINMENU_H
#define SCREEN_MAINMENU_H

#include <SFGUI/SFGUI.hpp>

#include "../libs/ResourcesManagerSFML2_1.hpp"

#include "../files.hpp"
#include "../constants.hpp"
#include "ScreenLink.hpp"
#include "Screen.hpp"

class Screen_MainMenu : public Screen
{
    public:
        Screen_MainMenu();
        virtual ~Screen_MainMenu();
        virtual int Run(sf::RenderWindow & App);

        void playButtonClick();
        void play2ButtonClick();
        void creditButtonClick();
        void editorButtonClick();
        void optionButtonClick();
    protected:
    private:
        int m_alpha_max;
        int m_alpha_div;
        bool m_playing;
        int m_changingMenu;
        sfg::Button::Ptr m_play_button;
        sfg::Button::Ptr m_play2_button;
        sfg::Button::Ptr m_credit_button;
        sfg::Button::Ptr m_editor_button;
        sfg::Button::Ptr m_option_button;
        sfg::Window::Ptr m_window;

        sf::Sprite m_background;

};

#endif // SCREEN_MAINMENU_H
