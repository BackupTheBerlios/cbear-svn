#ifndef CBEAR_BERLIOS_DE_RANGE_COPY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_COPY_HPP_INCLUDED

#include <algorithm>

#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class Container, class OutputIterator>
OutputIterator copy(const Container &X, OutputIterator O) 
{ 
	return std::copy(range::begin(X), range::end(X), O);
}

}
}

#endif
