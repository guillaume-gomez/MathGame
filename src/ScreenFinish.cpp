/*
 *  A 2D video game in C++ with SFML where platforms are actually Maths Curves resulting of equations you write
 *  Copyright (C) 2013,2017  Gomez Guillaume, Jarretier Adrien
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.*
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contact us on Github : https://github.com/guillaume-gomez/MathGame
 *                      or https://github.com/AdrienJarretier
 */

#include "ScreenFinish.hpp"

ScreenFinish::ScreenFinish()
{
    m_bg.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameBGFinish)));

    m_font.loadFromFile(FilenameFont);

    sf::Color color (112, 146, 190);

    m_stringList.push_back(sf::String("A video Game made by : Adrien Jarretier and Guillaume Gomez."));
    m_stringList.push_back(sf::String("I hope you enjoyed play this game as much we enjoy to develop it !"));
    m_stringList.push_back(sf::String("And thank you for have played this game fellow gamer :)"));

    for(auto index = 0 ; index < m_stringList.size(); ++index)
    {
        sf::Text newText;
                 newText.setFont(m_font);
                 newText.setString(m_stringList[index]);
                 newText.setColor(color);
                 newText.setCharacterSize(19);
                 unsigned int x = 20;
                 unsigned int y = WindowHeight / 2 - 100 + (50 * index);

           newText.setPosition((float)x, (float)y);
           m_textList.push_back(newText);
    }

}

ScreenFinish::~ScreenFinish()
{
    //dtor
}

 int ScreenFinish::Run(sf::RenderWindow & App)
 {
    bool Running = true;
    m_clock.restart();
    while(Running)
    {
         m_bg.setPosition(App.getSize().x/2 - m_bg.getGlobalBounds().width/2, App.getSize().y/2 - m_bg.getGlobalBounds().height/2);
         sf::Event event;
        //Verifing events
        while(App.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                Running = false;
                App.close();
            }

            if(event.type == sf::Event::KeyPressed)
            {
               if(event.key.code == sf::Keyboard::Escape)
               {
                   return MENU;
               }
            }

        }

        if(m_clock.getElapsedTime().asSeconds() > 10)
        {
            return MENU;
        }

    App.clear();
    App.draw(m_bg);
    for(auto index = 0 ; index < m_stringList.size(); ++index) {
        App.draw(m_textList[index]);
    }
    App.display();

    }

    return (SCREEN_EXIT);
 }
