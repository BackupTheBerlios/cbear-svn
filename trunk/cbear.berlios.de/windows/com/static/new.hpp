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
class implementation
{
public:
	implementation() {}
	implementation(const P &P_) {}
	void clear() throw()
	{
	}
};

template<class T>
class owner
{
public:
	typedef implementation<T> implementation_t;
	typedef pointer<implementation_t> pointer_t;
	~owner()
	{
		this->clear();
	}
	void clear() throw()
	{
		if(this->P) 
		{
			this->P->clear();
			this->P = pointer_t();
		}
	}
private:
	pointer_t P;	
};

template<class T>
class new_t: public meta::identity<pointer<implementation<T> > > {};

template<class T>
typename new_t<T>::type::move_t new_()
{
	typedef typename new_t<T>::type::interface_t interface_t;
	return base::move_copy(type::cpp_in(new interface_t()));
}

template<class T, class P>
typename new_t<T>::type::move_t new_(const P &P_)
{
	typedef typename new_t<T>::type::interface_t interface_t;
	return base::move_copy(type::cpp_in(new interface_t(P_)));
}

}
}
}
}

#endif
