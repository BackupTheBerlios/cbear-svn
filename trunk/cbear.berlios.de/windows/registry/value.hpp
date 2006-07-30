#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_VALUE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_VALUE_HPP_INCLUDED

#include <cbear.berlios.de/windows/registry/data.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

template<class Char>
class value: public std::pair<base::basic_string<Char>, data<Char> >
{
public:
	typedef Char char_type;
	typedef base::basic_string<char_type> string_type;
	typedef data<char_type> data_type;
	typedef std::pair<string_type, data_type> base_type;

	value() {}

	template<class DataType>
	explicit value(const DataType &data): base_type(string_type(), data) {}

	template<class DataType >
	value(const string_type &name, const DataType &data): base_type(name, data) {}
};

}
}
}

#endif
