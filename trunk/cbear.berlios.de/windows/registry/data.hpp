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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_DATA_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_DATA_HPP_INCLUDED

#include <boost/variant.hpp>
#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/windows/base.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

namespace detail
{

class data_none {};

template<class Char>
class data_variant
{
public:
	typedef boost::variant<
		data_none, dword_t, ulonglong_t, std::basic_string<Char> >
		type;
};

}

// Data.
template<class Char>
class data: public detail::data_variant<Char>::type
{
public:

	// Character.
	typedef Char char_type;

	// Base type.
	typedef typename detail::data_variant<char_type>::type base_type;

	// None type.
	typedef detail::data_none none_type;

	// Id type.
	class id_type: public policy::wrap<id_type, dword_t>
	{
		typedef policy::wrap<id_type, dword_t> wrap_type;
	public:
		enum enumeration_type
		{
			// Binary data in any form. 
			binary = REG_BINARY,
			// A 32-bit number. 
			dword = REG_DWORD,
			// A 32-bit number in little-endian format. 
			dword_little_endian = REG_DWORD_LITTLE_ENDIAN,
			// A 32-bit number in big-endian format. 
			dword_big_endian = REG_DWORD_BIG_ENDIAN,
			// Null-terminated string that contains unexpanded references to 
			// environment variables (for example, "%PATH%"). To expand the 
			// environment variable references, use the ExpandEnvironmentStrings
			// function.
			expand_sz = REG_EXPAND_SZ,
			// Reserved for system use. 
			link = REG_LINK,
			// Array of null-terminated strings, terminated by two null characters. 
			multi_sz = REG_MULTI_SZ,
			// No defined value type.
			none = REG_NONE,
			// A 64-bit number. 
			qword = REG_QWORD,
			// A 64-bit number in little-endian format. 
			qword_little_endian = REG_QWORD_LITTLE_ENDIAN,
			// Null-terminated string. It will be a Unicode or ANSI string, depending on
			// whether you use the Unicode or ANSI functions. 
			sz = REG_SZ,
		};
		id_type(enumeration_type X): wrap_type(X) {}
	};

	class properties_type
	{
	public:

		typedef const byte_t *pointer_type;
		typedef dword_t size_type;

		id_type id;
		pointer_type begin;
		size_type size;

		properties_type(id_type id, pointer_type begin, size_type size):
			id(id), begin(begin), size(size)
		{
		}
	};

	template<class Type>
	class traits;

	template<class Type, id_type::enumeration_type TypeId>
	class traits_helper
	{
	public:
		static const id_type::enumeration_type id = TypeId;
		static properties_type properties(const Type &X)
		{
			return properties_type(
				id, reinterpret_cast<properties_type::pointer_type>(&X), sizeof(Type));
		}
	};

	template<>
	class traits<none_type>: public traits_helper<none_type, id_type::none>
	{
	public:
		static properties_type properties(const Type &X)
		{
			return properties_type(id, 0, 0);
		}
	};

	template<>
	class traits<dword_t>: public traits_helper<dword_t, id_type::dword> {};

	template<>
	class traits<ulonglong_t>: public traits_helper<ulonglong_t, id_type::qword>
	{
	};

	typedef std::basic_string<char_type> string_type;

	template<>
	class traits<string_type>: public traits_helper<string_type, id_type::sz>
	{
	public:
		static properties_type properties(const string_type &X)
		{ 
			return properties_type(
				id, 
				reinterpret_cast<properties_type::pointer_type>(X.c_str()),
				(X.size() + 1) * sizeof(Char));
		}
	};

	template<std::size_t Size>
	class traits<char_type[Size]>: 
		public traits_helper<char_type[Size], id_type::sz>
	{
	public:
		static properties_type properties(const char_type(&X)[Size])
		{ 
			return properties_type(
				id,
				reinterpret_cast<properties_pointer::data_type>(X),
				Size * sizeof(char_type));
		}
	};

	template<>
	class traits<data>
	{
	private:
		class properties_visitor: public boost::static_visitor<properties_type>
		{
		public:
			template<class T>
			properties_type operator()(const T &X) const 
			{ 
				return traits<T>::properties(X); 
			}
		};
	public:
		static properties_type properties(const data &X) 
		{ 		
			boost::apply_visitor(properties_visitor(), *this);
		}
	};

	data() {}

	template<class T>
	data(const T &X): base_type(X) {}

	template<std::size_t Size>
	data(const char_type (&X)[Size]): base_type(string_type(X, Size - 1)) {}
};

}
}
}

#endif
