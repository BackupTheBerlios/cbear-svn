#ifndef CBEAR_BERLIOS_DE_STREAM_BINARY_DOUBLE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_BINARY_DOUBLE_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace stream
{
namespace binary
{

class double_t
{
public:
	double value;
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
