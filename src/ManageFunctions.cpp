#include "ManageFunctions.hpp"

ManageFunctions::ManageFunctions()
:m_changed(false), m_currentIndex(0), m_view(sf::View())
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
            colorize();
            break;

        case sf::Keyboard::M:

            m_changed = true;
            if( m_currentIndex == 0)
            {
            	m_currentIndex = m_vectorCurves.size() - 1;
            }
            else
            {
                m_currentIndex--;
            }
            colorize();
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
    return m_vectorCurves.at(m_currentIndex).getModel();
}

void ManageFunctions::colorize()
{
     showBefore();
     m_vectorCurves.at(m_currentIndex).setColor(CurveColor);
     showAfter();
}

bool ManageFunctions::showBefore()
{
    if( m_currentIndex - 1 < 0)
    {
        return false;
    }
    else
    {
        //m_vectorCurves.at(m_currentIndex - 1).receiveView(m_view);
        m_vectorCurves.at(m_currentIndex - 1).setColor(PreviousCurveColor);
    }
    return true;
}

bool ManageFunctions::drawBefore(sf::RenderTarget& app)
{
    if( m_currentIndex - 1 < 0)
    {
        return false;
    }
    else
    {
        //m_vectorCurves.at(m_currentIndex - 1).receiveView(m_view);
        m_vectorCurves.at(m_currentIndex - 1).drawInterval(app);
    }
    return true;
}

bool ManageFunctions::showAfter()
{
    if( (m_currentIndex + 1) >= m_vectorCurves.size())
    {
        return false;
    }
    else
    {
        //m_vectorCurves.at(m_currentIndex + 1).receiveView(m_view);
        m_vectorCurves.at(m_currentIndex + 1).setColor(NextCurveColor);
    }
    return true;
}

bool ManageFunctions::drawAfter(sf::RenderTarget& app)
{
    if( (m_currentIndex + 1) >= m_vectorCurves.size())
    {
        return false;
    }
    else
    {
        //m_vectorCurves.at(m_currentIndex + 1).receiveView(m_view);
        m_vectorCurves.at(m_currentIndex + 1).drawInterval(app);
    }
    return true;
}


void ManageFunctions::draw(sf::RenderTarget& app)
{
    drawBefore(app);
    m_vectorCurves.at(m_currentIndex).receiveView(m_view);
	m_vectorCurves.at(m_currentIndex).draw(app);
    drawAfter(app);
}

void ManageFunctions::setViews(const sf::View view)
{
    m_view = view;
}

void ManageFunctions::addFunction(std::string function)
{
    Curves newFunction(function);
    m_vectorCurves.push_back(newFunction);

}


void ManageFunctions::reset()
{
//std::cout << "clearManageFunctions" << std::endl;
    m_changed = true;
    m_vectorCurves.clear();
//    m_graphModel.clearFunction();
}

void ManageFunctions::resetToZero()
{
    m_currentIndex = 0;
    colorize();
}
