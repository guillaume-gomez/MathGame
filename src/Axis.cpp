#include <SFML/Graphics.hpp>
#include <vector>

#ifdef DEBUG
	#include <iostream>
#endif // DEBUG

#include "Axis.hpp"


#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)
#define FOR_STL_REVERSE_ITERATOR(container_type, name, iteratorName) for(container_type::reverse_iterator iteratorName=name.rbegin(); iteratorName!=name.rend(); iteratorName++)


/**
* @brief : Constructor of the class
**/
Axis::Axis(float _graduation)
:m_originyAxis(0.0f), m_originxAxis(0.0f), m_scale(1.0f), m_graduation(_graduation)
{
    sf::Color color(18, 25, 112, 75);
    float heightAxis = 4.0f;
    float widthAxis = 2000.0f;
    int nbGraduation = (int) widthAxis / m_graduation;

    float heightGrad = 10.0f;
    float widthGrad = 2.0f;
    float _x = -1000.0f;
    float _y = 0.0f - heightGrad / 2.0f ;

    ////////////////////////////////////////////////////////
    // XAxis Graduation
    for (int i = 0 ; i < nbGraduation / 2 ; i++)
    {
        sf::RectangleShape temp(sf::Vector2f(widthGrad, heightGrad));
                           temp.setPosition(_x - widthGrad / 2.0f, _y);
                           temp.setFillColor(color);
         m_listXGrad.push_back(temp);
         _x +=  m_graduation;
    }
    _x += m_graduation;
     for (int i = 0 ; i < nbGraduation / 2 ; i++)
    {

        sf::RectangleShape temp(sf::Vector2f(widthGrad, heightGrad));
                           temp.setPosition(_x - widthGrad / 2.0f, _y);
                           temp.setFillColor(color);
         m_listXGrad.push_back(temp);
         _x +=  m_graduation;
    }
    //
    ///////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////
    // YAxis Graduation
     _y = -1000.0f;
     _x = 0.0f - heightGrad / 2.0f ;
    for (int i = 0 ; i < nbGraduation / 2  ; i++)
    {

        sf::RectangleShape temp(sf::Vector2f(heightGrad, widthGrad));
                           temp.setPosition(_x, _y - widthGrad / 2.0f);
                           temp.setFillColor(color);
         m_listYGrad.push_back(temp);
         _y +=  m_graduation;
    }
    _y += m_graduation;
    for (int i = 0 ; i < nbGraduation / 2  ; i++)
    {

        sf::RectangleShape temp(sf::Vector2f(heightGrad, widthGrad));
                           temp.setPosition(_x, _y - widthGrad / 2.0f);
                           temp.setFillColor(color);
         m_listYGrad.push_back(temp);
         _y +=  m_graduation;
    }
    //
    ////////////////////////////////////////////////////////



    /////////////////////////////////////////////
    // xAxis
    m_shapexAxis.setSize(sf::Vector2f(widthAxis, heightAxis));
    m_shapexAxis.setPosition(-1000.0f, -heightAxis / 2);
    m_shapexAxis.setFillColor(color);
    //
    /////////////////////////////////////////////////

    /////////////////////////////////////////////////
    //
    m_shapeyAxis.setSize(sf::Vector2f(heightAxis, widthAxis));
    m_shapeyAxis.setPosition(-heightAxis / 2, -1000.0f);
    m_shapeyAxis.setFillColor(color);
    // yAxis
    /////////////////////////////////////////////////

}

/**
* @brief : Destructor of the class
**/
Axis::~Axis()
{
    //dtor
}

/**
* @brief : Accessor of xAxis
**/
int Axis::getxAxis()
{
     return m_originxAxis;
}

/**
* @brief : Accessor of yAxis
**/
int Axis::getyAxis()
{
    return m_originyAxis;
}

/**
* @brief : Accessor of scale
**/
float Axis::getScale()
{
    return m_scale;
}


void Axis::setGraduation(float _graduation)
{
    m_graduation = _graduation;
}

float Axis::getGraducation()
{
   return m_graduation;
}

/**
* @brief : Draw
**/
void Axis::draw(sf::RenderWindow& App)
{

    FOR_STL_ITERATOR(std::vector<sf::RectangleShape>, m_listXGrad, it)
    {
        App.draw(*it);
    }

     FOR_STL_ITERATOR(std::vector<sf::RectangleShape>, m_listYGrad, it)
    {
        App.draw(*it);
    }
   App.draw(m_shapexAxis);
   App.draw(m_shapeyAxis);
}
