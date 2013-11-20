#include "ScreenFinish.hpp"

ScreenFinish::ScreenFinish()
{
//    m_texture.loadFromFile(FilenameBGFinish);
//    m_bg.setTexture(m_texture);

   m_bg.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameBGFinish)));
}

ScreenFinish::~ScreenFinish()
{
    //dtor
}

 int ScreenFinish::Run(sf::RenderWindow & App)
 {
    bool Running = true;
    m_clock.restart();
    while( Running)
    {
         m_bg.setPosition(App.getSize().x/2 - m_bg.getGlobalBounds().width/2, App.getSize().y/2 - m_bg.getGlobalBounds().height/2);
         sf::Event event;
        //Verifing events
        while( App.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Running = false;
                App.close();
            }

            if ( event.type == sf::Event::KeyPressed)
            {
               if (event.key.code == sf::Keyboard::Escape)
               {
                   return MENU;
               }
            }

        }

        if (m_clock.getElapsedTime().asSeconds() > 10)
        {
            return MENU;
        }

    App.clear();
    App.draw(m_bg);
    App.display();

    }

    return (SCREEN_EXIT);
 }
