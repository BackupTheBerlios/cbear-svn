#ifndef CBEAR_BERLIOS_DE_STREAM_TRAITS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_TRAITS_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator_range.hpp>
#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/size.hpp>
#include <cbear.berlios.de/select/traits.hpp>
#include <cbear.berlios.de/meta/if.hpp>

namespace cbear_berlios_de
{
namespace stream
{

class unknown_traits 
{
};

class class_traits
{
public:
	template<class S, class T>
	static void write(S &s, const T &t) { t.write(s); }
};

class bool_traits
{
public:
	template<class S, class T>
	static void write(S &s, const T &t)
	{
		typedef typename S::value_type value_type;
		if(t)
			s.push_back_range(CBEAR_BERLIOS_DE_SELECT_STRING(value_type, "true"));
		else
			s.push_back_range(CBEAR_BERLIOS_DE_SELECT_STRING(value_type, "false"));
	}
};

class char_traits
{
public:
	template<class S, class T>
	static void write(S &s, const T &t)
	{
		s.push_back_range(range::make_iterator_range(&t, &t + 1));
	}
	template<class S, class T>
	static void read(S &s, T &t)
	{
		s.pop_front_range(base::const_ref(range::make_iterator_range(&t, &t + 1)));
	}
};

class integer_traits
{
public:
	template<class S, class T>
	static void write(S &s, const T &t)
	{
		base::out<10>(t).write(s);
	};
};

class array_traits
{
public:
	template<class S, class C, std::size_t Size>
	static void write(S &s, const C (&t)[Size])
	{
		BOOST_STATIC_ASSERT((boost::is_same<typename S::value_type, C>::value));
		s.push_back_range(t);
	}
};

template<class S, class T>
class traits: public 
	meta::if_<
		boost::is_class<T>, class_traits>::
	template else_if<
		boost::is_same<T, typename S::value_type>, char_traits>::o::
	template else_if<
		boost::is_same<T, bool>, bool_traits>::o::
	template else_if<
		boost::is_integral<T>, integer_traits>::o::
	template else_if<
		boost::is_array<T>, array_traits>::
	template else_<
		unknown_traits>::type
{
};

}
}

#endif
