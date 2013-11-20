#ifndef ABSTRACTWIDGET_H
#define ABSTRACTWIDGET_H

#include <SFML/Graphics.hpp>
#include "ScopedPtr.hpp"
#include "AbstractWidgetEvent.hpp"

class AbstractPanel;

class AbstractWidget
{
		AbstractWidget	* previous;
		AbstractWidget	* next;
		AbstractWidget	* left;
		AbstractWidget	* right;

		ScopedPtr<AbstractWidgetEvent> use_event;
		ScopedPtr<AbstractWidgetEvent> switch_left_event;
		ScopedPtr<AbstractWidgetEvent> switch_right_event;

		AbstractPanel	* next_panel;
		bool			panel_exit;

	protected:
		virtual void OnMove(){}
		virtual void OnUse(bool success){}
		virtual void OnSwitchLeft(bool success){}
		virtual void OnSwitchRight(bool success){}
		virtual void OnGainedFocus(){}
		virtual void OnLostFocus(){}
	public:
		// Constructeurs
		AbstractWidget();

		// Destructeur
		virtual ~AbstractWidget(){}

		// Accesseurs
		AbstractWidget * GetPreviousWidget() const;
		AbstractWidget * GetNextWidget() const;
		AbstractWidget * GetLeftWidget() const;
		AbstractWidget * GetRightWidget() const;
		AbstractPanel * GetNextPanel() const;
		bool IsPanelExit() const;
		bool IsSwitchLeftEvent() const;
		bool IsSwitchRightEvent() const;
		bool IsUseEvent() const;

		// Modificateurs de l'objet
		void SetPreviousWidget(AbstractWidget * previous);
		void SetNextWidget(AbstractWidget * next);
		void SetLeftWidget(AbstractWidget * left);
		void SetRightWidget(AbstractWidget * right);
		void SetUseEvent(AbstractWidgetEvent * use_event);
		void SetSwitchLeftEvent(AbstractWidgetEvent * switch_left_event);
		void SetSwitchRightEvent(AbstractWidgetEvent * switch_right_event);
		void SetNextPanel(AbstractPanel * next_panel);
		void SetPanelExit(bool panel_exit);


		// Fonctions de la classe
		bool Use();
		bool SwitchLeft();
		bool SwitchRight();
		void GainFocus();
		void LoseFocus();

		virtual void Calculate(float time_interval) = 0;
		virtual void Draw(sf::RenderTarget & target, float alpha = 1.f) = 0;
};

#endif // ABSTRACTWIDGET_H
