#include "IntergralModel.hpp"

IntergralModel::IntergralModel(std::string _function)
:ConstrueFonction(_function)
{
    //ctor
}

IntergralModel::~IntergralModel()
{
    //dtor
}

 
 void IntergralModelOld::getIntegraleCurve(float _begin , float _end , float step)
 {
    getRepresentativeCurve(_begin,_end,step);
    /sf::Vector2f fbegin (m_coords.front());
    m_coords.push_front(sf::Vector2f(fbegin.x,0.0f));
    sf::Vector2f fend = m_coords.back();
    m_coords.push_back(sf::Vector2f(fend.x,0.0f));

    //detect where the function cut the abscissa
    int sign = 0;
    bool addList = false;
    container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++
    std::list<sf::Vector2f>::iterator it = m_coords.begin();
    while(it != m_coords.end())
    {
        std::list<sf::Vector2f> temp;
        addList = false;
        //while the curve stay on on down the abscissa
        while(it != m_coords.end() && !addList)
        {
            temp.push_back(it);
            if( it->y > 0)
            {
                if (sign != 1)
                {
                    addList = true;
                }
            sign = 1;
            }
            else if (it->y < 0)
            {
                if(sign != -1)
                {
                    addList = true;
                }
            sign = -1;
            }
            else
            {
                if(sign != 0)
                {
                    addList = true;
                }
            sign = 0;
            }
            it++;
        }
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

/*
 void IntergralModelOld::getIntegraleCurve(float _begin , float _end , float step)
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