#ifndef VISITOROBJECTCOLLIDABLE_H
#define VISITOROBJECTCOLLIDABLE_H

namespace Physics
{
    class Object;
    class Box;
    /**
    @brief : Interface to visit each object collidable
    **/
    class VisitorObjectCollidable
    {
        public:
            VisitorObjectCollidable();
            virtual ~VisitorObjectCollidable();

//            virtual bool visit(const Object& object1, const Object& object2) = 0;
//            virtual bool visit(const Box& box, const Object& object) = 0;
//
//            virtual bool visit(const Object& object, const Box& box) = 0;
            virtual bool visit(const Box& box1, const Box& box2) = 0;
    };

    /**
    @brief : Methods which check colission with any other element than a BOX (square)
    **/
    class VisitBox : public VisitorObjectCollidable
    {
//        virtual bool visit(const Object& object1, const Object& object2);
//        virtual bool visit(const Box& box, const Object& object);
//
//        virtual bool visit(const Object& object, const Box& box);
        virtual bool visit(const Box& box1, const Box& box2);

    };

    //TODO
//    class VisitCircle : public VisitorObjectCollidable
//    {
////        virtual bool visit(const Object& object1, const Object& object2);
////        virtual bool visit(const Box& box, const Object& object);
////
////        virtual bool visit(const Object& object, const Box& box);
//        virtual bool visit(const Box& box1, const Box& box2);
//    };

} //namespace Physics
#endif // VISITOROBJECTCOLLIDABLE_H
