#include "ScreenLevelChoice.hpp"

/*ScreenLevelChoice::ScreenLevelChoice()
:m_playing(false),m_cursor( new Cursor(sf::Color::Yellow,3)),
 m_menu(m_cursor)
{

}
*/

ScreenLevelChoice::ScreenLevelChoice( ScreenLink* _stat)
: m_playing(false),m_cursor( new Cursor(sf::Color(50,38,94),2)),
 m_menu(m_cursor),m_stat(_stat),m_nbDifficulty(0)
{
//   m_backgroundTex.loadFromFile(FilenameBackGroundMenu);
//   m_background.setTexture(m_backgroundTex);
   m_background.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameBackGroundMenu)));
   m_background.setColor(sf::Color(backgroundColor,backgroundColor,backgroundColor));

   m_easyTex.loadFromFile(FilenameEasyButton);
   m_normalTex.loadFromFile(FilenameNormalButton);
   m_hardTex.loadFromFile(FilenameHardButton);

   m_easyBar.setTexture(m_easyTex);
   m_easyBar.setPosition(0.0f,PositionButtonEasyY - OffsetBarY);

   m_normalBar.setTexture(m_normalTex);
   m_normalBar.setPosition(0.0f,PositionButtonNormalY - OffsetBarY);

   m_hardBar.setTexture(m_hardTex);
   m_hardBar.setPosition(0.0f,PositionButtonHardY - OffsetBarY);

    sf::Font font;
    font.loadFromFile(FilenameFont);
    for (unsigned int i = 0 ; i < m_stat->getnbEasy() ; i++)
    {
        std::string directory = FilenameLevelDirectory;
        std::ostringstream oss;
        oss << i+1 ;

        Button * temp  = new Button(FilenameChooseLevel, sf::Vector2f(i*PositionButtonX + OffsetButtonX, PositionButtonEasyY),font,oss.str());
        m_easyList.push_back(temp);
    }

    for (unsigned int i = 0 ; i < m_stat->getnbNormal() ; i++)
    {
        std::string directory = FilenameLevelDirectory;
        std::ostringstream oss;
        oss << i + 1 ;

        Button * temp  = new Button(FilenameChooseLevel, sf::Vector2f(i*PositionButtonX + OffsetButtonX, PositionButtonNormalY),font,oss.str());
        m_normalList.push_back(temp);
    }

    for (unsigned int i = 0 ; i < m_stat->getnbHard() ; i++)
    {
        std::string directory = FilenameLevelDirectory;
        std::ostringstream oss;
        oss << i +1;

        Button * temp  = new Button(FilenameChooseLevel, sf::Vector2f(i*PositionButtonX + OffsetButtonX, PositionButtonHardY),font,oss.str());
        m_hardList.push_back(temp);
    }
//////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////////
    //
    sf::Color blur(255.0f,255.0,255.0,Blur);

    if ( m_easyList.size() > 1)
    {
      m_menu.AddWidget( m_easyList[0]);
      m_easyList[0]->SetRightWidget(m_easyList[1]);
      m_easyList[0]->SetNextWidget(m_normalList[0]);
    }

    for ( unsigned int i = 1 ; i < m_easyList.size(); i++)
    {
        if ( i >= m_stat->getMaxLevel(Easy))
        {
            m_easyList[i]->setColor(blur);
        }
        m_easyList[i-1]->SetRightWidget(m_easyList[i]);
        m_easyList[i]->SetLeftWidget(m_easyList[i-1]);
        m_easyList[i]->SetNextWidget(m_normalList[i]);
        m_menu.AddWidget( m_easyList[i]);
    }


    if ( m_normalList.size() > 1)
    {
      m_menu.AddWidget( m_normalList[0]);
      m_normalList[0]->SetRightWidget(m_normalList[1]);
      m_normalList[0]->SetNextWidget(m_hardList[0]);
      m_normalList[0]->SetPreviousWidget(m_easyList[0]);
    }

    for ( unsigned int i = 1 ; i < m_normalList.size(); i++)
    {
        if ( i >= m_stat->getMaxLevel(Normal))
        {
            m_normalList[i]->setColor(blur);
        }
        m_normalList[i-1]->SetRightWidget(m_normalList[i]);
        m_normalList[i]->SetLeftWidget(m_normalList[i-1]);
        m_normalList[i]->SetNextWidget(m_hardList[i]);
        m_normalList[i]->SetPreviousWidget(m_easyList[i]);
        m_menu.AddWidget( m_normalList[i]);
    }


    if ( m_hardList.size() > 1)
    {
      m_menu.AddWidget( m_hardList[0]);
      m_hardList[0]->SetRightWidget(m_hardList[1]);
      m_hardList[0]->SetPreviousWidget(m_normalList[0]);
    }

    for ( unsigned int i = 1 ; i < m_hardList.size(); i++)
    {
        if ( i >= m_stat->getMaxLevel(Hard))
        {
            m_hardList[i]->setColor(blur);
        }
        m_hardList[i-1]->SetRightWidget(m_hardList[i]);
        m_hardList[i]->SetLeftWidget(m_hardList[i-1]);
        m_hardList[i]->SetPreviousWidget(m_normalList[i]);
        m_menu.AddWidget( m_hardList[i]);
    }

    // Et on fait apparaitre notre menu
	m_menu.Display();

}

