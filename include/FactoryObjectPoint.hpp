#ifndef FACTORYOBJECTPOINT_HPP
#define FACTORYOBJECTPOINT_HPP

#include "../constants.hpp"
#include "ObjectFactoryAbstract.hpp"
#include "Point.hpp"

class FactoryObjectPoint : public ObjectFactoryAbstract
{
    public:
        FactoryObjectPoint();
        virtual ~FactoryObjectPoint();
        virtual EditorObject* setTypeObject (std::string type);
    protected:
    private:
};
#endif // FACTORYOBJECTPOINT_HPP

