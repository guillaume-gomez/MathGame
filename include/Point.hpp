#ifndef POINT_H
#define POINT_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "EditorCircle.hpp"
#include "../constants.hpp"
#include "../files.hpp"


class Point : public EditorCircle
{
    public:
        Point();
        Point(float radius = 1.0f,bool goalPoint = false, float scale = GraphScale);
        virtual ~Point();
        inline bool isGoal() const {return m_goalPoint;}
        virtual EditorObject* clone() const;
        virtual std::string save(float scale = GraphScale) const;
        EditorObject* loadView(const Element& elmt, float scale);
    protected:
        //if is the final point
        bool m_goalPoint;
    private:
};

#endif // POINT_H
