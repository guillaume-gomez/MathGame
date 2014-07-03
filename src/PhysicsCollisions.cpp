#include "PhysicsCollisions.hpp"

using namespace Physics;

CollisionAABoxAABox::CollisionAABoxAABox()
{
}

bool CollisionAABoxAABox::isColliding(const Box &box1, const Box &box2)
{

    return box1.getPosition().x<box2.getPosition().x+box2.getWidth()
        || box2.getPosition().x<box1.getPosition().x+box1.getWidth()
        || box1.getPosition().y<box2.getPosition().y+box2.getHeight()
        || box2.getPosition().y<box1.getPosition().y+box1.getHeight()
    ;
}
