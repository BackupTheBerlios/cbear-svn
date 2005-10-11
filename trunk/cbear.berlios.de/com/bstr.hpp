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
#ifndef CBEAR_BERLIOS_DE_COM_BSTR_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_COM_BSTR_HPP_INCLUDED

#include <cbear.berlios.de/com/traits.hpp>

namespace cbear_berlios_de
{
namespace com
{

namespace detail
{

struct bstr_policy: private policy::standard_policy< ::BSTR>
{
	typedef ::BSTR type;
	typedef policy::standard_policy<type> standard_policy_type;

	using standard_policy_type::construct;

	static void construct_copy(type &This, const type &Source) 
	{ 
		This = Source ? ::SysAllocStringLen(Source, ::SysStringLen(Source)): 0;
	}

	static void destroy(type &This) 
	{
		::SysFreeString(This);
	}

	static void assign(type &This, const type &Source)
	{ 
		type New;
		construct_copy(New, Source);
		destroy(This);
		This = New;
	}

	/*
	static bool equal(const type &A, const type &B)
	{
		return A==B;
	}

	static bool less(const type &A, const type &B)
	{
		return A<B;
	}

	typedef typename boost::remove_pointer<type>::type value_type;
	typedef typename boost::add_reference<value_type>::type reference;
	typedef typename boost::add_pointer<value_type>::type pointer;

	static reference reference_of(const type &This) { return *This; }
	*/
};

}

class bstr_t: public policy::wrap<bstr_t, ::BSTR>
{
};

}
}

#endif
