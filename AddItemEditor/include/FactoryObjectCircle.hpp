#ifndef FactoryObjectCircle_HPP
#define FactoryObjectCircle_HPP

#include "../constants.hpp"
#include "ObjectFactoryAbstract.hpp"
#include "GravityCircle.hpp"

class FactoryObjectCircle : public ObjectFactoryAbstract
{
    public:
        FactoryObjectCircle();
        virtual ~FactoryObjectCircle();
        virtual EditorObject* setTypeObject (std::string type);
    protected:
    private:
};
#endif // FactoryObjectCircle_HPP

