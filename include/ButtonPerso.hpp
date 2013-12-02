#ifndef BUTTONPERSO_H
#define BUTTONPERSO_H

#ifdef DEBUG
	 #include <iostream>
#endif //DEBUG
#include <string>

#include <SFML/Graphics.hpp>

#include "../constants.hpp"


class ButtonPerso :  public sf::Sprite
{
    public:
        ButtonPerso(const char* _filename = "");
        virtual ~ButtonPerso();
        void handle_input(sf::Event& event, sf::RenderTarget& target);
        void setAlpha (int _alpha);
        void draw(sf::RenderTarget& app);
        bool isClicked() const;
        void unclick();
        
    protected:
        bool m_clicked;
        std::string m_filename;
        sf::Texture m_texture;
};

/**
*
**/

inline bool ButtonPerso::isClicked() const {return m_clicked;};

inline void ButtonPerso::setAlpha (int _alpha)
{
    this->setColor(sf::Color(255, 255, 255, _alpha));
}

inline void ButtonPerso::unclick()
{
    m_clicked = false;
}

#endif // BUTTON_H
