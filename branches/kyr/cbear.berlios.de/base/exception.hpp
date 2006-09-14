#ifndef CBEAR_BERLIOS_DE_BASE_EXCEPTION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_EXCEPTION_HPP_INCLUDED

// std::exception
#include <exception>

#include <cbear.berlios.de/base/string.hpp>

namespace cbear_berlios_de
{
namespace base
{

/*
template<class Char>
class basic_exception
{
public:
	virtual void output(std::basic_ostream<Char> &O) const = 0;
};

typedef basic_exception<char> exception;
typedef basic_exception<wchar_t> wexception;

template<class Char>
std::basic_ostream<Char> &operator<<(
	std::basic_ostream<Char> &S, const basic_exception<Char> &E)
{
	E.output(S);
	return S;
}
*/

}
}

#endif
