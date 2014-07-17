#include "VisitorObjectCollidable.h"
#include "PhysicsObject.hpp"

#include <iostream>

using namespace  Physics;

VisitorObjectCollidable::VisitorObjectCollidable()
{}

VisitorObjectCollidable::~VisitorObjectCollidable()
{}

bool VisitBox::visit(const Box& box1, const Box& box2)
{
//    #ifdef DEBUG
//        std::cout << "box1.width : " << box1.getWidth() << " box2.width : " << box2.getWidth() << std::endl;
//        std::cout << "box1.x : " << box1.getPosition().x << " box2.x : " << box2.getPosition().x << std::endl;
//    #endif // DEBUG
    return !((box2.getPosition().x >= box1.getPosition().x + box1.getWidth()/2)  // trop à droite
        || (box2.getPosition().x + box2.getWidth()/2 <= box1.getPosition().x)  // trop à gauche
        || (box2.getPosition().y >= box1.getPosition().y + box2.getHeight()/2) // trop en bas
        || (box2.getPosition().y + box2.getHeight()/2 <= box1.getPosition().y)) // trop en haut
    ;
}

bool VisitBox::visit(const Box& box, const Circle& circle)
{
//    #ifdef DEBUG
//        std::cout << "box : "     << "x : " << box.getPosition().x    << " y : " << box.getPosition().y << std::endl;
//        std::cout << "circle : "  << "x : " << circle.getPosition().x << " y : " << circle.getPosition().y << std::endl << std::endl;
//    #endif // DEBUG

    float x,y;
    float boxCenterY = box.getPosition().y+box.getHeight()/2;

    if(box.getPosition().x > circle.getPosition().x)
        x = box.getPosition().x-circle.getPosition().x;
    else
        x = circle.getPosition().x-box.getPosition().x;

    if(boxCenterY > circle.getPosition().y)
        y = boxCenterY-circle.getPosition().y;
    else
        y = circle.getPosition().y-boxCenterY;

    return (sqrt(x*x+y*y) <= (box.getWidth()/2 + circle.getRadius()) );
}
