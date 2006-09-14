#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_LIST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_LIST_HPP_INCLUDED

#include <vector>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

template<class ValueType>
class list: public std::vector<ValueType>
{ 
public: 
	typedef ValueType value_type;
	list &operator()(const value_type &X)
	{
		this->push_back(X);
		return *this;
	}
};

}
}
}

#endif
