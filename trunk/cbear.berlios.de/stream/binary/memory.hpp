#ifndef CBEAR_BERLIOS_DE_STREAM_BINARY_MEMORY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_BINARY_MEMORY_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator_range.hpp>
#include <cbear.berlios.de/stream/virtual_write.hpp>
#include <cbear.berlios.de/stream/binary/read.hpp>
#include <cbear.berlios.de/stream/binary/write.hpp>
#include <cbear.berlios.de/select/traits.hpp>

namespace cbear_berlios_de
{
namespace stream
{
namespace binary
{

template<class E>
class memory: private std::vector<char>
{
public:

	typedef range::iterator_range<char *> range_type;
	typedef range::iterator_range<const char *> const_range_type;

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
					"::cbear_berlios_de::stream::binary::memory::exception");
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

	void push_back_range(const const_range_type &N)
	{
		this->insert(this->end(), N.begin(), N.end());
	}

	template<class T>
	void push_back_pod(T const &t)
	{
		E::push_back_pod(*this, t);
	}

	void pop_front_range(const range_type &N)
	{
		if(N.size() > this->size()) throw exception();

		const iterator B = this->begin();
		iterator I = B;
		for(range_type NI(N); !NI.empty(); ++NI.begin(), ++I)
			NI.front() = *I;
		this->erase(B, I);
	}

	template<class T>
	void pop_front_pod(T &t)
	{
		E::pop_front_pod(*this, t);
	}

	template<class T>
	memory &operator<<(const T &X)
	{
		binary::write(*this, X);
		return *this; 
	}

	template<class T>
	memory &operator>>(T &X)
	{
		binary::read(*this, X);
		return *this; 
	}
};

}
}
}

#endif