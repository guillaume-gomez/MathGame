#ifndef SCREEN_GAME_H
#define SCREEN_GAME_H

#include "Game.hpp"
#include "Screen.hpp"
#include "ScreenLink.hpp"

class Screen_Game : public Screen
{
    public:
        Screen_Game(RenderWindow& _app,  ScreenLink* _stat);
        virtual ~Screen_Game();
        int Run(sf::RenderWindow& App);
        void recenterCamera();
    private:
        Game *m_game;
        ScreenLink *m_stat;
};

#endif // SCREEN_GAME_H
