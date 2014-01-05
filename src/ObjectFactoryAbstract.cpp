#include "ObjectFactoryAbstract.hpp"
#include "../constants.hpp"
#include "GravityCircle.hpp"
#include "Point.hpp"

#include <stdexcept>


ObjectFactoryAbstract::ObjectFactoryAbstract()
{}

ObjectFactoryAbstract::~ObjectFactoryAbstract()
{
    //dtor
}

std::map<TypeObject, EditorObject*> ObjectFactoryAbstract::m_map = std::map<TypeObject, EditorObject*>();

void ObjectFactoryAbstract::_register (const TypeObject key, EditorObject* obj)
{
	if(m_map.find(key) == m_map.end())
	{
		m_map[key] = obj;
	}
}

EditorObject* ObjectFactoryAbstract::create(const TypeObject& key)
{
	EditorObject* newObject = nullptr;
	std::map<TypeObject, EditorObject*>::const_iterator it = m_map.find(key);

    if(m_map.size() == 0)
    {
        std::runtime_error("In the ObjectFactoryAbstract::create : the factory hasn't got any template method");
    }

	if(it != m_map.end())
	{
		newObject = ((*it).second)->clone();
	}
	else
	{
		std::runtime_error("In the ObjectFactoryAbstract::create : cannot make an object like this");
	}

	return newObject;
}
