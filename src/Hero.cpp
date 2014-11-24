#include "Hero.hpp"
#include <sstream>

Hero::Hero()
: m_model(true, sf::Vector2f(0.0f, 0.0f), CharSpeed),
  m_view(m_model,GraphScale)
{
    #ifdef DEBUG
//        std::cout << "Hero constructor" << std::endl;
    #endif // DEBUG
    this->m_type = TypeObject::Hero;

    m_model.setSize(m_view.getRectLocal().width, m_view.getRectLocal().height);
    m_model.addToEngine();
}

Hero::~Hero()
{
    //dtor
}

void Hero::handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction)
{
    m_model.handle_input(event, textAreaFunction);
}

void Hero::show()
{
     m_view.show();
}

void Hero::draw(sf::RenderTarget& app)
{
     m_view.draw(app);
}

void Hero::reset()
{
    m_model.setCoords(sf::Vector2f(0.0f, 0.0f));
    m_model.setAngle(0.0f);
//    m_model.getPhysicsBox().jump(false);
}

Hero::Hero(const Hero& copy)
:m_model(copy.m_model), m_view(m_model, GraphScale)
{
    m_model.setSize(m_view.getRectLocal().width, m_view.getRectLocal().height);
    m_type = TypeObject::Hero;
}

EditorObject* Hero::clone() const
{
	return new Hero(*this);
}

std::string Hero::save(float scale) const
{
    std::stringstream flux;
    flux << this->getTypeStr() << std::endl;
    //flux << m_model.getDirection() << std::endl;
    //flux << m_model.getCoords().x / scale << " " << - m_model.getCoords().y / scale << std::endl;
    return flux.str();
}
