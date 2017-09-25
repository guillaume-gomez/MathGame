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

#include "Screen_MainMenu.hpp"


Screen_MainMenu::Screen_MainMenu()
    : m_alpha_max(3 * 255), m_alpha_div(3), m_playing(false), m_changingMenu(SCREEN_EXIT)
{
//     m_backgroundTex.loadFromFile(FilenameBackGroundMenu);
    m_background.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameBackGroundMenu)));
    m_background.setColor(sf::Color(backgroundColor, backgroundColor, backgroundColor));

    //m_background.setPosition(WindowWidth/2 - m_background.getGlobalBounds().width/2, WindowHeight/2 - m_background.getGlobalBounds().height/2);

#ifdef ASSISTED_MODE_ACTIVATED
    m_play_button = sfg::Button::Create("Normal");
#endif
    m_play2_button = sfg::Button::Create("Play");
    m_credit_button = sfg::Button::Create("Credit");
    m_editor_button = sfg::Button::Create("Editor");
    m_option_button = sfg::Button::Create("Option");
    m_howTo_button = sfg::Button::Create("How To Play");


#ifdef ASSISTED_MODE_ACTIVATED
    m_play_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Screen_MainMenu::playButtonClick, this));
#endif // ASSISTED_MODE_ACTIVATED

    m_play2_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Screen_MainMenu::play2ButtonClick, this));
    m_credit_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Screen_MainMenu::creditButtonClick, this));
    m_option_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Screen_MainMenu::optionButtonClick, this));
    m_editor_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Screen_MainMenu::editorButtonClick, this));
    m_howTo_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Screen_MainMenu::howToButtonClick, this));
}


void Screen_MainMenu::playButtonClick()
{
    m_changingMenu = LEVEL_CHOICE_ONE;
}

void Screen_MainMenu::play2ButtonClick()
{
    m_changingMenu = LEVEL_CHOICE_TWO;
}

void Screen_MainMenu::creditButtonClick()
{
    m_changingMenu = CREDIT;
}

void Screen_MainMenu::editorButtonClick()
{
    m_changingMenu = EDITOR;
}

void Screen_MainMenu::optionButtonClick()
{
    m_changingMenu = OPTION;
}

void Screen_MainMenu::howToButtonClick()
{
    m_changingMenu = HOWTO;
}

void Screen_MainMenu::resize(float x, float y, sf::RenderWindow& App)
{
    // sf::View viewPerso = App.getView();
    // viewPerso.setCenter(0,0);
    // App.setView(viewPerso);
    //  m_background.scale(x,y);
}

int Screen_MainMenu::Run(sf::RenderWindow& App)
{
    bool Running = true;
    int alpha = 0 ;

    if(m_playing)
    {
        alpha = m_alpha_max;
    }

    App.resetGLStates();

    sfg::Box::Ptr box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 45.f );

#ifdef ASSISTED_MODE_ACTIVATED
    box->Pack( m_play_button );
#endif // ASSISTED_MODE_ACTIVATED

    box->Pack( m_play2_button );
    box->Pack( m_credit_button );
#ifdef DEBUG
    box->Pack( m_editor_button );
#endif
    box->Pack( m_option_button );
    box->Pack( m_howTo_button );

    m_window = sfg::Window::Create();
    m_window->SetTitle( "Main Menu" );
    m_window->SetRequisition(sf::Vector2f(300.0f,60.0f));
    m_window->Add( box );
    m_window->Show(true);
    m_changingMenu = SCREEN_EXIT;

    m_window->SetPosition(sf::Vector2f(App.getSize().x / 2.0f - m_window->GetAllocation().width /2.0f, App.getSize().y / 2.0f - m_window->GetAllocation().height /2.0f));
    m_desktop.Add(m_window);

    while(Running)
    {
        // Process events
        sf::Event event;
        float oldWidth = App.getSize().x;
        float oldHeight = App.getSize().y;

        while(App.pollEvent(event))
        {
            // Handle events
            m_window->HandleEvent(event);

            if(event.type == sf::Event::Resized)
            {
                resize((float)oldWidth/event.size.width, (float)oldHeight/event.size.height, App);
            }

            // Close window : exit
            if(event.type == sf::Event::Closed)
            {
                App.close();
                return SCREEN_EXIT;
            }

            if(m_changingMenu > 0)
            {
                m_window->Show(false);
                return m_changingMenu;
            }

            if(alpha < m_alpha_max)
            {
                alpha++;
            }
        }

        // Update the GUI, note that you shouldn't normally
        // pass 0 seconds to the update method.
        m_desktop.Update( 0.f );

        // Clear screen
        App.clear();
        // Draw the GUI
        App.draw(m_background);
        m_sfgui.Display( App );

        // Update the window
        App.display();
    }

    return (SCREEN_EXIT);
}

Screen_MainMenu::~Screen_MainMenu()
{

}
