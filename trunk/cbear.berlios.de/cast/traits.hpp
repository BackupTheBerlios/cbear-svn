/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
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
	static To reinterpret(From F) throw()
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
	static To *do_(From F) throw()
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
