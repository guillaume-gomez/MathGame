#ifndef IntegralModel_HPP_H
#define IntegralModel_HPP_H

#ifdef DEBUG
	#include <iostream>
#endif // DEBUG

#include <list>
#include "ConstrueFunction.hpp"

#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)

class IntegralModel : public ConstrueFonction
{
    public:
        IntegralModel(std::string _function ="") ;
        virtual ~IntegralModel();
        void getIntegraleCurve(float _begin , float _end , float step);
        inline std::list<std::list<sf::Vector2f> > getListCoordToShapes() const { return m_listCoordShapes;}
    private:
    	std::list<std::list<sf::Vector2f> > m_listCoordShapes;


};

#endif // IntegralModel_HPP_H
