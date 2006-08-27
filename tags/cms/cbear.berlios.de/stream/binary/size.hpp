#ifndef CBEAR_BERLIOS_DE_STREAM_BINARY_SIZE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_BINARY_SIZE_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator_range.hpp>
#include <cbear.berlios.de/stream/binary/write.hpp>

namespace cbear_berlios_de
{
namespace stream
{
namespace binary
{

class size
{
public:

	typedef range::iterator_range<const char *> const_range_type;
	typedef range::iterator_range<char *> range_type;

	size(): V(0) {}

	void push_back_range(const const_range_type &N)
	{
		this->V += N.size();
	}	

	void pop_front_range(const range_type &N)
	{
		this->V += N.size();
	}

	template<class T>
	size &operator<<(const T &t)
	{
		binary::write(*this, t);
		return *this;
	}

	std::size_t operator()() const { return this->V; }

private:
	std::size_t V;
};

}
}
}

#endif