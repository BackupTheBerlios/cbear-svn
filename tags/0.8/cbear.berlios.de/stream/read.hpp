#ifndef CBEAR_BERLIOS_DE_STREAM_READ_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_READ_HPP_INCLUDED

#include <cbear.berlios.de/stream/traits.hpp>

namespace cbear_berlios_de
{
namespace stream
{
template<class S, class T>
void read(S &s, T &t)
{
	traits<S, T>::read(s, t);
}

}
}

#endif
