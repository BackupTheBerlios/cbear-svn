#ifndef CBEAR_BERLIOS_DE_WINDOWS_DYNAMIC_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_DYNAMIC_HPP_INCLUDED

#include <vector>

namespace cbear_berlios_de
{
namespace windows
{

template<class Internal> 
class dynamic: private std::vector<char>
{
public:

	typedef std::vector<char> buffer;

	using buffer::size;

	typedef Internal internal_type;

	static const std::size_t min_size = sizeof(Internal);

	dynamic(): buffer(min_size) {}

	void resize(std::size_t Size) 
	{
		BOOST_ASSERT(Size >= min_size);
		this->buffer::resize(Size);
	}

	byte *begin() 
	{ 
		return this->buffer::empty() ? 
			0: (byte *)&*this->buffer::begin(); 
	}

	const byte *begin() const 
	{ 
		return this->buffer::empty() ? 0: &*this->buffer::begin(); 
	}

	byte_range range()
	{
		return byte_range(this->begin(), this->buffer::size());
	}

	const internal_type &internal() const
	{ 
		return *reinterpret_cast<const internal_type *>(this->begin());
	}

	internal_type &internal()
	{ 
		return *reinterpret_cast<internal_type *>(this->begin());
	}
};

}
}

#endif
