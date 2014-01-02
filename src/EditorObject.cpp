#include "EditorObject.hpp"

EditorObject::EditorObject()
{

}

EditorObject::~EditorObject()
{
    //dtor
}


std::ostream& operator<<( std::ostream &flux, TypeObject const type )
{
    switch(type)
    {
        case TypeObject::Abstract:
            flux << AbstractStr;
        break;

        case TypeObject::Circle:
            flux << CircleStr;
        break;

        case TypeObject::Point:
            flux << PointStr;
        break;

        case TypeObject::GoalPoint:
            flux << GoalPointStr;
        break;

        default:
            flux <<" Error invalid type";
        break;

    }
    return flux;
}


std::string EditorObject::getTypeStr() const
{
    switch(m_type)
    {
        case TypeObject::Abstract:
            return AbstractStr;
        break;

        case TypeObject::Circle:
            return CircleStr;
        break;

        case TypeObject::Point:
            return PointStr;
        break;

        case TypeObject::GoalPoint:
            return GoalPointStr;
        break;

        default:
            return " Error invalid type";
        break;

    }
}


bool EditorObject::compare(const EditorObject* r1, const EditorObject* r2)
{
	int valueR1 = 0;
	int valueR2 = 0;


	if(r1->getType() == TypeObject::Abstract)
	{
		valueR1 = -1;
	}
	else if(r1->getType() == TypeObject::Point)
	{
		valueR1 = 2;
	}
	else if (r1->getType() == TypeObject::GoalPoint)
	{
		valueR1 = 3;
	}
	else if(r1->getType() == TypeObject::Circle)
	{
		valueR1 = 1;
	}


	if(r2->getType() == TypeObject::Abstract)
	{
		valueR2 = -1;
	}
	else if(r2->getType() == TypeObject::Point)
	{
		valueR2 = 2;
	}
	else if (r2->getType() == TypeObject::GoalPoint)
	{
		valueR2 = 3;
	}
	else if(r2->getType() == TypeObject::Circle)
	{
		valueR2 = 1;
	}

    return valueR1 < valueR2;
}
