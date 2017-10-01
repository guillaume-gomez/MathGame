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

#include "Editor.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

#include "ObjectFactoryAbstract.hpp"

Editor::Editor(sf::RenderWindow& App)
    :m_app(App),m_axis( GraphScale ),
     m_textAreaFunction(6),
     m_graphView(m_graphModel,Thickness, GraphScale),
     m_buttonReset(FilenameButtonReset),
     m_buttonSave(FilenameButtonSave),
     m_buttonBack(FilenameButtonBack),
     m_buttonCursor(FilenameButtonCursor),
     m_buttonGoalButton(FilenamePointGoalTex),
     m_buttonCircle(FilenameButtonCircleTex),
     m_buttonNormalButton(FilenameNormalPointTex),
     m_buttonLeftEnemy(FilenameButtonEnemy),
     m_buttonPanel(FilenameButtonPanel),
     m_buttonInfo(FilenamePanelInfoTex),
     m_creatingType(TypeObject::Point),
     m_isBack(false),
     m_isNormalPoint(true),
     m_isZoom(false),
     m_saving(false),
     m_isLeftEnemy(true), m_nbAttempt(1),
     m_radiusBuilder(0.0f, 0.0f)
{
    //
    m_nbAttemptView.setColor(sf::Color(23,0,34,225));
    m_nbAttemptView.setString(sf::String("EnemyLife : 1"));
    m_nbAttemptView.setPosition(sf::Vector2f(m_app.getSize().x - 210, m_app.getSize().y - 25));

    sf::Texture* text = TextureManager::getTextureManager()->getResource(std::string(FilenameBGGame));
    text->setRepeated(true);
    m_spriteBG.setTexture(*text);
    m_spriteBG.setTextureRect(sf::IntRect(0, 0, WidthWorld, HeightWorld));
    m_spriteBG.setPosition(-1030, -1030);

    m_buttonCursor.setColor(sf::Color(0, 0, 0, Blur));

    int __x = (sf::Vector2f(m_app.mapPixelToCoords(sf::Vector2i(m_app.getSize().x - m_buttonPanel.getLocalBounds().width , 0)))).x;
    int __y = (sf::Vector2f(m_app.mapPixelToCoords(sf::Vector2i(m_app.getSize().x , 0)))).y ;

    setCenterCamera();


    m_textAreaFunction.setCharacterSize(20);
    m_textAreaFunction.setPosition(0, m_app.getSize().y - m_textAreaFunction.getGlobalBounds().height - 10);

    m_panel.setPosition(__x, __y);
    m_panel.setAlpha(150);
    m_panel.addButton(&m_buttonReset);
    m_panel.addButton(&m_buttonSave);
    m_panel.addButton(&m_buttonBack);
    m_panel.addButton(&m_buttonLeftEnemy);
    m_panel.addButton(&m_buttonNormalButton);
    m_panel.addButton(&m_buttonGoalButton);
    m_panel.addButton(&m_buttonCircle);
    m_panel.addButton(&m_buttonInfo);
}

void Editor::zoom()
{
    if (m_isZoom)
    {
        float zoom = m_viewPerso.getSize().x * (1 - float(m_event.mouseWheel.delta) / 10);
        if (zoom >= ZoomMax && zoom <= ZoomMin)
        {
            m_viewPerso.zoom(1 - float(m_event.mouseWheel.delta) / 10);
        }
    }
}

void Editor::resize(float scaleX, float scaleY)
{
    resetWindow();
    m_panel.scale(scaleX, 1);
    m_buttonReset.scale(scaleX, scaleY);
    m_buttonBack.scale(scaleX, scaleY);
    m_buttonSave.scale(scaleX, scaleY);
    m_buttonCursor.scale(scaleX, scaleY);
    m_buttonGoalButton.scale(scaleX, scaleY);
    m_buttonLeftEnemy.scale(scaleX, scaleY);
    m_buttonNormalButton.scale(scaleX, scaleY);
    m_buttonCircle.scale(scaleX, scaleY);
    m_textAreaFunction.scale(scaleX, scaleY);
    m_buttonInfo.scale(scaleX, scaleY);
}

