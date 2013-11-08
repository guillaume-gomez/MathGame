#ifndef MENU_H
#define MENU_H

#include "AbstractPanel.hpp"

class Menu : public AbstractPanel
{
		virtual void OnDisplay(bool entering);
		virtual void OnHide(bool entering);
	public:
		Menu(AbstractCursor * cursor, AbstractPanel * parent = 0);  // On doit pouvoir faire passer le curseur utilisé pour le panel.
		virtual void Calculate(float time_interval);
		virtual void Draw(sf::RenderTarget & target,float alpha = 1.f);
		void handle_input(sf::Event& event);

		bool m_down;
		bool m_up;
		bool m_right;
		bool m_left;


};

#endif
