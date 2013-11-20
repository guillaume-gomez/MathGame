#include "Editor.hpp"

Editor::Editor(sf::RenderWindow& App)
:m_app(App),m_axis( GraphScale ),m_graphView(m_graphModel,Thickness, GraphScale),m_textAreaFunction(6),
m_buttonReset(FilenameButtonReset),m_buttonSave(FilenameButtonSave),m_buttonBack(FilenameButtonBack),m_buttonCursor(FilenameButtonCursor),
m_buttonGoalButton(FilenamePointGoalTex),m_buttonNormalButton(FilenameNormalPointTex),
m_buttonPanel(FilenameButtonPanel),m_isBack(false),m_isAnimLeft(false),m_isAnimRight(false),m_isZoom(false),m_chooseTexture(false),m_drawable(false),
m_saving(false)
{
	sf::Texture* text = TextureManager::getTextureManager()->getResource(std::string(FilenameBGGame));
	text->setRepeated(true);
	m_spriteBG.setTexture(*text);
	m_spriteBG.setTextureRect(sf::IntRect(0,0,2048,2048));
	m_spriteBG.setPosition(-1030,-1030);

	m_buttonCursor.setColor(sf::Color(0,0,0,Blur));

    m_Buttonpoint.loadFromFile(FilenameNormalPointTex);
    m_Buttongoal.loadFromFile(FilenamePointGoalTex);

    int __x = (Vector2f(m_app.mapPixelToCoords(Vector2i(m_app.getSize().x - m_buttonPanel.getLocalBounds().width , 0 )))).x;
    int __y = (Vector2f(m_app.mapPixelToCoords(Vector2i(m_app.getSize().x , 0 )))).y ;

    float Y =  (m_buttonPanel.getLocalBounds().height - (m_buttonReset.getLocalBounds().height / 5)) / 5 ;
    int offsetY = int (Y) / 5;
    float X = m_buttonPanel.getLocalBounds().width /  2  - m_buttonReset.getLocalBounds().width/2 + __x;

    setCenterCamera();

	m_textAreaFunction.setCharacterSize(20);

    m_buttonPanel.setPosition(__x,__y);
    m_buttonPanel.setAlpha(200);

    m_buttonReset.setPosition(X, offsetY  );

    m_buttonSave.setPosition(X,offsetY + Y );

    m_buttonBack.setPosition(X,offsetY + Y*2 );

    m_buttonNormalButton.setPosition(X,offsetY + Y*3 );

    m_buttonGoalButton.setPosition(X,offsetY + Y*4 );

}

