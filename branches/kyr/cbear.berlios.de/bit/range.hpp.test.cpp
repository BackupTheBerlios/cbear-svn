#include <cbear.berlios.de/bit/range.hpp>

// boost::uint32_t
#include <boost/cstdint.hpp>
// BOOST_STATIC_ASSERT
#include <boost/static_assert.hpp>

#include <boost/test/minimal.hpp>

namespace Cbear = cbear_berlios_de;

template<class T>
void print(T X) 
{ 
	BOOST_STATIC_ASSERT(!Cbear::base::is_signed<T>::value);
}

int test_main(int, char*[])
{
	signed long Result;
	typedef Cbear::bit::one<signed long, 31> BitRange;

	BOOST_CHECK(BitRange::mask==0x80000000);

	print(boost::uint32_t(0x80000000));
	print(
		boost::uint32_t(0x80000000) & 
		boost::uint32_t(0x80000000));
	print(
		(boost::uint32_t(0x80000000) & 
		boost::uint32_t(0x80000000)) >> 31);

	Result = 0x80000000;
	BOOST_CHECK((Result & BitRange::mask) == 0x80000000);
	BOOST_CHECK((0x80000000 >> 31) == 1);
	BOOST_CHECK(
		static_cast<signed short>(0x8000) >> 15 == 
		static_cast<signed short>(0xFFFF));
	BOOST_CHECK(BitRange::first==31);
	BOOST_CHECK(((Result & BitRange::mask) >> 31) == 1);
	BOOST_CHECK(((Result & BitRange::mask) >> BitRange::first) == 1);

	BOOST_CHECK(BitRange::get(Result)==1);

	Result = 0;
	BOOST_CHECK(!BitRange::reference(Result));
	Result = 0x80000000;
	BOOST_CHECK(
		(BitRange::mask & BitRange::unsigned_type(Result)) == 0x80000000);
	BOOST_CHECK(
		(BitRange::mask & BitRange::unsigned_type(Result)) >> BitRange::first);
	BOOST_CHECK(BitRange::get(Result));
	BOOST_CHECK(BitRange::reference(Result));

	Result = 0;
	BitRange::make_reference(Result) = true;
	BOOST_CHECK(bool(BitRange::reference(Result)));
	BOOST_CHECK(Result==0x80000000);

	BitRange::make_reference(Result) = false;
	BOOST_CHECK(!BitRange::reference(Result));
	BOOST_CHECK(Result==0);

	return 0;
}
