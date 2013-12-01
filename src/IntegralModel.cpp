#include "IntegralModel.hpp"

IntegralModel::IntegralModel(std::string _function)
:ConstrueFonction(_function)
{
    getIntegraleCurveShape(-7,7,0.25f);
}

 void IntegralModel::getIntegraleCurveShape(float _begin , float _end , float step)
 {
     std::list<sf::Vector2f>::iterator firstPoint = m_coords.begin();
    //detect where the function cut the abscissa
    int sign = (firstPoint->y >= 0)? 1 : -1;

    getRepresentativeCurve(_begin,_end,step);
    sf::Vector2f fbegin (m_coords.front());
    m_coords.push_front(sf::Vector2f(fbegin.x,0.0f));
    sf::Vector2f fend = m_coords.back();
    m_coords.push_back(sf::Vector2f(fend.x,0.0f));

    bool addList = false;
    std::list<sf::Vector2f>::iterator it = m_coords.begin();
    std::list<sf::Vector2f>::iterator itNext = m_coords.begin();
                                      itNext++;
    while(it != m_coords.end())
    {
        std::cout << "DEBUT " << std::endl;
        std::cout <<"sign " << sign << std::endl;
        addList = false;
        unsigned int nbCoord = 0;
        if ( sign == 0)
        {
            m_listCoordShapes.push_back(sf::Vector2f(it->x  , 0.0f));
            nbCoord++;
        }
        //while the curve stay on on down the abscissa
        while(it != m_coords.end() && !addList)
        {
            if( itNext != m_coords.end())
            {
                if( it->y > 0.0f && itNext->y <= 0.0f)
                {
                    // if the sign had changed
                    addList = true;
                    sign = 1;
                }
                else if (it->y < 0.0f && itNext->y >= 0.0f)
                {
                    addList = true;
                    sign = -1;
                }
                else if ( it->y == 0.0f)
                {
                    addList = true;
                    sign = 0;
                }
              //  std::cout << "X " << itNext->x << " Y " << itNext->y << std::endl;
            }
            m_listCoordShapes.push_back(*it);
            std::cout << "X " << it->x << " Y " << it->y << std::endl;
            nbCoord++;
            it++;
            itNext++;
        }
        // a point is added if the curve doesn't cut the abscissa at 0 with the step
        // a second point is added to close the future shape in IntegralView
        if(sign != 0)
        {
           std::cout << "MACHINE" << std::endl;
           std::cout << ":X " << it->x << " :Y " << 0.0f << std::endl;
           m_listCoordShapes.push_back(sf::Vector2f(it->x, 0.0f));
           nbCoord++;
           sign = 0;
        }
        //to detect the end of a shape
        std::cout << "nbPOints " << nbCoord  << std::endl;
        m_nbCoordByShape.push_back(nbCoord);
        std::cout << "SIGN" << sign << std::endl;
        std::cout << "FINININININININ" << std::endl;
    }
 }



 void IntegralModel::getIntegraleCurveLine(float _begin , float _end , float step)
 {
     std::list<sf::Vector2f>::iterator firstPoint = m_coords.begin();
    //detect where the function cut the abscissa
    int sign = (firstPoint->y >= 0)? 1 : -1;

    getRepresentativeCurve(_begin,_end,step);
    sf::Vector2f fbegin (m_coords.front());
    m_coords.push_front(sf::Vector2f(fbegin.x,0.0f));
    sf::Vector2f fend = m_coords.back();
    m_coords.push_back(sf::Vector2f(fend.x,0.0f));

    bool addList = false;
    std::list<sf::Vector2f>::iterator it = m_coords.begin();
    std::list<sf::Vector2f>::iterator itNext = m_coords.begin();
                                      itNext++;
    while(it != m_coords.end())
    {
        std::cout << "DEBUT " << std::endl;
        std::cout <<"sign " << sign << std::endl;
        addList = false;
        unsigned int nbCoord = 0;
        sf::Vector2f beginLine = *it;

        if ( sign == 0)
        {
            m_listCoordShapes.push_back(sf::Vector2f(it->x  , 0.0f));
            beginLine = sf::Vector2f(it->x, 0.0f);
            nbCoord++;
        }
        //while the curve stay on on down the abscissa
        while(it != m_coords.end() && !addList)
        {
            if( itNext != m_coords.end())
            {
                if( it->y > 0.0f && itNext->y <= 0.0f)
                {
                    // if the sign had changed
                    addList = true;
                    sign = 1;
                }
                else if (it->y < 0.0f && itNext->y >= 0.0f)
                {
                    addList = true;
                    sign = -1;
                }
                else if ( it->y == 0.0f)
                {
                    addList = true;
                    sign = 0;
                }
              //  std::cout << "X " << itNext->x << " Y " << itNext->y << std::endl;
            }
            m_listCoordShapes.push_back(*it);
            std::cout << "X " << it->x << " Y " << it->y << std::endl;
            nbCoord++;
            it++;
            itNext++;
        }
        // a point is added if the curve doesn't cut the abscissa at 0 with the step
        // a second point is added to close the future shape in IntegralView
        if(sign != 0)
        {
           std::cout << "MACHINE" << std::endl;
           std::cout << ":X " << it->x << " :Y " << 0.0f << std::endl;
           m_listCoordShapes.push_back(sf::Vector2f(it->x, 0.0f));
           nbCoord++;
           sign = 0;
        }

        //to close the shape with lines, it is needed to get back to the first point created
        m_listCoordShapes.push_back(beginLine);
        nbCoord++;
        //to detect the end of a shape
        std::cout << "nbPOints " << nbCoord  << std::endl;
        m_nbCoordByShape.push_back(nbCoord);
        std::cout << "SIGN" << sign << std::endl;
        std::cout << "FINININININININ" << std::endl;
    }
 }

 IntegralModel::~IntegralModel()
 {}

/*
 void IntegralModelOld::getIntegraleCurve(float _begin , float _end , float step)
 {
    getRepresentativeCurve(_begin,_end,step);
    //
    /sf::Vector2f fbegin (m_coords.front());

    m_coords.push_front(sf::Vector2f(fbegin.x,0.0f));

    sf::Vector2f fend = m_coords.back();
    m_coords.push_back(sf::Vector2f(fend.x,0.0f));


    #ifdef DEBUG
		FOR_STL_ITERATOR(std::list<sf::Vector2f>, m_coords, it)
        {
            std::cout <<" x : "<< it->x << " y : " << it->y << std::endl;
        }
    #endif // DEBUG

 }
*/
