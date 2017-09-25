/*
 *  A 2D video game in C++ with SFML where platforms are actually Maths Curves resulting of equations you write
 *  Copyright (C) 2013,2017  Gomez Guillaume, Jarretier Adrien
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.*
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contact us on Github : https://github.com/guillaume-gomez/MathGame
 *                      or https://github.com/AdrienJarretier
 */

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
