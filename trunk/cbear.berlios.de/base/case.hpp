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
#ifndef CBEAR_BERLIOS_DE_BASE_CASE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_CASE_HPP_INCLUDED

#include <cbear.berlios.de/base/character.hpp>
#include <cbear.berlios.de/select/traits.hpp>

namespace cbear_berlios_de
{
namespace base
{

template<class Char>
Char to_lower(Char c)
{
	static const Char A = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'A');
	static const Char Z = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'Z');
	static const Char a = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'a');
	static const Char z = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, 'z');
	static const Char dif = A - a;
	return a <= c && c <= z ? c + dif: c;
}

template<class Char>
bool latin_case_insensetive_equal(Char c1, Char c2)
{
	return to_lower(c1) == to_lower(c2);
}

}
}

#endif
