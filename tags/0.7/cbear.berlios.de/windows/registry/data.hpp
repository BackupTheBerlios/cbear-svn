#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_DATA_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_DATA_HPP_INCLUDED

#include <boost/variant.hpp>

#include <cbear.berlios.de/windows/winnt.h>
#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/base/string.hpp>

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
		data_none, dword_t, ulonglong_t, base::basic_string<Char> >
		type;
};

}

class data_id_type: public base::initialized<dword_t>
{
	typedef base::initialized<dword_t> wrap_type;
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
	data_id_type() {}
	data_id_type(enumeration_type X): wrap_type(X) {}

	bool operator==(const data_id_type &B) const
	{
		return this->get() == B.get();
	}

	bool operator!=(const data_id_type &B) const
	{
		return this->get() != B.get();
	}
};

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
	typedef data_id_type id_type;

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

	template<class Type, class = void>
	class traits;

	template<class Type, id_type::enumeration_type TypeId>
	class traits_helper
	{
	public:
		static const id_type::enumeration_type id = TypeId;
		static properties_type properties(const Type &X)
		{
			return properties_type(
				id, reinterpret_cast<typename properties_type::pointer_type>(&X), sizeof(Type));
		}
	};

	template<class D>
	class traits<none_type, D>: public traits_helper<none_type, id_type::none>
	{
	public:
		static properties_type properties(const none_type &)
		{
			return properties_type(id_type::none, 0, 0);
		}
	};

	template<class D>
	class traits<dword_t, D>: public traits_helper<dword_t, id_type::dword> {};

	template<class D>
	class traits<ulonglong_t, D>: public traits_helper<ulonglong_t, id_type::qword>
	{
	};

	typedef base::basic_string<char_type> string_type;

	template<class D>
	class traits<string_type, D>: public traits_helper<string_type, id_type::sz>
	{
	public:
		static properties_type properties(const string_type &X)
		{ 
			typedef typename properties_type::size_type size_type;
			return properties_type(
				id_type::sz, 
				reinterpret_cast<typename properties_type::pointer_type>(X.c_str()),
				size_type((X.size() + 1) * sizeof(Char)));
		}
	};

	template<std::size_t Size, class D>
	class traits<char_type[Size], D>: 
		public traits_helper<char_type[Size], id_type::sz>
	{
	public:
		static properties_type properties(const char_type(&X)[Size])
		{ 
			return properties_type(
				id_type::sz,
				reinterpret_cast<typename properties_type::data_type>(X),
				Size * sizeof(char_type));
		}
	};

	template<class D>
	class traits<data, D>
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
			return boost::apply_visitor(properties_visitor(), X);
		}
	};

	template<class T>
	static properties_type properties(const T &X)
	{
		return traits<T>::properties(X);
	}

	data &operator=(const data &X)
	{
		base_type::operator=(static_cast<const base_type &>(X));
		return *this;
	}

	data() {}

	data(const data &X): base_type(static_cast<const base_type &>(X)) {}

	template<class T>
	data(const T &X): base_type(X) {}

	template<std::size_t Size>
	data(const char_type (&X)[Size]): base_type(string_type(X, Size - 1)) {}
};

}
}
}

#endif
