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
#ifndef CBEAR_BERLIOS_DE_COM_VARIANT_BOOL_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_COM_VARIANT_BOOL_HPP_INCLUDED

#include <cbear.berlios.de/com/traits.hpp>

namespace cbear_berlios_de
{
namespace com
{

class variant_bool_t;

namespace detail
{

class variant_bool_policy: policy::standard_policy< ::VARIANT_BOOL>
{
public:
	typedef ::VARIANT_BOOL type;
	typedef policy::standard_policy<type> standard_policy;
	using standard_policy::construct;
	using standard_policy::construct_copy;
	using standard_policy::destroy;
	using standard_policy::assign;

	typedef base::undefined pointer;
	typedef base::undefined reference;

	static bool cast(type This) { return This!=FALSE; }

	template<class Stream>
	static void output(Stream &S, type This) 
	{ 
		S << cast(This); 
	}
};

typedef policy::wrap<variant_bool_t, ::VARIANT_BOOL, variant_bool_policy> 
	variant_bool_wrap;

}

class variant_bool_t: public detail::variant_bool_wrap
{
public:
	typedef detail::variant_bool_wrap::internal_policy internal_policy;
	operator bool() const { return internal_policy::cast(this->internal()); }
};

}
}

#endif
