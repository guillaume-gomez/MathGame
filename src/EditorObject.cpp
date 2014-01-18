#include "EditorObject.hpp"


const std::map<TypeObject,int> EditorObject::objectValueMap =
{
    {TypeObject::Abstract,-1},
    {TypeObject::Point, 3},
    {TypeObject::GoalPoint, 4},
    {TypeObject::Circle, 2},
    {TypeObject::Enemy, 1}
};

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

        case TypeObject::Enemy:
            flux << EnemyStr;
        break;

        case TypeObject::Hero:
            flux << HeroStr;
        break;

        default:
            flux <<" Error invalid type";
        break;

    }
    return flux;
}


std::string EditorObject::getTypeStr() const
{
    return getTypeStr(m_type);
}

std::string EditorObject::getTypeStr(const TypeObject& type)
{
    switch(type)
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

        case TypeObject::Enemy:
            return EnemyStr;
        break;

        case TypeObject::Hero:
            return HeroStr;
        break;

        default:
            return " Error invalid type";
        break;

    }
}


bool EditorObject::compare(const EditorObject* r1, const EditorObject* r2)
{
    return EditorObject::objectValueMap.at(r1->getType()) < EditorObject::objectValueMap.at(r2->getType());
}