void ScreenLevelChoice::MovingMenu()
{
    // what a part of menu the cursor where
    if ( m_menu.m_down)
    {
        m_nbDifficulty = (m_nbDifficulty < TotalDifficulty) ? m_nbDifficulty+1 : TotalDifficulty-1 ;
    }

    if ( m_menu.m_up)
    {
        m_nbDifficulty = (m_nbDifficulty > 0) ? m_nbDifficulty-1 : 0 ;
    }

    int offsetRight =  ((m_cursor->GetPosition().x - WindowWidth) / PositionButtonX) + 1;
    int offsetLeft = (- m_cursor->GetPosition().x / PositionButtonX) + 1;

    switch (m_nbDifficulty)
    {
    case 0 :
            if ( m_cursor->GetPosition().x > WindowWidth )
            {
                for ( unsigned int i = 0 ;i < m_easyList.size(); i++)
                {
                    sf::Vector2f temp(m_easyList[i]->GetPosition().x  - offsetRight*PositionButtonX ,m_easyList[i]->GetPosition().y );
                    m_easyList[i]->SetPosition( temp );
                }
            }
            else if ( m_cursor->GetPosition().x <  0 )
            {
                for ( unsigned int i = 0 ;i <  m_easyList.size(); i++)
                {
                    sf::Vector2f temp(m_easyList[i]->GetPosition().x  + offsetLeft* PositionButtonX ,m_easyList[i]->GetPosition().y );
                    m_easyList[i]->SetPosition( temp );
                }
            }
        break;
    case 1:

            if (  m_cursor->GetPosition().x > WindowWidth )
            {
                for ( unsigned int i = 0 ;i < m_normalList.size(); i++)
                {
                    sf::Vector2f temp(m_normalList[i]->GetPosition().x  - offsetRight*PositionButtonX ,m_normalList[i]->GetPosition().y );
                    m_normalList[i]->SetPosition( temp );
                }
            }
            else if ( m_cursor->GetPosition().x <  0 )
            {
                for ( unsigned int i = 0 ;i <  m_normalList.size(); i++)
                {
                     sf::Vector2f temp(m_normalList[i]->GetPosition().x  +  offsetLeft*PositionButtonX ,m_normalList[i]->GetPosition().y );
                    m_normalList[i]->SetPosition( temp );
                }
            }

        break;
    case 2 :
        //then change the position of buttons

            if ( m_cursor->GetPosition().x > WindowWidth )
            {
                for ( unsigned int i = 0 ;i < m_hardList.size(); i++)
                {
                    sf::Vector2f temp(m_hardList[i]->GetPosition().x  - offsetRight*PositionButtonX  ,m_hardList[i]->GetPosition().y );
                    m_hardList[i]->SetPosition( temp );
                }
            }
            else if ( m_cursor->GetPosition().x <  0  )
            {
                for ( unsigned int i = 0 ;i <  m_hardList.size(); i++)
                {
                     sf::Vector2f temp(m_hardList[i]->GetPosition().x  + offsetLeft*PositionButtonX  ,m_hardList[i]->GetPosition().y );
                    m_hardList[i]->SetPosition( temp );
                }
            }
        break;
    default :
            break;
    }



}



ScreenLevelChoice::~ScreenLevelChoice()
{
}
