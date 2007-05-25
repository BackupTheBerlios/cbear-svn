#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/array/ref.hpp>

namespace R = cbear_berlios_de::range;

int main()
{
	const char Qwerty[] = "Qwerty";
	char QwertyM[] = "Qwerty";
	R::begin(CBEAR_BERLIOS_DE_ARRAY_REF("Qwerty"));
	R::begin(CBEAR_BERLIOS_DE_ARRAY_REF(Qwerty));
	R::begin(CBEAR_BERLIOS_DE_ARRAY_REF(QwertyM));

}
