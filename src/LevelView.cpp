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

#include "LevelView.hpp"

#include "ObjectFactoryAbstract.hpp"

sf::Texture LevelView::m_texNormal;
sf::Texture LevelView::m_texGoal;

bool LevelView::TexturesLoaded = (loadTex()) ;

bool LevelView::loadTex(const char* _filenameNormalText, const char* _filenameGoalText)
{
    bool isLoadedNormal = m_texNormal.loadFromFile(_filenameNormalText);
    bool isLoadedGoal = m_texGoal.loadFromFile(_filenameGoalText);

    return (isLoadedGoal && isLoadedNormal);
}

LevelView::LevelView()
    :m_model(std::string())
{
}

LevelView::LevelView(const LevelModel& model, float _scale)
    :m_model(model), m_scale(_scale), m_view(sf::View())
{

    //pré loading
//    float widthTex  = (float) m_texGoal.getSize().x / 2;
//    float heightTex = (float) m_texGoal.getSize().y / 2;

    loadCoord();
}


LevelView::~LevelView()
{
    for (auto it : m_listSprite)
    {
#ifdef DEBUG
        // std::cout << "Suppression de type " << EditorObject::getTypeStr(it->getType()) << std::endl;
#endif
        delete it;
    }
}

void LevelView::reset()
{
}

// To load if the model change
void LevelView::loadCoord()
{
    int nbPoints = m_model.getNbPoints();
    for(int i = 0 ; i < nbPoints - 1 ; i++)
    {
        switch(m_model.getType(i))
        {
        case (TypeObject::Circle):
        {
            GravityCircle * NewCircle =  dynamic_cast<GravityCircle*>(ObjectFactoryAbstract::create(m_model.getType(i)));
            if(NewCircle != nullptr)
            {
                NewCircle->setRadius(m_model.getRadius(i));
                NewCircle->setOrigin(m_model.getRadius(i), m_model.getRadius(i));
                NewCircle->setPosition(m_model.getCoordPoints(i).x * m_scale/*- widthTex*/ , - m_model.getCoordPoints(i).y * m_scale/* - heightTex*/);
                m_listSprite.push_back(NewCircle);
            }
        }
        break;
        case (TypeObject::Point):
        {
            Point * NewPoint =  dynamic_cast<Point*>(ObjectFactoryAbstract::create(m_model.getType(i)));
            if(NewPoint != nullptr)
            {
                NewPoint->setPosition(m_model.getCoordPoints(i).x * m_scale/*- widthTex*/ , - m_model.getCoordPoints(i).y * m_scale/* - heightTex*/);
                m_listSprite.push_back(NewPoint);
            }
        }
        break;
        case (TypeObject::Enemy):
        {
            Enemy* newEnemy =  dynamic_cast<Enemy*>(ObjectFactoryAbstract::create(m_model.getType(i)));
            if(newEnemy != nullptr)
            {
                newEnemy->setPosition(m_model.getCoordPoints(i).x /*- widthTex*/ ,  m_model.getCoordPoints(i).y /* - heightTex*/);
                newEnemy->setNbAttempt(m_model.getAttempt(i));
//                    std::cout << "direction << " << m_model.getSens(i) << std::endl;
                newEnemy->setDirection(m_model.getSens(i));
                newEnemy->addToEngine();
                m_listSprite.push_back(newEnemy);
            }
        }
        break;

        case (TypeObject::Integral):
        {
            Integral* integral =  dynamic_cast<Integral*>(ObjectFactoryAbstract::create(m_model.getType(i)));
            if(integral != nullptr)
            {
                integral->setFunction(m_model.getFunction(i));
                integral->build(m_model.getBegin(i), m_model.getEnd(i));
                m_listSprite.push_back(integral);
            }
        }
        break;

        case (TypeObject::Function):
        {

            Curves* curves =  dynamic_cast<Curves*>(ObjectFactoryAbstract::create(m_model.getType(i)));
            if(curves != nullptr)
            {
                curves->setFunction(m_model.getFunction(i));
                m_listSprite.push_back(curves);
                m_listFunctionLevel.push_back(m_model.getFunction(i));
            }
        }

        case (TypeObject::Info):
        {
            InfoDisplayer* info =  dynamic_cast<InfoDisplayer*>(ObjectFactoryAbstract::create(m_model.getType(i)));
            if(info != nullptr)
            {
                info->setMessage(m_model.getMessage(i));
                info->setPosition(m_model.getCoordPoints(i).x * m_scale/*- widthTex*/ , - m_model.getCoordPoints(i).y * m_scale/* - heightTex*/);
                m_listSprite.push_back(info);
            }
        }
        default:
            break;

        }
    }

    //the goal sprite
    Point * NewPoint = dynamic_cast<Point*>(ObjectFactoryAbstract::create(TypeObject::GoalPoint));
    NewPoint->setPosition(m_model.getGoalCoord().x * m_scale/*- widthTex*/ , - m_model.getGoalCoord().y * m_scale/* - heightTex*/);
    m_listSprite.push_back(NewPoint);

}


void LevelView::draw(sf::RenderTarget& app)
{
    for(unsigned int i = 0 ; i < m_listSprite.size(); i++)
    {
        if( m_listSprite.at(i)->get_Position().x >= m_view.getCenter().x - m_view.getSize().x
                &&  m_listSprite.at(i)->get_Position().x <= m_view.getCenter().x + m_view.getSize().x  )
        {
            if(m_model.getType(i) == TypeObject::Point || m_model.getType(i) == TypeObject::GoalPoint)
            {
                if(!m_model.getCheckValue(i))
                {
                    m_listSprite[i]->draw(app);
                }
            }
            //other element can't be deleted, so they haven't got a check value parameter. then function still in this list
            //<!>(bad conception)<!>
            else if (m_model.getType(i) != TypeObject::Function)
            {
                m_listSprite[i]->draw(app);
            }
        }
    }
}
