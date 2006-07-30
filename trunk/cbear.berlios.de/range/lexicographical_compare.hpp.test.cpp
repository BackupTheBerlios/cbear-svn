#include <cbear.berlios.de/range/lexicographical_compare.hpp>

#include <boost/test/minimal.hpp>

#include <boost/range/size.hpp>

namespace Container = cbear_berlios_de::range;

int a[] = { 1, 2, 3 };

int test_main(int, char*[])
{
	BOOST_CHECK(boost::size("\1\2\3")==3);
	BOOST_CHECK(!Container::lexicographical_compare(a, "\1\2\2\2"));
	BOOST_CHECK(Container::lexicographical_compare(a, "\1\2\3\4"));
	BOOST_CHECK(Container::lexicographical_compare(a, "\1\2\4"));
	BOOST_CHECK(!Container::lexicographical_compare(a, "\1\2\3"));
	BOOST_CHECK(!Container::lexicographical_compare("\1\2\3", a));
	BOOST_CHECK(!Container::lexicographical_compare("\1\2\4", a));
	BOOST_CHECK(!Container::lexicographical_compare("\1\2\3\4", a));
	BOOST_CHECK(Container::lexicographical_compare("\1\2\2\2", a));
	return 0;
}
