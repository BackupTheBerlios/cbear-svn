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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_HANDLE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_HANDLE_HPP_INCLUDED

#include <windows.h>

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/overlapped.hpp>
#include <cbear.berlios.de/windows/exception.hpp>
#include <cbear.berlios.de/windows/select.hpp>
#include <cbear.berlios.de/windows/lpstr.hpp>
#include <cbear.berlios.de/range/iterator_range.hpp>

namespace cbear_berlios_de
{
namespace windows
{

typedef range::iterator_range<byte *> byte_range_t;

template<class Char>
class win32_find_data: 
	public select_traits<Char, WIN32_FIND_DATAA, WIN32_FIND_DATAW>::type
{
};

// Handle to an object.
class handle: public policy::wrap<handle, ::HANDLE>
{
public:
	typedef policy::wrap<handle, ::HANDLE> wrap_type;
	typedef wrap_type::internal_type internal_type;

	handle() {}
	explicit handle(internal_type X): wrap_type(X) {}

	dword_t DeviceIoControl(
		dword_t IoControlCode,
		const byte_range_t &In,
		const byte_range_t &Out,
		overlapped_t *Overlapped) const
	{
		dword_t BytesReturned;
		{
			exception::scope_last_error ScopeLastError;
			::DeviceIoControl(
				this->internal(),
				IoControlCode,
				In.begin(),
				dword_t(In.size()),
				Out.begin(),
				dword_t(Out.size()),
				&BytesReturned, 
				Overlapped);
		}
		return BytesReturned;
	}
};

template<class Char>
static handle FindFirstFile(
	const basic_lpstr<const Char> &fileName, 
	win32_find_data<Char> &findFileData)
{
	handle result;
	{
		exception::scope_last_error ScopeLastError;
		result.internal() = 
			select<Char>(::FindFirstFileA, ::FindFirstFileW)(
				fileName.internal(),
				&findFileData);
	}
	return result;
}

typedef FINDEX_SEARCH_OPS findex_search_ops;

/*
template<class Char>
static handle FindFirstFileEx(
	const basic_lpstr<const Char> &fileName, 
	win32_find_data<Char> &findFileData,
	findex_search_ops searchOp)
{
	handle result;
	{
		exception::scope_last_error ScopeLastError;
		result.internal() = 
			select<Char>(::FindFirstFileExA, ::FindFirstFileExW)(
				fileName.internal(),
				::FindExInfoStandard,
				&findFileData,
				searchOp,
				0,
				0);
	}
	return result;
}
*/

}
}

#endif