bool Editor::handleInput()
{
    float oldWidth = m_app.getSize().x;
    float oldHeight = m_app.getSize().y;
    while(m_app.pollEvent(m_event))
    {
        switch(m_event.type)
        {
        case sf::Event::Closed:
            m_app.close();
            return false;
            break;

        case sf::Event::Resized:
            resize((float)oldWidth/m_event.size.width, (float)oldHeight/m_event.size.height);
            break;

        case sf::Event::MouseMoved:
        {
            int x = m_event.mouseMove.x - m_buttonCursor.getLocalBounds().width / 2;
            int y = m_event.mouseMove.y - m_buttonCursor.getLocalBounds().height / 2;
            sf::Vector2f coord = m_app.mapPixelToCoords((sf::Vector2i(x, y)));
            m_buttonCursor.setPosition(coord);

        }
        break;

        case sf::Event::MouseButtonPressed:
        {
            m_radiusBuilder = sf::Vector2f(m_event.mouseButton.x , m_event.mouseButton.y);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (m_creatingType == TypeObject::Circle)
                {
                    //the radius is starting to be drawn
                    m_radiusBuilder = sf::Vector2f(m_event.mouseButton.x , m_event.mouseButton.y);
                }
                else
                {
                    addObject(m_event.mouseButton.x , m_event.mouseButton.y);
                }
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                deletePoint(m_event.mouseButton.x, m_event.mouseButton.y);
            }
        }
        break;
        case sf::Event::MouseButtonReleased:
        {
            if(m_creatingType == TypeObject::Circle)
            {
                sf::Vector2f origin = m_radiusBuilder;
                m_radiusBuilder = sf::Vector2f(m_radiusBuilder - sf::Vector2f(m_event.mouseButton.x, m_event.mouseButton.y));
                addCircle(origin.x, origin.y);
            }
        }
        break;
        case sf::Event::MouseWheelMoved:
            m_isZoom = true;
            zoom();
            break;

        case sf::Event::KeyPressed:
            if(m_event.key.code == sf::Keyboard::F8)
            {
                resetWindow();
            }
            if(m_event.key.code == sf::Keyboard::Return)
            {
                m_graphModel.setFunction(m_textAreaFunction.getString());
                m_graphModel.getRepresentativeCurve(-MaxSizeGraph, MaxSizeGraph, Step);
            }
            if(m_event.key.code == sf::Keyboard::Escape)
            {
                m_isBack = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                sf::Vector2f center = m_viewPerso.getCenter();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                {
                    popPoint();
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    m_viewPerso.setCenter(center.x, center.y - 10);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    m_viewPerso.setCenter(center.x, center.y + 10);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    m_viewPerso.setCenter(center.x - 10, center.y);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    m_viewPerso.setCenter(center.x + 10, center.y);
                }
                m_axis.receiveView(m_viewPerso);
                m_graphView.receiveView(m_viewPerso);
            }

            if(m_event.key.code == sf::Keyboard::Left)
            {
                m_buttonCursor.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameButtonLeftEnemy)));
                m_isLeftEnemy = true;
            }
            if(m_event.key.code == sf::Keyboard::Right)
            {
                m_buttonCursor.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameButtonRightEnemy)));
                m_isLeftEnemy = false;
                //std::cout << "clickRight " << m_isLeftEnemy << std::endl;
            }

            if(m_event.key.code == sf::Keyboard::Up)
            {
                m_nbAttempt++;
                if( m_nbAttempt > MaxAttempt)
                {
                    m_nbAttempt = MaxAttempt;
                }
                std::ostringstream oss;
                oss <<"EnemyLife : " << m_nbAttempt;
                m_nbAttemptView.setString(sf::String(oss.str()));
            }

            if(m_event.key.code == sf::Keyboard::Down)
            {
                m_nbAttempt--;
                if(m_nbAttempt < 1)
                {
                    m_nbAttempt = 1;
                }
                std::ostringstream oss;
                oss <<"EnemyLife : "<< m_nbAttempt;
                m_nbAttemptView.setString(sf::String(oss.str()));
            }
            break;
        default:
            break;
        }

        m_textAreaFunction.handleInput(m_event, m_app);
        m_panel.handle_input(m_event, m_app);

        if(m_buttonGoalButton.isClicked())
        {
            m_buttonCursor.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameButtonCursor)));
            m_buttonCursor.setColor(sf::Color(255, 0, 0, Blur));
        }
        if(m_buttonNormalButton.isClicked())
        {
            m_buttonCursor.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameButtonCursor)));
            m_buttonCursor.setColor(sf::Color(0, 0, 0, Blur));
        }
        if(m_buttonCircle.isClicked())
        {
            m_buttonCursor.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameButtonCursor)));
            m_buttonCursor.setColor(sf::Color(0, 0, 150, Blur));
        }
        if(m_buttonLeftEnemy.isClicked())
        {
            m_buttonCursor.setColor(sf::Color(255, 255, 255, Blur));
            m_buttonCursor.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameButtonLeftEnemy)));
            m_isLeftEnemy = true;
        }
        if(m_buttonInfo.isClicked())
        {
            m_buttonCursor.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenamePanelInfoTex)));
            m_buttonCursor.setColor(sf::Color(0, 0, 150, Blur));
        }
    }
    return true ;
}


