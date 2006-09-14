#include <cbear.berlios.de/cbear/policy/main.hpp>

#include <boost/test/minimal.hpp>

// BOOST_STATIC_ASSERT
#include <boost/static_assert.hpp>
// boost::is_same
#include <boost/type_traits.hpp>

namespace Wrap = cbear_berlios_de::policy;

class My;

typedef Wrap::wrap<My, int> MyWrap;

class My: public MyWrap
{
public:
	My() {}
	explicit My(int X): MyWrap(X) {}
};

BOOST_STATIC_ASSERT((boost::is_same<My::internal_type, int>::value));

int test_main(int, char*[])
{
	My A;
	BOOST_ASSERT(A.internal()==0);
	A = My(7);
	BOOST_ASSERT(A.internal()==7);
	My B = A;

	int AI;
	My::internal_policy::construct(AI);
	BOOST_CHECK(AI==0);
	My::internal_policy::construct_copy(AI, 6);
	BOOST_CHECK(AI==6);
	My::internal_policy::assign(AI, 7);
	BOOST_CHECK(AI==7);
	My::internal_policy::destroy(AI);
	BOOST_CHECK(AI==7);
	return 0;
}
