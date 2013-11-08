#include <vector>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "constants.hpp"
#include "files.hpp"
/*
#include "Screen_MainMenu.hpp"
#include "ScreenLevelChoiceClassic.hpp"
#include "ScreenLevelChoiceNoChance.hpp"
#include "Screen_Game.hpp"
#include "ScreenOption.hpp"
#include "Screen_Editor.hpp"
#include "ScreenFinish.hpp"
#include "ScreenCredit.hpp"*/

#include "Game.hpp"

int main()
{
    ContextSettings contextPerso(0, 0, 2);
    RenderWindow App(VideoMode(WindowWidth, WindowHeight),"I Hate Maths",Style::Default, contextPerso);

/*    std::vector<Screen*> screens;
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


    while( screen >= 0)
    {
       screen = screens[ screen ]->Run(App);
    }

    stat->save();
*/


Game m_game(App);

      bool Running = true;
      m_game.loadConfigFile();
//    int alpha = 0 ;

    /*if (m_playing)
    {
        alpha = m_alpha_max;


    }*/
   // m_game.selectLevel(*m_stat);
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
/*
        if ( m_game.isBacked())
        {
            recenterCamera();
            return MENU;
        }
        */
//        gameFinish = m_game.levelOperation(*m_stat);
/*
        if ( gameFinish == -1)
        {
            return ENDING;
        }
        */
        m_game.move();
        m_game.manageSound();
        m_game.show();
        m_game.draw();
        App.display();
    }



    return 0;
}
