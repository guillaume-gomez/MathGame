#include "ScreenLevelChoice.hpp"

SelectLevel::SelectLevel( ScreenLink* _stat, unsigned int level, Difficulty difficulty)
: m_stat(_stat),m_difficulty(difficulty), m_level(level),m_modeSelectLevel(Classic),m_isClicked(false)
{
}

SelectLevel::~SelectLevel()
{

}

void SelectLevel::selectingLevel()
{
    std::cout << m_difficulty << " " <<  m_level << "  " << m_modeSelectLevel << std::endl;
    m_stat->setParamLevel(m_difficulty,m_level,m_modeSelectLevel);
    m_isClicked = true;
}

///////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////

ScreenLevelChoice::ScreenLevelChoice( ScreenLink* _stat)
: m_playing(false),m_selectionLevel(0),m_changingMenu(-1)
{
//   m_backgroundTex.loadFromFile(FilenameBackGroundMenu);
//   m_background.setTexture(m_backgroundTex);
   m_background.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameBackGroundMenu)));
   m_background.setColor(sf::Color(backgroundColor,backgroundColor,backgroundColor));

   m_easyTex.loadFromFile(FilenameEasyButton);
   m_normalTex.loadFromFile(FilenameNormalButton);
   m_hardTex.loadFromFile(FilenameHardButton);

   m_easyBar.setTexture(m_easyTex);
   m_normalBar.setTexture(m_normalTex);
   m_hardBar.setTexture(m_hardTex);

   m_window = sfg::Window::Create();
   m_window->SetTitle( "Resize me!" );

   m_scrolled_window_box = sfg::Box::Create(sfg::Box::VERTICAL);
   m_layoutEasy = sfg::Box::Create( sfg::Box::HORIZONTAL );
   m_layoutNormal = sfg::Box::Create( sfg::Box::HORIZONTAL );
   m_layoutHard = sfg::Box::Create( sfg::Box::HORIZONTAL );

   m_frameEasy = sfg::Frame::Create("Easy");
   m_frameNormal = sfg::Frame::Create("Normal");
   m_frameHard = sfg::Frame::Create("Hard");

    sf::Font font;
    font.loadFromFile(FilenameFont);

    for (unsigned int i = 0 ; i < _stat->getnbEasy() ; i++)
    {
        std::string directory = FilenameLevelDirectory;
        std::ostringstream oss;
        oss << i+1 ;
        SelectLevel* temp = new SelectLevel(_stat, i+1, Easy);
        m_selectionLevel.push_back(temp);
        sfg::Button::Ptr button = sfg::Button::Create(oss.str());
        button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &SelectLevel::selectingLevel, m_selectionLevel.at(i) );
        m_layoutEasy->Pack(button);
    }

    for (unsigned int i = 0 ; i < _stat->getnbNormal() ; i++)
    {
        std::string directory = FilenameLevelDirectory;
        std::ostringstream oss;
        oss << i + 1 ;
        SelectLevel* temp = new SelectLevel(_stat, i+1, Normal);
        m_selectionLevel.push_back(temp);
        sfg::Button::Ptr button = sfg::Button::Create(oss.str());
        button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &SelectLevel::selectingLevel, m_selectionLevel.at(i + _stat->getnbEasy()) );
        m_layoutNormal->Pack(button);
    }

    for (unsigned int i = 0 ; i < _stat->getnbHard() ; i++)
    {
        std::string directory = FilenameLevelDirectory;
        std::ostringstream oss;
        oss << i +1;
        SelectLevel* temp = new SelectLevel(_stat, i+1, Hard);
        m_selectionLevel.push_back(temp);
        sfg::Button::Ptr button = sfg::Button::Create(oss.str());
        button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &SelectLevel::selectingLevel, m_selectionLevel.at(i + _stat->getnbEasy() + _stat->getnbNormal()) );
        m_layoutHard->Pack(button);
    }
    m_frameEasy->Add(m_layoutEasy);
    m_frameNormal->Add(m_layoutNormal);
    m_frameHard->Add(m_layoutHard);

    m_scrolled_window_box->Pack(m_frameEasy);
    m_scrolled_window_box->Pack(m_frameNormal);
    m_scrolled_window_box->Pack(m_frameHard);
    m_window->Add(m_scrolled_window_box);
}


ScreenLevelChoice::~ScreenLevelChoice()
{
    for( unsigned int i = 0 ; i < m_selectionLevel.size();i++)
    {
        //m_selectionLevel.pop_back();
        std::cout << "jksdjgdkjgkj" << std::endl;
    }
}