void Editor::zoom()
{
    if ( m_isZoom)
    {
            float zoom = m_viewPerso.getSize().x * (1-float(m_event.mouseWheel.delta)/10);
            if ( zoom >= ZoomMax && zoom <= ZoomMin)
            {
                m_viewPerso.zoom(1-float(m_event.mouseWheel.delta)/10);
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

                     int x = m_event.mouseMove.x - m_buttonCursor.getLocalBounds().width/2;
                     int y = m_event.mouseMove.y - m_buttonCursor.getLocalBounds().height/2;
                     sf::Vector2f coord = m_app.mapPixelToCoords((sf::Vector2i(x,y)));
                     managePanel(x);
                     m_buttonCursor.setPosition(coord);
                     }
                break;

                 case Event::MouseButtonPressed:
                     {
                         if (Mouse::isButtonPressed(Mouse::Left))
                         {
                             int x = m_event.mouseButton.x - m_buttonCursor.getLocalBounds().width/2;
                             int y = m_event.mouseButton.y - m_buttonCursor.getLocalBounds().height/2;
                            addPoint(x, y);
                         }
                         else if (Mouse::isButtonPressed(Mouse::Right))
                         {
                            deletePoint(m_event.mouseButton.x, m_event.mouseButton.y);
                         }
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
						m_graphModel.getRepresentativeCurve(-MaxSizeGraph,MaxSizeGraph,Step);
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

                m_textAreaFunction.handleInput(m_event,m_app);
                m_buttonReset.handle_input(m_event,m_app);
                m_buttonSave.handle_input(m_event,m_app);
                m_buttonBack.handle_input(m_event,m_app);
                m_buttonGoalButton.handle_input(m_event,m_app);
                m_buttonNormalButton.handle_input(m_event,m_app);

                if(m_buttonGoalButton.isClicked())
					m_buttonCursor.setColor(sf::Color(255,0,0,Blur));
				if(m_buttonNormalButton.isClicked())
					m_buttonCursor.setColor(sf::Color(0,0,0,Blur));
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

     for ( unsigned int i = 0 ; i < m_spriteList.size();i++)
    {
        m_app.draw(m_spriteList[i]);
    }


    if ( 5 > m_timer.getElapsedTime().asSeconds() )
    {
         m_textVerifSave.draw(m_app);
    }

    m_axis.draw(m_app);
    m_graphView.draw(m_app);

    m_app.setView(m_app.getDefaultView());

    m_buttonPanel.draw(m_app);
    m_buttonReset.draw(m_app);
    m_buttonSave.draw(m_app);
    m_buttonBack.draw(m_app);
    m_buttonNormalButton.draw(m_app);
    m_buttonGoalButton.draw(m_app);
    m_buttonCursor.draw(m_app);
    m_textAreaFunction.setPosition(0,m_app.getSize().y-m_textAreaFunction.getGlobalBounds().height-10);
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
    sf::Vector2f coord = m_app.mapPixelToCoords((sf::Vector2i(x , y)),m_viewPerso);
    for (unsigned int i = 0 ; i < m_spriteList.size() ; i++)
    {
       if( m_spriteList[i].getGlobalBounds().contains(coord.x,coord.y))
       {
           m_spriteList.erase(m_spriteList.begin() + i);
       }
    }
}

void Editor::move()
{
    movePanel ();

    if ( m_buttonReset.isClicked())
    {
        reset();
        m_buttonReset.unclick();
    }

     if ( m_buttonBack.isClicked())
      {
          m_isBack = true;
          m_buttonBack.unclick();
      }

    if ( m_buttonSave.isClicked())
    {
        m_saving = true;
        m_buttonSave.unclick();
    }

    if ( m_buttonGoalButton.isClicked())
    {
        m_chooseTexture = true;
        m_buttonGoalButton.unclick();
    }

    if ( m_buttonNormalButton.isClicked())
    {
        m_chooseTexture = false;
        m_buttonNormalButton.unclick();
    }

    if ( m_graphModel.getChanged())
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

void Editor::managePanel( int coordMouseX )
{
    if (coordMouseX >= m_app.getSize().x*0.9)
    {
        m_drawable = false;
        m_isAnimLeft = true;
        m_isAnimRight = false;
    }

    if (coordMouseX < m_app.getSize().x*0.9 )
    {
        m_drawable = true;
        m_isAnimRight = true;
        m_isAnimLeft = false;
    }
}

void Editor::movePanel ()
{
    int offset = 4;
     if ( m_isAnimLeft && (m_buttonPanel.getPosition().x + m_buttonPanel.getGlobalBounds().width - offset) >= m_app.getSize().x)
    {
        if( m_timerPanel.getElapsedTime().asMilliseconds() > TimePanel )
        {
            m_buttonPanel.setPosition(m_buttonPanel.getPosition().x - offset , m_buttonPanel.getPosition().y);
            m_buttonReset.setPosition(sf::Vector2f(m_buttonReset.getPosition().x -offset, m_buttonReset.getPosition().y ));
            m_buttonSave.setPosition(sf::Vector2f(m_buttonSave.getPosition().x -offset, m_buttonSave.getPosition().y ));
            m_buttonBack.setPosition(sf::Vector2f(m_buttonBack.getPosition().x -offset, m_buttonBack.getPosition().y ));
            m_buttonNormalButton.setPosition(sf::Vector2f(m_buttonNormalButton.getPosition().x -offset, m_buttonNormalButton.getPosition().y ));
            m_buttonGoalButton.setPosition(sf::Vector2f(m_buttonGoalButton.getPosition().x -offset, m_buttonGoalButton.getPosition().y ));

            m_timerPanel.restart();
        }
    }

    if ( m_isAnimRight && (m_buttonPanel.getPosition().x) < m_app.getSize().x)
    {
        if( m_timerPanel.getElapsedTime().asMilliseconds() > TimePanel )
        {
            m_buttonPanel.setPosition(m_buttonPanel.getPosition().x +offset, m_buttonPanel.getPosition().y);
            m_buttonReset.setPosition(sf::Vector2f(m_buttonReset.getPosition().x +offset, m_buttonReset.getPosition().y ));
            m_buttonSave.setPosition(sf::Vector2f(m_buttonSave.getPosition().x +offset, m_buttonSave.getPosition().y ));
            m_buttonBack.setPosition(sf::Vector2f(m_buttonBack.getPosition().x +offset, m_buttonBack.getPosition().y ));
            m_buttonNormalButton.setPosition(sf::Vector2f(m_buttonNormalButton.getPosition().x +offset, m_buttonNormalButton.getPosition().y ));
            m_buttonGoalButton.setPosition(sf::Vector2f(m_buttonGoalButton.getPosition().x +offset, m_buttonGoalButton.getPosition().y ));

            m_timerPanel.restart();
        }

    }

}

int Editor::save(ScreenLink * link)
{

   if ( m_saving)
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
    for (unsigned int i = 0 ; i < m_spriteList.size(); i++)
    {
       if ( m_spriteList[i].getTexture() == &m_Buttongoal)
        {
            nbGoalPoint++;
        }
    }
    if ( nbGoalPoint != 1 )
    {
        m_textVerifSave.setString(sf::String("Level not Saved : there is not or too much goal point "));
        m_textVerifSave.setColor(sf::Color(237,28,36));
        return -1;
    }



    //sort m_spriteList
    for (unsigned int i = 0 ; i < m_spriteList.size() ; i++)
    {
        if ( m_spriteList[i].getTexture() == &m_Buttongoal)
        {
            sf::Sprite temp( m_spriteList[i]);
            m_spriteList[i] = m_spriteList[ m_spriteList.size() - 1];
            m_spriteList[ m_spriteList.size() - 1] = temp;
        }
    }

        std::vector<std::string> fileList;
        fileList.push_back("Easy");
        fileList.push_back("Normal");
        fileList.push_back("Hard");


        unsigned int numberattempt = m_spriteList.size() - 1;
        if ( numberattempt < 1)
        {
            //to avoid negative number
            numberattempt+= 2;
        }

        m_textVerifSave.setString(sf::String("Level Saved"));
        m_textVerifSave.setColor(sf::Color(34,177,76));
        for (unsigned int i = 0 ; i < TotalDifficulty ;i++)
        {
            std::ostringstream oss;
                        oss << FilenameLevelDirectory << link->getNbFiles() << "_" << fileList[i] <<".lvl" ;
            std::ofstream file(oss.str().c_str());
            if ( file.is_open())
            {
               file << m_spriteList.size() << std::endl;
               file << numberattempt << std::endl;

               for ( unsigned int j = 0 ; j < m_spriteList.size();j++)
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
    if (m_drawable)
    {
		sf::Sprite temp;
        sf::Vector2f coord = (sf::Vector2f)m_app.mapPixelToCoords((sf::Vector2i(x,y)),m_viewPerso);
        temp.setPosition(coord);

        if ( !m_chooseTexture )
        {
             temp.setTexture(m_Buttonpoint);
        }
        else
        {
        	static sf::Vector2f goalCoords;

        	std::vector<sf::Sprite>::iterator it=m_spriteList.begin();
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

            temp.setTexture(m_Buttongoal);
        }

        m_spriteList.push_back(temp);
    }
}

void Editor::popPoint()
{
    if ( m_spriteList.size() > 0)
    m_spriteList.pop_back();
}



Editor::~Editor()
{
    //dtor
}


