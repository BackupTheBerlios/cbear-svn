#ifndef CBEAR_BERLIOS_DE_STREAM_BINARY_IRANGE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_BINARY_IRANGE_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator_range.hpp>
#include <cbear.berlios.de/stream/virtual_write.hpp>
#include <cbear.berlios.de/stream/binary/read.hpp>
#include <cbear.berlios.de/select/traits.hpp>

namespace cbear_berlios_de
{
namespace stream
{
namespace binary
{

class irange
{
public:

	typedef range::iterator_range<char *> range_type;
	typedef range::iterator_range<const char *> const_range_type;

	irange(const const_range_type &R): R(R) {}

	class exception: 
		public stream::virtual_write,
		public stream::wvirtual_write
	{
	public:
		template<class S>
		void write(S &s) const
		{		
			typedef typename S::value_type value_type;
			s << 
				CBEAR_BERLIOS_DE_SELECT_STRING(
					value_type,
					"::cbear_berlios_de::stream::binary::irange::exception");
		}
	protected:
		void detail_write(::cbear_berlios_de::stream::virtual_write::stream &S) 
			const
		{
			this->write(S);
		}
		void detail_write(::cbear_berlios_de::stream::wvirtual_write::stream &S) 
			const
		{
			this->write(S);
		}
	};

	void pop_front_range(const range_type &N)
	{
		if(N.size() > this->R.size()) throw exception();
		const const_range_type RI(R.begin(), N.size());
		range::copy(RI, N.begin());
		this->R.begin() = RI.end();
	}

	template<class T>
	irange &operator>>(T &X)
	{
		binary::read(*this, X);
		return *this; 
	}

private:
	const_range_type R;
};

}
}
}

#endif