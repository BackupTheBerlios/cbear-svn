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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_INTERFACE_LIST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_INTERFACE_LIST_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/static/interface.hpp>
#include <cbear.berlios.de/meta/list.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

template<class T, class L>
class interface_list: 
	public interface_<T, typename L::front::type>, 
	public interface_list<T, typename L::pop_front::type>
{
protected:
	typedef interface_<T, typename L::front::type> interface_t;
	typedef interface_list<T, typename L::pop_front::type> pop_front_t;
	iunknown::move_t query_interface(const uuid &U) throw()
	{
		iunknown::move_t R = this->interface_t::query_interface(U);
		if(*R) 
		{
			return R;
		}
		return this->pop_front_t::query_interface(U);
	}
};

template<class T>
class interface_list<T, meta::list>
{
protected:
	iunknown::move_t query_interface(const uuid &) throw()
	{
		return iunknown::move_t();
	}
};

}
}
}
}

#endif
