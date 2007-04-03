#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_HRESULT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_HRESULT_HPP_INCLUDED

// ::HRESULT
#include <windef.h>
// CTL
#include <olectl.h>

// boost::uint16_t
#include <boost/cstdint.hpp>

#include <cbear.berlios.de/bit/range.hpp>
#include <cbear.berlios.de/policy/main.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class hresult;

typedef policy::wrap<hresult, ::HRESULT> hresult_wrap;

// An SCODE was specified. The type of the error is specified in scodee.
// Generally, operations on error values should raise an exception or 
// propagate the error to the return value, as appropriate.
//
// HRESULT has the following format:
//
//      31 | S, 0 - success, 1 - failure.
//      30 | R, reserved.
//      29 | C, reserved.
//      28 | N, reserved.
//      27 | r, reserved.
// 16 - 26 | Facility, 
//  0 - 15 | Code
//
class hresult: public hresult_wrap
{
public:

	typedef internal_type c_t;

	typedef hresult_wrap::internal_type internal_type;


	// Severity

	typedef bool severity_type;
	typedef bit::one<internal_type, 31> severity_bit;
	typedef severity_bit::reference severity_reference;

	severity_type failed() const
	{
		return severity_bit::get(this->internal());
	}
	severity_reference failed()
	{
		return severity_reference(this->internal()); 
	}

	// Facility

	class facility_type;

	typedef policy::wrap<facility_type, boost::uint16_t> facility_wrap;

	class facility_type: public facility_wrap
	{
	public:

		typedef facility_wrap::internal_type internal_type;

		enum enumeration
		{
			// For late-binding IDispatch interface errors. 
			dispatch = FACILITY_DISPATCH,

			// For most status codes returned from interface methods. The actual 
			// meaning of the error is defined by the interface. That is, two 
			// com::hresult with exactly the same 32-bit value returned from two 
			// different interfaces might have different meanings.  
			itf = FACILITY_ITF,
 
			// For broadly applicable common status codes such as hresult::s_ok. 
			null = FACILITY_NULL,

			// For status codes returned from remote procedure calls.
			rpc = FACILITY_RPC,

			// For status codes returned from IStorage or IStream method calls 
			// relating to structured storage. Status codes whose code (lower 16 bits)
			// value is in the range of DOS error codes (that is, less than 256) have
			// the same meaning as the corresponding DOS error.  
			storage = FACILITY_STORAGE,

			// Used to provide a means of handling error codes from functions in the 
			// Win32 API as an hresult. Error codes in 16-bit OLE that duplicated 
			// Win32 error codes have also been changed to facility::win32. 
			win32 = FACILITY_WIN32,
 
			// Used for additional error codes from Microsoft-defined interfaces.
			windows = FACILITY_WINDOWS,

			internet = FACILITY_INTERNET,
			
			// .NET
			dotnet = 0x0013,
		};

		facility_type() {}
		facility_type(enumeration E): facility_wrap(internal_type(E)) {}
		explicit facility_type(internal_type Value): facility_wrap(Value) {}
	};

	typedef bit::range<internal_type, 16, 26, facility_type::internal_type> 
			facility_range;

	facility_type facility() const
	{
		return facility_type(facility_range::get(this->internal()));
	}

	class facility_reference
	{
	public:
		explicit facility_reference(hresult &X): Value(X.internal()) {}
		operator facility_type() const { return facility_type(this->Value); }
		facility_reference &operator=(facility_type X)
		{
			this->Value = X.internal();
			return *this;
		}
	private:
		facility_range::reference Value;
	};

	facility_reference facility()
	{
		return facility_reference(*this);
	}

	// Code

	class code_type;

	typedef policy::wrap<code_type, boost::uint16_t> code_wrap;

	class code_type: public code_wrap
	{
	public:

		typedef code_wrap::internal_type internal_type;

		enum enumeration
		{
			min = 0x0200,
			max = 0xFFFF,
		};

		code_type() {}
		code_type(enumeration X): code_wrap(internal_type(X)) {}
		explicit code_type(internal_type X): code_wrap(X) {}
	};

	typedef bit::range<internal_type, 0, 15, code_type::internal_type> code_range;

	code_type code() const
	{
		return code_type(code_range::get(this->internal()));
	}

	class code_reference
	{
	public:
		explicit code_reference(hresult &X): Value(X.internal()) {}
		operator code_type() const { return code_type(this->Value); }
		code_reference &operator=(code_type X)
		{
			this->Value = X.internal();
			return *this;
		}
	private:
		code_range::reference Value;
	};

	code_reference code()
	{
		return code_reference(*this);
	}

	//

	const internal_type &c_in() const
	{
		return this->internal();
	}

	//

	hresult(bool S, facility_type F, code_type C)
	{
		this->failed() = S;
		this->facility() = F;
		this->code() = C;
	}

