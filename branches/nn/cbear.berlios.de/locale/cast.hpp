#ifndef CBEAR_BERLIOS_DE_LOCALE_CAST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_LOCALE_CAST_HPP_INCLUDED

#include <locale>

#include <cbear.berlios.de/range/value_type.hpp>
#include <cbear.berlios.de/range/transform.hpp>

namespace cbear_berlios_de
{
namespace locale
{

namespace detail
{

/// Casting.
template<class To, class From>
struct cast
{
	/// Main function.
	static To run(const From &Source)
	{
		typedef typename range::value_type<From>::type from_char_type;
		typedef typename range::value_type<To>::type to_char_type;
		To Result;
		Result.resize(range::size(Source));
		range::transform(
			Source, 
			Result.begin(),
			cast<to_char_type, from_char_type>::run);
		return Result;
	}
};

/// Returns std::ctype<Char>.
template<class Char>
const std::ctype<Char> &get_ctype()
{
	return std::use_facet<std::ctype<Char> >(std::locale());
}

/// Converts from wchar_t to char.
template<>
struct cast<char, wchar_t>
{
	/// Main function.
	static char run(wchar_t C) { return get_ctype<wchar_t>().narrow(C, '@'); }
};

/// Converts from char to wchar_t.
template<>
struct cast<wchar_t, char>
{
	/// Main function.
	static wchar_t run(char C) { return get_ctype<char>().widen(C); }
};

/*
/// Converts to std::basic_string<Char>.
template<class Char, class From>
struct cast<std::basic_string<Char>, From>
{
	typedef std::basic_string<Char> result_type; ///< A result type.
	/// Main function.
	static result_type run(const From &Source)
	{
		typedef typename range::value_type<From>::type source_char_type;
		result_type Result;
		range::transform(
			Source, 
			std::back_inserter(Result), 
			cast<Char, source_char_type>::run);
		return Result;
	}
};
*/

}

/// Casting.
template<class To, class From>
To cast(const From &X) { return detail::cast<To, From>::run(X); }

}
}

#endif
