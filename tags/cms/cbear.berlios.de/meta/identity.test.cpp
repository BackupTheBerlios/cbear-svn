#include <cbear.berlios.de/meta/identity.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace M = cbear_berlios_de::meta;

int main()
{
	BOOST_STATIC_ASSERT((boost::is_same<M::identity<char>::type, char>::value));
}
