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
#ifndef CBEAR_BERLIOS_DE_BASE_SAFE_REINTERPRET_CAST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_SAFE_REINTERPRET_CAST_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace base
{

template<class To, class From>
To safe_reinterpret_cast(From *X)
{
	BOOST_STATIC_ASSERT(boost::is_pointer<To>::value);
	BOOST_STATIC_ASSERT(sizeof(boost::remove_pointer<To>::type)<=sizeof(From));
	return reinterpret_cast<To>(X);
}

template<class To, class From>
To safe_reinterpret_cast(From &X)
{
	BOOST_STATIC_ASSERT(boost::is_reference<To>::value);
	BOOST_STATIC_ASSERT(sizeof(boost::remove_reference<To>::type)<=sizeof(From));
	return reinterpret_cast<To>(X);
}

template<class To, class From>
To safe_reinterpret_cast(const From &X)
{
	BOOST_STATIC_ASSERT(boost::is_reference<To>::value);
	BOOST_STATIC_ASSERT(sizeof(boost::remove_reference<To>::type)<=sizeof(From));
	return reinterpret_cast<To>(X);
}

}
}

#endif
