#ifndef BUTTON_H
#define BUTTON_H

#ifdef DEBUG
	 #include <iostream>
#endif //DEBUG
#include <string>

#include <SFML/Graphics.hpp>

#include "../constants.hpp"


class Button :  public sf::Sprite
{
    public:
        Button(const char* _filename = "");
        virtual ~Button();
        void handle_input(sf::Event& event,sf::RenderTarget& target);
        void setAlpha ( int _alpha);
        void draw(sf::RenderTarget& app);
        bool isClicked() const;

    protected:

        std::string m_filename;
        bool m_clicked;
        sf::Texture m_texture;

};

/**
*
**/

inline bool Button::isClicked() const{return m_clicked;};

inline void Button::setAlpha (int _alpha)
{
    this->setColor(sf::Color(255, 255, 255, _alpha));
}


#endif // BUTTON_H
