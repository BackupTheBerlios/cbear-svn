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

// ::cbear_berlios_de::base::safe_reinterpret_cast
#include <cbear.berlios.de/cast/traits.hpp>
// ::cbear_berlios_de::windows::com::pointer_content
#include <cbear.berlios.de/windows/com/pointer_content.hpp>
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
class pointer: public pointer_content<I, I>
{
private:

	typedef pointer_base<I> base_t;

public:

	typedef I interface_t;

	typedef move::t<pointer> move_t;

	pointer() throw() 
	{
	}

	template<class I1>
	pointer(const pointer<I1> &O1) throw()
	{
		this->assign(O1);
	} 

	template<class I1>
	pointer(const move::t<pointer<I1> > &M) throw() 
	{ 
		this->base_t::move_assign(*M);
	}

	template<class I1>
	pointer &operator=(const move::t<pointer<I1> > &M) throw()
	{
		this->base_t::move_assign(*M);
		return *this;
	}

	void swap(pointer &O1) throw() 
	{ 
		this->base_t::swap(O1); 
	}

	template<class I1>
	void move_assign(pointer<I1> &O1) throw()
	{
		this->base_t::move_assign(O1);
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

	template<class I1>
	typename pointer<I1>::move_t query_interface() const throw()
	{
		const c_in_t P = this->c_in();
		typename pointer<I1>::move_t R;
		if(P)
		{
			P->QueryInterface(
				*uuid::of<I1>().c_in(), 
				reinterpret_cast<void **>(R->c_out()));
		}
		return R;
	}

	template<class O1>
	typename O1::move_t interface_cast() const throw()
	{
		return this->query_interface<typename O1::interface_t>();
	}

public:

	template<class O1>
	typename O1::move_t dynamic_cast_() const throw()
	{
		return move::copy(O1::cpp_in(dynamic_cast<O1::c_in_t>(this->c_in())));
	}

public:

	static const pointer &cpp_in(const c_in_t &P) throw() 
	{ 
		return base::safe_reinterpret_cast<const pointer &>(P);
	}

	static pointer &cpp_in_out(c_in_out_t P) throw() 
	{ 
		return base::safe_reinterpret_cast<pointer &>(*P);
	}

	static pointer &cpp_out(c_out_t P) throw() 
	{ 
		*P = 0;
		return base::safe_reinterpret_cast<pointer &>(*P);
	}

// deprecated
public:

	// typedef object_policy<interface_type> internal_policy;
	class internal_policy
	{
	public:
		typedef I *type;
		static void construct(I *P)
		{
			P = 0;
		}
	};

	static const vartype_t vt = 
		boost::is_base_of< ::IDispatch, I>::value ? 
			::VT_DISPATCH: ::VT_UNKNOWN;

	typedef void *extra_result;

	typedef move_t move_type;

	c_in_t internal() const throw()
	{ 
		return this->c_in(); 
	}

	c_in_t &internal() throw()
	{ 
		return *this->c_in_out(); 
	}

	static void *extra()
	{
		return const_cast<uuid::c_in_out_t>(uuid::of<interface_t>().c_in());
	}

	static const pointer &wrap_ref(const c_in_t &P) { return cpp_in(P); }
	static pointer &wrap_ref(interface_t * &P) { return cpp_in_out(&P); }
};

}
}
}

#endif
