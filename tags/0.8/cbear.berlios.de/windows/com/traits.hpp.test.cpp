#include <cbear.berlios.de/windows/com/traits.hpp>

#include <boost/test/minimal.hpp>

// BOOST_STATIC_ASSERT
#include <boost/static_assert.hpp>
// boost::is_same
#include <boost/type_traits.hpp>

namespace Cbear = cbear_berlios_de;
namespace Com = cbear_berlios_de::windows::com;

class My
{
public:

	typedef Cbear::policy::standard_policy<int> internal_policy;

	const int &internal() const { return this->I; }
	int &internal() { return this->I; }
	
private:
	int I;
};

BOOST_STATIC_ASSERT((
	boost::is_same<Com::traits<My>::internal_policy::type, int>::value));

int test_main(int, char*[])
{
	return 0;
}
