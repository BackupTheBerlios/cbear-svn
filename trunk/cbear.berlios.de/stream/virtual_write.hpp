/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
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
