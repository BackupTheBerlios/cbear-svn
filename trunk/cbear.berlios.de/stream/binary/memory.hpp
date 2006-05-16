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
#ifndef CBEAR_BERLIOS_DE_STREAM_BINARY_MEMORY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_STREAM_BINARY_MEMORY_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator_range.hpp>
#include <cbear.berlios.de/stream/virtual_write.hpp>

namespace cbear_berlios_de
{
namespace stream
{
namespace binary
{

class memory
{
public:

	typedef range::iterator_range<char *> range_type;

	explicit memory(const range_type &R): R(R) {}

	class exception: 
		public stream::virtual_write,
		public stream::wvirtual_write
	{
	public:
		template<class S>
		void write(S &s) const
		{		
			S << 
				CBEAR_BERLIOS_DE_BASE_SELECT(
					typename S::value_type, 
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

	void pop_front_range(range_type N)
	{
		if(N.size() > this->R.size()) throw exception();
		for(; !N.empty(); ++N.begin(), ++this->R.begin())
			N.front() = this->R.front();
	}	

private:
	range_type R;
};

}
}
}

#endif