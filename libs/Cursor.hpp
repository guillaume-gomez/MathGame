#ifndef CURSOR_H
#define CURSOR_H

#include "AbstractCursor.hpp"
#include "Button.hpp"

class Cursor : public AbstractCursor
{
		sf::RectangleShape	shape;
	public:
		// Constructeurs
		Cursor(sf::Color color = sf::Color::White , unsigned int thick = 1,AbstractWidget * first = 0 );
		void setSize ( sf::Vector2f );
		Button* getButton();

		// Fonctions de la classe
		virtual void Calculate(float time_interval);
		virtual void Draw(sf::RenderTarget & target, float alpha = 1.f);
		sf::Vector2f GetPosition() const { return shape.getPosition();};
};

#endif
