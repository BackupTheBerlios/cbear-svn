/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
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
