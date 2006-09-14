#include <cbear.berlios.de/select/traits.hpp>

int main()
{
	::cbear_berlios_de::select::get<char>("Hello world!", L"Hello world!");
	CBEAR_BERLIOS_DE_SELECT_STRING(char, "Hello world!");
}
