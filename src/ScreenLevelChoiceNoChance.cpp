#include "ScreenLevelChoiceNoChance.hpp"

ScreenLevelChoiceNoChance::ScreenLevelChoiceNoChance(ScreenLink* _stat)
:ScreenLevelChoice(_stat)
{

}

ScreenLevelChoiceNoChance::~ScreenLevelChoiceNoChance()
{
    //dtor
}


int ScreenLevelChoiceNoChance::Run(sf::RenderWindow & App)
{
     bool Running = true;
//    int alpha = 0 ;

    /*if (m_playing)
    {
        alpha = m_alpha_max;
    }*/

    while( Running)
    {
         sf::Event event;
        //Verifing events
        while( App.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Running = false;
                App.close();
            }

            m_menu.handle_input(event);
            MovingMenu();
            m_menu.TimerOperation();

            if ( event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Return)
                {
                    for ( unsigned int i = 0 ; i < m_easyList.size() ; i++)
                    {

                        if ( m_easyList[i]->getAlpha() != Blur && m_easyList[i] == m_cursor->getButton())
                        {
                             m_stat->setParamLevel(Easy,i+1 , NoChance);


                               return GAME;

                        }
                    }

                    for ( unsigned int i = 0 ; i < m_normalList.size() ; i++)
                    {
                        if (m_normalList[i]->getAlpha() != Blur  && m_normalList[i] == m_cursor->getButton())
                        {
                            m_stat->setParamLevel(Normal,i+1,NoChance);


                               return GAME;

                        }
                    }


                    for ( unsigned int i = 0 ; i < m_hardList.size() ; i++)
                    {
                        if ( m_hardList[i]->getAlpha() != Blur &&  m_hardList[i] == m_cursor->getButton())
                        {
                            m_stat->setParamLevel(Hard,i+1,NoChance);


                               return GAME;

                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    return MENU;
                }
            }

        }


    /*if ( alpha < m_alpha_max)
    {
        alpha++;
    }*/

    App.clear();
    App.draw(m_background);
    App.draw(m_easyBar);
    App.draw(m_normalBar);
    App.draw(m_hardBar);
    m_menu.Draw(App);
    App.display();

    }

    return (SCREEN_EXIT);
}
