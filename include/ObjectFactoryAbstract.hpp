#ifndef OBJECTFACTORYABSTRACT_HPP
#define OBJECTFACTORYABSTRACT_HPP

#include <string>

#include "EditorObject.hpp"

class ObjectFactoryAbstract
{
    public:
        ObjectFactoryAbstract();
        virtual ~ObjectFactoryAbstract();
        EditorObject* makeObject(std::string type);
        virtual EditorObject* setTypeObject (std::string type) = 0;
    protected:
    private:
};

#endif // OBJECTFACTORYABSTRACT_HPP
