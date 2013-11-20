#ifndef WIDGETEVENT_H_INCLUDED
#define WIDGETEVENT_H_INCLUDED

class BoolSwapWidgetEvent : public AbstractWidgetEvent
{
		bool & m_value;
	public:
		BoolSwapWidgetEvent(bool & value) : m_value(value){}
		virtual bool Execute()
		{
			m_value = !m_value;
			return true;	// Renvoyer true si l'opération s'est bien passée, false en cas contraire.
		}
};

#endif // WIDGETEVENT_H_INCLUDED
