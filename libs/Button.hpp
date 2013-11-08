#ifndef BUTTON_H
#define BUTTON_H

#include "AbstractWidget.hpp"
#include <string>

class Button : public AbstractWidget
{
		sf::Texture	m_image;	// L'image de notre bouton
		sf::Sprite	m_sprite;	// Le sprite pour afficher l'image
		sf::Vector2f	m_position;	// La position de notre bouton à l'écran
        sf::Font        m_font;
		sf::Text        m_text;
		sf::String      m_string;

		void OnUse(bool success);	// Principalement pour montrer l'utilité des fonctions evenement;
	public:
	    Button();
		Button(const std::string & _image_name, const sf::Vector2f & _position = sf::Vector2f(0.0f,0.0f) , const sf::Font & _font = sf::Font(), sf::String _string = sf::String() );
		virtual void Calculate(float time_interval);
		virtual void Draw(sf::RenderTarget & target, float alpha = 1.f);
		const sf::Vector2f & GetPosition() const;		// Retourne la position du button, sera utile pour notre cursor
        sf::Vector2u  GetSize () const;
        bool Collide( int x , int y );
        void setColor(sf::Color& color);
        void setSizeFont( unsigned int  _size);
        sf::String getString()const;
        void SetPosition(const sf::Vector2f& pos){ m_position = pos;};
        void setColorText(sf::Color _color);
        void manageSprite(const std::string & image_name, const sf::Vector2f & position);
        void manageFont(sf::Font _font,sf::String _string );
        inline int getAlpha ()const { return m_sprite.getColor().a;};

};

#endif // BUTTON_H
