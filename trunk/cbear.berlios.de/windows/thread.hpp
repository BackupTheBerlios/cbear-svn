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
			scope_last_error S();
			::WaitForSingleObject(this->H, INFINITE);
		}
		{
			scope_last_error S();
			::CloseHanle(this->H);
		}
		this->H = internal_t();
	}

	template<class T>
	dword_t create(
		const security_attributtes_t &Attributtes, 
		size_t StackSize,
		T &P,
		dword_t Flag,)
	{
		this->close();
		dword_t Id;	
		::CreateThread(A.get(), StackSize, traits<T>::func, &P, &Id);
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
		}
	};
};

}
}

#endif
