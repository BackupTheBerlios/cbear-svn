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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_INTERFACE_CONTENT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_INTERFACE_CONTENT_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/iunknown.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

template<class T>
class implementation;

template<class T, class B, class I>
class interface_content;

template<class T, class B>
class interface_content<T, B, ::IUnknown>: public B
{
protected:
	typedef implementation<T> implementation_t;
	class access_t: public implementation_t::access_t
	{
	public:
		access_t(interface_content *This):
			implementation_t::access_t(static_cast<implementation_t *>(This))
		{
		}
	};
	iunknown::move_t query_interface(const uuid &U) throw()
	{
		if(uuid::of< ::IUnknown>()==U)
		{
			return move::copy(iunknown::cpp_in(static_cast< ::IUnknown *>(this)));
		}
		return iunknown::move_t();
	}
};

}
}
}
}

#endif
