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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_MINIDUMP_MAIN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_MINIDUMP_MAIN_HPP_INCLUDED

#include <dbghelp.h>

#include <cbear.berlios.de/windows/hmodule.hpp>

#pragma comment(lib, "dbghelp.lib")

namespace cbear_berlios_de
{
namespace windows
{

namespace detail
{

template<class T>
class minidump
{
protected:
	static std::wstring FileName;
};

template<class T>
std::wstring minidump<T>::FileName;

}

class minidump: private detail::minidump<void>
{
public:
	static void init(hmodule Module)
	{
		FileName = Module.file_name<wchar_t>() + L".dmp";
		::SetUnhandledExceptionFilter(&filter);
	}
private:
	static long_t __stdcall filter(EXCEPTION_POINTERS *ExceptionPointers)
	{
		::MINIDUMP_EXCEPTION_INFORMATION ExInfo;
		ExInfo.ThreadId = ::GetCurrentThreadId();
		ExInfo.ExceptionPointers = ExceptionPointers;
		ExInfo.ClientPointers = 0;
		HANDLE hFile = ::CreateFileW(
			FileName.c_str(),
			GENERIC_WRITE, 
			FILE_SHARE_WRITE, 
			NULL, 
			CREATE_ALWAYS, 
			FILE_ATTRIBUTE_NORMAL, 
			NULL);
		if(hFile==INVALID_HANDLE_VALUE) return EXCEPTION_CONTINUE_SEARCH;
		if(!::MiniDumpWriteDump(
			::GetCurrentProcess(), 
			::GetCurrentProcessId(), 
			hFile, 
			MiniDumpNormal, 
			&ExInfo, 
			0, 
			0)) return EXCEPTION_CONTINUE_SEARCH;
		CloseHandle(hFile);
		return EXCEPTION_CONTINUE_SEARCH;
	}
};

}
}

#endif
