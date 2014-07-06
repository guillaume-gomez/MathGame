#include "VisitorObjectCollidable.h"
#include "PhysicsObject.hpp"

#include <iostream>

using namespace  Physics;

VisitorObjectCollidable::VisitorObjectCollidable()
{}

VisitorObjectCollidable::~VisitorObjectCollidable()
{}

//bool VisitBox::visit(const Object& object1, const Object& object2)
//{
//    std::cout << "Test de collision entre une 'Object' et un 'Object' "<< std::endl;
//    return true;
//
//}
//
//bool VisitBox::visit(const Box& box, const Object& object)
//{
//    std::cout << "Test de collision entre une 'Box' et un 'Object' "<< std::endl;
//    return true;
//
//}
//
//bool VisitBox::visit(const Object& object, const Box& box)
//{
//    std::cout << "Test de collision entre une 'object' et un 'box' "<< std::endl;
//    return true;
//
//}

bool VisitBox::visit(const Box& box1, const Box& box2)
{
//    std::cout << "Test de collision entre une 'Box' et un 'box' "<< std::endl;
//    std::cout << "box2.getPosition().x : " << box2.getPosition().x << std::endl;
//    std::cout << "box1.getPosition().x : " << box1.getPosition().x << std::endl;
//    std::cout << "box1.getWidth() : " << box1.getWidth() << std::endl;
//    std::cout << "box2.getPosition().x >= box1.getPosition().x + box1.getWidth() : " << (box2.getPosition().x >= box1.getPosition().x + box1.getWidth()) << std::endl;

    return !((box2.getPosition().x >= box1.getPosition().x + box1.getWidth())  // trop à droite
        || (box2.getPosition().x + box2.getWidth() <= box1.getPosition().x)  // trop à gauche
        || (box2.getPosition().y >= box1.getPosition().y + box2.getHeight()) // trop en bas
        || (box2.getPosition().y + box2.getHeight() <= box1.getPosition().y)) // trop en haut
    ;
}
