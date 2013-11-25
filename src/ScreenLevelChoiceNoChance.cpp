#include "ScreenLevelChoiceNoChance.hpp"

ScreenLevelChoiceNoChance::ScreenLevelChoiceNoChance(ScreenLink* _stat)
:ScreenLevelChoice(_stat)
{
    for(unsigned int i=0; i < m_selectionLevel.size();i++)
    {
        m_selectionLevel.at(i)->setGameMode(NoChance);
    }
}

ScreenLevelChoiceNoChance::~ScreenLevelChoiceNoChance()
{
    //dtor
}


int ScreenLevelChoiceNoChance::Run(sf::RenderWindow & App)
{
 bool Running = true;
    App.resetGLStates();

    // Create the ScrolledWindow.
	sfg::ScrolledWindow::Ptr scrolledwindow = sfg::ScrolledWindow::Create();

	scrolledwindow->SetScrollbarPolicy( sfg::ScrolledWindow::HORIZONTAL_ALWAYS | sfg::ScrolledWindow::VERTICAL_AUTOMATIC );
	//scrolledwindow->AddWithViewport( m_scrolled_window_box );

	// Always remember to set the minimum size of a ScrolledWindow.
	scrolledwindow->SetRequisition( sf::Vector2f( 500.f, 100.f ) );
	m_window->SetPosition(sf::Vector2f(App.getSize().x / 2.0f - m_window->GetAllocation().width /2.0f, App.getSize().y / 2.0f - m_window->GetAllocation().height /2.0f));

    m_window->Show(true);
	//m_scrolled_window_box->Pack( scrolledwindow, false, true );
    while(Running)
    {
         sf::Event event;
          m_changingMenu = -1;
        //Verifing events
        while( App.pollEvent(event))
        {
            // Handle events
			m_window->HandleEvent( event );
            if (event.type == sf::Event::Closed)
            {
                Running = false;
                App.close();
            }

            if ( event.type == sf::Event::KeyPressed)
            {
                if ( event.key.code == sf::Keyboard::Escape)
                {
                    m_window->Show(false);
                    return MENU;
                }
            }

             for(unsigned int i=0; i < m_selectionLevel.size();i++)
            {
                if(m_selectionLevel.at(i)->isClicked())
                {
                    m_selectionLevel.at(i)->unclicked();
                    m_window->Show(false);
                    return GAME;
                }
            }

        }
    m_window->Update( 0.f );

    App.clear();
    App.draw(m_background);
    sfgui.Display( App );
    App.display();

    }

return (SCREEN_EXIT);
}
