#include "ButtonPerso.hpp"

ButtonPerso::ButtonPerso(const char* _filename)
:m_filename(_filename), m_clicked(false)
{
    sf::Texture * texture = nullptr;
    texture = TextureManager::getTextureManager()->getResource(std::string(m_filename));
    if(texture)
    {
        this->setTexture(*texture);
    }
    else
    {
        std::cout << "Warning : in ButtonPerso, Constructor didn't find a file texture " << m_filename << std::endl;
    }
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
