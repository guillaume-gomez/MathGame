#ifndef GAME_H
#define GAME_H

#include <fstream>

#include "SFML/Graphics.hpp"

#include "Axis.hpp"
#include "ButtonAnim.hpp"
#include "../constants.hpp"
#include "Hero.hpp"
#include "../files.hpp"
#include "GravityCircle.hpp"
#include "Integral.hpp"
#include "../libs/TextAreaSFML2_0.hpp"
#include "ManageLevel.hpp"
#include "ScreenLink.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"



using namespace sf;

class Game
{
    public:
        TypeOfCamera m_typeOfCamera;

        RenderWindow &m_app;
        Game( RenderWindow& _app, Difficulty _diff = Normal );
        virtual ~Game();
        bool handleInput();
        void draw();
        void move();
        void zoom();
        void resetWindow();
        int levelOperation(ScreenLink& stat);
        void selectLevel(ScreenLink& stat);
        void show();
        void reset();
        void resize(float scaleX, float scaleY);
        void manageSound();
        inline bool isBacked()const { return m_isBack;};
        inline void setBack( bool _b){ m_isBack = _b;};
        inline void setZoom(bool _b){ m_isZoom = _b;};
        void setCenterCamera();
        void setGameMode( GameMode mode);
        GameMode getGameMode() const;
        void loadConfigFile();
        void cameraMoved();

    private:
        Game(const Game& orig);
        Axis m_axis;
        TextAreaSFML2_0 m_textAreaFunction;
        ManageLevel m_level;
        GameMode m_gameMode;
        ButtonPerso m_buttonReset;
        ButtonAnim m_buttonSound;
        ButtonPerso m_buttonBack;
        Curves m_curves;
    #ifdef DEBUG
        int m_frameCount;
        sf::Clock m_frameCountClock;
        sf::Text m_frameCountText;
    #endif
        Event m_event;
        bool m_gameStarted;
        bool m_isZoom;
        bool m_isSound;
        bool m_isBack;
        sf::Clock m_timer;
        Hero *m_player;
        Sprite m_spriteBG;
        View m_viewPerso;
        bool m_playerDead;

        ManageFunctions m_functionManager;
};

inline void Game::setGameMode( GameMode mode) {m_gameMode = mode;}

inline GameMode Game::getGameMode() const { return m_gameMode;}

#endif // GAME_H