	hresult() {}

	template<bool S, ::boost::uint16_t F, ::boost::uint16_t C>
	class make_t
	{
	public:
		static ::HRESULT const v = 
			(static_cast< ::HRESULT>(S) << 31) | 
			(static_cast< ::HRESULT>(F) << 16) |
			(static_cast< ::HRESULT>(C));
	};
	
	template<dword_t R>
	class from_win32_t
	{
	public:
		static ::HRESULT const v = 
			R < 0 ? R : make_t<true, facility_type::win32, R>::v;
	};

	enum enumeration
	{
		// Operation successful
		s_ok = S_OK,

		s_false = S_FALSE,

		// 0x80004001, Not implemented, .NET System.NotImplementedException
		e_notimpl = E_NOTIMPL,
		// 0x80004002, No such interface supported, .NET System.InvalidCastException
		e_nointerface = E_NOINTERFACE,
		// 0x80004003, Invalid pointer, .NET System.NullReferenceException
		e_pointer = E_POINTER,
		
		// Unexpected failure
		e_unexpected = E_UNEXPECTED,

		// Failed to allocate necessary memory
		e_outofmemory = E_OUTOFMEMORY,

		// One or more arguments are invalid
		e_invalidarg = E_INVALIDARG,

		// Invalid handle
		e_handle = E_HANDLE,

		// Operation aborted
		e_abort = E_ABORT,

		// Unspecified failure
		e_fail = E_FAIL,

		// General access denied error
		e_accessdenied = E_ACCESSDENIED,

		disp_e_badindex = DISP_E_BADINDEX,
		// Dispatch, 0x80020012, .NET System.DivideByZeroException
		disp_e_divbyzero = DISP_E_DIVBYZERO,
		// Dispatch, 0x8002000E, .NET System.Reflection.TargetParameterCountException
		disp_e_badparamcount = DISP_E_BADPARAMCOUNT,

		// Storage, 0x80030003, .NET System.IO.DirectoryNotFoundException
		stg_e_pathnotfound = STG_E_PATHNOTFOUND,

		class_e_noaggregation = CLASS_E_NOAGGREGATION,
		class_e_classnotavailable = CLASS_E_CLASSNOTAVAILABLE,

