#ifndef CBEAR_BERLIOS_DE_WINDOWS_MINIDUMP_MAIN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_MINIDUMP_MAIN_HPP_INCLUDED

// _X86_
#include <windows.h>
// CONST
#include <windef.h>
// PSTR
#include <winnt.h>
#include <dbghelp.h>

#include <string>

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
