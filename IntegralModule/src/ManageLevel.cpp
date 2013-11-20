#include "ManageLevel.hpp"

sf::Texture ManageLevel::toolTipTex;


bool ManageLevel::toolTipTexLoaded = loadToolTipTex(FilenameToolTipTex);

bool ManageLevel::loadToolTipTex(const char* filenameToolTipText)
{
    return toolTipTex.loadFromFile(filenameToolTipText);
}


ManageLevel::ManageLevel(unsigned int _level  ,  Difficulty _diff , float _scale)
:m_scale(_scale),m_difficulty(_diff),m_levelCurrent(_level),m_changeLevel(false),m_isDisplayToolTip(false)
{
    std::string directory = FilenameLevelDirectory;
    std::ostringstream oss;
    oss << m_levelCurrent << "_" << convertEnum(m_difficulty) << ".lvl";
    directory += oss.str();
    m_filenameCurrent = oss.str();

    m_LevelModel = new LevelModel (directory);
    m_LevelView = new LevelView(*m_LevelModel,m_scale);

    m_tooltip.setTexture(toolTipTex);

    if ( !m_font.loadFromFile(FilenameFont))
    {
    	#ifdef DEBUG
			std::cerr << "Error : ManageText::ManageText()" << std::endl;
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
    delete m_LevelView;
    delete m_LevelModel;
}


void ManageLevel::loadFile(int numLevel , GameMode mode)
{
    delete m_LevelView;
    delete m_LevelModel;

    std::string directory = FilenameLevelDirectory;

    setLevel( numLevel);
    std::ostringstream oss;
    oss << numLevel << "_" << convertEnum(m_difficulty) << ".lvl";
    directory += oss.str();
    m_filenameCurrent = oss.str();

    m_LevelModel = new LevelModel (directory , mode );
    m_LevelView = new LevelView(*m_LevelModel,m_scale);
}

void ManageLevel::IsNextLevel()
{
    if ( m_LevelModel->isWin() )
    {
         m_changeLevel = true;
    }
}

void ManageLevel::levelFinished ( CharacterModel& charModel,bool & soundplayable)
{
    m_LevelModel->IsLosing();
    m_LevelModel->IsFinishing(charModel,m_scale, soundplayable);
    if ( m_LevelModel->isWin() || m_LevelModel->IsLose())
    {
        m_changeLevel = true;
    }
}

int  ManageLevel::changeLevel (ScreenLink * link)
{
    if ( m_changeLevel)
    {
        if ( m_LevelModel->isWin())
        {
            //load an other level

            if ( getLevel() + 1 > link->getnbNormal() )
            {
                return - 1 ;
            }
//            link->setMaxLevel( link->getDiff() , link->getCurrentLevel() + 1 );
            setLevel( getLevel() + 1);
            loadFile( getLevel(), m_LevelModel->getMode());
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
    m_LevelModel->reset();
    m_changeLevel = false;
}

void ManageLevel::displaying(sf::Event& event , sf::RenderTarget& target , sf::View& myView)
{
	std::vector<sf::Sprite> temp = m_LevelView->getSpriteList();
	m_isDisplayToolTip = false;
	if(event.type == sf::Event::MouseMoved)
	{
		int x =  event.mouseMove.x;
		int y =  event.mouseMove.y;
		sf::Vector2f coord = target.mapPixelToCoords((sf::Vector2i(x,y)),myView);

		for ( unsigned int i = 0 ; i < temp.size() ; i++)
		{
			if ( temp[i].getGlobalBounds().contains(coord.x,coord.y) )
			{
				m_isDisplayToolTip = true;
				sf::Vector2i position = target.mapCoordsToPixel(temp[i].getPosition(),myView);

				position.x -= toolTipTex.getSize().x ;
				position.y -= toolTipTex.getSize().y ;

				std::string info ;
				std::ostringstream oss;
				oss << "x = " << m_LevelModel->getCoordPoints(i).x <<"\ny = " <<m_LevelModel->getCoordPoints(i).y ;
				info += oss.str();

				m_text.setString(info);
				m_text.setPosition(sf::Vector2f(position.x + m_tooltip.getLocalBounds().width/2 - m_text.getLocalBounds().width/2 ,position.y + m_tooltip.getLocalBounds().height/2 - m_text.getLocalBounds().height/2 - 10.0f ));
				m_tooltip.setPosition((sf::Vector2f)position);
			}
		}
	}
}


void ManageLevel::displayNbAttempt()
{
     std::string nbAttemp ;
     std::ostringstream oss;
     oss <<"Nb attempts : " << m_LevelModel->getNbAttempt() <<" / " << m_LevelModel->getSaveAttempt() ;
     nbAttemp += oss.str();

     m_nbAttemp.setString(nbAttemp);
}

void ManageLevel::drawPoints( sf::RenderTarget& app)
{
	m_LevelView->draw(app);
}
void ManageLevel::drawUI( sf::RenderTarget& app)
{
    if( m_isDisplayToolTip )
    {
        app.draw(m_tooltip);
        app.draw(m_text);
    }
        app.draw(m_nbAttemp);
}


std::string ManageLevel::convertEnum ( Difficulty _diff)
{
    std::string val;

    switch ( _diff)
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
