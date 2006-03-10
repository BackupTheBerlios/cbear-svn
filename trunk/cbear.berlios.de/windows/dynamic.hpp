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
