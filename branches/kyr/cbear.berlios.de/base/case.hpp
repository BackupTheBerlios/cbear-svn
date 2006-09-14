#ifndef CBEAR_BERLIOS_DE_BASE_CASE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_CASE_HPP_INCLUDED

#include <cbear.berlios.de/base/character.hpp>
#include <cbear.berlios.de/select/traits.hpp>

namespace cbear_berlios_de
{
namespace base
{

template<class Char>
Char to_lower(Char c)
{
	static const Char A = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'A');
	static const Char Z = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'Z');
	static const Char a = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'a');
	static const Char z = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'z');
	static const Char dif = A - a;
	return a <= c && c <= z ? c + dif: c;
}

template<class Char>
bool latin_case_insensetive_equal(Char c1, Char c2)
{
	return to_lower(c1) == to_lower(c2);
}

}
}

#endif
