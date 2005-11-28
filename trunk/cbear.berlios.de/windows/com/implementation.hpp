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
#include <cbear.berlios.de/windows/com/lcid.hpp>
#include <cbear.berlios.de/windows/com/itypelib.hpp>
#include <cbear.berlios.de/range/sub_range.hpp>
#include <cbear.berlios.de/intrusive/list.hpp>

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

class basic_interface_info: public intrusive::node<basic_interface_info>
{
public:
	virtual const com::uuid &get_uuid() = 0;
	virtual iunknown::internal_type get_pointer() = 0;
};

template<class Interface>
class interface_info: public basic_interface_info
{
public:
	virtual const com::uuid &get_uuid() { return uuid::of<Interface>(); }
private:
	// Against VC warnings.
	interface_info(const interface_info &);
	interface_info operator=(const interface_info &);
};

class implementation_info: public intrusive::node<implementation_info>
{
protected:

	implementation_info(): Group(0) {}

	template<class Interface>
	void add_interface(interface_info<Interface> *P) 
	{ 
		this->List.push_back(*P);
	}

	typedef intrusive::list<basic_interface_info> list_type;

	hresult::internal_type query_interface(
		const uuid::internal_type &Uuid, void **PP)
	{
		for(
			range::sub_range<list_type>::type R(this->List); 
			!R.empty(); 
			++R.begin())
		{
			if(R.front().get_uuid().internal()==Uuid)
			{
				iunknown::internal_policy::construct_copy(
					*reinterpret_cast<iunknown::internal_type *>(PP), 
					R.front().get_pointer());
				return hresult::s_ok;
			}
		}
		*PP = 0;
		return hresult::e_nointerface;
	}

	com::group &group() const { return *this->Group; }

private:

	com::group *Group;

	list_type List;

	friend class detail::implementation_counter;
};

}

template<class Base, class Interface, class Parent>
class implementation_base: 
	public implementation<Base, Parent>,
	private detail::interface_info<Interface>
{
public:
	implementation_base() 
	{ 
		detail::implementation_info::add_interface<Interface>(this); 
	}
private:
	iunknown::internal_type get_pointer() 
	{ 
		return static_cast<Interface *>(this); 
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
private:
	// Against VC warnings.
	implementation(const implementation &);
	implementation &operator=(const implementation &);
};

template<class Base>
class implementation<Base, detail::implementation_info>: 
	protected virtual detail::implementation_info,
	public Base
{
private:
	// Against VC warnings.
	implementation(const implementation &);
	implementation &operator=(const implementation &);
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
		this->TypeInfo = this->group().type_lib().GetTypeInfoOfGuid<Base>();
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
	group(const itypelib &TypeLib): TypeLib(TypeLib) {}
	~group() { this->wait(); }

	void wait()
	{
		boost::mutex::scoped_lock Lock(this->ConditionMutex);
		if(this->Value.read()!=0) this->Condition.wait(Lock);
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

	template<class T, class P1, class P2>
	typename new_result<T>::type new_(const P1 &X1, const P2 &X2)
	{
		return new_result<T>::type(new detail::implementation_instance<T>(
			*this, X1, X2));
	}

	template<class T, class P1, class P2, class P3>
	typename new_result<T>::type new_(const P1 &X1, const P2 &X2, const P3 &X3)
	{
		return new_result<T>::type(new detail::implementation_instance<T>(
			*this, X1, X2, X3));
	}

	template<class T, class P1, class P2, class P3, class P4>
	typename new_result<T>::type new_(
		const P1 &X1, const P2 &X2, const P3 &X3, const P4 &X4)
	{
		return new_result<T>::type(new detail::implementation_instance<T>(
			*this, X1, X2, X3, X4));
	}

	template<class T, class P1, class P2, class P3, class P4, class P5>
	typename new_result<T>::type new_(
		const P1 &X1, const P2 &X2, const P3 &X3, const P4 &X4, const P5 &X5)
	{
		return new_result<T>::type(new detail::implementation_instance<T>(
			*this, X1, X2, X3, X4, X5));
	}

	const itypelib &type_lib() const { return this->TypeLib; }

	int size() { return this->Value.read(); }

private:

	void increment() 
	{ 
		boost::mutex::scoped_lock Lock(this->ConditionMutex);
		this->Value.increment();
	}
	void decrement()
	{
		boost::mutex::scoped_lock Lock(this->ConditionMutex);
		if(this->Value.decrement()==0)
		{ 
			this->Condition.notify_one(); 
		}
	}

	boost::mutex ConditionMutex;
	boost::condition Condition;
	atomic::wrap<int> Value;

	intrusive::list<detail::implementation_info> List;

	friend class detail::implementation_counter;

	itypelib TypeLib;
};

template<class Base>
class implementation<Base, ::ISupportErrorInfo>:
	public implementation_base<Base, ::ISupportErrorInfo, ::IUnknown>
{
public:
	hresult::internal_type __stdcall InterfaceSupportsErrorInfo(const IID &)
	{
		return S_OK;
	}
private:
	// Against VC warnings.
	implementation(const implementation &);
	implementation &operator=(const implementation &);
};

typedef object< ::ISupportErrorInfo> isupporterrorinfo;

namespace detail
{

class implementation_counter: 
	private atomic::wrap<ulong_t>,
	private virtual implementation_info
{
protected:

	typedef atomic::wrap<ulong_t>::internal_type internal_type;

	implementation_counter(com::group &Group)
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
	public T,
	public isupporterrorinfo::implementation_type
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

	implementation_instance(com::group &Group): implementation_counter(Group) {}

  template<class P>
	implementation_instance(com::group &Group, const P &X): 
		implementation_counter(Group), T(X) 
	{
	}

  template<class P1, class P2>
	implementation_instance(com::group &Group, const P1 &X1, const P2 &X2): 
		implementation_counter(Group), T(X1, X2)
	{
	}

  template<class P1, class P2, class P3>
	implementation_instance(
		com::group &Group, const P1 &X1, const P2 &X2, const P3 &X3):
		implementation_counter(Group), T(X1, X2, X3)
	{
	}

  template<class P1, class P2, class P3, class P4>
	implementation_instance(
		com::group &Group, const P1 &X1, const P2 &X2, const P3 &X3, const P4 &X4):
		implementation_counter(Group), T(X1, X2, X3, X4)
	{
	}

  template<class P1, class P2, class P3, class P4, class P5>
	implementation_instance(
		com::group &Group, 
		const P1 &X1, 
		const P2 &X2, 
		const P3 &X3, 
		const P4 &X4, 
		const P5 &X5):
		implementation_counter(Group), T(X1, X2, X3, X4, X5)
	{
	}
};

}

}
}
}

#endif