		// Win 32, 0x80070002, .NET System.IO.FileNotFoundException
		error_file_not_found =
			from_win32_t<windows::exception::file_not_found>::v,
		// Win 32, 0x80070003, .NET System.IO.DirectoryNotFoundException
		error_path_not_found = 
			from_win32_t<windows::exception::path_not_found>::v,
		// Win 32, 0x80070004, .NET System.IO.FileLoadException
		error_too_many_open_files =
			from_win32_t<windows::exception::too_many_open_files>::v,
		// Win 32, 0x80070005, .NET System.UnauthorizedAccessException
		error_access_denied =
			from_win32_t<windows::exception::access_denied>::v,
		// Win 32, 0x8007000B, .NET System.BadImageFormatException
		error_bad_format = 
			from_win32_t<windows::exception::bad_format>::v,
		// Win 32, 0x8007000E, .NET System.OutOfMemoryException
		error_outofmemory =
			from_win32_t<windows::exception::outofmemory>::v,
		// Win 32, 0x80070015, .NET System.FileNotFoundException
		error_not_ready =
			from_win32_t<windows::exception::not_ready>::v,
		// Win 32, 0x80070020, .NET System.IO.FileLoadException
		error_sharing_violation =
			from_win32_t<windows::exception::sharing_violation>::v,
		// Win 32, 0x80070021, .NET System.IO.FileLoadException
		error_lock_violation =
			from_win32_t<windows::exception::lock_violation>::v,
		// Win 32, 0x80070026, .NET System.IO.EndOfStreamException
		error_handle_eof =
			from_win32_t<windows::exception::handle_eof>::v,
		// Win 32, 0x80070035, .NET System.IO.FileNotFoundException
		error_bad_netpath =
			from_win32_t<windows::exception::bad_netpath>::v,
		// Win 32, 0x80070043, .NET System.IO.FileNotFoundException
		error_bad_net_name =
			from_win32_t<windows::exception::bad_net_name>::v,
		// Win 32, 0x80070057, .NET System.ArgumentException
		error_invalid_parameter =
			from_win32_t<windows::exception::invalid_parameter>::v,
		// Win 32, 0x8007006E, .NET System.IO.FileLoadException
		error_open_failed =
			from_win32_t<windows::exception::open_failed>::v,
		// Win 32, 0x8007007B, .NET System.IO.FileNotFoundException
		error_invalid_name =
			from_win32_t<windows::exception::invalid_name>::v,
		// Win 32, 0x8007007E, .NET System.IO.FileNotFoundException
		error_mod_not_found =
			from_win32_t<windows::exception::mod_not_found>::v,
		// Win 32, 0x800700B6, .NET System.BadImageFormatException
		error_invalid_ordinal =
			from_win32_t<windows::exception::invalid_ordinal>::v,
		// Win 32, 0x800700C0, .NET System.BadImageFormatException
		error_exe_marked_invalid =
			from_win32_t<windows::exception::exe_marked_invalid>::v,
		// Win 32, 0x800700C1, .NET System.BadImageFormatException
		error_bad_exe_format =
			from_win32_t<windows::exception::bad_exe_format>::v,
		// Win 32, 0x800700CE, .NET System.IO.PathTooLongException
		error_filename_exced_range =
			from_win32_t<windows::exception::filename_exced_range>::v,
		// Win 32, 0x80070216, .NET System.ArithmeticException
		error_arithmetic_overflow = 
			from_win32_t<windows::exception::arithmetic_overflow>::v,
		// Win 32, 0x800703E6, .NET System.BadImageFormatException
		error_noaccess =
			from_win32_t<windows::exception::noaccess>::v,
		// Win 32, 0x800703E9, .NET System.StackOverflowException
		error_stack_overflow =
			from_win32_t<windows::exception::stack_overflow>::v,
		// Win 32, 0x800703ED, .NET System.IO.FileLoadException
		error_unrecognized_volume =
			from_win32_t<windows::exception::unrecognized_volume>::v,
		// Win 32, 0x800703EE, .NET System.IO.FileLoadException
		error_file_invalid =
			from_win32_t<windows::exception::file_invalid>::v,
		// Win 32, 0x80070459, System.ArgumentOutOfRangeException
		error_no_unicode_translation =
			from_win32_t<windows::exception::no_unicode_translation>::v,
		// Win 32, 0x8007045A, .NET System.IO.FileLoadException
		error_dll_init_failed =
			from_win32_t<windows::exception::dll_init_failed>::v,
		// Win 32, 0x80070482, .NET System.BadImageFormatException
		error_invalid_dll =
			from_win32_t<windows::exception::invalid_dll>::v,
		// Win 32, 0x80070485, .NET System.IO.FileNotFoundException
		error_dll_not_found =
			from_win32_t<windows::exception::dll_not_found>::v,
		// Win 32, 0x80070570, .NET System.BadImageFormatException
		error_file_corrupt =
			from_win32_t<windows::exception::file_corrupt>::v,
		// Win 32, 0x80070571, .NET System.IO.FileLoadException
		error_disk_corrupt =
			from_win32_t<windows::exception::disk_corrupt>::v,
		// Win 32, 0x80070574, .NET System.IO.FileNotFoundException
		error_wrong_target_name =
			from_win32_t<windows::exception::wrong_target_name>::v,

		// Control, 0x800A0006, .NET System.OverflowException
		ctl_e_overflow = CTL_E_OVERFLOW,
		// Control, 0x800A0007, .NET System.OutOfMemoryException
		ctl_e_outofmemory = CTL_E_OUTOFMEMORY,
		// Control, 0x800A0009, .NET System.IndexOutOfRangeException, 
		// subscript out of range
		ctl_e_subscript_out_of_range = 0x800A0009,
		// Control, 0x800A000B, .NET System.DivideByZeroException
		ctl_e_divisionbyzero = CTL_E_DIVISIONBYZERO,
		// Control, 0x800A001C, .NET System.StackOverflowException
		ctl_e_outofstackspace = CTL_E_OUTOFSTACKSPACE,
		// Control, 0x800A0035, .NET System.IO.FileNotFoundException
		ctl_e_filenotfound = CTL_E_FILENOTFOUND,
		// Control, 0x800A0039, .NET System.IO.IOException
		ctl_e_deviceioerror = CTL_E_DEVICEIOERROR,
		// Control, 0x800A003E, .NET System.IO.EndOfStreamException, 
		// input past end of file
		ctl_e_input_past_end_of_file = 0x800A003E,
		// Control, 0x800A0046, .NET System.Security.SecurityException
		ctl_e_permissiondenied = CTL_E_PERMISSIONDENIED,
		// Control, 0x800A004B, .NET System.UnauthorizedAccessException
		ctl_e_pathfileaccesserror = CTL_E_PATHFILEACCESSERROR,
		// Control, 0x800A004C, .NET System.IO.DirectoryNotFoundException
		ctl_e_pathnotfound = CTL_E_PATHNOTFOUND,
		// Control, 0x800A014F, .NET System.UnauthorizedAccessException
		ctl_e_014f = 0x800A014F,
		// Control, 0x800A01A3, .NET System.Security.SecurityException, 
		// permission to use object denied
		ctl_e_permission_to_use_object_denied = 0x800A01A3,
		// Control, 0x800A01B6, .NET System.NotSupportedException,
		// object doesn't support this property or method
		ctl_e_object_does_not_support_this_property_or_method = 0x800A01B6,
		// Control, 0x800A01BD, .NET System.NotSupportedException,
		// object doesn't support this operation.
		ctl_e_object_does_not_support_this_operation = 0x800A01BD,
		// Control, 0x800A01C1, .NET System.ArgumentException
		// argument not optional
		ctl_e_argument_not_optional = 0x800A01C1,
		// Control, 0x800A01C2, .NET System.ArgumentException
		// wrong number of arguments or invalid property
		ctl_e_wrong_number_of_arguments_or_invalid_property = 0x800A01C2,
		// Control, 0x800A01CA: System.NotSupportedException
		// variable uses an automation type not supported in vbscript
		ctl_e_variable_uses_an_automation_type_not_supported_in_vbscript = 
			0x800A01CA,
		// Control, 0x800A01CB, .NET System.NotSupportedException
		ctl_e_01CB = 0x800A01CB,
		// Control, 0x800A01CD, .NET System.MissingMemberException
		ctl_e_01CD = 0x800A01CD,

