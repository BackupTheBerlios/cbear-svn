#ifndef CBEAR_BERLIOS_DE_STREAM_WRITE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_WRITE_HPP_INCLUDED

#include <cbear.berlios.de/stream/traits.hpp>

namespace cbear_berlios_de
{
namespace stream
{

template<class S, class T>
void write(S &s, T const &t)
{
	traits<S, T>::write(s, t);
}

}
}

#endif
