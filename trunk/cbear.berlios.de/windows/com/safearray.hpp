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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_SAFEARRAY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_SAFEARRAY_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/traits.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

template<class ValueType>
class safearray_t;

namespace detail
{

template<class ValueType>
class safearray_policy: private policy::standard_policy< ::SAFEARRAY *>
{
public:
	typedef ::SAFEARRAY *type;
	typedef policy::standard_policy<type> standard_policy;

	using standard_policy::construct;

	static void construct_copy(type &X, const type &C) 
	{ 
		if(C)
		{
			exception::throw_unless(::SafeArrayCopy(C, &X));
		}
		else
		{
			X = 0;
		}
	}
	static void destroy(type &X)
	{
		if(X) exception::throw_unless(::SafeArrayDestroy(X));
	}
	static void assign(type &X, const type &C)
	{
		destroy(X);
		construct_copy(X, C);
	}
};

}

template<class ValueType>
class safearray_t: public policy::wrap<safearray_t<ValueType>, ::SAFEARRAY *>
{
public:
	static const vartype_t value_type_vt = traits<ValueType>::vt;
	static const vartype_t vt = VT_ARRAY | value_type_vt;
};

}
}
}

#endif
