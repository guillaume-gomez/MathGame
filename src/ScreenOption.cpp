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

#include "ScreenOption.hpp"
#include <ostream>


//std::vector<Button*> m_listButton;
//

std::string ScreenOption::m_filenameChar = FilenameDefaultChar;


ScreenOption::ScreenOption(unsigned int _button)
    :m_character_array(0),
     m_gravityType(NoSliding),
     m_nbButton(_button),
     m_quit(false)
{

    m_window = sfg::Window::Create();
    m_window->SetTitle( "Option" );

    m_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.0f);
    m_boxClose = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    m_layoutPhysics = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL);
    m_layoutCharacter = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL);

    m_framePhysics = sfg::Frame::Create("Gravity Type");
    m_frameCharacter = sfg::Frame::Create("Select a character");

    m_background.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameBackGroundMenu)));
    m_background.setColor(sf::Color(backgroundColor,backgroundColor,backgroundColor));

    for ( unsigned int i = 0 ; i < m_nbButton ; i++)
    {
        std::ostringstream oss;

        oss << i + 1;
        ChoiceCharacter temp = ChoiceCharacter(i+1);
        m_character_array.push_back(temp);
        sfg::Button::Ptr button (sfg::Button::Create("Character_" + oss.str()));

        button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&ChoiceCharacter::defineCharacter , &(m_character_array.at(i))));
        m_layoutCharacter->Pack(button);

    }

    sfg::RadioButton::Ptr radio1(sfg::RadioButton::Create("Sliging"));
    sfg::RadioButton::Ptr radio2(sfg::RadioButton::Create("No Sliding", radio1->GetGroup()));
    radio1->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ScreenOption::activateSliding, this));
    radio2->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ScreenOption::desactivateSliding, this));

    sfg::Button::Ptr saveButton(sfg::Button::Create("Save"));
    saveButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ScreenOption::save, this));

    sfg::Button::Ptr quitButton(sfg::Button::Create("Go back main menu"));
    quitButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ScreenOption::quit, this));
    quitButton->SetId("quitButton");

    m_layoutPhysics->Pack(radio1);
    m_layoutPhysics->Pack(radio2);

    m_frameCharacter->Add(m_layoutCharacter);
    m_framePhysics->Add(m_layoutPhysics);

    m_box->Pack(m_frameCharacter);
    m_box->Pack(m_framePhysics);
    m_box->Pack(saveButton);
    m_box->Pack(quitButton);

    m_window->Add(m_box);

    //m_desktop.LoadThemeFromFile(FilenameTheme);
    m_desktop.Add(m_window);


}

void ScreenOption::desactivateSliding()
{
    m_gravityType = NoSliding;
}

void ScreenOption::activateSliding()
{
    m_gravityType = Sliding;
}

void ScreenOption::quit()
{
    m_quit = true;
}

void ScreenOption::save()
{
    std::string filename ;
    unsigned int width = 0;
    unsigned int height = 0;
    float friction;
    std::ofstream configFile(FilenameConfigFile);


    if(m_filenameChar == FilenameDefaultChar)
    {
        friction = DefautCharFriction;
        width = DefaultCharWidth;
        height = DefaultCharHeight;
    }
    else if(m_filenameChar == FilenameBike)
    {
        friction = Bikefriction;
        width = BikeWidth ;
        height = BikeHeight;
    }

//     std::cout << m_filenameChar << std::endl;
    configFile <<"FilenameCharacterTex = "<< m_filenameChar << std::endl;
    configFile << "width = "<< width << std::endl;
    configFile << "height = "<< height<< std::endl;
    configFile << "MoveType = "<< m_gravityType << std::endl;
    configFile << "FrictionCoefficient = "<< friction << std::endl;

//    std::cout << "Saved" << std::endl;
}


int ScreenOption::Run( sf::RenderWindow& App)
{
    bool Running = true;

    App.resetGLStates();

    m_window->SetPosition(sf::Vector2f(App.getSize().x / 2.0f - m_window->GetAllocation().width /2.0f, App.getSize().y / 2.0f - m_window->GetAllocation().height /2.0f));
    m_window->Show(true);
    while(Running)
    {
        sf::Event event;
        //Verifing events
        while(App.pollEvent(event))
        {
            m_window->HandleEvent( event );

            if(event.type == sf::Event::Closed)
            {
                Running = false;
                App.close();
            }

            if( event.type == sf::Event::KeyPressed)
            {
                if( event.key.code == sf::Keyboard::Escape)
                {
                    m_window->Show(false);
                    return MENU;
                }
            }

            if(m_quit)
            {

                m_window->Show(false);
                m_quit = false;
                return MENU;
            }
        }

        m_desktop.Update( 0.f );

        App.clear();
        App.draw(m_background);
        m_sfgui.Display( App );
        App.draw(currentChoice);
        App.display();
        currentChoice.Update();
    }
    return (SCREEN_EXIT);
}


ScreenOption::~ScreenOption()
{}

ChoiceCharacter::ChoiceCharacter(unsigned int type)
    :m_type(type)
{
//    std::cout << "Constructor " << m_type<<std::endl;
}

ChoiceCharacter::~ChoiceCharacter()
{}

void ChoiceCharacter::defineCharacter()
{
    switch(m_type)
    {
    case 1:
        ScreenOption::m_filenameChar = FilenameDefaultChar;

        break;
    case 2:
        ScreenOption::m_filenameChar = FilenameBike;

        break;
    default:
        //degeux mais je ne comprends pas le probleme
        ScreenOption::m_filenameChar = FilenameDefaultChar;
        break;
    }
}
