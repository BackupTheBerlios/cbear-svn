#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_ARRAY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_ARRAY_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/traits.hpp>
#include <boost/array.hpp>
#include <boost/serialization/base_object.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

template<class ValueType, std::size_t Size>
class array_t: public boost::array<ValueType, Size>
{
public:
	typedef boost::array<ValueType, Size> parent;
	typedef typename parent::reference reference;
	typedef typename parent::const_reference const_reference;
	typedef typename parent::iterator iterator;
	typedef range::iterator_range<iterator> range_type;
	typedef range::iterator_range<const_iterator> const_range_type;

	reference operator[](std::size_t I) 
	{ 
		if(I>=Size) throw std::exception("Wrong index");
		return this->parent::operator[](I); 
	}
	const_reference operator[](std::size_t I) const
	{ 
		if(I>=Size) throw std::exception("Wrong index");
		return this->parent::operator[](I); 
	}

	array_t operator=(const ValueType (&S)[Size])
	{
		range::copy(S, this->begin());
		return *this;
	}

	template<class StreamType>
	void binary_read(StreamType &S)
	{
		for(range_type R(*this); !R.empty(); ++R.begin())
			stream::binary::read(S, R.front());
	}

	template<class StreamType>
	void binary_write(StreamType &S) const
	{
		for(const_range_type R(*this); !R.empty(); ++R.begin())
			stream::binary::write(S, R.front());
	}

	void move_assign(array_t &A)
	{
		for(range_type R(*this), RA(A); !R.empty(); ++R.begin(), ++RA.begin())
		{
			move::assign(R.front(), RA.front());
		}
	}
};

}
}
}

#endif
