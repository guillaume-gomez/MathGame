#ifndef ConstrueFonction_H
#define ConstrueFonction_H

#ifdef DEBUG
	#include <iostream>
#endif //DEBUG

#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>


//include math librairy ( exprtk )
// see more :  "http://www.partow.net/programming/exprtk/index.html"
#include "../libs/exprtk.hpp"

#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)

class ConstrueFonction
{
    public:
        std::list<sf::Vector2f> m_coords;

        ConstrueFonction( std::string function = std::string() );
        std::string& getFunction();
        float getFunctionValue( float x) const;
        float getDerivative( float x) const;
        void getRepresentativeCurve(float _begin , float _end , float step);
        void setFunction(std::string _function);
        virtual ~ConstrueFonction();
        void manageEvent(const sf::Event &event);
//        float getScale() const;
        bool isDefined(float x, float* y) const;
        void setChanged(bool _changed);
        bool getChanged()const;
        bool isRepresented(float x);
        bool isRepresented(float x, float y);
        void clearFunction();

    protected:
        std::string m_function;
        bool m_changed;
		struct IntervalOfDefinition
		{
			float xStart;
			float xEnd;
		};
		std::vector<IntervalOfDefinition> intervals;

//        float m_scale;
//        float m_begin, m_end, m_step;

};

/***************************************** Definitions *****************************************/

    inline void ConstrueFonction::setChanged(bool _changed)
    {
        m_changed = _changed;
    }


    inline bool ConstrueFonction::getChanged()const
    {
        return m_changed;
    }

/***************************************** // Definitions *****************************************/

#endif // ConstrueFonction_H
