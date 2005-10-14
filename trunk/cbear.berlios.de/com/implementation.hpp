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
#ifndef CBEAR_BERLIOS_DE_COM_IMPLEMENTATION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_COM_IMPLEMENTATION_HPP_INCLUDED

// std::map
#include <map>                                    

#include <cbear.berlios.de/atomic/main.hpp>
#include <cbear.berlios.de/com/hresult.hpp>
#include <cbear.berlios.de/com/object.hpp>
#include <cbear.berlios.de/com/uint.hpp>

namespace cbear_berlios_de
{
namespace com
{

namespace detail
{

class implementation_info: private std::map<uuid, iunknown::internal_type>
{
protected:
	
	template<class Interface>
	void add_interface(Interface *P) { this->add(uuid::of<Interface>(), P); }

	hresult::internal_type query_interface(
		const uuid::internal_type &Uuid, void **PP)
	{
		const_iterator Iterator = this->find(uuid(Uuid));
		if(Iterator==this->end()) 
		{
			*PP = 0;
			return hresult::e_nointerface;
		}
		iunknown::internal_policy::construct_copy(
			*reinterpret_cast<iunknown::internal_type *>(PP), 
			Iterator->second);
		return hresult::s_ok;
	}

private:

	void add(const uuid &Uuid, iunknown::internal_type P)
	{
		if(this->find(Uuid)!=this->end()) return;
		(*this)[Uuid] = P;
	}
};

}

template<class Interface, class Base = Interface>
class implementation;

template<class Interface, class Base, class Parent>
class implementation_base: public implementation<Parent, Base>
{
public:
	implementation_base() 
	{ 
		detail::implementation_info::add_interface<Interface>(this); 
	}
};

template<class Interface, class Base>
class implementation: 
	public implementation_base<Interface, Base, iunknown::interface_type>
{
};

template<class Base>
class implementation<IUnknown, Base>: 
	public implementation_base<IUnknown, Base, detail::implementation_info>
{
};

template<class Base>
class implementation<detail::implementation_info, Base>: 
	protected virtual detail::implementation_info,
	public Base
{
};

namespace detail
{

class implementation_counter: private atomic::wrap<ulong_t>
{
protected:

	typedef atomic::wrap<ulong_t>::internal_type internal_type;

	virtual ~implementation_counter() = 0;

	internal_type add_ref() { return this->increment(); }

	internal_type release() 
	{ 
		internal_type Result = this->decrement();
		if(!Result) delete this;
		return Result;
	}	
private:
	implementation_counter(const implementation_counter &);
	implementation_counter &operator=(const implementation_counter &);
};

template<class T>
class implementation_instance: 
	private implementation_counter,
	public T
{
public:
	implementation_instance() {}

  template<class P>
  implementation_instance(const P &X): T(X) {}

	// IUnknown

  ulong_t __stdcall AddRef() { return implementation_counter::add_ref(); }
  ulong_t __stdcall Release() { return implementation_counter::release(); }
	hresult::internal_type __stdcall QueryInterface(
		const uuid::internal_type &U, void **PP)
  { 
     return implementation_info::query_interface(U, PP); 
  }

	// IDispatch

	hresult::internal_type __stdcall GetTypeInfoCount(uint_t *) 
	{ 
		return hresult::e_fail; 
	}
};

}

template<class T>
struct new_result { typedef object<detail::implementation_instance<T> > type; };

template<class T>
typename new_result<T>::type new_()
{
	return new detail::implementation_instance<T>();
};

template<class T, class P>
typename new_result<T>::type new_(const P &X)
{
	return new detail::implementation_instance<T>(X);
}

}
}

#endif
