#include <vector>
#include <SFML/Graphics.hpp>

#include <iostream>
using namespace sf;

#include "constants.hpp"
#include "files.hpp"

#include "Screen_MainMenu.hpp"
#include "ScreenLevelChoiceClassic.hpp"
#include "ScreenLevelChoiceNoChance.hpp"
#include "Screen_Game.hpp"
#include "ScreenOption.hpp"
#include "Screen_Editor.hpp"
#include "ScreenFinish.hpp"
#include "ScreenCredit.hpp"

#include "Game.hpp"

int main()
{
    ContextSettings contextPerso(0, 0, 2);
    RenderWindow App(VideoMode(WindowWidth, WindowHeight),"I Hate Maths",Style::Default, contextPerso);

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

//    Physics::Engine::getEngine()->cleanEngine();

    while( screen >= 0)
    {
       screen = screens[ screen ]->Run(App);
       // // std::cout << screen << std::endl;
    }

    stat->save();
    delete stat;
    return 0;
}
