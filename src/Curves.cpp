#include "Curves.hpp"

Curves::Curves(std::string function, float _begin, float _end, float step)
:m_model(function),//function),
 m_view(m_model, Thickness, GraphScale)//, m_type(TypeObject::Curves)
{
    if(_begin != 0.0f && _end != 0.1f)
    {
    	build(_begin,_end, step);
    }
}

Curves::~Curves()
{
    //dtor
}

Curves::Curves(const Curves& copy)
: m_model(copy.m_model), m_view(m_model, Thickness, GraphScale)//, m_type(TypeObject::Curves)
{
    if(copy.m_model.m_coords.front().x != 0.0f && copy.m_model.m_coords.back().x != 0.1f)
    {
        build(-GraphScale,GraphScale, Step);
    }
}


EditorObject* Curves::clone() const
{
	return new Curves(*this);
}


std::string Curves::save(float scale) const
{
	std::stringstream flux;
    flux << this->getTypeStr() << std::endl;
    flux << m_model.getFunction() << std::endl;
    return flux.str();
}

void Curves::draw(sf::RenderTarget& app)
{
	m_view.draw(app);
}

void Curves::represent(float step)
{
        m_view.represent(step);
}

void Curves::build(int _begin , int _end, float step)
{
	m_model.getRepresentativeCurve(_begin, _end, step);
	m_view.represent(step);
}

const ConstrueFunction* Curves::getModel()
{
    #ifdef DEBUG
     // std::cout << "fdsfsfds" << std::endl;
    #endif
    return &m_model;
}

void Curves::move(float step)
{
    if ( m_model.getChanged())
    {
        m_view.represent(step);
        m_model.setChanged(false);
    }
}

void Curves::reset()
{
    m_model.setChanged(true);
    m_model.clearFunction();
    m_view.represent(Step);
}
