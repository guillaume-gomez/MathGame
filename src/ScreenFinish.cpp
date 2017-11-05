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
    m_font.loadFromFile(FilenameFont);

    sf::Color color (31, 41, 46);

    m_stringList.push_back(sf::String("A video Game made by : Adrien Jarretier and Guillaume Gomez."));
    m_stringList.push_back(sf::String("I hope you enjoyed playing this game as much we enjoyed developing it !"));
    m_stringList.push_back(sf::String("Thank you fellow gamer :)"));

    for(auto index = 0 ; index < m_stringList.size(); ++index)
    {
        sf::Text newText;
                 newText.setFont(m_font);
                 newText.setString(m_stringList[index]);
                 newText.setColor(color);
                 newText.setCharacterSize(17);
                 unsigned int x = 40;
                 unsigned int y = WindowHeight / 2 - 80 + (60 * index);

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
    bool running = true;
    m_clock.restart();
    while(running)
    {
         sf::Event event;
        //Verifing events
        while(App.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                running = false;
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

    App.clear(sf::Color(207,216,220));
    for(auto index = 0 ; index < m_stringList.size(); ++index) {
        App.draw(m_textList[index]);
    }
    App.display();

    }

    return (SCREEN_EXIT);
 }
