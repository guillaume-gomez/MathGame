#include "ManageLevel.hpp"

sf::Texture ManageLevel::toolTipTex;


bool ManageLevel::toolTipTexLoaded = loadToolTipTex(FilenameToolTipTex);

bool ManageLevel::loadToolTipTex(const char* filenameToolTipText)
{
    return toolTipTex.loadFromFile(filenameToolTipText);
}


ManageLevel::ManageLevel(unsigned int _level, Difficulty _diff, float _scale)
:m_scale(_scale), m_difficulty(_diff), m_levelCurrent(_level), m_changeLevel(false), m_isDisplayToolTip(false)
{
    std::string directory = FilenameLevelDirectory;
    std::ostringstream oss;
    oss << m_levelCurrent << "_" << convertEnum(m_difficulty) << ".lvl";
    directory += oss.str();
    m_filenameCurrent = oss.str();

    m_levelModel = new LevelModel(directory);
    m_levelView = new LevelView(*m_levelModel, m_scale);

    m_tooltip.setTexture(toolTipTex);

    if(!m_font.loadFromFile(FilenameFont))
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
    delete m_levelView;
    delete m_levelModel;
}


void ManageLevel::loadFile(int numLevel, GameMode mode)
{
    delete m_levelView;
    delete m_levelModel;

    std::string directory = FilenameLevelDirectory;

    setLevel( numLevel);
    std::ostringstream oss;
    oss << numLevel << "_" << convertEnum(m_difficulty) << ".lvl";
    directory += oss.str();
    m_filenameCurrent = oss.str();

    m_levelModel = new LevelModel(directory, mode );
    m_levelView = new LevelView(*m_levelModel, m_scale);
}

void ManageLevel::IsNextLevel()
{
    if(m_levelModel->isWin())
    {
         m_changeLevel = true;
    }
}

void ManageLevel::levelFinished (CharacterModel& charModel, bool & soundplayable)
{
    m_levelModel->IsLosing();
    m_levelModel->IsFinishing(charModel,m_scale, soundplayable);
    if(m_levelModel->isWin() || m_levelModel->IsLose())
    {
        m_changeLevel = true;
    }
}

int  ManageLevel::changeLevel (ScreenLink * link)
{
    if(m_changeLevel)
    {
        if(m_levelModel->isWin())
        {
            //load an other level

            if(getLevel() + 1 > link->getnbNormal())
            {
                return - 1 ;
            }
//            link->setMaxLevel( link->getDiff() , link->getCurrentLevel() + 1 );
            setLevel(getLevel() + 1);
            loadFile(getLevel(), m_levelModel->getMode());
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
    m_levelModel->reset();
    m_changeLevel = false;
}

void ManageLevel::displaying(sf::Event& event , sf::RenderTarget& target , sf::View& myView)
{
	std::vector<EditorCircle*> temp = m_levelView->getSpriteList();
	if(event.type == sf::Event::MouseMoved)
	{
        m_isDisplayToolTip = false;
		int x = event.mouseMove.x;
		int y = event.mouseMove.y;
		sf::Vector2f coord = target.mapPixelToCoords((sf::Vector2i(x, y)), myView);

		for(unsigned int i = 0 ; i < temp.size() ; i++)
        {
            if(temp[i]->getType() == TypeObject::Point || temp[i]->getType() == TypeObject::GoalPoint)
            {
                if(temp[i]->getGlobalBounds().contains(coord.x, coord.y))
                {
                        m_isDisplayToolTip = true;
                        sf::Vector2i position = target.mapCoordsToPixel(temp[i]->getPosition(), myView);

                        position.x -= toolTipTex.getSize().x ;
                        position.y -= toolTipTex.getSize().y ;

                        std::string info ;
                        std::ostringstream oss;
                        oss << "x = " << m_levelModel->getCoordPoints(i).x <<"\ny = " <<m_levelModel->getCoordPoints(i).y ;
                        info += oss.str();

                        m_text.setString(info);
                        m_text.setPosition(sf::Vector2f(position.x + m_tooltip.getLocalBounds().width / 2 - m_text.getLocalBounds().width / 2 ,position.y + m_tooltip.getLocalBounds().height / 2 - m_text.getLocalBounds().height / 2 - 10.0f));
                        m_tooltip.setPosition((sf::Vector2f)position);
                }
            }
        }
    }
}


void ManageLevel::displayNbAttempt()
{
     std::string nbAttemp ;
     std::ostringstream oss;
     oss <<"Nb attempts : " << m_levelModel->getNbAttempt() <<" / " << m_levelModel->getSaveAttempt() ;
     nbAttemp += oss.str();

     m_nbAttemp.setString(nbAttemp);
}

void ManageLevel::drawPoints( sf::RenderTarget& app)
{
	m_levelView->draw(app);
}
void ManageLevel::drawUI( sf::RenderTarget& app)
{
    if(m_isDisplayToolTip)
    {
        app.draw(m_tooltip);
        app.draw(m_text);
    }
        app.draw(m_nbAttemp);
}


std::string ManageLevel::convertEnum ( Difficulty _diff)
{
    std::string val;

    switch (_diff)
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
