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
	typedef Char value_type;

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
