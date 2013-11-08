#ifndef BUTTONPERSO_H
#define BUTTONPERSO_H

#include "../constants.hpp"
#include <SFML/Graphics.hpp>
#ifdef DEBUG
	 #include <iostream>
#endif //DEBUG
#include <string>

class ButtonPerso :  public sf::Sprite
{
    public:
        ButtonPerso(const char* _filename = "");
        virtual ~ButtonPerso();
        void handle_input(sf::Event& event,sf::RenderTarget& target);
        void setAlpha ( int _alpha);
        void draw(sf::RenderTarget& app);
        bool isClicked() const;
        void unclick();
    protected:
        sf::Texture m_texture;
        std::string m_filename;
        bool m_clicked;

};

/**
*
**/

inline bool ButtonPerso::isClicked() const{return m_clicked;};

inline void ButtonPerso::setAlpha ( int _alpha)
{
    this->setColor(sf::Color(255,255,255,_alpha));
}

inline void ButtonPerso::unclick()
{
    m_clicked = false;
}

#endif // BUTTON_H
