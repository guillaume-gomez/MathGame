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


 void IntergralModel::getIntegraleCurve(float _begin , float _end , float step)
 {
    getRepresentativeCurve(_begin,_end,step);
    //
    sf::Vector2f fbegin (m_coords.front());

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
