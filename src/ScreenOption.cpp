#include "ScreenOption.hpp"


//std::vector<Button*> m_listButton;

ScreenOption::ScreenOption(unsigned int _button)
: m_cursor(new Cursor(sf::Color(220,51,92),2)),
 m_menu(m_cursor),m_nbButton(_button)
{

    m_background.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameBackGroundMenu)));
    m_background.setColor(sf::Color(backgroundColor,backgroundColor,backgroundColor));

    Button coord(FilenameButtonOption2);
    float X =  (WindowWidth - (coord.GetSize().x / m_nbButton)) / m_nbButton ;
    int offsetX = int (X) / m_nbButton;
    float Y = (WindowHeight - (coord.GetSize().y / 2)) / 2 ;
    int offsetY = int (Y) / 2;


    m_sliding = new Button(FilenameButtonOption2,sf::Vector2f( offsetX ,Y  + offsetY));
    m_noSliding = new Button(FilenameButtonOption2,sf::Vector2f(X + offsetX , Y + offsetY));

    m_noSliding->SetLeftWidget(m_sliding);
    m_sliding->SetRightWidget(m_noSliding);



    for ( unsigned int i = 0 ; i < m_nbButton ; i++)
    {
        Button * temp = new Button(FilenameButtonOption2,sf::Vector2f(i*X + offsetX , offsetY));
        m_listButton.push_back(temp);
    }


    m_listButton[0]->SetRightWidget(m_listButton[1]);
    m_listButton[1]->SetLeftWidget( m_listButton[0]);
    m_menu.AddWidget(m_listButton[0]);
    for ( unsigned int i = 1 ; i < m_listButton.size() ; i++)
    {
        m_listButton[m_listButton.size()-1]->SetRightWidget(m_listButton[i]);
        m_listButton[i]->SetLeftWidget(m_listButton[i-1]);
        m_menu.AddWidget(m_listButton[i]);
    }

      m_listButton[m_listButton.size()-1]->SetNextWidget(m_noSliding);
      m_listButton[0]->SetNextWidget(m_sliding);

      m_noSliding->SetPreviousWidget( m_listButton[m_listButton.size()-1]);
      m_sliding->SetPreviousWidget( m_listButton[0]);

       m_menu.AddWidget(m_noSliding);
        m_menu.AddWidget(m_sliding);

    // On défini le button de sortie pour répondre à l'action Exit()
    m_menu.SetExitWidget(m_listButton[m_listButton.size() - 1]);

	// On défini les bouton play et exit comme des bouton fermant le panel
	m_listButton[0]->SetPanelExit(true);
	m_listButton[m_listButton.size() - 1]->SetPanelExit(true);

	m_menu.Display();


}

int ScreenOption::Run( sf::RenderWindow& App)
{
	bool Running = true;
    currentChoice.Play(0,3);
    currentChoice.setPosition(WindowWidth-100,100);
    currentChoice.setTexture(*TextureManager::getTextureManager()->getResource(FilenameCharacterTex),true);
    currentChoice.SetLoopTime(4);

	while( Running)
	{
		App.clear();
		App.draw(m_background);
		App.draw(currentChoice);
		m_menu.Draw(App);
		App.display();


		sf::Event event;
		//Verifing events
		App.pollEvent(event);

		if (event.type == sf::Event::Closed)
		{
			Running = false;
			App.close();
		}

		m_menu.handle_input(event);
		m_menu.TimerOperation();
		if ( event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Return)
			{
                    std::string filename ;
				    std::string type;
				    unsigned int width = 0;
				    unsigned int height = 0;
				    float friction;
                    std::ofstream configFile(FilenameConfigFile);
				if(m_listButton.size()>0)
				{
					if(m_cursor->getButton() == m_listButton[0])
					{
					    filename = "resources/sprites/bonhommeNoir.gif";
						currentChoice.setTexture(*TextureManager::getTextureManager()->getResource(filename),true);
                        currentChoice.Play(0,7);
                        friction = 0.1;
						width = 24;
						height = 34;
						currentChoice.SetFrameSize(width,height);
					}
					else if(m_cursor->getButton() == m_listButton[1])
					{
					    filename = "resources/sprites/velo.png";
						currentChoice.setTexture(*TextureManager::getTextureManager()->getResource(filename),true);
                        currentChoice.Play(0,7);
                        friction = 0.05;
						width = 50;
						height = 50;
						currentChoice.SetFrameSize(width,height);
					}
					else
					{
                        filename = "resources/sprites/bonhommeNoir.gif";
						friction = 0.1;
						width = 24;
						height = 34;
						currentChoice.setTexture(*TextureManager::getTextureManager()->getResource(filename),true);
                        currentChoice.Play(0,7);
						currentChoice.SetFrameSize(width,height);
					}
				}

				if (m_cursor->getButton() == m_noSliding )
                {
                    type =  "NoSliding";
                }
                else if (m_cursor->getButton() == m_sliding)
                {
                     type =  "WithSliding";
                }

                configFile <<"FilenameCharacterTex = "<< filename << std::endl;
                configFile << "width = "<< width << std::endl;
                configFile << "height = "<< height<< std::endl;
                configFile << "MoveType = "<<type << std::endl;
                configFile << "FrictionCoefficient = "<<friction << std::endl;
			}
			if ( event.key.code == sf::Keyboard::Escape)
				return MENU;
		}

        currentChoice.Update();
	}

return (SCREEN_EXIT);
}


ScreenOption::~ScreenOption()
{
//    delete m_cursor;
//	FOR_STL_REVERSE_ITERATOR(std::vector<Button*>, m_listButton, rit)
//	{
//		delete *rit;
//		m_listButton.erase(rit.base()-1);
//	}
}
