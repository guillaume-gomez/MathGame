#ifndef ABSTRACTPANEL_H
#define ABSTRACTPANEL_H
#include "PtrVector.hpp"
#include "PtrList.hpp"
#include "ScopedPtr.hpp"
#include <SFML/Graphics.hpp>
#include "AbstractCursor.hpp"
#include "AbstractWidget.hpp"

class AbstractPanel
{

	protected:

	    AbstractWidget					* initial_widget;
		AbstractWidget					* exit_widget;
		PtrVector<AbstractWidget>			widgets;

		bool						visible;
		bool						focused;
		bool						locked;
		ScopedPtr<AbstractCursor>			cursor;

		AbstractPanel					* parent;
		PtrList<AbstractPanel>				childs;

		bool						persistant;

		sf::Clock                   clock;
		bool                        intervalOk;

		virtual void OnDisplay(bool entering) = 0;
		virtual void OnHide(bool entering) = 0;

		void CalculateWidgets(float time_interval);
		void CalculateCursor(float time_interval);
		void CalculatePanels(float time_interval);

		void DrawWidgets(sf::RenderTarget & target,float alpha);
		void DrawCursor(sf::RenderTarget & target,float alpha);
		void DrawPanels(sf::RenderTarget & target,float alpha);

	public:
		// Constructeur
		AbstractPanel(AbstractCursor * cursor, AbstractPanel * parent = 0);

		// Destructeur
		virtual ~AbstractPanel(){}

		// Accesseurs
		bool IsVisible() const;
		bool IsPersistant() const;
		bool IsLocked() const;

		// Modificateurs de l'objet
		void SetVisible(bool visible);
		void SetExitWidget(AbstractWidget * exit_widget);
		void AddWidget(AbstractWidget * widget);
		void AddChild(AbstractPanel * child);
		void SetParent(AbstractPanel * parent);
		void SetPersistant(bool persistant);


		// Fonctions de la classe
		void Next();
		void Previous();
		void Left();
		void Right();
		bool Use();
		void Exit();

		void Display(bool entering = true);
		void Hide(bool entering = true);
		void Focus(bool init);
		void UnFocus();
		void Lock();
		void Unlock();

		void TimerOperation();

		virtual void Calculate(float time_interval) = 0;
		virtual void Draw(sf::RenderTarget & target, float alpha = 1.f) = 0;
};

#endif // ABSTRACTPANEL_H
