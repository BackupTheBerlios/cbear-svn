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
