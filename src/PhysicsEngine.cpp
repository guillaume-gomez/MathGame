#include "PhysicsEngine.hpp"

using namespace Physics;

Engine* Engine::getEngine()
{
    static Engine engine;
    return &engine;
}

Engine::Engine(sf::Vector2f GravityAcceleration)
:m_GravityAcceleration(GravityAcceleration)
{}

Engine::~Engine()
{}

Engine::Engine(const Engine& original)
{}

void Engine::addObject(Object* object)
{
    if(!object->m_inEngine)
    {
        m_PhysicsObjects.push_back(object);
        object->m_inEngine = true;
    }
}

void Engine::delObject(Object* object)
{
    if(object->m_inEngine)
    {
        m_PhysicsObjects.remove(object);
        object->m_inEngine = false;
    }
}

void Engine::cleanEngine()
{
    while(!m_PhysicsObjects.empty())
    {
        delObject(m_PhysicsObjects.front());
    }
    m_Function = nullptr;
}

void Engine::update(float elapsedSeconds)
{
    static float yCurve, derivative;
    Physics::Object* object;
    //for(Physics::Object* object : m_PhysicsObjects)
//    #ifdef DEBUG
//        std::cout << "m_PhysicsObjects.size() : " << m_PhysicsObjects.size() << std::endl;
//    #endif // DEBUG
    for(std::list<Object*>::iterator itPhysicsObjects=m_PhysicsObjects.begin(); itPhysicsObjects!=m_PhysicsObjects.end(); itPhysicsObjects++)
    {
        object = *itPhysicsObjects;
        for(std::list<Object*>::const_iterator it = std::next(itPhysicsObjects, 1) ; it != m_PhysicsObjects.cend() ; it++)
        {
            #ifdef DEBUG
                std::cout << "15" << std::endl;
            #endif // DEBUG
        }
            #ifdef DEBUG
                std::cout << "U     U" << std::endl;
            #endif // DEBUG

        if((!object->m_onCurve && std::abs(object->m_Velocity.x)<std::abs(object->m_Thrust.x))
        || ((object->m_Thrust.x<0 && object->m_Velocity.x>0) || (object->m_Thrust.x>0 && object->m_Velocity.x<0))
        )
            object->m_Velocity.x += object->m_Thrust.x*elapsedSeconds;

        object->m_angle = 0.0f;
        if(m_Function->isRepresented(object->m_Position.x))
        {
            yCurve = m_Function->getFunctionValue(object->m_Position.x);
            if(object->m_Position.y>yCurve)
            {
//                bool prevVelocityYPos = object->m_Velocity.y>0;
        //				elapsedSeconds = m_timer.getElapsedTime().asSeconds();
                object->m_Velocity.y += m_GravityAcceleration.y*elapsedSeconds;
              //  if(prevVelocityYPos && object->m_Velocity.y<=0)

                object->m_Position += object->m_Velocity*elapsedSeconds;
                // si le personnage a traversé la courbe on le positionne sur la courbe
                if(m_Function->isRepresented(object->m_Position.x) && (object->m_Position.y < m_Function->getFunctionValue(object->m_Position.x)))
                {
                    object->m_Position.y=m_Function->getFunctionValue(object->m_Position.x);
                    object->isOnCurve();
                }
                else
                {
                    object->jump(false);
                    object->isOnCurve(false);
                }
            }
            // si le personnage est sur la courbe
            else if(object->m_Position.y == yCurve)
            {
                derivative=m_Function->getDerivative(object->m_Position.x);
                object->m_Velocity.x=cos(atan2(derivative, (object->m_Thrust.x<0 ? -1 : 1)))*abs(object->m_Thrust.x);
                if(object->m_jumping)
                {
                    object->m_Velocity.y = JumpSpeed;
                }
                else
                    object->m_Velocity.y=sin(atan2(derivative, (object->m_Thrust.x<0 ? -1 : 1)))*object->m_Thrust.x;

        //				object->m_Position += object->m_Velocity*m_timer.getElapsedTime().asSeconds();
                object->m_Position += object->m_Velocity*elapsedSeconds;
                // si apres déplacement le personnage est toujours dans une zone où la courbe est représentée
                if(m_Function->isRepresented(object->m_Position.x))
                {
                    yCurve = m_Function->getFunctionValue(object->m_Position.x);
                    // si le personnage est en dessous de la courbe (due aux erreurs inéluctables de précision de calcul)
                    // alors correction en placant le personnage sur la bonne coordonnée y
                    // si il est au dessus, on ne fait rien et au prochain appel de cette methode le perso sera déplacé en retombant selon la gravité
                    if(object->m_Position.y < yCurve)
                    {
                        object->m_Position.y = yCurve;
                        object->isOnCurve();
                    }
                    else
                        object->isOnCurve(false);
                }
                else
                    object->isOnCurve(false);

            }
            // si le personnage est en dessous de la courbe
            else
            {
        //				elapsedSeconds = m_timer.getElapsedTime().asSeconds();
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
    }
            #ifdef DEBUG
                std::cout << "**************" << std::endl;
            #endif // DEBUG
}

void Engine::resetAllObjects()
{
    for(Physics::Object* object : m_PhysicsObjects)
    {
        #ifdef DEBUG
            // std::cout << " caca caca caca caca caca caca avant : " << object->getVelocity().x << std::endl;
        #endif
        object->setAllToNull();
        #ifdef DEBUG
            // std::cout << " caca caca caca caca caca caca apres : " << object->getVelocity().x << std::endl;
        #endif
    }
}
