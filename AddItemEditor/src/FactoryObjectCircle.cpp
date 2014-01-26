#include "FactoryObjectCircle.hpp"

FactoryObjectCircle::FactoryObjectCircle()
{
    //ctor
}

FactoryObjectCircle::~FactoryObjectCircle()
{
    //dtor
}


EditorObject* FactoryObjectCircle::setTypeObject (std::string type)
{
	GravityCircle* newCircle = nullptr;
	
	if (type == CircleStr)
	{
		GravityCircle* newCircle = new GravityCircle();
		if(newCircle == nullptr)
		{
			std::runtime_error("In the class FactoryObjectCircle::setTypeObject : cannot allocate à new object \"GravityCircle\"");
		}
	}
	return newCircle;
}