#include "PhysicsEngine.hpp"

using namespace Physics;

Engine* Engine::getEngine()
{
    static Engine engine;
    return &engine;
}

Engine::Engine(sf::Vector2f GravityAcceleration)
:m_GravityAcceleration(GravityAcceleration)
{
//    m_functionsList.push_back(&m_Function);
}

Engine::~Engine()
{
    cleanEngine();
}

Engine::Engine(const Engine& original)
{}

void Engine::addObject(Object* object)
{
    if(!object->m_inEngine)
    {
        #ifdef DEBUG
//            std::cout << "Engine::addObject object : " << object << std::endl;
        #endif // DEBUG
        m_PhysicsObjects.push_back(object);
        object->m_inEngine = true;
    }
}

void Engine::delObject(Object* object)
{
    if(object->m_inEngine)
    {
        object->collidable(false);
        m_PhysicsObjects.remove(object);
        object->m_inEngine = false;
    }
}

void Engine::addIntegral(IntegralModel* integral)
{
    if(!integral->inPhysicsEngine())
    {
//        #ifdef DEBUG
//            std::cout << "Engine::addIntegral &integral : " << &integral << " integral : " << integral << " integral->getFunction() : " << integral->getFunction() << std::endl;
//        #endif // DEBUG
        integral->m_inPhysicsEngine=true;
        m_integrals.push_back(integral);
//        #ifdef DEBUG
//            std::cout << "(const ConstrueFunction**)&integral : " << (const ConstrueFunction**)&integral << std::endl;
//            std::cout << "                       *(&integral) : " << *(&integral) << std::endl;
//        #endif // DEBUG
//        m_functionsList.push_back((const ConstrueFunction**)&(m_integrals.back()));
//        #ifdef DEBUG
//            std::cout << "Engine::addIntegral &integral : " << &integral << " (const ConstrueFunction**)&integral : " << (const ConstrueFunction**)&integral << std::endl;
//            std::cout << "Engine::addIntegral *(m_functionsList.back()) : " << *(m_functionsList.back()) << std::endl;
//        #endif // DEBUG
    }
}

void Engine::delIntegral(IntegralModel* integral)
{
//    #ifdef DEBUG
//        std::cout << "Engine::delIntegral integral : " << integral << std::endl;
//    #endif // DEBUG
//    m_functionsList.remove((const ConstrueFunction**)&integral);
    m_integrals.remove(integral);
    integral->m_inPhysicsEngine=false;
}

void Engine::cleanEngine()
{
    while(!m_PhysicsObjects.empty())
    {
        delObject(m_PhysicsObjects.front());
    }

    while(!m_integrals.empty())
    {
        delIntegral(m_integrals.front());
    }

//    m_functionsList.remove(&m_Function);

    m_Function = nullptr;
}

