#ifndef POINT_H
#define POINT_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "EditorObject.hpp"
#include "../constants.hpp"


class Point : public EditorObject
{
    public:
        Point();
        Point(float radius = 1.0f,bool goalPoint = false, float scale = GraphScale, std::string filename = "");
        virtual ~Point();
        inline bool isGoal() const {return m_goalPoint;}
    protected:
        //if is the final point
        bool m_goalPoint;
    private:
};

#endif // POINT_H
