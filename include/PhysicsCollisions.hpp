#ifndef PHYSICSCOLLISIONS_HPP
#define PHYSICSCOLLISIONS_HPP

#include "PhysicsObject.hpp"

namespace Physics
{
//    namespace Collisions
//    {
//        bool boxesCollide(const Box &box1, const Box &box2);
//    }

    class CollisionStrategy
    {
        public:
            virtual bool isColliding() = 0;

        private:
    };

    class CollisionAABoxAABox : public CollisionStrategy
    {
        public:
            CollisionAABoxAABox();
            bool isColliding(const Box &box1, const Box &box2);
        private:
    };

} // namespace Physics

#endif // t
