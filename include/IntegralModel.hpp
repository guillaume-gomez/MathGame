#ifndef IntegralModel_HPP_H
#define IntegralModel_HPP_H

#ifdef DEBUG
	#include <iostream>
#endif // DEBUG

#include <list>
#include "../constants.hpp"
#include "ConstrueFunction.hpp"

#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)

class IntegralModel : public ConstrueFunction
{
    public:
        IntegralModel(std::string _function ="");
        IntegralModel(const IntegralModel& copy);
        virtual ~IntegralModel();
        void getIntegraleCurveShape(float _begin , float _end , float step);
        inline sf::Vector2f getCoordToShapes(unsigned int index ) const { if(m_listCoordShapes.size()) return m_listCoordShapes[index];}
        inline unsigned int getNbPoints () const {return m_listCoordShapes.size();}
        inline unsigned int getNbCoordByShape(unsigned int index) const { if(index < m_nbCoordByShape.size())return m_nbCoordByShape[index];}
        void showPoints();
        sf::Vector2f getBegin() const;
        sf::Vector2f getEnd() const;
    private:
    	std::vector<sf::Vector2f> m_listCoordShapes;
    	std::vector<unsigned int> m_nbCoordByShape;


};

inline sf::Vector2f IntegralModel::getBegin() const
{
    if(m_listCoordShapes.size() > 0)
    {
        return m_listCoordShapes.front();
    }
    else
    {
        std::runtime_error("IntegralModel::getBegin() : the array is empty");
    }
}

inline sf::Vector2f IntegralModel::getEnd() const 
{
    if(m_listCoordShapes.size() > 0)
    {
        return m_listCoordShapes.back();
    }
    else
    {
        std::runtime_error("IntegralModel::getBegin() : the array is empty");
    }
}

#endif // IntegralModel_HPP_H
