#ifndef ABSTRACTWIDGETEVENT_H_INCLUDED
#define ABSTRACTWIDGETEVENT_H_INCLUDED

class AbstractWidgetEvent
{
	public:
		virtual ~AbstractWidgetEvent(){}
		virtual bool Execute() = 0;
};



#endif // ABSTRACTWIDGETEVENT_H_INCLUDED
