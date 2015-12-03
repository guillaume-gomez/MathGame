#include "Count.hpp"

int Count::count = 0;

Count::Count()
{

}

int Count::countAllInstances()
{
	return count;
}
