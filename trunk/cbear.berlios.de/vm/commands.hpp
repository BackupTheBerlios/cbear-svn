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
#ifndef CBEAR_BERLIOS_DE_VM_COMMANDS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_VM_COMMANDS_HPP_INCLUDED

#include <cbear.berlios.de/vm/process.hpp>

namespace cbear_berlios_de
{
namespace vm
{

// command(stop),
inline void stop(process &P) { P.result = process::stop; }

// command(goto), code
inline void goto_(process &P)
{
	P.code = P.code[1].code;
}

// command(if_goto), condition, code
inline void if_goto(process &P)
{
	if(P.code[1].condition)
	{
		P.code = P.code[2].code;
	}
	else
	{
		P.code += 3;
	}
}

// command(unless_goto), condition, code
inline void unless_goto(process &P)
{
	if(P.code[1].condition)
	{
		P.code += 3;
	}
	else
	{
		P.code = P.code[2].code;
	}
}

// command(push), value
inline void push(process &P)
{
	if(!P.push()) return;
	*P.stack = P.code[1];
	P.code += 2;
}

// command(call), code
inline void call(process &P)
{
	if(!P.push()) return;
	P.stack->code = P.code + 2;
	P.code = P.code[1].code;
}

// command(return)
inline void return_(process &P)
{
	P.code = (P.stack++)->code;
}

}
}

#endif
