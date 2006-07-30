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
