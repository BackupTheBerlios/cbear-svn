#include <cbear.berlios.de/windows/com/hresult.hpp>

// BOOST_STATIC_ASSERT
#include <boost/static_assert.hpp>

#include <boost/test/minimal.hpp>

namespace Cbear = cbear_berlios_de;
namespace Com = cbear_berlios_de::windows::com;

template<class T>
void print(T X) 
{ 
	BOOST_STATIC_ASSERT(!Cbear::base::is_signed<T>::value);
}

int test_main(int, char*[])
{
	Com::hresult Result;
	Result = Com::hresult::s_ok;
	BOOST_CHECK(Result==Com::hresult::s_ok);
	BOOST_CHECK(!(Com::hresult::e_fail==Result));
	BOOST_CHECK(!(Result!=Com::hresult::s_ok));
	BOOST_CHECK(Com::hresult::e_fail!=Result);

	BOOST_CHECK(Com::hresult::severity_bit::mask==0x80000000);

	print(boost::uint32_t(0x80000000));
	print(
		boost::uint32_t(0x80000000) & 
		boost::uint32_t(0x80000000));
	print(
		(boost::uint32_t(0x80000000) & 
		boost::uint32_t(0x80000000)) >> 31);

	BOOST_CHECK((
		Com::hresult(Com::hresult::e_fail).internal() & 
		Com::hresult::severity_bit::mask) == 0x80000000);
	BOOST_CHECK((0x80000000 >> 31) == 1);
	BOOST_CHECK(
		static_cast<signed short>(0x8000) >> 15 == 
		static_cast<signed short>(0xFFFF));
	BOOST_CHECK(Com::hresult::severity_bit::first==31);
	BOOST_CHECK(((
			Com::hresult(Com::hresult::e_fail).internal() & 
			Com::hresult::severity_bit::mask) >> 
		31) == 1);
	BOOST_CHECK(((
			Com::hresult(Com::hresult::e_fail).internal() & 
			Com::hresult::severity_bit::mask) >> 
		Com::hresult::severity_bit::first) == 1);

	BOOST_CHECK(
		Com::hresult::severity_bit::get(
			Com::hresult(Com::hresult::e_fail).internal())==1);

	BOOST_CHECK(!Com::hresult(Com::hresult::s_ok).failed());
	BOOST_CHECK(Com::hresult(Com::hresult::e_fail).failed());

	Result.internal() = 0;
	BOOST_CHECK(Result.internal() == 0);

	// Severity

	Result.failed() = true;
	BOOST_CHECK(Result.failed());
	BOOST_CHECK(FAILED(Result.internal()));
	BOOST_CHECK(!SUCCEEDED(Result.internal()));

	Result.failed() = false;
	BOOST_CHECK(!Result.failed());
	BOOST_CHECK(!FAILED(Result.internal()));
	BOOST_CHECK(SUCCEEDED(Result.internal()));

	// Facility

	Com::hresult::facility_type Facility = Com::hresult::facility_type::itf;
	BOOST_CHECK(Facility==Com::hresult::facility_type::itf);
	BOOST_CHECK(Com::hresult::facility_type::itf==Facility);

	BOOST_CHECK(Com::hresult::facility_type().internal()==0);

	Result.facility() = Facility;
	BOOST_CHECK(
		Result.internal() == MAKE_HRESULT(false, Facility.internal(), 0));

	// Code

	Com::hresult::code_type Code(1);
	BOOST_CHECK(Code==Com::hresult::code_type(1));
	BOOST_CHECK(
		Com::hresult::code_type()==Com::hresult::code_type(0));

	Result.code() = Code;
	BOOST_CHECK(
		Result.internal() == MAKE_HRESULT(false, Facility.internal(), 1));

	BOOST_CHECK(Com::hresult::code_type::min==0x0200);

	return 0;
}
