#include "LevelView.hpp"

#include "ObjectFactoryAbstract.hpp"

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
    ObjectFactoryAbstract::_register(TypeObject::Circle,new GravityCircle());
    ObjectFactoryAbstract::_register(TypeObject::Point,new Point(sizePoint));
    ObjectFactoryAbstract::_register(TypeObject::GoalPoint,new Point(sizePoint, true));
    ObjectFactoryAbstract::_register(TypeObject::Enemy,new Enemy());
    ObjectFactoryAbstract::_register(TypeObject::Integral,new Integral());
    ObjectFactoryAbstract::_register(TypeObject::Function,new Curves());

    //pré loading
//    float widthTex  = (float) m_texGoal.getSize().x / 2;
//    float heightTex = (float) m_texGoal.getSize().y / 2;

    loadCoord();

}


LevelView::~LevelView()
{
    for (auto it : m_listSprite)
    {
        #ifdef DEBUG
            // std::cout << "Suppression de type " << EditorObject::getTypeStr(it->getType()) << std::endl;
        #endif
        delete it;
    }
}

void LevelView::reset()
{
}

// To load if the model change
void LevelView::loadCoord()
{
    int nbPoints = m_model.getNbPoints();
    for(int i = 0 ; i < nbPoints - 1 ; i++)
    {
        switch(m_model.getType(i))
        {
            case (TypeObject::Circle):
            {
                GravityCircle * NewCircle =  dynamic_cast<GravityCircle*>(ObjectFactoryAbstract::create(m_model.getType(i)));
                if(NewCircle != nullptr)
                {
                    NewCircle->setRadius(m_model.getRadius(i));
                    NewCircle->setOrigin(m_model.getRadius(i), m_model.getRadius(i));
                    NewCircle->setPosition(m_model.getCoordPoints(i).x * m_scale/*- widthTex*/ , - m_model.getCoordPoints(i).y * m_scale/* - heightTex*/);
                    m_listSprite.push_back(NewCircle);
                }
            }
            break;
            case (TypeObject::Point):
            {
                Point * NewPoint =  dynamic_cast<Point*>(ObjectFactoryAbstract::create(m_model.getType(i)));
                if(NewPoint != nullptr)
                {
                    NewPoint->setPosition(m_model.getCoordPoints(i).x * m_scale/*- widthTex*/ , - m_model.getCoordPoints(i).y * m_scale/* - heightTex*/);
                    m_listSprite.push_back(NewPoint);
                }
            }
            break;
            case (TypeObject::Enemy):
            {
                Enemy* newEnemy =  dynamic_cast<Enemy*>(ObjectFactoryAbstract::create(m_model.getType(i)));
                if(newEnemy != nullptr)
                {
                    newEnemy->setPosition(m_model.getCoordPoints(i).x /*- widthTex*/ ,  m_model.getCoordPoints(i).y /* - heightTex*/);
                    newEnemy->setNbAttempt(m_model.getAttempt(i));
//                    std::cout << "direction << " << m_model.getSens(i) << std::endl;
                    newEnemy->setDirection(m_model.getSens(i));
                    newEnemy->addToEngine();
                    m_listSprite.push_back(newEnemy);
                }
            }
            break;

            case (TypeObject::Integral):
            {
                Integral* integral =  dynamic_cast<Integral*>(ObjectFactoryAbstract::create(m_model.getType(i)));

                if(integral != nullptr)
                {
                    integral->setFunction(m_model.getFunction(i));
                    integral->build(m_model.getBegin(i), m_model.getEnd(i));
                    m_listSprite.push_back(integral);
                }
            }
            break;

            case (TypeObject::Function):
            {

//                #ifdef DEBUG
//                    std::cout << "void LevelView::loadCoord() case (TypeObject::Function):" << EditorObject::getTypeStr(m_model.getType(i)) << std::endl;
//                #endif // DEBUG
                Curves* curves =  dynamic_cast<Curves*>(ObjectFactoryAbstract::create(m_model.getType(i)));
                if(curves != nullptr)
                {
                    curves->setFunction(m_model.getFunction(i));
                    m_listSprite.push_back(curves);
                    m_listFunctionLevel.push_back(m_model.getFunction(i));
                }
            }
            default:
            break;

        }
    }

    //the goal sprite
    Point * NewPoint = dynamic_cast<Point*>(ObjectFactoryAbstract::create(TypeObject::GoalPoint));
    NewPoint->setPosition(m_model.getGoalCoord().x * m_scale/*- widthTex*/ , - m_model.getGoalCoord().y * m_scale/* - heightTex*/);
    m_listSprite.push_back(NewPoint);

}


void LevelView::draw(sf::RenderTarget& app)
{
    for(unsigned int i = 0 ; i < m_listSprite.size(); i++)
    {
        if(m_model.getType(i) == TypeObject::Point || m_model.getType(i) == TypeObject::GoalPoint)
        {
            if(!m_model.getCheckValue(i))
            {
               m_listSprite[i]->draw(app);
            }
        }
        //other element can't be deleted, so they haven't got a check value parameter. then function still in this list
        //<!>(bad conception)<!>
        else if (m_model.getType(i) != TypeObject::Function)
        {
             m_listSprite[i]->draw(app);
        }
    }
}
