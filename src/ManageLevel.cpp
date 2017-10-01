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

#include "ManageLevel.hpp"

sf::Texture ManageLevel::toolTipTex;


bool ManageLevel::toolTipTexLoaded = loadToolTipTex(FilenameToolTipTex);

bool ManageLevel::loadToolTipTex(const char* filenameToolTipText)
{
    return toolTipTex.loadFromFile(filenameToolTipText);
}


ManageLevel::ManageLevel(unsigned int _level, Difficulty _diff, float _scale)
    :m_scale(_scale), m_difficulty(_diff), m_levelCurrent(_level), m_changeLevel(false), m_isDisplayToolTip(false)
{
    std::string directory = FilenameLevelDirectory;
    std::ostringstream oss;
    oss << m_levelCurrent << "_" << convertEnum(m_difficulty) << ".lvl";
    directory += oss.str();
    m_filenameCurrent = oss.str();

    m_levelModel = new LevelModel(directory);
    m_levelView = new LevelView(*m_levelModel, m_scale);

//    	#ifdef DEBUG
//			std::cout << "ManageLevel::ManageLevel()" << std::endl;
//    	#endif // DEBUG
    m_tooltip.setTexture(toolTipTex);

    if(!m_font.loadFromFile(FilenameFont))
    {
#ifdef DEBUG
        std::cerr << "ManageLevel::ManageLevel()" << std::endl;
#endif // DEBUG
    }
    m_nbAttemp.setColor(sf::Color::Black);
    m_nbAttemp.setFont(m_font);
    m_nbAttemp.setCharacterSize(Font);
    m_text.setFont(m_font);
    m_text.setColor(sf::Color::Black);
    m_text.setStyle(sf::Text::Bold);
    m_text.setCharacterSize(12);

}

ManageLevel::~ManageLevel()
{
    if(m_levelView != nullptr)
        delete m_levelView;

    if(m_levelModel != nullptr)
        delete m_levelModel;
}


void ManageLevel::loadFile(int numLevel, GameMode mode)
{
    if(m_levelView != nullptr)
        delete m_levelView;

    if(m_levelModel != nullptr)
        delete m_levelModel;

    std::string directory = FilenameLevelDirectory;

    setLevel( numLevel);
    std::ostringstream oss;
    oss << numLevel << "_" << convertEnum(m_difficulty) << ".lvl";
    std::cout << "fileLoad " << oss.str() << std::endl;
    directory += oss.str();
    m_filenameCurrent = oss.str();

    std::ifstream ifile(directory);
    if(ifile.fail())
    {
        m_levelView = nullptr;
        m_levelModel= nullptr;
        throw std::ios_base::failure("unable to open level");
    }

#ifdef DEBUG
    //std::cout << "ManageLevel::loadFile - directory : " << directory << std::endl;
    //std::cout << "ManageLevel::loadFile - m_filenameCurrent : " << m_filenameCurrent << std::endl;
#endif // DEBUG

    m_levelModel = new LevelModel(directory, mode );
    m_levelView = new LevelView(*m_levelModel, m_scale);
}

void ManageLevel::IsNextLevel()
{
    if(m_levelModel->isWin())
    {
        m_changeLevel = true;
    }
}

void ManageLevel::levelFinished (const CharacterModel& charModel, bool & soundplayable)
{
    m_levelModel->IsLosing();
    m_levelModel->IsFinishing(charModel,m_scale, soundplayable);
    if(m_levelModel->isWin() || m_levelModel->IsLose())
    {
        m_changeLevel = true;
    }
}

int  ManageLevel::changeLevel (ScreenLink * link)
{
    if(m_changeLevel)
    {
        if(m_levelModel->isWin())
        {
            //load an other level
            if(getLevel() + 1 > link->getnbNormal())
            {
                return - 1 ;
            }
            link->setMaxLevel( link->getDiff() , link->getCurrentLevel() + 1 );
            link->setCurrentLevel( link->getCurrentLevel() +1 );
            setLevel(getLevel() + 1);
            loadFile(getLevel(), m_levelModel->getMode());
            m_changeLevel = false;
        }
        else
        {
            reset();
        }
    }
    else
    {
        reset();
    }
    return 0 ;
}

void ManageLevel::reset()
{
    m_levelModel->reset();
    resetEnemies();
    m_changeLevel = false;
}

void ManageLevel::showEnemies()
{
    std::vector<EditorObject*> listEnemies = m_levelView->getSpriteList();
    for(auto it : m_levelView->getSpriteList())
    {
        if(it->getType() == TypeObject::Enemy)
        {
            Enemy* enemy = dynamic_cast<Enemy*>(it);
            if( enemy == nullptr)
            {
                std::runtime_error("Error in ManageLevel::showEnemies : cannot dynamic_cast in enemy");
            }
            enemy->show();
        }
    }
}

