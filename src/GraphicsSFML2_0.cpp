#include "GraphicsSFML2_0.hpp"

/**
* @brief : Constructor of the class
* @param : xmin
* @param : xmax
* @param : scale
**/
GraphicsSFML2_0::GraphicsSFML2_0(int xMin, int xMax, int scale , construeFunction calculus)
: interval(abs(xMax-xMin)), plots(sf::VertexArray(sf::LinesStrip, interval*scale))
{
    for(int i=0; i<(xMax-xMin)*scale; i++)
    {
        float x=(xMin*scale)+i;
        plots[i].position.x=x;
        x/=scale;
        plots[i].position.y=-x*x*scale;

        // TODO (adrizn#1#): On doit pouvoir choisir la fonction à représenter

      /*  #ifdef DEBUG
            //std::cout << "x : " << plots[i].position.x << " y : " << plots[i].position.y << std::endl;
        #endif // DEBUG*/
    }
}

/**
* @brief : Destructor of the class
**/
GraphicsSFML2_0::~GraphicsSFML2_0()
{

}
