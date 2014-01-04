#include "ButtonPerso.hpp"

ButtonPerso::ButtonPerso(const char* _filename)
:m_filename(_filename), m_clicked(false)
{
  m_texture.loadFromFile(m_filename);
  this->setTexture(m_texture);
  setAlpha(Blur);

}

void ButtonPerso::handle_input(sf::Event& event,sf::RenderTarget& target)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;
            sf::Vector2f coord = target.mapPixelToCoords((sf::Vector2i(x, y)));

        if(getGlobalBounds().contains(coord.x, coord.y))
        {
            m_clicked = true;
        }
    }

    else if(event.type == sf::Event::MouseButtonReleased)
    {
        m_clicked = false;
    }

    else if(event.type == sf::Event::MouseMoved)
    {
        int x =  event.mouseMove.x;
        int y =  event.mouseMove.y;
        sf::Vector2f coord = target.mapPixelToCoords((sf::Vector2i(x, y)));

        if(getGlobalBounds().contains(coord.x, coord.y))
        {
            setAlpha(Clear);
        }
        else
        {
            setAlpha(Blur);
        }
    }
}


void ButtonPerso::draw(sf::RenderTarget& app)
{
    app.draw(*this);
}

ButtonPerso::~ButtonPerso()
{
    //dtor
}
