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
        Point(float radius = 1.0f, float scale = GraphScale, std::string filename = "");
        virtual ~Point();
    protected:
    private:
};

#endif // POINT_H
