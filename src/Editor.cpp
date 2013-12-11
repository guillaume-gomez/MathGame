#include "Editor.hpp"

Editor::Editor(sf::RenderWindow& App)
:m_app(App),m_axis( GraphScale ),m_graphView(m_graphModel,Thickness, GraphScale),m_textAreaFunction(6),
m_buttonReset(FilenameButtonReset), m_buttonSave(FilenameButtonSave), m_buttonBack(FilenameButtonBack), m_buttonCursor(FilenameButtonCursor),
m_buttonGoalButton(FilenamePointGoalTex), m_buttonNormalButton(FilenameNormalPointTex),m_buttonCircle(FilenameButtonCircleTex), m_isBack(false), m_isZoom(false), m_chooseTexture(false),
m_saving(false)
{
	sf::Texture* text = TextureManager::getTextureManager()->getResource(std::string(FilenameBGGame));
	text->setRepeated(true);
	m_spriteBG.setTexture(*text);
	m_spriteBG.setTextureRect(sf::IntRect(0, 0, 2048, 2048));
	m_spriteBG.setPosition(-1030, -1030);


	m_buttonCursor.setColor(sf::Color(0, 0, 0, Blur));

    m_Buttonpoint.loadFromFile(FilenameNormalPointTex);
    m_Buttongoal.loadFromFile(FilenamePointGoalTex);

    int __x = (Vector2f(m_app.mapPixelToCoords(Vector2i(m_app.getSize().x - m_panel.getLocalBounds().width , 0)))).x;
    int __y = (Vector2f(m_app.mapPixelToCoords(Vector2i(m_app.getSize().x , 0)))).y ;

    

    setCenterCamera();

	m_textAreaFunction.setCharacterSize(20);

    m_panel.setPosition(__x, __y);
    m_panel.setAlpha(200);

    m_panel.addButton(&m_buttonReset);

    m_panel.addButton(&m_buttonSave);

    m_panel.addButton(&m_buttonBack);

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


bool Editor::handleInput()
{
    while(m_app.pollEvent(m_event))
    {
        switch(m_event.type)
        {
            case Event::Closed:
                m_app.close();
                return false;
            break;

             case Event::MouseMoved:
                 {
                     int x = m_event.mouseMove.x - m_buttonCursor.getLocalBounds().width / 2;
                     int y = m_event.mouseMove.y - m_buttonCursor.getLocalBounds().height / 2;
                     sf::Vector2f coord = m_app.mapPixelToCoords((sf::Vector2i(x, y)));
                     m_buttonCursor.setPosition(coord);
                 }
            break;

             case Event::MouseButtonPressed:
                 {
                     if (Mouse::isButtonPressed(Mouse::Left))
                     {
                        int x = m_event.mouseButton.x - m_buttonCursor.getLocalBounds().width / 2;
                        int y = m_event.mouseButton.y - m_buttonCursor.getLocalBounds().height / 2;
                        addPoint(x, y);
                     }
                     else if (Mouse::isButtonPressed(Mouse::Right))
                     {
                        deletePoint(m_event.mouseButton.x, m_event.mouseButton.y);
                     }
                 }
            break;
            case sf::Event::MouseButtonReleased:
                {
                std::cout << m_event.mouseButton.x   << std::endl;
                int x = m_event.mouseButton.x - m_buttonCursor.getLocalBounds().width / 2;
                int y = m_event.mouseButton.y - m_buttonCursor.getLocalBounds().height / 2;
                //addCirle(x, y);
                }
            break;
            case Event::MouseWheelMoved:
                    m_isZoom = true;
                    zoom();
            break;

            case Event::KeyPressed:
                if(m_event.key.code == Keyboard::F8)
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
            break;
            default:
                break;
        }

        m_textAreaFunction.handleInput(m_event, m_app);
        m_panel.handle_input(m_event, m_app);

        if(m_buttonGoalButton.isClicked())
        {
    		m_buttonCursor.setColor(sf::Color(255, 0, 0, Blur));
        }
    	if(m_buttonNormalButton.isClicked())
        {
    		m_buttonCursor.setColor(sf::Color(0, 0, 0, Blur));
        }
        if(m_buttonCircle.isClicked())
        {
            m_buttonCursor.setColor(sf::Color(0, 0, 150, Blur));
        }
    }
    return true ;
}


void Editor::show()
{
//    m_textAreaFunction.textOperation();

	m_textAreaFunction.blinkCaret();
}

void Editor::draw()
{
    m_app.clear();

    m_app.setView(m_viewPerso);
    m_app.draw(m_spriteBG);
    m_axis.draw(m_app);

    for( unsigned int i = 0 ; i < m_spriteList.size();i++)
    {
        m_app.draw(m_spriteList[i]);
    }


    if (m_timer.getElapsedTime().asSeconds() < 5)
    {
         m_textVerifSave.draw(m_app);
    }
    m_graphView.draw(m_app);

    m_app.setView(m_app.getDefaultView());

    m_panel.draw(m_app);

    m_buttonCursor.draw(m_app);
    m_textAreaFunction.setPosition(0, m_app.getSize().y - m_textAreaFunction.getGlobalBounds().height - 10);
    m_app.draw(m_textAreaFunction);
//    m_textAreaFunction.draw(m_app);
}

void Editor::resetWindow()
{
    sf::View view;
    view.setSize(Vector2f(m_app.getSize()));
    view.setCenter(0, 0);
}

void Editor::deletePoint(int x , int y)
{
    sf::Vector2f coord = m_app.mapPixelToCoords((sf::Vector2i(x , y)), m_viewPerso);
    for(unsigned int i = 0 ; i < m_spriteList.size() ; i++)
    {
       if( m_spriteList[i].getGlobalBounds().contains(coord.x, coord.y))
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
        m_chooseTexture = true;
        m_buttonGoalButton.unclick();
    }

    if(m_buttonNormalButton.isClicked())
    {
        m_chooseTexture = false;
        m_buttonNormalButton.unclick();
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
    for(unsigned int i = 0 ; i < m_spriteList.size(); i++)
    {
       try
       {
            if(Point* point = dynamic_cast<Point*>(&m_spriteList[i]))
            {
                if(point->isGoal())
                {
                    nbGoalPoint++;
                }
            }
            else
            {
                std::cout << "TUTUTU" << std::endl;
            }
        }
        catch (const std::bad_cast& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    if(nbGoalPoint != 1)
    {
        m_textVerifSave.setString(sf::String("Level not Saved : there is not or too much goal point "));
        m_textVerifSave.setColor(sf::Color(237,28,36));
        return -1;
    }



    //sort m_spriteList
    for(unsigned int i = 0 ; i < m_spriteList.size() ; i++)
    {
        if(m_spriteList[i].getTexture() == &m_Buttongoal)
        {
            EditorObject temp( m_spriteList[i]);
            m_spriteList[i] = m_spriteList[ m_spriteList.size() - 1];
            m_spriteList[ m_spriteList.size() - 1] = temp;
        }
    }

        std::vector<std::string> fileList;
        fileList.push_back("Easy");
        fileList.push_back("Normal");
        fileList.push_back("Hard");


        unsigned int numberattempt = m_spriteList.size() - 1;
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
                   file << m_spriteList[j].getPosition().x / GraphScale <<" " << m_spriteList[j].getPosition().y / GraphScale << std::endl ;
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
   sf::FloatRect coord = m_textVerifSave.m_text.getLocalBounds ();
   m_textVerifSave.setPosition(sf::Vector2f(-coord.width/2 , 0));
   return 0 ;

}

void Editor::addPoint( int x , int y)
{
    if(m_panel.isVisible())
    {
		Point *newPoint = 0;
        sf::Vector2f coord = (sf::Vector2f)m_app.mapPixelToCoords((sf::Vector2i(x,y)),m_viewPerso);

        if(!m_chooseTexture)
        {
            newPoint = new Point(sizePoint, false);
        }
        else
        {
        	static sf::Vector2f goalCoords;

        	std::vector<EditorObject>::iterator it=m_spriteList.begin();
			bool goalSpriteFound=false;
			while(it!=m_spriteList.end() && !goalSpriteFound)
			{
				if(it->getPosition() == goalCoords)
				{
					m_spriteList.erase(it);
					goalSpriteFound = true;
				}
				else
					it++;
			}
			goalCoords = coord;
            newPoint = new Point(sizePoint, true);
        }
        newPoint->setPosition(coord);
        m_spriteList.push_back(*newPoint);
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


