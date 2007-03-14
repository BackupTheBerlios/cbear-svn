#ifndef CBEAR_BERLIOS_DE_STREAM_BINARY_SINGLE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_BINARY_SINGLE_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace stream
{
namespace binary
{

class single_t
{
public:
	float value;
	template<class S>
	void binary_read(S &s)
	{
		s >> this->value;
	}
};

}

}
}

#endif
