#include "Integral.hpp"

Integral::Integral(std::string function, float _begin, float _end, float step)
:m_model(function),//function),
 m_view(m_model, GraphScale)//, m_type(TypeObject::Integral)
{
    if(_begin != 0.0f && _end != 0.1f)
    {
    	build(_begin,_end, step);
    }
}

Integral::~Integral()
{
    //dtor
}

Integral::Integral(const Integral& copy)
: m_model(copy.m_model), m_view(m_model,GraphScale)//, m_type(TypeObject::Integral)
{

}


EditorObject* Integral::clone() const
{
	return new Integral(*this);
}


std::string Integral::save(float scale) const
{
	std::stringstream flux;
    flux << this->getTypeStr() << std::endl;
    flux << m_model.getFunction() << std::endl;
    flux << m_model.getBegin().x << std::endl;
    flux << m_model.getEnd().x << std::endl;
    return flux.str();
}

void Integral::draw(sf::RenderTarget& app)
{
	m_view.drawShape(app);
}

void Integral::build(int _begin , int _end, float step)
{
	m_model.getIntegraleCurveShape(_begin, _end, Step);
	m_view.representShape();
}
