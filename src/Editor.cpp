#include "Editor.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

#include "ObjectFactoryAbstract.hpp"

Editor::Editor(sf::RenderWindow& App)
:m_app(App),m_axis( GraphScale ),m_graphView(m_graphModel,Thickness, GraphScale),m_textAreaFunction(6),
m_buttonReset(FilenameButtonReset),
m_buttonSave(FilenameButtonSave),
m_buttonBack(FilenameButtonBack),
m_buttonCursor(FilenameButtonCursor),
m_buttonGoalButton(FilenamePointGoalTex),
m_buttonLeftEnemy(FilenameButtonEnemy),
m_buttonNormalButton(FilenameNormalPointTex),
m_buttonCircle(FilenameButtonCircleTex),
m_creatingType(TypeObject::Point), m_isBack(false), m_isZoom(false), m_isNormalPoint(true),
m_saving(false), m_radiusBuilder(0.0f, 0.0f),
m_isLeftEnemy(true), m_nbAttempt(1)
{
    //
    m_nbAttemptView.setColor(sf::Color(23,0,34,225));
    m_nbAttemptView.setString(sf::String("EnemyLife : 1"));
    m_nbAttemptView.setPosition(sf::Vector2f(m_app.getSize().x - 200, m_app.getSize().y - 25));

    //build all the template method
    ObjectFactoryAbstract::_register(TypeObject::Circle,new GravityCircle());
    ObjectFactoryAbstract::_register(TypeObject::Point,new Point(sizePoint));
    ObjectFactoryAbstract::_register(TypeObject::GoalPoint,new Point(sizePoint, true));
    ObjectFactoryAbstract::_register(TypeObject::Enemy,new Enemy());


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
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                    {
                        popPoint();
                    }
                }

                if(m_event.key.code == sf::Keyboard::Left)
                {
                       m_buttonCursor.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameButtonLeftEnemy)));
                       m_isLeftEnemy = true;
                       std::cout << "click " << m_isLeftEnemy << std::endl;
                }
                if(m_event.key.code == sf::Keyboard::Right)
                {
                       m_buttonCursor.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameButtonRightEnemy)));
                       m_isLeftEnemy = false;
                       std::cout << "clickRight " << m_isLeftEnemy << std::endl;
                }

                if(m_event.key.code == sf::Keyboard::Up)
                {
                    m_nbAttempt++;
                    if( m_nbAttempt > MaxAttempt) {
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
        }
    }
    return true ;
}


void Editor::show()
{
	m_textAreaFunction.blinkCaret();
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
    //if there is one red points
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
        for(unsigned int i = 0 ; i < TotalDifficulty ;i++)
        {
            std::ostringstream oss;
                        oss << FilenameLevelDirectory << link->getNbFiles() << "_" << fileList[i] <<".lvl" ;
            std::ofstream file(oss.str().c_str());
            if( file.is_open())
            {
               file << m_spriteList.size() << std::endl;
               file << numberattempt << std::endl;

               for( unsigned int j = 0 ; j < m_spriteList.size();j++)
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
            newEnemy->setPosition(coord.x / GraphScale, - coord.y / GraphScale);
            newEnemy->setDirection(m_isLeftEnemy);
            newEnemy->setNbAttempt(m_nbAttempt);
            newEnemy->show();
            std::cout << "know your enemy " << m_isLeftEnemy << std::endl;
            m_spriteList.push_back(newEnemy);
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



Editor::~Editor()
{
    //dtor
}


