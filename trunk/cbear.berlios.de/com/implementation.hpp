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

// boost::mutex
#include <boost/thread/mutex.hpp>
// boost::condition
#include <boost/thread/condition.hpp>

#include <cbear.berlios.de/atomic/main.hpp>
#include <cbear.berlios.de/com/hresult.hpp>
#include <cbear.berlios.de/com/object.hpp>
#include <cbear.berlios.de/com/uint.hpp>

namespace cbear_berlios_de
{
namespace com
{

class group;

namespace detail
{

class implementation_info
{
protected:
	
	implementation_info(): Group(0) {}

	template<class Interface>
	void add_interface(Interface *P) { this->add(uuid::of<Interface>(), P); }

	hresult::internal_type query_interface(
		const uuid::internal_type &Uuid, void **PP)
	{
		map_type::const_iterator Iterator = this->Map.find(uuid(Uuid));
		if(Iterator==this->Map.end()) 
		{
			*PP = 0;
			return hresult::e_nointerface;
		}
		iunknown::internal_policy::construct_copy(
			*reinterpret_cast<iunknown::internal_type *>(PP), 
			Iterator->second);
		return hresult::s_ok;
	}

	group *Group;

private:

	typedef std::map<uuid, iunknown::internal_type> map_type;
	map_type Map;

	void add(const uuid &Uuid, iunknown::internal_type P)
	{
		if(this->Map.find(Uuid)!=this->Map.end()) return;
		this->Map[Uuid] = P;
	}
};

}

template<class Base, class Interface, class Parent>
class implementation_base: public implementation<Base, Parent>
{
public:
	implementation_base() 
	{ 
		detail::implementation_info::add_interface<Interface>(this); 
	}
};

template<class Base, class Interface>
class implementation: 
	public implementation_base<Base, Interface, iunknown::interface_type>
{
};

template<class Base>
class implementation<Base, IUnknown>: 
	public implementation_base<Base, IUnknown, detail::implementation_info>
{
};

template<class Base>
class implementation<Base, detail::implementation_info>: 
	protected virtual detail::implementation_info,
	public Base
{
};

namespace detail
{

class implementation_counter;

template<class T>
class implementation_instance;

}

class group
{
public:
	group(): Value(0) {}
	~group()
	{ 
		boost::mutex::scoped_lock Lock(this->ConditionMutex);
		if(this->Value) this->Condition.wait(Lock);
	}

	template<class T>
	struct new_result 
	{ 
		typedef object<detail::implementation_instance<T> > type; 
	};

	template<class T>
	typename new_result<T>::type new_()
	{
		return new_result<T>::type(new detail::implementation_instance<T>(*this));
	};

	template<class T, class P>
	typename new_result<T>::type new_(const P &X)
	{
		return new_result<T>::type(new detail::implementation_instance<T>(*this, X));
	}

private:
	boost::mutex ConditionMutex;
	boost::condition Condition;
	int Value;

	void increment() 
	{ 
		boost::mutex::scoped_lock Lock(this->ConditionMutex);
		++this->Value;
	}
	void decrement()
	{
		boost::mutex::scoped_lock Lock(this->ConditionMutex);
		if(!--this->Value) 
		{ 
			this->Condition.notify_one(); 
		}
	}

	friend class detail::implementation_counter;	
};

namespace detail
{

class implementation_counter: 
	private atomic::wrap<ulong_t>,
	private implementation_info
{
protected:

	typedef atomic::wrap<ulong_t>::internal_type internal_type;

	implementation_counter(group &Group)
	{
		this->Group = &Group;
		this->Group->increment();
	}

	virtual ~implementation_counter() 
	{
		this->Group->decrement();
	}

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
	// IUnknown

  ulong_t __stdcall AddRef() { return implementation_counter::add_ref(); }
  ulong_t __stdcall Release() { return implementation_counter::release(); }
	hresult::internal_type __stdcall QueryInterface(
		const uuid::internal_type &U, void **PP)
  { 
     return implementation_info::query_interface(U, PP); 
  }

private:

	friend class group;

	implementation_instance(group &Group): implementation_counter(Group)
	{
	}

  template<class P>
  implementation_instance(group &Group, const P &X): 
		implementation_counter(Group), T(X) 
	{
	}
};

}

}
}

#endif
