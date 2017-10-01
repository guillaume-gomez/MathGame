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

#include <vector>
#include <SFML/Graphics.hpp>

#include <iostream>
using namespace sf;

#include "constants.hpp"
#include "files.hpp"

#include "ObjectFactoryAbstract.hpp"
#include "Screen_MainMenu.hpp"
#include "ScreenLevelChoiceClassic.hpp"
#include "ScreenLevelChoiceNoChance.hpp"
#include "Screen_Game.hpp"
#include "ScreenOption.hpp"
#include "Screen_Editor.hpp"
#include "ScreenFinish.hpp"
#include "ScreenCredit.hpp"
#include "ScreenHowTo.hpp"

#include "Game.hpp"

int main()
{
    ObjectFactoryAbstract::_register(TypeObject::Circle,new GravityCircle());
    ObjectFactoryAbstract::_register(TypeObject::Point,new Point(sizePoint));
    ObjectFactoryAbstract::_register(TypeObject::GoalPoint,new Point(sizePoint, true));
    ObjectFactoryAbstract::_register(TypeObject::Enemy,new Enemy());
    ObjectFactoryAbstract::_register(TypeObject::Integral,new Integral());
    ObjectFactoryAbstract::_register(TypeObject::Function,new Curves());
    ObjectFactoryAbstract::_register(TypeObject::Info,new InfoDisplayer());

    ContextSettings contextPerso(0, 0, 2);

    RenderWindow App(VideoMode(WindowWidth, WindowHeight),"I Hate Maths",sf::Style::Default, contextPerso);

    std::vector<Screen*> screens;
    int screen = 0 ;

    ScreenLink *stat = new ScreenLink();

    //building intancies
    Screen_MainMenu mainMenu;
    screens.push_back(&mainMenu);
    ScreenLevelChoiceClassic levelChoiceClassic(stat);
    screens.push_back(&levelChoiceClassic);
    ScreenLevelChoiceNoChance levelChoiceNoChance(stat);
    screens.push_back(&levelChoiceNoChance);
    Screen_Game game(App,stat);
    screens.push_back(&game);
    Screen_Editor screenEditor(App,stat);
    screens.push_back(&screenEditor);
    ScreenOption screenOption(2);
    screens.push_back(&screenOption);
    ScreenCredit screenCredit;
    screens.push_back(&screenCredit);
    ScreenFinish screenFinish;
    screens.push_back(&screenFinish);
    ScreenHowTo screenHowTo;
    screens.push_back(&screenHowTo);

//    Physics::Engine::getEngine()->cleanEngine();

    while( screen >= 0)
    {
        screen = screens[ screen ]->Run(App);
        // std::cout << screen << "   " << screens.size()<< std::endl;
    }

    stat->save();
    delete stat;
    return 0;
}
