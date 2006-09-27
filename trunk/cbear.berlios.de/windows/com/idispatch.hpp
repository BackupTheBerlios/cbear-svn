#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_IDISPATCH_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_IDISPATCH_HPP_INCLUDED

#include <cbear.berlios.de/windows/oaidl.h>
// #include <cbear.berlios.de/windows/com/dynamic/implementation.hpp>
#include <cbear.berlios.de/windows/com/lcid.hpp>

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

/*
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
		internal_result<out, itypeinfo_t>::type ppTInfo)
	{
		if(iTInfo != 0) return hresult::disp_e_badindex;
		wrap<out, itypeinfo>(ppTInfo) = scoped_type_info<Base>::typeinfo();
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
			internal<in>(scoped_type_info<Base>::typeinfo()), 
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
*/

}
}
}

#endif
