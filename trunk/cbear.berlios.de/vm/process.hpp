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
#ifndef CBEAR_BERLIOS_DE_VM_PROCESS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_VM_PROCESS_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace vm
{

class process
{
public:

	typedef void command(process &);

	union value_type
	{
		bool condition;
		std::ptrdiff_t signed_int;
		std::size_t unsigned_int;
		command *command;
		value_type *code;
	};

	typedef value_type *iterator;

	iterator code;
	iterator stack;
	iterator stack_end;

	enum result_type
	{
		continue_,
		stop,
		stack_overflow,
	};

	bool push()
	{
		--P.stack;
		if(P.stack <= P.stack_end)
		{
			P.state = process::stack_overflow;
			return false;
		}
		return true;
	}

	result_type result;

	process(iterator code, iterator stack, iterator stack_end):
		code(code), stack(stack), stack_end(stack_end)
	{
	}

	void run()
	{ 
		this->result = continue_;
		do
		{
			(*this->code.command)(*this);
		} while(result == continue_);
	}
};

}
}

#endif
