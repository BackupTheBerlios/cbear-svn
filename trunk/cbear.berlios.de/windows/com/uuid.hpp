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
#ifndef CBEAR_SOURCEFORGE_NET_WINDOWS_COM_UUID_HPP_INCLUDED
#define CBEAR_SOURCEFORGE_NET_WINDOWS_COM_UUID_HPP_INCLUDED

// ::UUID
#include <basetyps.h>
// ::IUnknown
#include <unknwn.h>

#include <iostream>
#include <iomanip>

// boost::uint32_t, boost::uint16_t, boost::uint8_t.
#include <boost/cstdint.hpp>

#include <cbear.berlios.de/base/integer.hpp>
#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/range/lexicographic/less.hpp>
#include <cbear.berlios.de/base/integer.hpp>
#include <cbear.berlios.de/windows/select.hpp>
#include <cbear.berlios.de/windows/com/traits.hpp>

template<class Char>
std::basic_ostream<Char> &operator<<(
	std::basic_ostream<Char> &O, const ::UUID &X)
{
	// For example: "9051E94D-6A0C-44b8-B163-716CD2117C58"
	// Format:      "11111111-2222-3333-4444-444444444444"
	namespace Windows = cbear_berlios_de::windows;
	namespace Range = cbear_berlios_de::range;
	typedef Char char_type;
	typedef Range::iterator_range<const boost::uint8_t *> range_type;
	static const char_type Zero = Windows::select<char_type>('0', L'0');
	static const char_type Minus = Windows::select<char_type>('-', L'-');
	O << ::cbear_berlios_de::base::hex(X.Data1, 8) <<
		Minus <<
		::cbear_berlios_de::base::hex(X.Data2, 4) <<
		Minus <<
		::cbear_berlios_de::base::hex(X.Data3, 4) <<
		Minus;
	for(range_type R(X.Data4, X.Data4 + 2); !R.empty(); R.begin()++)
	{
		O << ::cbear_berlios_de::base::hex(R[0], 2);
	}
	O << Minus;
	for(range_type R(X.Data4 + 2, X.Data4 + 8); !R.empty(); R.begin()++)
	{
		O << ::cbear_berlios_de::base::hex(R[0], 2);
	}
	return O;
}

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class uuid;

namespace detail
{

typedef ::UUID uuid_internal_type;

struct uuid_policy: policy::standard_policy<uuid_internal_type>
{
	static bool less(const uuid_internal_type &A, const uuid_internal_type &B)
	{
		if(A.Data1!=B.Data1) return A.Data1<B.Data1;
		if(A.Data2!=B.Data2) return A.Data2<B.Data2;
		if(A.Data3!=B.Data3) return A.Data3<B.Data3;
		return range::lexicographic::less(A.Data4, B.Data4);
	}
};

typedef policy::wrap<uuid, uuid_internal_type, uuid_policy> uuid_wrap;

}

class uuid: public detail::uuid_wrap
{
public:

	static const vartype_t vt = ::VT_EMPTY;

	typedef uuid move_type;

	uuid() {}

	typedef boost::uint32_t data1_type;
	typedef boost::uint16_t data2_type;
	typedef boost::uint16_t data3_type;
	typedef boost::uint8_t data4_value_type;
	static const int data4_size = 8;
	typedef data4_value_type data4_type[data4_size];

	typedef detail::uuid_wrap::internal_type internal_type;

	uuid(
		const data1_type &Data1,
		const data2_type &Data2, 
		const data3_type &Data3,
		const data4_value_type &Data40,
		const data4_value_type &Data41,
		const data4_value_type &Data42,
		const data4_value_type &Data43,
		const data4_value_type &Data44,
		const data4_value_type &Data45,
		const data4_value_type &Data46,
		const data4_value_type &Data47)
	{
		internal_type &tmp = this->internal();
		tmp.Data1 = Data1;
		tmp.Data2 = Data2;
		tmp.Data3 = Data3;
		tmp.Data4[0] = Data40;
		tmp.Data4[1] = Data41;
		tmp.Data4[2] = Data42;
		tmp.Data4[3] = Data43;
		tmp.Data4[4] = Data44;
		tmp.Data4[5] = Data45;
		tmp.Data4[6] = Data46;
		tmp.Data4[7] = Data47;
	}

	explicit uuid(const internal_type &Value): detail::uuid_wrap(Value) {}

	template<class Interface>
	struct of_type 
	{
		static const uuid &create() 
		{ 
			return uuid::wrap_ref(__uuidof(Interface));
		}
	};

	template<class Interface>
	static const uuid &of() { return of_type<Interface>::create(); }

	typedef void extra_result;
};

}
}
}

#define CBEAR_BERLIOS_DE_WINDOWS_COM_UUID_DECLARE(Interface)\
	namespace cbear_berlios_de { namespace windows { namespace com { \
	template<> struct uuid::of_type< ::Interface>	\
	{ static const uuid &create() { \
	return uuid::wrap_ref(::IID_##Interface); } }; } } }

CBEAR_BERLIOS_DE_WINDOWS_COM_UUID_DECLARE(IUnknown);
CBEAR_BERLIOS_DE_WINDOWS_COM_UUID_DECLARE(IDispatch);

#endif
