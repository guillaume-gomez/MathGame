#ifndef ABSTRACTCURSOR_H
#define ABSTRACTCURSOR_H

#include <SFML/Graphics.hpp>

class AbstractWidget;
class AbstractPanel;

class AbstractCursor
{
		AbstractWidget * previous;
		AbstractWidget * current;

	protected:
		virtual void OnMoveNext(bool success){}
		virtual void OnMovePrevious(bool success){}
		virtual void OnMoveLeft(bool success){}
		virtual void OnMoveRight(bool success){}
		virtual void OnMoveExit(bool success){}
		virtual void OnSwitchLeft(bool success){}
		virtual void OnSwitchRight(bool success){}

		virtual void OnUse(bool success){}
		virtual void OnInit(){}
	public:
		// Constructeurs
		AbstractCursor(AbstractWidget * first = 0);

		// Destructeur
		virtual ~AbstractCursor(){}

		// Accesseurs
		AbstractWidget * GetPrevious() const;
		AbstractWidget * GetCurrent() const;
		AbstractPanel * GetNextPanel() const;
		bool IsPanelExit() const;

		// Modificateurs de l'objet
		void InitWidget(AbstractWidget * widget);
		void GoToWidget(AbstractWidget * widget);

		// Fonctions de la classe
		void Next();
		void Previous();
		void Left();
		void Right();
		void Use();
		void Exit();

		virtual void Calculate(float time_interval) = 0;
		virtual void Draw(sf::RenderTarget & target, float alpha = 1.f) = 0;
};

#endif // ABSTRACTCURSOR_H
