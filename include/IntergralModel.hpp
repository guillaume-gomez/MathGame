#ifndef INTERGRALMODEL_HPP_H
#define INTERGRALMODEL_HPP_H

#ifdef DEBUG
	#include <iostream>
#endif // DEBUG

#include "ConstrueFunction.hpp"

#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)

class IntergralModel : public ConstrueFonction
{
    public:
        IntergralModel(std::string _function ="") ;
        virtual ~IntergralModel();
        void getIntegraleCurve(float _begin , float _end , float step);


};

#endif // INTERGRALMODEL_HPP_H
