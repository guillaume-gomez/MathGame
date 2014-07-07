#ifndef VISITOROBJECTCOLLIDABLE_H
#define VISITOROBJECTCOLLIDABLE_H

namespace Physics
{
    class Object;
    class Box;
    class Circle;
    /**
    @brief : Interface to visit each object collidable
    **/
    class VisitorObjectCollidable
    {
        public:
            VisitorObjectCollidable();
            virtual ~VisitorObjectCollidable();
            virtual bool visit(const Box& box1, const Box& box2) = 0;
            virtual bool visit(const Box& box, const Circle& circle) = 0;
    };

    /**
    @brief : Methods which check colission with any other element than a BOX (square)
    **/
    class VisitBox : public VisitorObjectCollidable
    {
        public:
            virtual bool visit(const Box& box1, const Box& box2);
            virtual bool visit(const Box& box, const Circle& circle);
    };

//    class VisitCircle : public VisitorObjectCollidable
//    {
//        virtual bool visit(const Box& box, const Circle& circle);
//    };

} //namespace Physics
#endif // VISITOROBJECTCOLLIDABLE_H
