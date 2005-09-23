/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.sourceforge.net)

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
#ifndef NET_SOURCEFORGE_CBEAR_COM_UUID_HPP_INCLUDED
#define NET_SOURCEFORGE_CBEAR_COM_UUID_HPP_INCLUDED

// ::UUID
#include <basetyps.h>
// ::IUnknown
#include <unknwn.h>

// boost::uint32_t, boost::uint16_t, boost::uint8_t.
#include <boost/cstdint.hpp>

#include <net/sourceforge/cbear/policy/main.hpp>
#include <net/sourceforge/cbear/range/lexicographical_compare.hpp>
#include <net/sourceforge/cbear/base/integer.hpp>

namespace net
{
namespace sourceforge
{
namespace cbear
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
		return range::lexicographical_compare(A.Data4, B.Data4);
	}
};

typedef policy::wrap<uuid, uuid_internal_type, uuid_policy> uuid_wrap;

}

class uuid: public detail::uuid_wrap
{
public:

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
	struct of_type {};

	template<class Interface>
	static uuid of() { return of_type<Interface>::create(); }
};

}
}
}
}

#define NET_SOURCEFORGE_CBEAR_COM_UUID_DECLARE(Interface)\
	namespace net { namespace sourceforge { namespace cbear {\
	namespace com {	template<> struct uuid::of_type< ::Interface>\
	{ static uuid create() { return uuid(::IID_##Interface);	} }; } } } }

NET_SOURCEFORGE_CBEAR_COM_UUID_DECLARE(IUnknown);

#endif
