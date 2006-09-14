#ifndef CBEAR_BERLIOS_DE_RANGE_TRANSFORM_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_TRANSFORM_HPP_INCLUDED

// std::transform
#include <algorithm>

#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>

namespace cbear_berlios_de
{
namespace range
{

/** @brief Assigns through every iterator I in the range
	[result, result + size(R)) a new value equal to op(at(R, I - result)).

    @result result + size(R).

    @sa std::transform.
*/
template<class InputRange, class OutputIterator, class UnaryOperation>
OutputIterator
transform(InputRange &R, OutputIterator result, UnaryOperation op)
{
	return std::transform(range::begin(R), range::end(R), result, op);
}

}
}

#endif
