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

	/*
	template<class ArchiveT>
	void serialize(ArchiveT &Archive, const unsigned int Version)
	{
		for(iterator It = this->begin(); It!=this->end(); ++It)
		{
			Archive & boost::serialization::make_nvp("item", *It);
		}
	}
	*/

	template<class StreamType>
	void binary_read(StreamType &S)
	{
		for(range_type R(*this); !R.empty(); ++R.begin())
			stream::binary::read(S, R.front());
	}
};

}
}
}

#endif
