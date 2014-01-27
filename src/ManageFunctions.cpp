#include "ManageFunctions.h"

ManageFunctions::ManageFunctions()
:m_changed(false), currentIndex(0)
{
    //ctor
}

ManageFunctions::~ManageFunctions()
{
    //dto
}


void handle_input(sf::Event& event)
{
    m_changed = false;
	if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {

        case sf::Keyboard::P:
            m_currentIndex++;
            m_changed = true;
            if (m_currentIndex > m_vectorModel.size())
            {
            	m_currentIndex = 0;
            }
            break;

        case sf::Keyboard::M:
            m_currentIndex--;
            m_changed = true;
            if( m_currentIndex < 0)
            {
            	m_currentIndex = m_vectorModel.size() - 1;
            }
            break;

        default:
            break;
        }
    }
     
}

void ManageFunctions::represent(float step)
{
    if(m_changed)
    {
	   m_view.standAloneRepresent(m_vectorModel[m_currentIndex], step);
    }
}


void ManageFunctions::draw(sf::RenderTarget& app)
{
	m_view.draw(app);
}


void ManageFunctions::addFunction(std::string function)
{
    ConstrueFunction newFunction(function);
    m_vectorModel.push_back(newFunction);
}