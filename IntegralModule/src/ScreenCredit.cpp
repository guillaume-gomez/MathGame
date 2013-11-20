#include "ScreenCredit.hpp"

ScreenCredit::ScreenCredit():picture(0),alpha(0.0f),m_HangStart(false),m_won(false),m_enterText(false)
{
    srand(time(NULL));
    sf::Color color (112,146,190);

    m_font.loadFromFile(FilenameFont);

    m_hanged.loadFromFile(FilenameHanged);
    m_hangGui.setTexture(m_hanged);
    m_hangGui.setColor(color);
//
//    m_textbg.loadFromFile(FilenameBackGroundMenu);
//    m_bg.setTexture(m_textbg);
   m_bg.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameBackGroundMenu)));

    m_bg.setColor(sf::Color(backgroundColor,backgroundColor,backgroundColor));
    m_textUnderline.loadFromFile(FilenameUnderline);
    m_underline.setTexture(m_textUnderline);
    m_underline.setColor(color);

    m_stringList.push_back(sf::String("A video Game"));
    m_stringList.push_back(sf::String("Made by : "));
    m_stringList.push_back(sf::String("Adrien Jarretier"));
    m_stringList.push_back(sf::String("And "));
    m_stringList.push_back(sf::String("Guillaume Gomez"));
    m_stringList.push_back(sf::String("These guys"));
    m_stringList.push_back(sf::String("are"));

    m_wordText.setFont(m_font);
    m_wordText.setColor(color);


    m_underline.setPosition(WindowWidth/2 , WindowHeight/2 + m_wordText.getGlobalBounds().height + 30);
    m_underline.setColor(color);
    m_hangGui.setPosition(0,WindowHeight/2 - m_hangGui.getGlobalBounds().height/2 );
    m_hangGui.setColor(color);

    for (unsigned int i = 0 ; i < m_stringList.size(); i++)
    {
        sf::Text temp;
                 temp.setFont(m_font);
                 temp.setString(m_stringList[i]);
                 temp.setColor(color);
                 unsigned int x = rand() % WindowWidth/2;
                 unsigned int y = rand() % WindowHeight/2;

            temp.setPosition((float)x,(float)y);
           m_textList.push_back(temp);
    }

}

int ScreenCredit::Run ( sf::RenderWindow &App)
{
    bool Running = true;
    m_clock.restart();
    m_clockAlpha.restart();
    int time = 2 ;
    m_HangStart = false;
    m_won = false;
    m_enterText= false;
    picture = 0 ;
    m_word ="L ";

    while( Running)
    {
         sf::Event event;
        //Verifing events
        while( App.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Running = false;
                return SCREEN_EXIT;
                App.close();
            }

            if ( event.type == sf::Event::KeyPressed)
            {
               if (event.key.code == sf::Keyboard::Escape)
               {
                   return MENU;
               }
            }
            handle_input(event);
        }

        if (m_clock.getElapsedTime().asSeconds() >= (float)time)
        {
            m_clock.restart();
            picture++;

            if ( picture >= m_stringList.size() )
            {
                picture--;
                m_HangStart = true;
            }

            if (m_won)
            {
                return MENU;
            }
            alpha = 0;
        }

        if ( m_clockAlpha.getElapsedTime().asSeconds() >= ((time)/255.0f))
        {
            if ( !m_HangStart)
            {
                alpha++;
            }
            m_clockAlpha.restart();

            if (alpha > 255) alpha = 0 ;
        }

    if (m_HangStart)
    {
        hanged();
    }


    m_wordText.setPosition(WindowWidth/2 , WindowHeight/2);
    sf::Color color = m_textList[picture].getColor();
    m_textList[picture].setColor(sf::Color(color.r,color.g,color.b,alpha));

    App.clear();
    App.draw(m_bg);
    if (m_HangStart)
    {
        App.draw(m_underline);
        App.draw(m_hangGui);
        App.draw(m_wordText);
    }
    App.draw(m_textList[picture]);
    App.display();

    }
    return SCREEN_EXIT;
}

ScreenCredit::~ScreenCredit()
{
    //dtor
}

void ScreenCredit::hanged()
{
    std::string finish1("L O O S E R ");
    std::string finish2("L o o s e r ");

    if ( (m_word == finish1 || m_word == finish2) && m_enterText)
    {
        m_word = "YOU WON :)";
        m_won = true;
    }
   /* else if ( m_enterText )
    {
        std::string word = m_word.toAnsiString();
        std::string temp;
        for ( unsigned int i = 0 ; i < word.size();i++)
        {
            if ( word[i] == finish1[i] || word[i] == finish2[i] )
            {
                temp.push_back(word[i]);
            }
            else
            {
                temp.push_back(' ');
            }
        }
        m_word = temp;
    }*/
    m_enterText = false;
}

void ScreenCredit::handle_input(sf::Event& event )
{
    if ( event.type == sf::Event::KeyPressed)
     {
     	switch(event.key.code)
     	{
		case sf::Keyboard::BackSpace:
			if(m_word.getSize()>0)
            {
				m_word.erase( m_word.getSize() - 1 );
            }
			break;
        case sf::Keyboard::Return  :
            m_enterText = true;
        break;
		default:
			break;
     	}
     }

     if (event.type == sf::Event::TextEntered)
     {
     	if(isprint(event.text.unicode))
		{
         sf::String temp( event.text.unicode );
         m_word += temp;
         m_word += ' ';

		}
     }

	m_wordText.setString( m_word );
}

