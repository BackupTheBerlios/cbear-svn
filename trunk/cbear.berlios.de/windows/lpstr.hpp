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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_LPSTR_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_LPSTR_HPP_INCLUDED

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/policy/main.hpp>

namespace cbear_berlios_de
{
namespace windows
{

// Pointer to a null-terminated string
template<class Char>
class basic_lpstr: public base::initialized<Char *>
{
public:
	typedef base::initialized<Char *> base_t;
	typedef Char *internal_type;
	basic_lpstr() 
	{
	}
	template<class T>
	basic_lpstr(const T &X): 
		base_t(X.c_str()) 
	{
	}
	basic_lpstr(internal_type X): 
		base_t(X) 
	{
	}
	static basic_lpstr &cpp_in_out(Char * &X)
	{
		return cast::traits<basic_lpstr &>::reinterpret(X);
	}
};

// Pointer to a null-terminated string of 8-bit Windows (ANSI) characters.
typedef basic_lpstr<char_t> lpstr_t;

// Pointer to a constant null-terminated string of 8-bit Windows (ANSI) 
// characters.
typedef basic_lpstr<const char_t> lpcstr_t;

// Pointer to a null-terminated string of 16-bit Unicode characters.
typedef basic_lpstr<wchar_t_> lpwstr_t;

// Pointer to a constant null-terminated string of 16-bit Unicode characters.
typedef basic_lpstr<const wchar_t_> lpcwstr_t;

template<class Char>
basic_lpstr<Char> make_lpstr(Char *P) 
{ 
	return basic_lpstr<Char>(P); 
}

typedef OLECHAR olechar_t;

typedef basic_lpstr<olechar_t> lpolestr_t;
typedef basic_lpstr<const olechar_t> lpcolestr_t;

}
}

#endif
