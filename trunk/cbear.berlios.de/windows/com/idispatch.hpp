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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_IDISPATCH_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_IDISPATCH_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/dynamic_implementation.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

typedef VARIANT variant_t;
typedef DISPID dispid_t;
typedef DISPPARAMS dispparams_t;
typedef EXCEPINFO excepinfo_t;

namespace dynamic
{

template<class Base>
class implementation<Base, ::IDispatch>:
	public implementation_base<Base, ::IDispatch, ::IUnknown>
{
public:

	hresult::internal_type __stdcall GetTypeInfoCount(
		internal_result<out, uint_t>::type _result) 
	{
		wrap<out, uint_t>(_result) = 1;
		return hresult::s_ok;
	}

	hresult::internal_type __stdcall GetTypeInfo(
		uint_t iTInfo,
		lcid_t,
		internal_result<out, itypeinfo>::type ppTInfo)
	{
		if(iTInfo != 0) return hresult::disp_e_badindex;
		wrap<out, itypeinfo>(ppTInfo) = scoped_type_info<Base>::typeinfo();
		return hresult::s_ok;
	}

	hresult::internal_type __stdcall GetIDsOfNames(
		const uuid::internal_type &, 
		lpolestr_t::internal_type *rgszNames, 
		uint_t cNames, 
		lcid_t, 
		dispid_t *rgDispId)
	{
		return ::DispGetIDsOfNames(
			internal<in>(scoped_type_info<Base>::typeinfo()), 
			rgszNames, 
			cNames, 
			rgDispId);
	}

	HRESULT __stdcall Invoke(
		dispid_t dispidMember,
		const uuid::internal_type &,
		lcid_t,
		word_t wFlags,
		dispparams_t * pdispparams,
		variant_t * pvarResult,
		excepinfo_t * pexcepinfo,
		uint_t * puArgErr)
	{
		return DispInvoke(
			(Base *)this, 
			internal<in>(scoped_type_info<Base>::typeinfo()),
			dispidMember, 
			wFlags, 
			pdispparams,
			pvarResult, 
			pexcepinfo, 
			puArgErr);
	}
};

}
}
}
}

#endif
