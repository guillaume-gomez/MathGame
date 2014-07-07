#include "Screen_Game.hpp"

Screen_Game::Screen_Game(RenderWindow& _app, ScreenLink* _stat)
:m_game(new Game(_app)), m_stat(_stat)
{
    //to change the camera sets in m_game
    recenterCamera();
}

int Screen_Game::Run(sf::RenderWindow& App)
{
    #ifdef DEBUG
//        std::cout << std::endl << "---------- Screen_Game::Run ----------" << std::endl << std::endl;
    #endif // DEBUG
    try
    {
        if(m_game == 0)
        {
//            #ifdef DEBUG
//                std::cout << "m_game == 0" << std::endl;
//            #endif // DEBUG
            m_game = new Game(App);
        }

        bool Running = true;
         //temp
        m_game->setGameMode(GameMode::Classic);
        //
        m_game->loadConfigFile();
        m_game->selectLevel(*m_stat);
        int gameFinish = 0;
        m_game->setBack(false);
        m_game->setCenterCamera();
        m_game->setZoom(true);


        std::cout << App.getSize().x << "  "<< App.getSize().y << std::endl;
        m_game->resize(WindowWidth / App.getSize().x,  WindowHeight/ App.getSize().y);

        while(Running && gameFinish == 0)
        {
            /*if ( alpha < m_alpha_max)
            {
                alpha++;
            }*/
           Running =  m_game->handleInput();

            if(m_game->isBacked())
            {
                recenterCamera();
                Physics::Engine::getEngine()->cleanEngine();
                delete m_game;
                m_game = 0;
                return MENU;
            }
            gameFinish = m_game->levelOperation(*m_stat);
            if(gameFinish == -1)
            {
                return ENDING;
            }
            m_game->move();
            m_game->manageSound();
            m_game->show();
            m_game->draw();
            App.display();
        }
        return (SCREEN_EXIT);
    }
    catch(std::ios_base::failure& failure)
    {
        #ifdef DEBUG
//            std::cout << "Screen_Game Run" << std::endl;
            std::cerr << failure.what() << std::endl;
        #endif // DEBUG
        delete m_game;
        m_game=0;
    }
    catch(std::exception& e)
    {
        // std::cout << e.what() << std::endl;
    }
}


void Screen_Game::recenterCamera()
{
 #ifdef DEBUG
  //// std::cout << "caca" << std::endl;
 #endif
    sf::View   viewPerso = m_game->m_app.getView();
   viewPerso.reset(sf::FloatRect(0,0,WindowWidth, WindowHeight));
	m_game->m_app.setView(viewPerso);
}


Screen_Game::~Screen_Game()
{
    delete m_game;
    m_game=0;
}
