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
