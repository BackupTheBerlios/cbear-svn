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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_EXCEPTION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_EXCEPTION_HPP_INCLUDED

#include <cbear.berlios.de/windows/base.hpp>

namespace cbear_berlios_de
{
namespace windows
{

#pragma warning(push)
// 'type' : the copy constructor is inaccessible
#pragma warning(disable: 4671)
// throwing 'identifier' the following types will not be considered at the 
// catch site
#pragma warning(disable: 4673)

// Exception.
class exception: 
	public std::exception, public policy::wrap<windows::exception, dword_t>
{
public:
	typedef policy::wrap<windows::exception, dword_t> wrap_type;
	static void throw_if(internal_type X)
	{
		if(X) throw windows::exception(X);
	}
	static void throw_if_last_error()
	{
		internal_type LastError = ::GetLastError(); 
		if(LastError) throw exception(LastError);
	}
	const char *what() const throw()
	{
		return this->Message.c_str();
	}
private:
	class buffer_policy: private policy::standard_policy<char *>
	{
	public:
		typedef policy::standard_policy<char *> std_policy_type;
		typedef std_policy_type::reference reference;
		typedef std_policy_type::pointer pointer;
		using std_policy_type::construct;
		using std_policy_type::output;
		static void destroy(char * &X)
		{
			if(X) ::LocalFree(X);
		}
	};
	exception(internal_type X): wrap_type(X) 
	{
		policy::std_wrap<char *, buffer_policy> Buffer;
		::FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
			0,
			X,
			0,
			(char *)&Buffer.internal(),
			0,
			NULL);
		std::ostringstream O;
		O << 
			"cbear_berlios_de::windows::exception(0x" << std::hex << std::uppercase <<
			this->internal() << "): " << std::endl << Buffer;
		this->Message = O.str();
	}
	std::string Message;
};

#pragma warning(pop)

}
}

#endif
