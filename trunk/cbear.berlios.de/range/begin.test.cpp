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
#include <cbear.berlios.de/range/begin.hpp>

namespace R = cbear_berlios_de::range;

const char Qwerty[] = "QWERTY";
char QwertyM[15] = "QWERTY";

template<class M>
void T1(const M &X)
{
	//X.get();
}

template<class M>
void T1(M &X)
{
	//X.get();
}

template<class M, std::size_t S>
class array_ref_t
{
public:
	explicit array_ref_t(M *B) throw():
		B(B) 
	{
	}
private:
	M *B;
};

template<std::size_t S, class M>
array_ref_t<const M, S> const_array_ref(const M *B)
{
	return array_ref_t<const M, S>(B);
}

template<std::size_t S, class M>
array_ref_t<M, S> array_ref(M *B)
{
	return array_ref_t<M, S>(B);
}

#define CBEAR_BERLIOS_DE_ARRAY_REF(X) array_ref<sizeof(X)/sizeof(*X)>(X)

int main()
{
	T1(CBEAR_BERLIOS_DE_ARRAY_REF("Qwerty"));
	T1(CBEAR_BERLIOS_DE_ARRAY_REF(Qwerty));
	T1(CBEAR_BERLIOS_DE_ARRAY_REF(QwertyM));
	//T("QWERTY");
	//R::begin(Qwerty);
}
