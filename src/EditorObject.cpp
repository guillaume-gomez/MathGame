#include "EditorObject.hpp"

const std::map<TypeObject,std::string> EditorObject::objectStrMap =
{
    {TypeObject::Hero, HeroStr},
    {TypeObject::Abstract, AbstractStr},
    {TypeObject::Point, PointStr},
    {TypeObject::GoalPoint, GoalPointStr},
    {TypeObject::Circle, CircleStr},
    {TypeObject::Enemy, EnemyStr}
};

const std::map<TypeObject,int> EditorObject::objectValueMap =
{
    {TypeObject::Hero, -1},
    {TypeObject::Abstract, -1},
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
 // TODO
}

TypeObject EditorObject::getTypeByStr(const std::string str)
{
    for (auto it : EditorObject::objectStrMap)
    {
        if(it.second == str)
        {
            return it.first;
        }
    }
    std::runtime_error("EditorObject::getTypeByStr(const std::string str)  cannot find this value");
}

std::string EditorObject::getTypeStr() const
{
    return getTypeStr(m_type);
}

std::string EditorObject::getTypeStr(const TypeObject& type)
{
    const std::map<TypeObject,std::string>::const_iterator it =  EditorObject::objectStrMap.find(type);
    if(it != objectStrMap.end())
    {
        return it->second;
    }
    else
    {
        return AbstractStr;
    }
}


bool EditorObject::compare(const EditorObject* r1, const EditorObject* r2)
{
    return EditorObject::objectValueMap.at(r1->getType()) < EditorObject::objectValueMap.at(r2->getType());
}
