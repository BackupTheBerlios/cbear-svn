#include <cbear.berlios.de/array/ref.hpp>

template< ::std::size_t Size, class T>
void M(const T &)
{
	BOOST_STATIC_ASSERT(T::const_size == Size);
}

int main()
{
	const char HelloWorld[] = "Hello world!";
	char HelloWorldM[] = "Hello world!";

	M<12>(CBEAR_BERLIOS_DE_ARRAY_REF("Hello world!"));
	M<12>(CBEAR_BERLIOS_DE_ARRAY_REF(HelloWorld));
	M<12>(CBEAR_BERLIOS_DE_ARRAY_REF(HelloWorldM));

	const wchar_t HelloWorldW[] = L"Hello world!";
	wchar_t HelloWorldWM[] = L"Hello world!";
	M<12>(CBEAR_BERLIOS_DE_ARRAY_REF(L"Hello world!"));
	M<12>(CBEAR_BERLIOS_DE_ARRAY_REF(HelloWorldW));
	M<12>(CBEAR_BERLIOS_DE_ARRAY_REF(HelloWorldWM));

	const unsigned char HelloWorldU[] = "Hello world!";
	signed char HelloWorldSM[] = "Hello world!";
	M<13>(CBEAR_BERLIOS_DE_ARRAY_REF(HelloWorldU));
	M<13>(CBEAR_BERLIOS_DE_ARRAY_REF(HelloWorldSM));
}
