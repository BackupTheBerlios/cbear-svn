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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COUT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COUT_HPP_INCLUDED

#include <cbear.berlios.de/range/size.hpp>
#include <cbear.berlios.de/stream/virtual_write.hpp>
#include <cbear.berlios.de/windows/exception.hpp>
#include <cbear.berlios.de/windows/select.hpp>
#include <cbear.berlios.de/windows/base.hpp>

namespace cbear_berlios_de
{
namespace windows
{

template<class Char>
class basic_cout
{
public:

	basic_cout()
	{
		exception::scope_last_error ScopeLastError;
		this->h = ::GetStdHandle(STD_OUTPUT_HANDLE);
	}

	typedef Char char_type;

	template<class C>
	void push_back_range(const C &c)
	{
		// Because VC 7.1 is a bad compiler.
		//BOOST_STATIC_ASSERT((boost::is_same<
		//	typename range::const_traits<C>::iterator, const Char *>::value));
		exception::scope_last_error ScopeLastError;
		dword_t returned;
		CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::WriteConsole)(
			this->h,
			range::begin(c), 
			(dword_t)range::size(c),
			&returned, 
			0);
	}

	template<class T>
	basic_cout &operator<<(const T &t)
	{
		stream::write(*this, t);
		return *this;
	}

private:
	::HANDLE h;
};

typedef basic_cout<char> cout;
typedef basic_cout<wchar_t> wcout;

}
}

#endif
