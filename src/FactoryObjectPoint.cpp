#include "FactoryObjectPoint.hpp"

FactoryObjectPoint::FactoryObjectPoint()
{
    //ctor
}

FactoryObjectPoint::~FactoryObjectPoint()
{
    //dtor
}


EditorObject* FactoryObjectPoint::setTypeObject (std::string type)
{
	Point* newPoint = nullptr;

	if (type == PointStr)
	{
		newPoint = new Point(sizePoint, GraphScale, GraphScale);
		if(newPoint == nullptr)
		{
			std::runtime_error("In the class FactoryObjectPoint::setTypeObject : cannot allocate à new object \"Point\"");
		}
	}
	else if (type == GoalPointStr)
	{
		newPoint = new Point(sizePoint,true, GraphScale);
		if(newPoint == nullptr)
		{
			std::runtime_error("In the class FactoryObjectPoint::setTypeObject : cannot allocate à new object \"Point\"");
		}
	}
	return newPoint;
}
