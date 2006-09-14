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
	template<class Char1>
	basic_lpstr(Char1 *X):
		base_t(X)
	{
	}
	template<class Char1>
	basic_lpstr(const Char1 *X):
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
