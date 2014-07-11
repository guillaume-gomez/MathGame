#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include "ConstrueFunction.hpp"
#include "IntegralModel.hpp"
#include "PhysicsObject.hpp"
#include "VisitorObjectCollidable.h"

#include "../constants.hpp"

#include <SFML/System/Vector2.hpp>

#include <cmath>
#include <list>

class IntegralModel;

namespace Physics
{
    class Engine
    {
        public:

            static Engine* getEngine();

            void addObject(Object* object);
            void delObject(Object* object);
            void addIntegral(IntegralModel* object);
            void delIntegral(IntegralModel* object);
            void cleanEngine();
            void update(float elapsedSeconds);

            void setGravity(sf::Vector2f GravityAcceleration);
            sf::Vector2f getGravity() const;
            void setFunction(const ConstrueFunction* Function);
            const ConstrueFunction* getFunction() const;
            std::list<Object*> m_PhysicsObjects;
            std::list<IntegralModel*> m_integrals;
            void resetAllObjects();

        private:
            Engine(sf::Vector2f GravityAcceleration = GravityAcceleration);
            ~Engine();
            Engine(const Engine& original);

            sf::Vector2f m_GravityAcceleration;
            const ConstrueFunction* m_Function;

//            std::list<const ConstrueFunction**> m_functionsList;

            //ensuite transformé ce visiteur par une map de visiteur avec pour clé le type de l'objet
    };

    inline void Engine::setGravity(sf::Vector2f GravityAcceleration)
    {
        m_GravityAcceleration=GravityAcceleration;
    }

    inline sf::Vector2f Engine::getGravity() const
    {
        return m_GravityAcceleration;
    }

    inline void Engine::setFunction(const ConstrueFunction* Function)
    {
        m_Function = Function;
    }

    inline const ConstrueFunction* Engine::getFunction() const
    {
        return m_Function;
    }
} // namespace Physics

#endif // PHYSICSENGINE_HPP
