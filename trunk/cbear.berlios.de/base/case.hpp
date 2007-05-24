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
	static Char const A = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'A');
	static Char const Z = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'Z');
	static Char const a = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'a');
	static Char const z = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'z');
	static Char const dif = A - a;
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
