#ifndef SCREENLEVELCHOICE_H
#define SCREENLEVELCHOICE_H

#include <sstream>
#include <vector>

#include <SFGUI/SFGUI.hpp>

#include "../files.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "Screen.hpp"
#include "ScreenLink.hpp"


class SelectLevel
{
    public:
        friend class ScreenLevelChoice;
        SelectLevel(ScreenLink* _stat, unsigned int level = 1, Difficulty difficulty = Normal);
        ~SelectLevel();
        virtual void selectingLevel();
        inline void setGameMode(GameMode _g){m_modeSelectLevel = _g;};
        inline bool isClicked()const {return m_isClicked;};
        inline void unclicked(){ m_isClicked = false;};
    private:
        ScreenLink* m_stat;
        Difficulty m_difficulty;
        unsigned int m_level;
        GameMode m_modeSelectLevel;
        bool m_isClicked;
};

class ScreenLevelChoice : public Screen
{
    public:
        friend class SelectLevel;

        ScreenLevelChoice(ScreenLink* _stat);
        virtual ~ScreenLevelChoice();
        virtual int Run(sf::RenderWindow & App) = 0 ;

    protected:
        bool m_playing;
        std::vector<SelectLevel*> m_selectionLevel;
        int m_changingMenu;

        sf::Sprite m_background;
        sf::Sprite m_easyBar;
        sf::Texture m_easyTex;
        sfg::Frame::Ptr m_frameEasy;
        sfg::Frame::Ptr m_frameNormal;
        sfg::Frame::Ptr m_frameHard;
        sf::Sprite m_hardBar;
        sf::Texture m_hardTex;
        sf::Sprite m_normalBar;
        sf::Texture m_normalTex;
        sfg::Box::Ptr m_layoutEasy;
        sfg::Box::Ptr m_layoutNormal;
        sfg::Box::Ptr m_layoutHard;
        sfg::Box::Ptr m_scrolled_window_box;
        sfg::SFGUI m_sfgui;
        sfg::Window::Ptr m_window;
};
#endif // SCREENLEVELCHOICE_H
