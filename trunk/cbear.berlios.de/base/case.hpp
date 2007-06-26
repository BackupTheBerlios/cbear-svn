#ifndef CBEAR_BERLIOS_DE_BASE_CASE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_CASE_HPP_INCLUDED

#include <cbear.berlios.de/base/character.hpp>
#include <cbear.berlios.de/select/traits.hpp>

namespace cbear_berlios_de
{
namespace base
{

template<class Char>
class case_traits
{
public:
	static Char const A = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'A');
	static Char const Z = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'Z');
	static Char const a = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'a');
	static Char const z = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'z');
	static Char const dif = static_cast<Char>(A - a);
};

class to_lower
{
public:
	template<class Char>
	void operator()(Char &c) const
	{
		typedef case_traits<Char> traits;
		if(traits::A <= c && c <= traits::Z) 
		{
			c -= traits::dif;
		}
	}
};

class to_upper
{
public:
	template<class Char>
	void operator()(Char &c) const
	{
		BOOST_STATIC_ASSERT(!::boost::is_const<Char>::value);
		typedef case_traits<Char> traits;
		if(traits::a <= c && c <= traits::z)
		{
			c += traits::dif;
		}
	}
};

class latin_case_insensetive_equal
{
public:
	template<class Char>
	bool operator()(Char c1, Char c2) const
	{
		to_lower()(c1);
		to_lower()(c2);
		return c1 == c2;
	}
};

}
}

#endif
