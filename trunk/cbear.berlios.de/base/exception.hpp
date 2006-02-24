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
#ifndef CBEAR_BERLIOS_DE_BASE_EXCEPTION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_EXCEPTION_HPP_INCLUDED

// std::exception
#include <exception>

namespace cbear_berlios_de
{
namespace base
{

template<class Char>
class basic_exception
{
public:
	virtual void print(std::basic_ostream<Char> &O) const = 0;
};

typedef basic_exception<char> exception;
typedef basic_exception<wchar_t> wexception;

template<class Stream, class Char>
Stream &operator<<(Stream &S, const basic_exception<Char> &E)
{
	E.print(S);
	return S;
}

}
}

#endif
