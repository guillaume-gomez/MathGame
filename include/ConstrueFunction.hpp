#ifndef ConstrueFunction_H
#define ConstrueFunction_H

#include <cmath>
#ifdef DEBUG
	#include <iostream>
#endif //DEBUG
#include <list>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
//include math librairy ( exprtk )
// see more :  "http://www.partow.net/programming/exprtk/index.html"
#include "../libs/exprtk.hpp"


#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)


class ConstrueFunction
{

    struct IntervalOfDefinition
		{
			float xStart;
			float xEnd;
		};

    public:
        std::list<sf::Vector2f> m_coords;

        ConstrueFunction( std::string function = std::string() );
        ConstrueFunction(const ConstrueFunction& copy);
        std::string getFunction()const ;
        float getFunctionValue(float x) const;
        float getDerivative(float x) const;
        void getRepresentativeCurve(float _begin, float _end, float step);
        void setFunction(std::string _function);
        virtual ~ConstrueFunction();
        void manageEvent(const sf::Event &event);
        bool isDefined(float x, float* y) const;
        void setChanged(bool _changed);
        bool getChanged()const;
        bool isRepresented(float x) const;
        bool isRepresented(float x, float y) const;
        void clearFunction();

    protected:
        bool m_changed;
        std::string m_function;
        std::vector<IntervalOfDefinition> intervals;
};

/***************************************** Definitions *****************************************/

    inline void ConstrueFunction::setChanged(bool _changed)
    {
        m_changed = _changed;
    }


    inline bool ConstrueFunction::getChanged() const
    {
        return m_changed;
    }

/***************************************** // Definitions *****************************************/

#endif // ConstrueFunction_H