void ManageLevel::resetEnemies()
{
    std::vector<EditorObject*> listEnemies = m_levelView->getSpriteList();
    unsigned int index = 0;
    for(auto it : m_levelView->getSpriteList())
    {
        if(it->getType() == TypeObject::Enemy)
        {
            Enemy* enemy = dynamic_cast<Enemy*>(it);
            if( enemy == nullptr)
            {
                std::runtime_error("Error in ManageLevel::showEnemies : cannot dynamic_cast in enemy");
            }
            enemy->reset();
            sf::Vector2f pos = m_levelModel->getCoordPoints(index);
            enemy->setNbAttempt(m_levelModel->getAttempt(index));
            enemy->setPosition(pos);
        }
        index++;
    }
}



void ManageLevel::decrementAttempt()
{
    m_levelModel->decrementAttempt();

    std::vector<EditorObject*> listEnemies = m_levelView->getSpriteList();
    for(auto it : m_levelView->getSpriteList())
    {
        if(it->getType() == TypeObject::Enemy)
        {
            Enemy* enemy = dynamic_cast<Enemy*>(it);
            if( enemy == nullptr)
            {
                std::runtime_error("Error in ManageLevel::decrementAttempt : cannot dynamic_cast in enemy");
            }
            enemy->decrementAttempt();
        }
    }
}

void ManageLevel::handle_inputEnnemies(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction)
{
    std::vector<EditorObject*> listEnemies = m_levelView->getSpriteList();
    for(auto it : m_levelView->getSpriteList())
    {
        if(it->getType() == TypeObject::Enemy)
        {
            Enemy* enemy = dynamic_cast<Enemy*>(it);
            if( enemy == nullptr)
            {
                std::runtime_error("Error in ManageLevel::decrementAttempt : cannot dynamic_cast in enemy");
            }
            enemy->handle_input(event, textAreaFunction);
        }
    }
}

void ManageLevel::displaying(sf::Event& event , sf::RenderTarget& target , sf::View& myView)
{
    std::vector<EditorObject*> temp = m_levelView->getSpriteList();
    if(event.type == sf::Event::MouseMoved)
    {
        m_isDisplayToolTip = false;
        int x = event.mouseMove.x;
        int y = event.mouseMove.y;
        sf::Vector2f coord = target.mapPixelToCoords((sf::Vector2i(x, y)), myView);

        for(unsigned int i = 0 ; i < temp.size() ; i++)
        {
            if(temp[i]->getType() == TypeObject::Point || temp[i]->getType() == TypeObject::GoalPoint)
            {

                if(temp[i]->get_GlobalBounds().contains(coord.x, coord.y))
                {
                    m_isDisplayToolTip = true;
                    sf::Vector2i position = target.mapCoordsToPixel(temp[i]->get_Position(), myView);

                    position.x -= toolTipTex.getSize().x ;
                    position.y -= toolTipTex.getSize().y ;

                    std::string info ;
                    std::ostringstream oss;
                    oss << "x = " << m_levelModel->getCoordPoints(i).x <<"\ny = " <<m_levelModel->getCoordPoints(i).y ;
                    info += oss.str();

                    m_text.setString(info);
                    m_text.setPosition(sf::Vector2f(position.x + m_tooltip.getLocalBounds().width / 2 - m_text.getLocalBounds().width / 2 ,position.y + m_tooltip.getLocalBounds().height / 2 - m_text.getLocalBounds().height / 2 - 10.0f));
                    m_tooltip.setPosition((sf::Vector2f)position);
                }
            }
        }
    }
}


void ManageLevel::displayNbAttempt()
{
    std::string nbAttemp ;
    std::ostringstream oss;
    oss <<"Curves used : " << m_levelModel->getNbAttempt() <<" / " << m_levelModel->getSaveAttempt() ;
    nbAttemp += oss.str();

    m_nbAttemp.setString(nbAttemp);
}

void ManageLevel::scaleNbAttempt(float scaleX, float scaleY)
{
    m_nbAttemp.scale(scaleX, scaleY);
}

void ManageLevel::drawPoints( sf::RenderTarget& app)
{
    m_levelView->draw(app);
}
void ManageLevel::drawUI( sf::RenderTarget& app)
{
    if(m_isDisplayToolTip)
    {
        app.draw(m_tooltip);
        app.draw(m_text);
    }
    app.draw(m_nbAttemp);
}

void ManageLevel::fillLevelFunctions(ManageFunctions& func)
{
    func.reset();
#ifdef DEBUG
    /*if(m_levelModel->getVectorFunctions())
    {
        std::runtime_error("Error in ManageLevel::fillLevelFunctions : no curves loaded");
    }*/
#endif
    for(auto it : m_levelModel->getVectorFunctions())
    {
#ifdef DEBUG
        std::cerr << "function added " << it << std::endl;
#endif
        func.addFunction(it);
    }
}

std::string ManageLevel::convertEnum ( Difficulty _diff)
{
    std::string val;

    switch (_diff)
    {
    case  Easy:
        return val= "Easy";
        break;

    case  Normal:
        return val = "Normal";
        break;

    case  Hard:
        return val = "Hard";
        break;

    default:
        break;
    }
    return val;
}
