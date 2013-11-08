#ifndef SCREENLEVELCHOICE_H
#define SCREENLEVELCHOICE_H

#include "../libs/Menu.hpp"
#include "../libs/Cursor.hpp"
#include "../libs/Button.hpp"
#include "../files.hpp"
#include "Screen.hpp"

#include "../libs/ResourcesManagerSFML2_0.hpp"
#include <sstream>
#include <vector>

#include "ScreenLink.hpp"

class ScreenLevelChoice : public Screen
{
    public:
        ScreenLevelChoice( ScreenLink* _stat);
        virtual ~ScreenLevelChoice();
        virtual int Run(sf::RenderWindow & App) = 0 ;
        void MovingMenu();
    protected:
        //ScreenLevelChoice();
        bool m_playing;
        Cursor *m_cursor;
        Menu m_menu;

        std::vector<Button*> m_easyList ;
        std::vector<Button*> m_normalList ;
        std::vector<Button*> m_hardList ;

        sf::Sprite m_easyBar;
        sf::Sprite m_normalBar;
        sf::Sprite m_hardBar;

        sf::Texture m_easyTex;
        sf::Texture m_normalTex;
        sf::Texture m_hardTex;

        sf::Sprite m_background;

        ScreenLink* m_stat;

        unsigned int m_nbDifficulty;

};

#endif // SCREENLEVELCHOICE_H
