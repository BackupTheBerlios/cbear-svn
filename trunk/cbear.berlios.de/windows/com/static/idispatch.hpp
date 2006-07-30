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
