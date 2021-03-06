#ifndef CBEAR_BERLIOS_DE_STREAM_VIRTUAL_WRITE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_VIRTUAL_WRITE_HPP_INCLUDED

#include <cbear.berlios.de/stream/write.hpp>

namespace cbear_berlios_de
{
namespace stream
{

template<class Char>
class basic_virtual_write
{
public:

	class stream
	{
	public:

		typedef Char value_type;

		typedef range::iterator_range<const Char *> range_type;

		template<class Container>
		void push_back_range(const Container &R) 
		{ 
			this->detail_push_back_range(range_type(R)); 
		}

		template<class T>
		stream &operator<<(const T &t)
		{
			::cbear_berlios_de::stream::write(*this, t);
			return *this;
		}

	protected:

		virtual void detail_push_back_range(const range_type &R) = 0;
	};

private:

	template<class S>
	class stream_implementation: public stream
	{
	public:
		stream_implementation(S &s): s(s) {}
	protected:
		void detail_push_back_range(const range::iterator_range<const Char *> &R) 
		{ 
			this->s.push_back_range(R);
		}
	private:
		S &s;
		stream_implementation &operator=(const stream_implementation &)
		{
			return *this;
		}
	};

public:

	template<class S>
	void write(S &s) const 
	{ 
		stream_implementation<S> v(s);
		this->detail_write(v); 
	}

protected:

	virtual void detail_write(stream &v) const = 0;
};

typedef basic_virtual_write<char> virtual_write;
typedef basic_virtual_write<wchar_t> wvirtual_write;

}
}

#endif
