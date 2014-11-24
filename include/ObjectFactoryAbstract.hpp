#ifndef OBJECTFACTORYABSTRACT_HPP
#define OBJECTFACTORYABSTRACT_HPP

#include <iostream>
#include <string>

#include "EditorObject.hpp"

//template <class Object, class key = std:string> class

class ObjectFactoryAbstract
{
    public:
    	static std::map<TypeObject, EditorObject*> m_map;
        ObjectFactoryAbstract();
        virtual ~ObjectFactoryAbstract();
        static void _register(TypeObject key, EditorObject* obj);
        static EditorObject* create(const TypeObject& key);
    protected:
    private:
};

#endif // OBJECTFACTORYABSTRACT_HPP