void Editor::show()
{
    m_textAreaFunction.blinkCaret();
    cameraMoved();
}

void Editor::draw()
{
    m_app.clear();

    m_app.setView(m_viewPerso);
    m_app.draw(m_spriteBG);
    m_axis.draw(m_app);

    for (auto it : m_spriteList)
    {
        it->draw(m_app);
    }

    if (m_timer.getElapsedTime().asSeconds() < 5)
    {
        m_textVerifSave.draw(m_app);
    }
    m_graphView.draw(m_app);

    m_app.setView(m_app.getDefaultView());

    m_panel.draw(m_app);

    m_nbAttemptView.draw(m_app);

    m_buttonCursor.draw(m_app);
    m_app.draw(m_textAreaFunction);
}

void Editor::resetWindow()
{
    m_viewPerso.setSize(sf::Vector2f(m_app.getSize()));
    m_viewPerso.setCenter(0, 0);
}

void Editor::deletePoint(int x , int y)
{
    sf::Vector2f coord = m_app.mapPixelToCoords((sf::Vector2i(x , y)), m_viewPerso);
    for(unsigned int i = 0 ; i < m_spriteList.size() ; i++)
    {
        if( m_spriteList[i]->get_GlobalBounds().contains(coord.x, coord.y))
        {
            m_spriteList.erase(m_spriteList.begin() + i);
        }
    }
}

void Editor::deleteGravityCircle(int x, int y)
{
}

void Editor::move()
{
    m_panel.movePanel(m_app);

    if(m_buttonReset.isClicked())
    {
        reset();
        m_buttonReset.unclick();
    }

    if(m_buttonBack.isClicked())
    {
        m_isBack = true;
        m_buttonBack.unclick();
    }
    if(m_buttonSave.isClicked())
    {
        m_saving = true;
        m_buttonSave.unclick();
    }

    if(m_buttonGoalButton.isClicked())
    {
        m_creatingType = TypeObject::GoalPoint;
        m_isNormalPoint = false;
        m_buttonGoalButton.unclick();
    }

    if(m_buttonNormalButton.isClicked())
    {
        m_creatingType = TypeObject::Point;
        m_isNormalPoint = true;
        m_buttonNormalButton.unclick();
    }
    if(m_buttonCircle.isClicked())
    {
        m_creatingType = TypeObject::Circle;
        m_buttonCircle.unclick();
    }

    if(m_buttonLeftEnemy.isClicked())
    {
        m_creatingType = TypeObject::Enemy;
        m_buttonLeftEnemy.unclick();
    }

    if(m_buttonInfo.isClicked())
    {
        m_creatingType = TypeObject::Info;
        m_buttonInfo.unclick();
    }

    if(m_graphModel.getChanged())
    {
        m_graphView.represent(Step);
        m_graphModel.setChanged(false);
    }

}

