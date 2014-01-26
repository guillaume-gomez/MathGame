#include "Button.hpp"

Button::Button(const char* _filename)
:m_filename(_filename), m_clicked(false)
{

  m_texture.loadFromFile(m_filename);
  this->setTexture(m_texture);

}


void Button::handle_input(sf::Event& event, sf::RenderTarget& target)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;
            sf::Vector2f coord = target.mapPixelToCoords((sf::Vector2i(x, y)));

        if ( getGlobalBounds().contains(coord.x, coord.y))
        {
           // setAlpha(255);
            m_clicked = true;
        }
        //else
       // {
           // setAlpha(Clear);
       // }
    }

    else if ( event.type == sf::Event::MouseButtonReleased)
    {
        m_clicked = false;
    }

    else if(event.type == sf::Event::MouseMoved)
    {
        int x =  event.mouseMove.x;
        int y =  event.mouseMove.y;
        sf::Vector2f coord = target.mapPixelToCoords((sf::Vector2i(x, y)));

        if ( getGlobalBounds().contains(coord.x, coord.y))
        {
            setAlpha(Clear);
        }
        else
        {
            setAlpha(Blur);
        }
    }
}


void Button::draw(sf::RenderTarget& app)
{
    app.draw(*this);
}

Button::~Button()
{
    //dtor
}
