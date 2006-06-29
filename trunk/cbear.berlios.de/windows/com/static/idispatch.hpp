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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_IDISPATCH_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_IDISPATCH_HPP_INCLUDED

#include <cbear.berlios.de/c/in.hpp>
#include <cbear.berlios.de/c/cpp_in.hpp>
#include <cbear.berlios.de/c/out.hpp>
#include <cbear.berlios.de/c/cpp_out.hpp>
#include <cbear.berlios.de/windows/com/static/interface_content.hpp>
#include <cbear.berlios.de/windows/com/lcid.hpp>
#include <cbear.berlios.de/windows/com/idispatch.hpp>
#include <cbear.berlios.de/windows/com/itypeinfo.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

// One class can't contain more than one IDispatch.
template<class T, class B>
class interface_content<T, B, ::IDispatch>: public interface_<T, B, ::IUnknown>
{
public:
	::HRESULT __stdcall GetTypeInfoCount(c::out_t<uint_t>::type R_)
	{
		// parameters:
		uint_t &R = c::cpp_out<uint_t>(R_);
		//
		R = 1;
		return hresult::s_ok;
	}
	::HRESULT __stdcall GetTypeInfo(
		c::in_t<uint_t>::type N_, 
		c::in_t<lcid_t>::type, 
		itypeinfo::c_out_t P_)
	{
		// parameters:
		const uint_t &N = c::cpp_in<uint_t>(N_);
		itypeinfo &P = c::cpp_out<itypeinfo>(P_);
		//
		if(N != 0) return hresult::disp_e_badindex;
		P = scoped_type_info<B>::typeinfo();
		return hresult::s_ok;
	}

	hresult::internal_type __stdcall GetIDsOfNames(
		const uuid::c_t &, 
		lpolestr_t::internal_type *rgszNames, 
		uint_t cNames, 
		lcid_t, 
		dispid_t *rgDispId)
	{
		return ::DispGetIDsOfNames(
			scoped_type_info<B>::typeinfo().c_in(), 
			rgszNames, 
			cNames, 
			rgDispId);
	}

	HRESULT __stdcall Invoke(
		dispid_t dispidMember,
		const uuid::c_t &,
		lcid_t,
		word_t wFlags,
		dispparams_t * pdispparams,
		variant_t * pvarResult,
		excepinfo_t * pexcepinfo,
		uint_t * puArgErr)
	{
		return DispInvoke(
			(B *)this, 
			internal<in>(scoped_type_info<B>::typeinfo()),
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
