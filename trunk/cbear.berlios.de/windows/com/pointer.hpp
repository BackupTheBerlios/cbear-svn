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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_POINTER_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_POINTER_HPP_INCLUDED

// ::cbear_berlios_de::windows::com::pointer_base
#include <cbear.berlios.de/windows/com/pointer_base.hpp>
// ::cbear_berlios_de::windows::com::uuid
#include <cbear.berlios.de/windows/com/uuid.hpp>
// ::cbear_berlios_de::base::swap
#include <cbear.berlios.de/base/swap.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

template<class I>
class pointer: private pointer_base<I>
{
private:

	typedef pointer_base<I> base_t;

public:

	typedef base::move_t<pointer> move_t;

	pointer() throw() 
	{
	}

	template<class I1>
	pointer(const pointer<I1> &O1): 
		base_t(O1) 
	{
	} 

	pointer(const move_t &M) throw() 
	{ 
		M.swap(*this); 
	}

	pointer &operator=(const move_t &M) throw()
	{
		M.swap(*this);
		return *this;
	}

	void swap(pointer &O1) throw() 
	{ 
		this->base_t::swap(O1); 
	}

public:

	template<class I1>
	bool operator==(const pointer<I1> &O1) const throw()
	{
		return this->c_in() == O1.c_in();
	}

	template<class I1>
	bool operator!=(const pointer<I1> &O1) const throw()
	{
		return this->c_in() != O1.c_in();
	}

	operator bool() const throw()
	{
		return this->c_in() != 0;
	}

	bool operator!() const throw()
	{
		return this->c_in() == 0;
	}

public:

	class uninitialized {};

	I &operator*() const throw(uninitialized)
	{
		return this->reference();
	}

	I *operator->() const throw(uninitialized)
	{
		return &this->reference();
	}

private:

	I &reference() const throw(uninitialized)
	{
		I *const P = this->c_in();
		if(P) 
		{
			return *P;
		}
		else
		{
			throw uninitilized();
		}
	}

public:

	template<class I1>
	typename pointer<I1>::move_t query_interface() const throw()
	{
		I *const P = this->c_in();
		pointer<I1>::move_t R;
		if(P)
		{
			P->QueryInterface(*uuid::of<I1>().c_in(), R->c_out());
		}
		return R;
	}
};

}
}
}

#endif
