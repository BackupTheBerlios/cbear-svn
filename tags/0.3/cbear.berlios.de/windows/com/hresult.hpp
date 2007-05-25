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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_HRESULT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_HRESULT_HPP_INCLUDED

// ::HRESULT
#include <windef.h>

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

	hresult() {}

	enum enumeration
	{
		// Operation successful
		s_ok = S_OK,

		s_false = S_FALSE,
		
		// Unexpected failure
		e_unexpected = E_UNEXPECTED,

		// Not implemented
		e_notimpl = E_NOTIMPL,

		// Failed to allocate necessary memory
		e_outofmemory = E_OUTOFMEMORY,

		// One or more arguments are invalid
		e_invalidarg = E_INVALIDARG,

		// No such interface supported
		e_nointerface = E_NOINTERFACE,

		// Invalid pointer
		e_pointer = E_POINTER,

		// Invalid handle
		e_handle = E_HANDLE,

		// Operation aborted
		e_abort = E_ABORT,

		// Unspecified failure
		e_fail = E_FAIL,

		// General access denied error
		e_accessdenied = E_ACCESSDENIED,

		disp_e_badindex = DISP_E_BADINDEX,

		class_e_noaggregation = CLASS_E_NOAGGREGATION,
	};

	hresult(enumeration E): hresult_wrap(internal_type(E)) {}


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
		const facility_reference &operator=(facility_type X) const
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
		const code_reference &operator=(code_type X) const
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

	hresult(bool S, facility_type F, code_type C)
	{
		this->failed() = S;
		this->facility() = F;
		this->code() = C;
	}


	explicit hresult(const internal_type &X): hresult_wrap(X) {}
};

}
}
}

#endif
