#ifndef INTERGRALMODEL_HPP_H
#define INTERGRALMODEL_HPP_H

#ifdef DEBUG
	#include <iostream>
#endif // DEBUG

#include <list>
#include "ConstrueFunction.hpp"

#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)

class IntergralModel : public ConstrueFonction
{
    public:
        IntergralModel(std::string _function ="") ;
        virtual ~IntergralModel();
        void getIntegraleCurve(float _begin , float _end , float step);
        inline std::list<std::list<sf::Vector2f>> getListCoordToShapes() const { return m_listCoordShapes;}
    private:
    	std::list<std::list<sf::Vector2f>> m_listCoordShapes;


};

#endif // INTERGRALMODEL_HPP_H