void Editor::reset()
{
    m_spriteList.clear();
    m_graphModel.setChanged(true);
    m_graphModel.clearFunction();
}


void Editor::setCenterCamera()
{
    m_viewPerso = m_app.getView();
    m_viewPerso.setCenter(0,0);
    m_axis.receiveView(m_viewPerso);
    m_graphView.receiveView(m_viewPerso);
}



int Editor::save(ScreenLink * link)
{

    if(m_saving)
    {
        m_saving = false;
        m_timer.restart();
        //if there is no points
        if ( m_spriteList.size() < 2)
        {
            m_textVerifSave.setString(sf::String("Level not Saved : not enough points "));
            m_textVerifSave.setColor(sf::Color(237,28,36));
            return -1;
        }

        int nbGoalPoint = 0;
        //if there is just one red point
        //for(std::vector<EditorCircle*>::iterator it = m_spriteList.begin(); it != m_spriteList.end() ; it++)
        for(auto it : m_spriteList)
        {
            if(it->getType() == TypeObject::GoalPoint)
            {
                nbGoalPoint++;
            }
        }
        if(nbGoalPoint != 1)
        {
            m_textVerifSave.setString(sf::String("Level not Saved : there is not or too much goal point "));
            m_textVerifSave.setColor(sf::Color(237,28,36));
            return -1;
        }

        //sort m_spriteList
        std::sort (m_spriteList.begin(), m_spriteList.end(), EditorObject::compare);

        std::vector<std::string> fileList;
        fileList.push_back("Easy");
        fileList.push_back("Normal");
        fileList.push_back("Hard");


        unsigned int numberattempt = 0;
        for( auto it : m_spriteList)
        {
            if(it->getType() == TypeObject::Point || it->getType() == TypeObject::GoalPoint)
            {
                numberattempt++;
            }
        }

        if(numberattempt < 1)
        {
            //to avoid negative number
            numberattempt+= 2;
        }

        m_textVerifSave.setString(sf::String("Level Saved"));
        m_textVerifSave.setColor(sf::Color(34,177,76));
        for(unsigned int i = 0 ; i < TotalDifficulty ; i++)
        {
            std::ostringstream oss;
            oss << FilenameLevelDirectory << link->getNbFiles() + 1 << "_" << fileList[i] <<".lvl" ;
            std::ofstream file(oss.str().c_str());
            if( file.is_open())
            {
                file << m_spriteList.size() << std::endl;
                file << numberattempt << std::endl;

                for( unsigned int j = 0 ; j < m_spriteList.size(); j++)
                {
                    file <<  m_spriteList[j]->save(GraphScale);
                }

                file.close();
            }
            else
            {
                m_textVerifSave.setString(sf::String("Level not Saved"));
                m_textVerifSave.setColor(sf::Color(237,28,36));
                return -1;
            }
            numberattempt-- ;
        }
        link->setnbFiles(link->getNbFiles()+1);
    }
    sf::FloatRect coord = m_textVerifSave.getText().getLocalBounds ();
    m_textVerifSave.setPosition(sf::Vector2f(-coord.width/2 , 0));
    return 0 ;

}

