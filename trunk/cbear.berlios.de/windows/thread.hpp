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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_THREAD_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_THREAD_HPP_INCLUDED

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/security_attributes.hpp>
#include <cbear.berlios.de/windows/exception.hpp>
#include <cbear.berlios.de/windows/optional_ref.hpp>

namespace cbear_berlios_de
{
namespace windows
{

class thread
{
public:

	thread(): 
		H() 
	{
	}

	~thread()
	{
		this->close();
	}

	void close()
	{
		if(!this->H)
		{
			return;
		}
		{
			exception::scope_last_error S;
			::WaitForSingleObject(this->H, INFINITE);
		}
		{
			exception::scope_last_error S;
			::CloseHandle(this->H);
		}
		this->H = internal_t();
	}

	template<class T>
	dword_t create(
		const security_attributes &Attributes,
		size_t StackSize,
		T &P,
		dword_t Flags)
	{
		this->close();
		exception::scope_last_error S;
		dword_t Id;
		this->H = ::CreateThread(
			Attributes.get(), StackSize, traits<T>::func, &P, Flags, &Id);
		return Id;
	}

private:
	typedef ::HANDLE internal_t;
	internal_t H;

	template<class T>
	class traits
	{
	public:
		static DWORD WINAPI func(LPVOID lpParameter)
		{
			(*reinterpret_cast<T *>(lpParameter))();
			return 0;
		}
	};
};

}
}

#endif
