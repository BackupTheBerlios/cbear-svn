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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_NEW_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_NEW_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

template<class T>
class implementation: public T::template t<implementation<T> >
{
public:

	typedef T::template t<implementation<T> > base_t;

	typedef com::pointer<implementation> pointer_t;

	implementation() 
	{
	}

	implementation(const P &P_): 
		base_t(P_)
	{
	}		

	static typename pointer_t::move_t this_pointer(base_t &B)
	{
		return move::copy(pointer_t::cpp_in_cast(
			&static_cast<implementation &>(B)));
	}
};

template<class T>
typename pointer<implementation<T> >::move_t new_()
{
	typedef implementation<T> implementation_t;
	typedef pointer<implementation_t> pointer_t;
	return move::copy(pointer_t::cpp_in_cast(new implementation_t()));
}

template<class T, class P>
typename pointer<implementation<T> >::move_t new_(const P &P_)
{
	typedef implementation<T> implementation_t;
	typedef pointer<implementation_t> pointer_t;
	return move::copy(pointer_t::cpp_in_cast(new implementation_t(P_)));
}

}
}
}
}

#endif
