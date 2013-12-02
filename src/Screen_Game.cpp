#include "Screen_Game.hpp"

Screen_Game::Screen_Game(RenderWindow& _app, ScreenLink* _stat)
:m_game(_app), m_stat(_stat)
{
    //to change the camera sets in m_game
    recenterCamera();
}

int Screen_Game::Run(sf::RenderWindow& App)
{
    bool Running = true;
    m_game.loadConfigFile();
    m_game.selectLevel(*m_stat);
    int gameFinish = 0;
    m_game.setBack(false);
    m_game.setCenterCamera();
    m_game.setZoom(true);


    while(Running && gameFinish == 0)
    {

        /*if ( alpha < m_alpha_max)
        {
            alpha++;
        }*/
       Running =  m_game.handleInput();

        if(m_game.isBacked())
        {
            recenterCamera();
            return MENU;
        }
        gameFinish = m_game.levelOperation(*m_stat);
        if(gameFinish == -1)
        {
            return ENDING;
        }
        m_game.move();
        m_game.manageSound();
        m_game.show();
        m_game.draw();
        App.display();
    }
    return (SCREEN_EXIT);
}


void Screen_Game::recenterCamera()
{
    sf::View   viewPerso = m_game.m_app.getView();
   viewPerso.reset(sf::FloatRect(0,0,WindowWidth, WindowHeight));
	m_game.m_app.setView(viewPerso);
}


Screen_Game::~Screen_Game()
{

}
