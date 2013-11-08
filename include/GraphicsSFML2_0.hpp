#ifndef GRAPHICS_SFML_2_0
#define GRAPHICS_SFML_2_0

#ifdef DEBUG
    #include <iostream>
#endif // DEBUG

#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>

#include "

class GraphicsSFML2_0
{
public:
    int interval;
    sf::VertexArray plots;

    GraphicsSFML2_0(int xMin, int xMax, int scale , construeFunction calculus);
    virtual ~GraphicsSFML2_0();

private :

};

#endif // GRAPHICS_SFML_2_0