void Engine::update(float elapsedSeconds)
{
//    #ifdef DEBUG
//        std::cout << "------------------------ Update ------------------------ m_PhysicsObjects.size() : " << m_PhysicsObjects.size() << std::endl;
//    #endif // DEBUG
//    static float yCurve, derivative;
    Physics::Object* object;

    for(std::list<Object*>::iterator itPhysicsObjects=m_PhysicsObjects.begin(); itPhysicsObjects!=m_PhysicsObjects.end(); itPhysicsObjects++)
    {
        object = *itPhysicsObjects;

        sf::Vector2f oldGravityAcceleration(getGravity());

        if(object->collidable())
        {
//            #ifdef DEBUG
//            std::cout << "***************************************************" << std::endl;
//            #endif // DEBUG
            for(std::list<Circle*>::iterator itGravityCircle=Circle::m_gravityCircles.begin(); itGravityCircle!=Circle::m_gravityCircles.end(); itGravityCircle++)
            {
                if(object->testCollision(*(*itGravityCircle)))
                {
                    setGravity(sf::Vector2f(getGravity().x, -getGravity().y));
                    if(getGravity().y>0)
                        object->m_Position.y+=0.001;
                }
            }
//            #ifdef DEBUG
//            std::cout << "***************************************************" << std::endl;
//            #endif // DEBUG
        }

        // permet le deplacement (au ralenti) d'un objet si il est en l'air
        if( (!object->isOnCurve() && std::abs(object->m_Velocity.x) < std::abs(object->m_Thrust.x))
         || ((object->m_Thrust.x<0 && object->m_Velocity.x>0) || (object->m_Thrust.x>0 && object->m_Velocity.x<0))
          )
            object->m_Velocity.x += object->m_Thrust.x*elapsedSeconds;

        object->m_angle = 0.0f;

        bool curveBelow=false, isIntegral=false;
        float maxValue=0;
        float derivative=0;
        const ConstrueFunction* functionPtr = 0;

        if(m_Function->isRepresented(object->m_Position.x))
        {
            float y=m_Function->getFunctionValue(object->m_Position.x);
            if(y <= object->getPosition().y)
            {
                functionPtr = m_Function;
                curveBelow = true;
                maxValue = y;
                derivative = m_Function->getDerivative(object->m_Position.x);
            }
        }
        for(std::list<IntegralModel*>::const_iterator itFunctionPtr=m_integrals.cbegin(); itFunctionPtr!=m_integrals.cend(); itFunctionPtr++)
        {
            if((*itFunctionPtr)->isRepresented(object->m_Position.x))
            {
                float y = (*itFunctionPtr)->getFunctionValue(object->m_Position.x);
                if(y <= object->getPosition().y && (!curveBelow || (curveBelow && y>maxValue)))
                {
                    functionPtr = *itFunctionPtr;
                    curveBelow = true;
                    isIntegral = true;
                    if(y>=0)
                    {
                        maxValue = y;
                        derivative = (*itFunctionPtr)->getDerivative(object->m_Position.x);
                    }
                    else
                    {
                        maxValue = 0;
                        derivative = 0;
                    }
                }
            }
        }

        if(curveBelow)
        {
            // si l'objet est au dessus de la courbe (sans etre en contact)
            if(object->m_Position.y>maxValue)
            {
                object->m_Velocity.y += m_GravityAcceleration.y*elapsedSeconds;
                object->m_Position += object->m_Velocity*elapsedSeconds;

                // si le personnage a traversé la courbe on le positionne sur la courbe
                if( functionPtr->isRepresented(object->m_Position.x))
                {
                    float currentYCurve = functionPtr->getFunctionValue(object->m_Position.x);
                    if(isIntegral && currentYCurve<0)
                        currentYCurve=0;
                    if((object->m_Position.y < currentYCurve))
                    {
                        object->m_Position.y=currentYCurve;
    //                    object->m_Position.y=maxValue;
                        object->isOnCurve();
                    }
                    else
                    {
                        object->jump(false);
                        object->isOnCurve(false);
                    }
                }
                else
                {
                    object->jump(false);
                    object->isOnCurve(false);
                }
            }
            // si le personnage est sur la courbe
            else if(object->m_Position.y == maxValue)
            {
                object->m_Velocity.x=cos(atan2(derivative, (object->m_Thrust.x<0 ? -1 : 1)))*abs(object->m_Thrust.x);
                if(object->m_jumping)
                {
                    object->m_Velocity.y = JumpSpeed;
                }
                else
                {
                    object->m_Velocity.y=sin(atan2(derivative, (object->m_Thrust.x<0 ? -1 : 1)))*object->m_Thrust.x;
                }

                object->m_Position += object->m_Velocity*elapsedSeconds;
                // si apres déplacement le personnage est toujours dans une zone où la courbe est représentée
                if(functionPtr->isRepresented(object->m_Position.x))
                {
                    // si le personnage est en dessous de la courbe (due aux erreurs inéluctables de précision de calcul)
                    // alors correction en placant le personnage sur la bonne coordonnée y
                    // si il est au dessus, on ne fait rien et au prochain appel de cette methode le perso sera déplacé en retombant selon la gravité
    /*************************************************/
                    float currentYCurve = functionPtr->getFunctionValue(object->m_Position.x);
                    if(isIntegral && currentYCurve<0)
                        currentYCurve=0;
                    if((object->m_Position.y < currentYCurve))
                    {
                        object->m_Position.y=currentYCurve;
                        object->isOnCurve();
                    }
                    else
                    {
                        object->isOnCurve(false);
                    }
    /***************************************************/
                }
                else
                    object->isOnCurve(false);

            }
            // si le personnage est en dessous de la courbe
            else
            {
                object->m_Velocity.y += m_GravityAcceleration.y*elapsedSeconds;
                object->m_Position += object->m_Velocity*elapsedSeconds;
                object->isOnCurve(false);
            }
            object->m_angle = atan(derivative);
        }
        else
        {
            object->m_Velocity.y += m_GravityAcceleration.y * elapsedSeconds;
            object->m_Position += object->m_Velocity * elapsedSeconds;
            object->isOnCurve(false);
        }

        bool revertMove = false;
        for(std::list<IntegralModel*>::const_iterator itFunctionPtr=m_integrals.cbegin(); itFunctionPtr!=m_integrals.cend() && !revertMove; itFunctionPtr++)
        {
            if(*itFunctionPtr != functionPtr && (*itFunctionPtr)->isRepresented(object->m_Position.x))
            {
                float fctY = (*itFunctionPtr)->getFunctionValue(object->getPosition().x);
                float objY = object->getPosition().y+object->getHeight();

                if( (objY>=fctY && objY<=0)
                 || (objY<=fctY && objY>=0)
                  )
                {
                    revertMove = true;
                }
            }
        }

        if(revertMove)
        {
            object->m_Velocity.x *= -1.0f;
            object->m_Position += object->getVelocity() * elapsedSeconds;
//            if(object->getVelocity().y>0)
//                object->m_Velocity.y=0;
            object->m_Velocity.x=0;
        }

        setGravity(oldGravityAcceleration);
    }
}

void Engine::resetAllObjects()
{
    for(Physics::Object* object : m_PhysicsObjects)
    {
        object->setAllToNull();
    }
}
