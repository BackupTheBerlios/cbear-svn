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

#include <sstream>

#include <boost/noncopyable.hpp>

#include <cbear.berlios.de/base/exception.hpp>
#include <cbear.berlios.de/policy/main.hpp>
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
	public std::exception,
	public base::exception, 
	public base::wexception
{
public:

	const char *what() const { return "::cbear_berlios_de::windows::exception"; }

	static void throw_if(dword_t X)
	{
		if(X) throw windows::exception(X);
	}

	class scope_last_error: boost::noncopyable
	{
	public:
		scope_last_error() { ::SetLastError(0); }
		~scope_last_error() 
		{
			dword_t LastError = ::GetLastError(); 
			if(LastError) throw exception(LastError);
		}
	};

	enum enum_t
	{
		no_more_items = ERROR_NO_MORE_ITEMS,
		insufficient_buffer = ERROR_INSUFFICIENT_BUFFER,
	};

	void print(std::ostream &Stream) const
	{
		this->detail_print(Stream);
	}

	void print(std::wostream &Stream) const
	{
		this->detail_print(Stream);
	}

	dword_t result() const throw() { return this->Result; }

private:

	template<class Char>
	class buffer_policy: private policy::standard_policy<Char *>
	{
	public:
		typedef policy::standard_policy<Char *> std_policy_type;
		typedef typename std_policy_type::reference reference;
		typedef typename std_policy_type::pointer pointer;
		using std_policy_type::construct;
		using std_policy_type::output;
		static void destroy(Char * &X)
		{
			if(X) ::LocalFree(X);
		}
	};

	template<class Char>
	void detail_print(std::basic_ostream<Char> &O) const
	{
		policy::std_wrap<Char *, buffer_policy<Char> > Buffer;
		select<Char>(::FormatMessageA, ::FormatMessageW)(
			FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
			0,
			this->result(),
			0,
			(Char *)&Buffer.internal(),
			0,
			0);
		O << 
			select<Char>(
				"cbear_berlios_de::windows::exception(0x", 
				L"cbear_berlios_de::windows::exception(0x") << 
			base::hex(this->result()) << 
			select<Char>("): ", L"): ") << 
			std::endl << 
			Buffer.internal();
	}

	dword_t Result;

	exception(dword_t X): Result(X) {}
};

template<class Stream>
Stream &operator<<(Stream &S, const exception &E)
{
	E.print(S);
	return S;
}

#pragma warning(pop)

}
}

#endif
