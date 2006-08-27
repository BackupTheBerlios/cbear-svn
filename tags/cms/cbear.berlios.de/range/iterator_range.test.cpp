#include <cbear.berlios.de/range/iterator_range.hpp>
#include <cbear.berlios.de/array/ref.hpp>

namespace R = cbear_berlios_de::range;

int main()
{
	R::iterator_range<const char *> A(CBEAR_BERLIOS_DE_ARRAY_REF("QWERTY"));
	A.begin();
}
