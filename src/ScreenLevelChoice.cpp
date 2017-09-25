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

#include "ScreenLevelChoice.hpp"

SelectLevel::SelectLevel( ScreenLink* _stat, unsigned int level, Difficulty difficulty)
    :m_stat(_stat), m_difficulty(difficulty), m_level(level), m_modeSelectLevel(Classic), m_isClicked(false)
{
#ifdef DEBUG
    std::cout << "SelectLevel::SelectLevel( ScreenLink* _stat, level "<< level <<", Difficulty "<< difficulty <<")" << std::endl;
#endif // DEBUG
}

SelectLevel::~SelectLevel()
{

}

void ScreenLevelChoice::loadLevelUnlocked()
{
//    std::cout <<"_____________________________" <<std::endl;
//    std::cout << (*m_stat) << std::endl;
//    std::cout <<"_____________________________" <<std::endl;
    unsigned int increment = 1U;
    for (auto it : m_layoutEasy->GetChildren())
    {
        if(increment > m_stat->getMaxLevel(Difficulty::Easy))
        {
            //std::cout << it->GetId() << std::endl;
            it->SetState(sfg::Widget::State::INSENSITIVE);
            it->SetId("Lock");
        }
        else
        {
            it->SetState(sfg::Widget::State::NORMAL);
            it->SetId("Unlock");
        }
        increment++;
    }

    increment = 1;
    for (auto it : m_layoutNormal->GetChildren())
    {
        if(increment > m_stat->getMaxLevel(Difficulty::Normal))
        {
            //std::cout << it->GetId() << std::endl;
            it->SetState(sfg::Widget::State::INSENSITIVE);
            it->SetId("Lock");
        }
        else
        {
            it->SetState(sfg::Widget::State::NORMAL);
            it->SetId("Unlock");
        }
        increment++;
    }

    increment = 1;
    for (auto it : m_layoutHard->GetChildren())
    {
        if(increment > m_stat->getMaxLevel(Difficulty::Hard))
        {
            //std::cout << it->GetId() << std::endl;
            it->SetState(sfg::Widget::State::INSENSITIVE);
            it->SetId("Lock");
        }
        else
        {
            it->SetState(sfg::Widget::State::NORMAL);
            it->SetId("unLock");
        }
        increment++;
    }
}

void SelectLevel::selectingLevel()
{
    // // std::cout << m_difficulty << " " <<  m_level << "  " << m_modeSelectLevel << std::endl;
    m_stat->setParamLevel(m_difficulty,m_level,m_modeSelectLevel);
    m_isClicked = true;
}

///////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////

ScreenLevelChoice::ScreenLevelChoice( ScreenLink* _stat)
    :m_changingMenu(-1), m_playing(false)
{

    m_stat = _stat;
//   m_backgroundTex.loadFromFile(FilenameBackGroundMenu);
//   m_background.setTexture(m_backgroundTex);
    m_background.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameBackGroundMenu)));
    m_background.setColor(sf::Color(backgroundColor,backgroundColor,backgroundColor));

    m_easyTex.loadFromFile(FilenameEasyButton);
    m_normalTex.loadFromFile(FilenameNormalButton);
    m_hardTex.loadFromFile(FilenameHardButton);

    m_easyBar.setTexture(m_easyTex);
    m_normalBar.setTexture(m_normalTex);
    m_hardBar.setTexture(m_hardTex);

    m_window = sfg::Window::Create();
    m_window->SetTitle("Select a Level");

    m_scrolled_window_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    m_layoutEasy = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL);
    m_layoutNormal = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL);
    m_layoutHard = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL);

    m_frameEasy = sfg::Frame::Create("Easy");
    m_frameNormal = sfg::Frame::Create("Normal");
    m_frameHard = sfg::Frame::Create("Hard");

    sf::Font font;
    font.loadFromFile(FilenameFont);

#ifdef DEBUG
    std::cout << "_stat->getnbEasy() : " << _stat->getnbEasy() << std::endl;
#endif // DEBUG

    for(unsigned int i = 0 ; i < _stat->getnbEasy() ; i++)
    {
        std::string directory = FilenameLevelDirectory;
        std::ostringstream oss;
        oss << i + 1 ;
        SelectLevel* temp = new SelectLevel(_stat, i + 1, Easy);
        m_selectionLevel.push_back(temp);
        sfg::Button::Ptr button = sfg::Button::Create(oss.str());
        button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&SelectLevel::selectingLevel, m_selectionLevel.at(i)));
        button->SetId("EasyButton" + oss.str());
        m_layoutEasy->Pack(button);
    }

    for(unsigned int i = 0 ; i < _stat->getnbNormal() ; i++)
    {
        std::string directory = FilenameLevelDirectory;
        std::ostringstream oss;
        oss << i + 1 ;
        SelectLevel* temp = new SelectLevel(_stat, i + 1, Normal);
        m_selectionLevel.push_back(temp);
        sfg::Button::Ptr button = sfg::Button::Create(oss.str());
        button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&SelectLevel::selectingLevel, m_selectionLevel.at(i + _stat->getnbEasy())));
        button->SetId("NormalButton" + oss.str());
        m_layoutNormal->Pack(button);
    }

    for(unsigned int i = 0 ; i < _stat->getnbHard() ; i++)
    {
        std::string directory = FilenameLevelDirectory;
        std::ostringstream oss;
        oss << i +1;
        SelectLevel* temp = new SelectLevel(_stat, i + 1, Hard);
        m_selectionLevel.push_back(temp);
        sfg::Button::Ptr button = sfg::Button::Create(oss.str());
        button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&SelectLevel::selectingLevel, m_selectionLevel.at(i + _stat->getnbEasy() + _stat->getnbNormal())) );
        button->SetId("HardButton" + oss.str());
        m_layoutHard->Pack(button);
    }
    m_frameEasy->Add(m_layoutEasy);
    m_frameNormal->Add(m_layoutNormal);
    m_frameHard->Add(m_layoutHard);

    m_scrolled_window_box->Pack(m_frameEasy);
    m_scrolled_window_box->Pack(m_frameNormal);
    m_scrolled_window_box->Pack(m_frameHard);
    m_window->Add(m_scrolled_window_box);
    m_window->SetRequisition(sf::Vector2f(300.0f,60.0f));
}


ScreenLevelChoice::~ScreenLevelChoice()
{
    // // std::cout << "ScreenLevelCHoice's destrcutor" << std::endl;
    for( unsigned int i = 0 ; i < m_selectionLevel.size(); i++)
    {
        m_selectionLevel.pop_back();
    }
}
