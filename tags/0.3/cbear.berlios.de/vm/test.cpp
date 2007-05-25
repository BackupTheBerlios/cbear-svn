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

#include <cbear.berlios.de/vm/commands.hpp>
#include <cbear.berlios.de/range/end.hpp>

namespace Range = cbear_berlios_de::range;
namespace Vm = cbear_berlios_de::vm;

Vm::process::result Main(Vm::process &P)
{
	std::cout << "Hello world!" << std::endl;
	P.code++;
	return Vm::process::continue_;
}

Vm::process::value_type Code[] =
{
	{ Main },
	{ Main },
	{ Main },
	{ Vm::stop },
};

Vm::process::value_type Stack[10];

int main()
{
	Vm::process P(Code, Stack, Range::end(Stack));
	P.run();
}