		// .NET
		// msee_e_appdomainunloaded = 0x80131014,
		// cor_e_appdomainunloade = msee_e_appdomainunloaded,
		// cor_e_application = 0x80131600,
		cor_e_argument = e_invalidarg,
		// cor_e_argumentoutofrange = 0x80131502,
		cor_e_arithmetic = error_arithmetic_overflow,
		// cor_e_arraytypemismatch = 0x80131503,
		cor_e_badimageformat = error_bad_format,
		// cor_e_comemulate_error = ...,
		// cor_e_contextmarshal = 0x80131504,
		// cor_e_core = ...,
		// nte_fail = 0x80131430,
		// corsec_e_crypto = nte_fail,
		cor_e_directorynotfound = error_path_not_found,
		cor_e_dividebyzero = disp_e_divbyzero,
		// cor_e_duplicatewaitobject = 0x80131529,
		cor_e_endofstream = error_handle_eof,
		// cor_e_typeload = 0x80131522,
		// cor_e_exception = 0x80131500,
		// cor_e_executionengine = 0x80131506,
		// cor_e_fieldaccess = 0x80131507,
		cor_e_filenotfound = error_file_not_found,
		// cor_e_format = 0x80131537,
		// cor_e_indexoutofrange = 0x80131508,
		cor_e_invalidcast = e_nointerface,
		// cor_e_invalidcomobject = 0x80131527,
		// cor_e_invalidfiltercriteria = 0x80131601,
		// cor_e_invalidolesvarianttype = 0x80131531,
		// cor_e_invalidoperation = 0x80131509,
		// cor_e_io = 0x80131620,
		// cor_e_memberaccess = 0x8013151A,
		// cor_e_methodaccess = 0x80131510,
		// cor_e_missingfield = 0x80131511,
		// cor_e_missingmanifestresource = 0x80131532,
		// cor_e_missingmember = 0x80131512,
		// cor_e_missingmethod = 0x80131513,
		// cor_e_multicastnotsupported = 0x80131514,
		// cor_e_notfinitenumber = 0x80131528,
		cor_e_notimpl = e_notimpl,
		// cor_e_notsupported = 0x80131515,
		cor_e_nullreference = e_pointer,
		cor_e_outofmemory = e_outofmemory,
		// cor_e_overflow = 0x80131516,
		cor_e_pathtoolong = error_filename_exced_range,
		// cor_e_rank = 0x80131517,
		// cor_e_reflectiontypeload = 0x80131602,
		// cor_e_remoting = 0x8013150B,
		// cor_e_safearraytypemismatch = 0x80131533,
		// cor_e_security = 0x8013150A,
		// cor_e_serialization = 0x8013150C,
		cor_e_stackoverflow = error_stack_overflow,
		// cor_e_synchronizationlock = 0x80131518,
		// cor_e_system = 0x80131501,
		// cor_e_target = ...,
		// cor_e_targetinvocation = 0x80131604,
		cor_e_targetparamcount = disp_e_badparamcount,
		// cor_e_threadaborted = 0x80131530,
		// cor_e_threadinterrupted = 0x80131519,
		// cor_e_threadstate = 0x80131520,
		// cor_e_threadstop = ...,
		// cor_e_typeinitialization = 0x80131534,
		// cor_e_verification = ...,
		// cor_e_weakreference = ...,
		// cor_e_vtablecallsnotsupported = ...,
	};

	hresult(enumeration E): hresult_wrap(internal_type(E)) {}

	explicit hresult(const internal_type &X): hresult_wrap(X) {}
};

}
}
}

#endif
