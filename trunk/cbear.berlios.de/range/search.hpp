#ifndef CBEAR_BERLIOS_DE_RANGE_SEARCH_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_SEARCH_HPP_INCLUDED

#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class R1, class R2>
typename traits<R1>::iterator search(R1 &r1, R2 const &r2)
{
	return ::std::search(begin(r1), end(r1), begin(r2), end(r2));
}

template<class R1, class R2>
typename traits<R1 const>::iterator search(R1 const &r1, R2 const &r2)
{
	return ::std::search(begin(r1), end(r1), begin(r2), end(r2));
}

}
}

#endif
