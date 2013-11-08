#ifndef SCREEN_MAINMENU_H
#define SCREEN_MAINMENU_H

#include "../libs/Menu.hpp"
#include "../libs/Cursor.hpp"
#include "../libs/Button.hpp"
#include "../libs/ResourcesManagerSFML2_0.hpp"

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
    protected:
    private:
        int m_alpha_max;
        int m_alpha_div;
        bool m_playing;
        Cursor *m_cursor;
        Menu m_menu;
        Button * m_play_button ;
        Button * m_play2_button;
        Button * m_credit_button ;
        Button * m_editor_button ;
        Button * m_option_button;

        sf::Sprite m_background;

};

#endif // SCREEN_MAINMENU_H
