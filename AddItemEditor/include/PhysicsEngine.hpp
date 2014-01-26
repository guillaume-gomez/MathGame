#ifndef PHYSICSENGINE_HPP
#define PHYSICSENGINE_HPP

#include "ConstrueFunction.hpp"
#include "PhysicsObject.hpp"

#include <SFML/System/Vector2.hpp>

#include <list>
namespace Physics
{
    class Engine
    {
        public:

            static Engine* getEngine();

            void addObject(Object* object);
            void delObject(Object* object);
            void cleanEngine();
            void update(float elapsedSeconds);

            void setGravity(sf::Vector2f GravityAcceleration);
            sf::Vector2f getGravity() const;
            void setFunction(const ConstrueFunction* Function);
            const ConstrueFunction* getFunction() const;
            std::list<Object*> m_PhysicsObjects;

        private:
            Engine(sf::Vector2f GravityAcceleration = sf::Vector2f(0.0f, -16.677f));
            ~Engine();
            Engine(const Engine& original);

            sf::Vector2f m_GravityAcceleration;
            const ConstrueFunction* m_Function;
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
