#ifndef PhysicsObject_HPP
#define PhysicsObject_HPP

#include <SFML/System/Vector2.hpp>

#ifdef DEBUG
    #include <iostream>
#endif

namespace Physics
{
    class Object
    {
        friend class Engine;

        public:
            Object();
            virtual ~Object() = 0;
            Object(const Object& original);

            sf::Vector2f getPosition() const;
            void setPosition(sf::Vector2f Position);

            sf::Vector2f getVelocity() const;
            void setVelocity(sf::Vector2f Velocity);

            sf::Vector2f getThrust() const;
            void setThrust(sf::Vector2f Thrust);

            float getAngle() const;
            void setAngle(float angle);

        private:
            sf::Vector2f m_Position;
            sf::Vector2f m_Velocity;

            sf::Vector2f m_Thrust;
            float m_angle;

            bool inEngine;
    };

    inline sf::Vector2f Object::getPosition() const
    {
//        #ifdef DEBUG
//            std::cout << m_Thrust.x << std::endl;
//        #endif
        return m_Position;
    }

    inline void Object::setPosition(sf::Vector2f Position) { m_Position=Position; }

    inline sf::Vector2f Object::getVelocity() const { return m_Velocity; }
    inline void Object::setVelocity(sf::Vector2f Velocity) { m_Velocity=Velocity; }

    inline sf::Vector2f Object::getThrust() const { return m_Thrust; }
    inline void Object::setThrust(sf::Vector2f Thrust) { m_Thrust=Thrust; }

    inline float Object::getAngle() const { return m_angle; }
    inline void Object::setAngle(float angle) { m_angle = angle; }

    class Box : public Object
    {
        public:
            Box(float width=1.0f, float height=1.0f);
            ~Box();
            Box(const Box& original);

            float getWidth() const;
            float getHeight() const;
            void setSize(float width, float height);

        private:
            float m_width, m_height;
    };

    inline float Box::getWidth() const { return m_width;  }
    inline float Box::getHeight() const { return m_height;  }
    inline void Box::setSize(float width, float height) { m_width=width, m_height=height ; }
} // namespace Physics

#endif // PhysicsObject_HPP
