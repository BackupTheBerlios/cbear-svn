#ifndef CBEAR_BERLIOS_DE_CAST_TRAITS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_CAST_TRAITS_HPP_INCLUDED

#include <boost/static_assert.hpp>

namespace cbear_berlios_de
{

namespace cast
{

template<class To>
class traits
{
public:
	template<class From>
	static To reinterpret(const From &F) throw()
	{
		BOOST_STATIC_ASSERT(sizeof(To)==sizeof(From));
		return reinterpret_cast<To>(F);
	}
};

template<class To>
class traits<To &>
{
public:
	template<class From>
	static To &reinterpret(From &F) throw()
	{
		BOOST_STATIC_ASSERT(sizeof(To)==sizeof(From));
		return reinterpret_cast<To &>(F);
	}
};

template<class To>
class traits<const To &>
{
public:
	template<class From>
	static const To &reinterpret(const From &F) throw()
	{
		BOOST_STATIC_ASSERT(sizeof(To)==sizeof(From));
		return reinterpret_cast<const To &>(F);
	}
};

template<class To>
class traits<To *>
{
public:
	template<class From>
	static To *reinterpret(From *F) throw()
	{
		BOOST_STATIC_ASSERT(sizeof(To)==sizeof(From));
		return reinterpret_cast<To *>(F);
	}
	template<class From>
	static To *reinterpret(const From &F) throw()
	{
		BOOST_STATIC_ASSERT(sizeof(To *)==sizeof(From));
		return reinterpret_cast<To *>(F);
	}
};

}

/*
template<class To, class From>
class safe_reinterpret_cast_traits
{
public:
	typedef To to_type;
	typedef From from_type;
};

template<class To, class From>
class safe_reinterpret_cast_traits<To &, From>
{
public:
	typedef To to_type;
	typedef From from_type;
};

template<class To, class From>
class safe_reinterpret_cast_traits<To *, From *>
{
public:
	typedef To to_type;
	typedef From from_type;
};

template<class To, class From>
To safe_reinterpret_cast(From &X)
{
	typedef safe_reinterpret_cast_traits<To, From> traits;
	BOOST_STATIC_ASSERT(
		sizeof(typename traits::to_type)==sizeof(typename traits::from_type));
	return reinterpret_cast<To>(X);
}

template<class To, class From>
To safe_reinterpret_cast(const From &X)
{
	typedef safe_reinterpret_cast_traits<To, From> traits;
	BOOST_STATIC_ASSERT(
		sizeof(typename traits::to_type)==sizeof(typename traits::from_type));
	return reinterpret_cast<To>(X);
}
*/

}

#endif
