#include <cbear.berlios.de/move/main.hpp>

namespace Move = cbear_berlios_de::move;

void move_test()
{
	int A;
	Move::t<int &> MA(A);
	MA = Move::copy(5);
}
