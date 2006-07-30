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
