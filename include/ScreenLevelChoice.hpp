#ifndef SCREENLEVELCHOICE_H
#define SCREENLEVELCHOICE_H

#include <SFGUI/SFGUI.hpp>

#include "../files.hpp"
#include "Screen.hpp"

#include "../libs/ResourcesManagerSFML2_1.hpp"
#include <sstream>
#include <vector>

#include "ScreenLink.hpp"

class SelectLevel
{
    public:
        friend class ScreenLevelChoice;
        SelectLevel( ScreenLink* _stat , unsigned int level = 1, Difficulty difficulty = Normal);
        ~SelectLevel();
        virtual void selectingLevel();
        inline void setGameMode(GameMode _g){ m_modeSelectLevel = _g;};
        inline bool isClicked()const {return m_isClicked;};
        inline bool unclicked(){ m_isClicked = false;};
    private:
        Difficulty m_difficulty;
        unsigned int m_level;
        bool m_isClicked;
        GameMode m_modeSelectLevel;
        ScreenLink* m_stat;
};

class ScreenLevelChoice : public Screen
{
    public:
        friend class SelectLevel;

        ScreenLevelChoice( ScreenLink* _stat);
        virtual ~ScreenLevelChoice();
        virtual int Run(sf::RenderWindow & App) = 0 ;

    protected:
        bool m_playing;
        //sfg::SFGUI m_sfgui;
        sfg::Window::Ptr m_window;

        sf::Sprite m_easyBar;
        sf::Sprite m_normalBar;
        sf::Sprite m_hardBar;

        sf::Texture m_easyTex;
        sf::Texture m_normalTex;
        sf::Texture m_hardTex;

        sf::Sprite m_background;
        sfg::Box::Ptr m_scrolled_window_box;

        sfg::Box::Ptr m_layoutEasy;
        sfg::Box::Ptr m_layoutNormal;
        sfg::Box::Ptr m_layoutHard;

        sfg::Frame::Ptr m_frameEasy;
        sfg::Frame::Ptr m_frameNormal;
        sfg::Frame::Ptr m_frameHard;
        int m_changingMenu;
        sfg::SFGUI sfgui;

        std::vector<SelectLevel*> m_selectionLevel;

};

#endif // SCREENLEVELCHOICE_H
