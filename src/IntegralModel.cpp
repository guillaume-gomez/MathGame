#include "IntegralModel.hpp"

IntegralModel::IntegralModel(std::string _function)
:ConstrueFonction(_function)
{
    getIntegraleCurve(-5,5,0.1f);
}

 void IntegralModel::getIntegraleCurve(float _begin , float _end , float step)
 {
    getRepresentativeCurve(_begin,_end,step);
    sf::Vector2f fbegin (m_coords.front());
    m_coords.push_front(sf::Vector2f(fbegin.x,0.0f));
    sf::Vector2f fend = m_coords.back();
    m_coords.push_back(sf::Vector2f(fend.x,0.0f));

    //detect where the function cut the abscissa
    int sign = 0;
    bool addList = false;
    std::list<sf::Vector2f>::iterator it = m_coords.begin();
    while(it != m_coords.end())
    {
        std::list<sf::Vector2f> temp;
        addList = false;
        //while the curve stay on on down the abscissa
        std::cout << "DEBUT" << std::endl;
        while(it != m_coords.end() && !addList)
        {
            temp.push_back(*it);
            if( it->y > 0.0f)
            {
                if (sign != 1)
                {
                    addList = true;
                }
            sign = 1;
            std::cout <<it->y<< "   ADDLIST    " << sign << std::endl;
            }
            else if (it->y < 0.0f)
            {
                if(sign != -1)
                {
                    addList = true;
                }
            sign = -1;
            std::cout <<it->y<< "   ADDLIST    " << sign << std::endl;
            }
            else
            {
                if(sign != 0)
                {
                    addList = true;
                }
            sign = 0;
            std::cout <<it->y<< "   ADDLIST    " << sign << std::endl;
            }
            it++;
        }
        std::cout << "FIN" << std::endl;
        // a point is added if the curve doesn't cut the abscissa at 0 with the step
        // a second point is added to close the future shape in IntegralView
        if(sign != 0)
        {
            temp.push_back(sf::Vector2f(0.0f, 0.0f));
            temp.push_back(temp.front());
        }
        m_listCoordShapes.push_back(temp);
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
