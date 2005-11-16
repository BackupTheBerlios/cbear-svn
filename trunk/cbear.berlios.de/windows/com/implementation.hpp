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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_IMPLEMENTATION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_IMPLEMENTATION_HPP_INCLUDED

// std::map
#include <map>                                    

// boost::mutex
#include <boost/thread/mutex.hpp>
// boost::condition
#include <boost/thread/condition.hpp>

#include <cbear.berlios.de/atomic/main.hpp>
#include <cbear.berlios.de/windows/com/hresult.hpp>
#include <cbear.berlios.de/windows/com/object.hpp>
#include <cbear.berlios.de/windows/com/uint.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class group;

namespace detail
{

class implementation_counter;

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

	group &get_group() { return *this->Group; }

private:

	typedef std::map<uuid, iunknown::internal_type> map_type;
	map_type Map;

	void add(const uuid &Uuid, iunknown::internal_type P)
	{
		if(this->Map.find(Uuid)!=this->Map.end()) return;
		this->Map[Uuid] = P;
	}

	group *Group;

	friend class detail::implementation_counter;
};

}

template<class Base, class Interface, class Parent>
class implementation_base: 
	public implementation<Base, Parent>
{
public:
	implementation_base() 
	{ 
		detail::implementation_info::add_interface<Interface>(this); 
	}
private:
	const uuid &get_uuid() { return uuid::of<Interface>(); }
	void *get_pointer() { return static_cast<Interface *>(this); }
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

typedef LPOLESTR lpolestr_t;
typedef DISPID dispid_t;
typedef WORD word_t;
typedef DISPPARAMS dispparams_t;
typedef VARIANT variant_t;
typedef EXCEPINFO excepinfo_t;

template<class Base>
class implementation<Base, ::IDispatch>:
	public implementation_base<Base, ::IDispatch, ::IUnknown>
{
public:

	implementation()
	{
		this->TypeInfo = this->get_group().type_lib().GetTypeInfoOfGuid<Base>();
	}

	hresult::internal_type __stdcall GetTypeInfoCount(
		internal_result<out, uint_t>::type _result) 
	{
		wrap<out, uint_t>(_result) = 1;
		return hresult::s_ok;
	}

	hresult::internal_type __stdcall GetTypeInfo(
		uint_t iTInfo,
		lcid_t,
		internal_result<out, itypeinfo>::type ppTInfo)
	{
		if(iTInfo != 0) return hresult::disp_e_badindex;
		wrap<out, itypeinfo>(ppTInfo) = this->TypeInfo;
		return hresult::s_ok;
	}

	hresult::internal_type __stdcall GetIDsOfNames(
		const uuid::internal_type &, 
		lpolestr_t *rgszNames, 
		uint_t cNames, 
		lcid_t, 
		dispid_t *rgDispId)
	{
		return ::DispGetIDsOfNames(
			internal<in>(this->TypeInfo), 
			rgszNames, 
			cNames, 
			rgDispId);
	}

	HRESULT __stdcall Invoke(
		dispid_t dispidMember,
		const uuid::internal_type &,
		lcid_t,
		word_t wFlags,
		dispparams_t * pdispparams,
		variant_t * pvarResult,
		excepinfo_t * pexcepinfo,
		uint_t * puArgErr)
	{
		return DispInvoke(
			(Base *)this, 
			internal<in>(TypeInfo),
			dispidMember, 
			wFlags, 
			pdispparams,
			pvarResult, 
			pexcepinfo, 
			puArgErr);
	}
private:
	itypeinfo TypeInfo;
};

typedef BOOL bool_t;

template<class Base>
class implementation<Base, ::IClassFactory>:
	public implementation_base<Base, ::IClassFactory, ::IUnknown>
{
public:
	hresult::internal_type __stdcall CreateInstance(
		internal_result<in, iunknown>::type Outer, 
		const uuid::internal_type &Uuid, 
		void **ppObject)
	{
		// Cannot aggregate.
		if(Outer) return hresult::class_e_noaggregation;
		return QueryInterface(Uuid, ppObject);
	}
	hresult::internal_type __stdcall LockServer(bool_t fLock)
	{
		if(fLock!=FALSE) this->AddRef(); else this->Release();
		return hresult::s_ok;
	}
};

namespace detail
{

class implementation_counter;

template<class T>
class implementation_instance;

}

class group: boost::noncopyable
{
public:
	group() {}
	group(const object< ::ITypeLib> &TypeLib): TypeLib(TypeLib) {}
	~group() 
	{
		boost::mutex::scoped_lock Lock(this->ConditionMutex);
		if(this->Value!=policy::std_wrap<int>()) this->Condition.wait(Lock);
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
		return new_result<T>::type(new detail::implementation_instance<T>(
			*this, X));
	}

	const object< ::ITypeLib> &type_lib() const { return this->TypeLib; }

	int value() { return this->Value.internal(); }

private:

	void increment() 
	{ 
		boost::mutex::scoped_lock Lock(this->ConditionMutex);
		++this->Value;
	}
	void decrement()
	{
		boost::mutex::scoped_lock Lock(this->ConditionMutex);
		--this->Value;
		if(this->Value==policy::std_wrap<int>())
		{ 
			this->Condition.notify_one(); 
		}
	}

	boost::mutex ConditionMutex;
	boost::condition Condition;
	policy::std_wrap<int> Value;

	friend class detail::implementation_counter;

	object< ::ITypeLib> TypeLib;
};

namespace detail
{

class implementation_counter: 
	private atomic::wrap<ulong_t>,
	private virtual implementation_info
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

	implementation_instance(group &Group): implementation_counter(Group) {}

  template<class P>
  implementation_instance(group &Group, const P &X): 
		implementation_counter(Group), T(X) 
	{
	}
};

}

// This class is deprecated. You should use group::new_ instead when the 
// garbage collection implementation will be ready.
template<class T>
class local_object: private T
{
public:

	template<class I>
	operator object<I>() { return object<I>(static_cast<I *>(this)); }

	local_object() {}

	template<class P>
	local_object(const P &X): T(X) {}

private:
	ulong_t __stdcall AddRef() { return 0; }
	ulong_t __stdcall Release() { return 0; }
	hresult::internal_type __stdcall QueryInterface(
		const uuid::internal_type &U, void **PP)
  { 
		return detail::implementation_info::query_interface(U, PP);
  }
	local_object(const local_object &);
};

}
}
}

#endif
