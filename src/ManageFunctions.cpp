#include "ManageFunctions.hpp"

ManageFunctions::ManageFunctions()
:m_changed(false), m_currentIndex(0)
{
    //ctor
}

ManageFunctions::~ManageFunctions()
{
    //dto
}


void ManageFunctions::handle_input(sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {

        case sf::Keyboard::P:
            m_currentIndex++;
            m_changed = true;
            if (m_currentIndex >= m_vectorCurves.size())
            {
            	m_currentIndex = 0;
            }
            break;

        case sf::Keyboard::M:
            m_currentIndex--;
            m_changed = true;
            if( m_currentIndex < 0)
            {
            	m_currentIndex = m_vectorCurves.size() - 1;
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
       //// std::cout << "Represent " << m_currentIndex << std::endl;
	   m_vectorCurves.at(m_currentIndex).represent(step);
	   m_changed = false;
    }
}

const ConstrueFunction* ManageFunctions::getModelIndex()
{
#ifdef DEBUG
    // std::cout << m_currentIndex << " INDEX " << std::endl;
#endif
    return m_vectorCurves.at(m_currentIndex).getModel();
}

bool ManageFunctions::drawBefore(sf::RenderTarget& app)
{
    if( m_currentIndex - 1 < 0)
    {
        return false;
    }
    else
    {
        m_vectorCurves.at(m_currentIndex - 1).setColor(PreviousCurveColor);
        m_vectorCurves.at(m_currentIndex - 1).drawInterval(app);
        m_vectorCurves.at(m_currentIndex - 1).setColor(CurveColor);
    }
    return true;
}

bool ManageFunctions::drawAfter(sf::RenderTarget& app)
{
    if( m_currentIndex + 1 >= m_vectorCurves.size())
    {
        return false;
    }
    else
    {
        m_vectorCurves.at(m_currentIndex + 1).setColor(NextCurveColor);
        m_vectorCurves.at(m_currentIndex + 1).drawInterval(app);
        m_vectorCurves.at(m_currentIndex + 1).setColor(CurveColor);

    }
    return true;
}


void ManageFunctions::draw(sf::RenderTarget& app)
{
    drawBefore(app);
	m_vectorCurves.at(m_currentIndex).draw(app);
    drawAfter(app);
}


void ManageFunctions::addFunction(std::string function)
{
    Curves newFunction(function);
    m_vectorCurves.push_back(newFunction);

}

void ManageFunctions::reset()
{
    m_changed = true;
    m_vectorCurves.clear();
    //m_graphModel.clearFunction();
}

void ManageFunctions::resetToZero()
{
    m_currentIndex = 0;
}
