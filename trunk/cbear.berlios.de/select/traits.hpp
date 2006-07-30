#ifndef CBEAR_BERLIOS_DE_SELECT_TRAITS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_SELECT_TRAITS_HPP_INCLUDED

#include <cbear.berlios.de/pp/widen.hpp>
#include <cbear.berlios.de/array/ref.hpp>

namespace cbear_berlios_de
{
namespace select
{

template<class Char, class A, class W>
struct traits;

template<class A, class W>
struct traits<char, A, W>
{
	typedef A type;
	static type get(A X, W ) { return X; }
};

template<class A, class W>
struct traits<wchar_t, A, W>
{
	typedef W type;
	static type get(A, W X) { return X; }
};

template<class C, class A, class W>
typename traits<C, const A &, const W &>::type get(const A &A_, const W &W_)
{
	return traits<C, const A &, const W &>::get(A_, W_);
}

}
}

#define CBEAR_BERLIOS_DE_SELECT_CHAR(Char, X) \
	::cbear_berlios_de::select::get<Char>(X, CBEAR_BERLIOS_DE_PP_WIDEN(X))

#define CBEAR_BERLIOS_DE_SELECT_STRING(Char, X) \
	::cbear_berlios_de::select::get<Char>( \
		CBEAR_BERLIOS_DE_ARRAY_REF(X), \
		CBEAR_BERLIOS_DE_ARRAY_REF(CBEAR_BERLIOS_DE_PP_WIDEN(X)))

#endif
