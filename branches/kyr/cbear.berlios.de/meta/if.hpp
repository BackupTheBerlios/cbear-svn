#ifndef CBEAR_BERLIOS_DE_META_IF_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_META_IF_HPP_INCLUDED

namespace cbear_berlios_de
{

namespace meta
{

namespace detail
{
class no_else;
}

template<bool C, class T = void, class E = detail::no_else>
class if_c;

namespace detail
{

template<bool C, class T>
class if_c
{
public:

	typedef if_c o;

	template<bool C1, class T1 = void, class E1 = no_else>
	class else_if_c: 
		public meta::if_c<C || C1, typename meta::if_c<C, T, T1>::type, E1>
	{
	};

	template<class C1, class T1 = void, class E1 = no_else>
	class else_if: public else_if_c<C1::value, T1, E1> {};

	template<class E>
	class else_: public meta::if_c<C, T, E> {};
};

}

template<class T, class E>
class if_c<false, T, E>
{
public:
	typedef E type;
};

template<class T, class E>
class if_c<true, T, E>
{
public:
	typedef T type;
};

template<class T>
class if_c<false, T, detail::no_else>: public detail::if_c<false, T>
{
};

template<class T>
class if_c<true, T, detail::no_else>: public detail::if_c<true, T>
{
public:
	typedef T type;
};

template<class C, class T = void, class E = detail::no_else>
class if_: public if_c<C::value, T, E> {};

}
}

#endif
