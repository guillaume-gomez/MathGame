#include "ConstrueFunction.hpp"

/**
* @brief : Constructor of the class
**/
ConstrueFonction::ConstrueFonction(std::string _function)
:m_function(_function), m_changed(false)/*, m_scale(scale), m_begin(0.0f), m_end(0.0f), m_step(0.0f)*/
{
    //ctor
}

/**
* @brief : Destructor of the class
**/
ConstrueFonction::~ConstrueFonction()
{
    //dtor
}

/**
* @brief : Accessor of m_function
**/
std::string& ConstrueFonction::getFunction() {return m_function ;}

/**
* @brief : Accessor of m_function
* @param : the new function
**/
void ConstrueFonction::setFunction(std::string _function)
{
    m_function = _function;
    setChanged(true);
}

/**
* @brief : return the value of the function for a x
**/
float ConstrueFonction::getFunctionValue( float x) const
{
   exprtk::symbol_table<float> symbol_table;
   symbol_table.add_variable("x",x);

   exprtk::expression<float> expression;
   expression.register_symbol_table(symbol_table);

   exprtk::parser<float> parser;
   parser.compile( m_function ,expression);

   return  expression.value();

}

float ConstrueFonction::getDerivative(float x) const
{
	exprtk::symbol_table<float> symbol_table;
	symbol_table.add_variable("x",x);

	exprtk::expression<float> expression;
	expression.register_symbol_table(symbol_table);

	exprtk::parser<float> parser;
	parser.compile(m_function, expression);

	return exprtk::derivative(expression, x);
}

void ConstrueFonction::clearFunction()
{
    m_coords.clear();
	intervals.clear();
}

/**
* @brief : Store in a vector all the value for the function
**/
void ConstrueFonction::getRepresentativeCurve(float _begin, float _end, float step)
{
    m_coords.clear();
	intervals.clear();

	int i=0;
	const float StepLimits = 100.0f;
	IntervalOfDefinition intervalTmp;
	intervalTmp.xStart = _begin;
   for(float x = _begin ; x <= _end ; x += step )
   {
		float y;
		if(isDefined(x, &y))
		{
			if(i!=1)
				m_coords.push_back(sf::Vector2f(x,y));

			if(i==2)
			{
				i=3;
				x-=step;
				step/=StepLimits;
			}
			else if(i==3)
			{
				intervalTmp.xStart = x;
				i=0;
				step*=StepLimits;
			}
		}
		else if(x==_begin)
		{
			i=2;
		}
		else if(i==0)
		{
			i=1;
			x-=step;
			step/=StepLimits;
		}
		else if(i==1)
		{
			m_coords.push_back(sf::Vector2f(x-step,getFunctionValue(x-step)));
			intervalTmp.xEnd = x-step;
			intervals.push_back(intervalTmp);
			step*=StepLimits;
			i=2;
		}

   }
	intervalTmp.xEnd = _end;
	if(i!=2)
	{
		intervals.push_back(intervalTmp);
	}

}

bool ConstrueFonction::isDefined(float x, float* y) const
{
	exprtk::symbol_table<float> symbol_table;
	symbol_table.add_variable("x", x);

	exprtk::expression<float> expression;
	expression.register_symbol_table(symbol_table);

	exprtk::parser<float> parser;
	parser.compile( m_function ,expression);

	*y = expression.value();

	return((*y)==(*y)	// test si la valeur est un nombre exemple : sqrt(-5) n'existe pas, le resultat du test sera faux
			&& (*y)!=std::numeric_limits<float>::infinity()
			&& (*y)!=-std::numeric_limits<float>::infinity());
}

bool ConstrueFonction::isRepresented(float x)
{
	FOR_STL_ITERATOR(std::vector<IntervalOfDefinition>, intervals, itIntervals)
	{
		if(x>=itIntervals->xStart)
		{
			if(x<=itIntervals->xEnd)
				return true;
			else
				return false;
		}
	}
	return false;
}

bool ConstrueFonction::isRepresented(float x, float y)
{
	if(isRepresented(x) && getFunctionValue(x) == y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
