#include "LevelView.hpp"

sf::Texture LevelView::m_texNormal;
sf::Texture LevelView::m_texGoal;

bool LevelView::TexturesLoaded = (loadTex()) ;

bool LevelView::loadTex(const char* _filenameNormalText, const char* _filenameGoalText)
{
    bool isLoadedNormal = m_texNormal.loadFromFile(_filenameNormalText);
    bool isLoadedGoal = m_texGoal.loadFromFile(_filenameGoalText);

    return (isLoadedGoal && isLoadedNormal);
}

LevelView::LevelView()
:m_model(std::string())
{
}

LevelView::LevelView(const LevelModel& model, float _scale)
:m_model(model), m_scale(_scale)
{
    int nbPoints = m_model.getNbPoints();

    //pré loading
    float widthTex  = (float) m_texGoal.getSize().x / 2;
    float heightTex = (float) m_texGoal.getSize().y / 2;

    for(int i = 0 ; i < nbPoints - 1 ; i++)
    {
        sf::Sprite temp(LevelView::m_texNormal);
                   temp.setPosition(m_model.getCoordPoints(i).x * m_scale - widthTex , - m_model.getCoordPoints(i).y * m_scale  - heightTex);
        m_listSprite.push_back(temp);
    }

    //the goal sprite
    sf::Sprite temp( LevelView::m_texGoal);
               temp.setPosition(m_model.getGoalCoord().x * m_scale- widthTex,  - m_model.getGoalCoord().y * m_scale - heightTex );
    m_listSprite.push_back(temp);

}


LevelView::~LevelView()
{
    //dtor
}

// To load if the model change
void LevelView::loadCoord()
{
    float widthTex  = (float) m_texGoal.getSize().x / 2;
    float heightTex = (float) m_texGoal.getSize().y / 2;

    for(unsigned int i = 0 ; i < m_listSprite.size() - 1 ; i++)
    {
        sf::Vector2f coord(m_model.getCoordPoints(i).x * m_scale - widthTex, - m_model.getCoordPoints(i).y * m_scale - heightTex);
        m_listSprite[ i ].setPosition(coord);
    }

     sf::Vector2f coord(m_model.getGoalCoord().x * m_scale - widthTex, - m_model.getGoalCoord().y * m_scale  - heightTex);
        m_listSprite[ m_listSprite.size() - 1 ].setPosition(coord);


}


void LevelView::draw(sf::RenderTarget& app)
{
    for(unsigned int i = 0 ; i < m_listSprite.size(); i++)
    {
        if(!m_model.getCheckValue(i))
        {
           app.draw(m_listSprite[i]);
        }
    }
}
