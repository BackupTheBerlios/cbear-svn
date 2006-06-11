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

#include <boost/noncopyable.hpp>

#include <cbear.berlios.de/stream/virtual_write.hpp>
#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/select.hpp>

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
	public stream::virtual_write, 
	public stream::wvirtual_write
{
public:

	const char *what() const throw() 
	{ 
		return "::cbear_berlios_de::windows::exception"; 
	}

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

	template<class S>
	void write(S &O) const
	{
		typedef typename S::value_type char_type;
		policy::std_wrap<char_type *, buffer_policy<char_type> > Buffer;
		const dword_t Size = CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(
			char_type, ::FormatMessage)(
				FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
				0,
				this->result(),
				0,
				(char_type *)&Buffer.internal(),
				0,
				0);
		O <<
			CBEAR_BERLIOS_DE_BASE_SELECT(
				char_type, "cbear_berlios_de::windows::exception(0x") <<
			base::hex(this->result()) << 
			CBEAR_BERLIOS_DE_BASE_SELECT(char_type, "):\n") << 
			range::make_iterator_range(Buffer.internal(), Size);
	}

	dword_t result() const throw() { return this->Result; }

	explicit exception(dword_t X): Result(X) {}

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

	void detail_write(::cbear_berlios_de::stream::virtual_write::stream &S) const
	{
		this->write(S);
	}

	void detail_write(::cbear_berlios_de::stream::wvirtual_write::stream &S) const
	{
		this->write(S);
	}

	dword_t Result;
};

#pragma warning(pop)

}
}

#endif
