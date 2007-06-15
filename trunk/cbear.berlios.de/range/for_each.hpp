#ifndef CBEAR_BERLIOS_DE_RANGE_FOR_EACH_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_FOR_EACH_HPP_INCLUDED

#include <cbear.berlios.de/range/begin.hpp>
#include <cbear.berlios.de/range/end.hpp>

#include <algorithm>

namespace cbear_berlios_de
{
namespace range
{

template<class R, class P>
void for_each(R const &r, P p)
{
	::std::for_each(begin(r), end(r), p);
}

template<class R, class P>
void for_each(R &r, P p)
{
	::std::for_each(begin(r), end(r), p);
}

}
}

#endif
