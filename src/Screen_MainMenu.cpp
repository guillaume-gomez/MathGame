#include "Screen_MainMenu.hpp"

Screen_MainMenu::Screen_MainMenu()
: m_alpha_max( 3*255),m_alpha_div(3),m_playing(false),m_cursor( new Cursor(sf::Color(220,51,92),2)),
 m_menu(m_cursor)
 {
//     m_backgroundTex.loadFromFile(FilenameBackGroundMenu);
     m_background.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameBackGroundMenu)));
     m_background.setColor(sf::Color(backgroundColor,backgroundColor,backgroundColor));

    //m_background.setPosition(WindowWidth/2 - m_background.getGlobalBounds().width/2, WindowHeight/2 - m_background.getGlobalBounds().height/2);

    Button coord(FilenameButtonGame1);

    float Y =  (WindowHeight - (coord.GetSize().y / 5)) / 5 ;
    int offsetY = int (Y) / 5;
    float X = WindowWidth /  2  - coord.GetSize().x/2;

    m_play_button = new Button(FilenameButtonGame1, sf::Vector2f(X, offsetY));
    m_play2_button= new Button(FilenameButtonGame2, sf::Vector2f(X, Y + offsetY));
    m_editor_button = new Button(FilenameButtonEditor, sf::Vector2f(X, 2*Y + offsetY));
    m_option_button = new Button(FilenameButtonOption, sf::Vector2f(X,3*Y + offsetY));
    m_credit_button = new Button(FilenameButtonCredit, sf::Vector2f(X, 4*Y + offsetY));

    //element de base
    m_play_button->SetNextWidget(m_play2_button);

    m_play2_button->SetNextWidget(m_editor_button);
    m_play2_button->SetPreviousWidget(m_play_button);

    m_editor_button->SetPreviousWidget(m_play2_button);
    m_editor_button->SetNextWidget(m_option_button);

    m_option_button->SetPreviousWidget(m_editor_button);
	m_option_button->SetNextWidget(m_credit_button);

	m_credit_button->SetPreviousWidget(m_option_button);



	// On ajoute les button à notre menu
	// Le premier widget ajouté est considéré comme le widget d'entré
	m_menu.AddWidget(m_play_button);
	m_menu.AddWidget(m_play2_button);
	m_menu.AddWidget(m_editor_button);
	m_menu.AddWidget(m_option_button);
	m_menu.AddWidget(m_credit_button);

	// On défini le button de sortie pour répondre à l'action Exit()
    m_menu.SetExitWidget(m_credit_button);

	// On défini les bouton play et exit comme des bouton fermant le panel
	m_play_button->SetPanelExit(true);
	m_credit_button->SetPanelExit(true);

	// Et on fait apparaitre notre menu
	m_menu.Display();


}

int Screen_MainMenu::Run(sf::RenderWindow& App)
{
    bool Running = true;
    int alpha = 0 ;

    if (m_playing)
    {
        alpha = m_alpha_max;
    }

    while( Running)
    {

        //display first in order to using App.waitEvent
        App.clear();
        App.draw(m_background);
        m_menu.Draw(App);
        App.display();


         sf::Event event;
         App.waitEvent(event);
        //Verifing events
        //{
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
                    if ( m_cursor->getButton() == m_play_button)
                    {
                        return LEVEL_CHOICE_ONE;
                    }
                    else if ( m_cursor->getButton() == m_play2_button)
                    {
                        return LEVEL_CHOICE_TWO;
                    }
                    else if ( m_cursor->getButton() == m_editor_button )
                    {
                        return EDITOR;
                    }
                    else if ( m_cursor->getButton() == m_option_button )
                    {
                        return OPTION;
                    }
                    else
                    {
                        return CREDIT;
                    }
                }
            }

        //}


    if ( alpha < m_alpha_max)
    {
        alpha++;
    }

    }

    return (SCREEN_EXIT);
}

Screen_MainMenu::~Screen_MainMenu()
{

}
