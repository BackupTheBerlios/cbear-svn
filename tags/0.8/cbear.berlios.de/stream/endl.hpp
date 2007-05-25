#ifndef CBEAR_BERLIOS_DE_STREAM_ENDL_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_ENDL_HPP_INCLUDED

#include <cbear.berlios.de/select/traits.hpp>

namespace cbear_berlios_de
{
namespace stream
{

class endl
{
public:
	template<class S>
	void write(S &s) const
	{
		s << CBEAR_BERLIOS_DE_SELECT_CHAR(typename S::value_type, '\n');
	}
};

}
}

#endif