void Editor::addObject(int x , int y)
{
    if(m_panel.isVisible())
    {
        sf::Vector2f coord = (sf::Vector2f)m_app.mapPixelToCoords((sf::Vector2i(x,y)),m_viewPerso);

        if(m_creatingType == TypeObject::Point || m_creatingType == TypeObject::GoalPoint)
        {
            Point *newPoint = nullptr;
            if(m_isNormalPoint)
            {
                newPoint = dynamic_cast<Point*>(ObjectFactoryAbstract::create(TypeObject::Point));
            }
            else
            {
                static sf::Vector2f goalCoords;
                std::vector<EditorObject*>::iterator it = m_spriteList.begin();
                bool goalSpriteFound=false;
                while(it!=m_spriteList.end() && !goalSpriteFound)
                {
                    if((*it)->get_Position() == goalCoords)
                    {
                        m_spriteList.erase(it);
                        goalSpriteFound = true;
                    }
                    else
                    {
                        it++;
                    }
                }
                goalCoords = coord;
                newPoint = dynamic_cast<Point*>(ObjectFactoryAbstract::create(TypeObject::GoalPoint));
            }
            newPoint->setPosition(coord);
            m_spriteList.push_back(newPoint);
        }
        else if (m_creatingType == TypeObject::Enemy)
        {
            Enemy* newEnemy = dynamic_cast<Enemy*>(ObjectFactoryAbstract::create(TypeObject::Enemy));
            newEnemy->setPosition(coord.x / GraphScale, -coord.y / GraphScale);
            newEnemy->setDirection(m_isLeftEnemy);
            newEnemy->setNbAttempt(m_nbAttempt);
            newEnemy->show();

            m_spriteList.push_back(newEnemy);
        }
        else if (m_creatingType == TypeObject::Info)
        {
            InfoDisplayer* newInfo = dynamic_cast<InfoDisplayer*>(ObjectFactoryAbstract::create(TypeObject::Info));
            newInfo->setPosition(coord.x - m_buttonCursor.getLocalBounds().width / 2,
                                 coord.y - m_buttonCursor.getLocalBounds().height / 2);
            newInfo->setMessage("Message temporaire");
            m_spriteList.push_back(newInfo);
        }
    }
}

void Editor::addCircle(int x, int y)
{
    float radius = abs(m_radiusBuilder.x);
    if(radius > 0.0f)
    {
        GravityCircle* newCircle = new GravityCircle(radius);
        sf::Vector2f coord = m_app.mapPixelToCoords((sf::Vector2i(x,y)),m_viewPerso);
        newCircle->setPosition(coord);
        m_spriteList.push_back(newCircle);
    }
    else
    {
        std::cerr << "In Editor::addCircle : you tried to create a gravityCircle with a negative radius" << std::endl;
    }

}

void Editor::popPoint()
{

    if(m_spriteList.size() > 0)
    {
        m_spriteList.pop_back();
    }

}


void Editor::cameraMoved()
{
    float centerX = m_viewPerso.getCenter().x,
          centerY = m_viewPerso.getCenter().y;

    //Si on dépasse à gauche
    if(centerX - (m_viewPerso.getSize().x/2) < -(WidthWorld/2))
    {
        centerX = -(WidthWorld/2) + (m_viewPerso.getSize().x/2);
        //std::cout << "on depasse à gauche "<< centerX  - m_viewPerso.getSize().x << std::endl;
    }

    //Si on dépasse en haut
    if(centerY - (m_viewPerso.getSize().y/2) < -(HeightWorld/2))
    {
        centerY = -(HeightWorld/2) + (m_viewPerso.getSize().y/2);
        //std::cout << "on depasse à haut "<<  centerY - m_viewPerso.getSize().y <<std::endl;
    }

    //Si on dépasse à droite
    if(centerX + (m_viewPerso.getSize().x /2) > (WidthWorld/2))
    {
        centerX = (WidthWorld/2) - (m_viewPerso.getSize().x/2);
        //std::cout << "on depasse à droite "<< centerX + m_viewPerso.getSize().x<<std::endl;
    }

    //si on dépasse en bas
    if(centerY + (m_viewPerso.getSize().y/2) > (HeightWorld/2))
    {
        centerY = (HeightWorld/2) - (m_viewPerso.getSize().y/2);
        //std::cout << "on depasse à bas "<< centerY + m_viewPerso.getSize().y<<std::endl;
    }


    m_viewPerso.setCenter(centerX, centerY);
}


Editor::~Editor()
{
    //dtor
}


