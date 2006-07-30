#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_DYNAMIC_IMPLEMENTATION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_DYNAMIC_IMPLEMENTATION_HPP_INCLUDED

// boost::mutex
#include <boost/thread/mutex.hpp>
// boost::condition
#include <boost/thread/condition.hpp>

#include <cbear.berlios.de/atomic/main.hpp>
#include <cbear.berlios.de/windows/bool.hpp>
#include <cbear.berlios.de/windows/com/hresult.hpp>
#include <cbear.berlios.de/windows/com/pointer.hpp>
#include <cbear.berlios.de/windows/com/uint.hpp>
#include <cbear.berlios.de/windows/com/lcid.hpp>
#include <cbear.berlios.de/windows/com/itypelib.hpp>
#include <cbear.berlios.de/windows/com/iunknown.hpp>
#include <cbear.berlios.de/range/sub_range.hpp>
#include <cbear.berlios.de/intrusive/list.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace dynamic
{

class group;

namespace detail
{

class implementation_counter;

class basic_interface_info: public intrusive::node<basic_interface_info>
{
public:
	virtual const com::uuid &get_uuid() = 0;
	virtual iunknown::c_in_t get_pointer() = 0;
};

template<class Interface>
class interface_info: public basic_interface_info
{
public:
	virtual const com::uuid &get_uuid() { return uuid::of<Interface>(); }
	interface_info() {}
private:
	// Against VC warnings.
	interface_info(const interface_info &);
	interface_info operator=(const interface_info &);
};

class implementation_info
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
		const uuid::c_t &Uuid, void **PP)
	{
		iunknown &P = iunknown::cpp_out(reinterpret_cast<iunknown::c_out_t>(PP));
		for(
			range::sub_range<list_type>::type R(this->List); 
			!R.empty(); 
			++R.begin())
		{
			if(*R.front().get_uuid().c_in()==Uuid)
			{
				P = iunknown::cpp_in(R.front().get_pointer());
				return hresult::s_ok;
			}
		}
		return hresult::e_nointerface;
	}

	dynamic::group &group() const { return *this->Group; }

private:

	dynamic::group *Group;

	list_type List;

	friend class detail::implementation_counter;
};

}

template<class Base, class Interface = Base>
class implementation;

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
protected:
	// useless...
	implementation<Base, Interface> *base()
	{
		return static_cast<implementation<Base, Interface> *>(this);
	}
private:
	iunknown::c_in_t get_pointer() 
	{ 
		return static_cast<Interface *>(this); 
	}
};

template<class Base, class Interface>
class implementation: 
	public implementation_base<Base, Interface, iunknown::c_in_t>
{
};

template<class Base>
class implementation<Base, IUnknown>: 
	public implementation_base<Base, IUnknown, detail::implementation_info>
{
public:
	implementation() {}
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
public:
	implementation() {}
private:
	// Against VC warnings.
	implementation(const implementation &);
	implementation &operator=(const implementation &);
};

template<class Base>
class implementation<Base, ::IClassFactory>:
	public implementation_base<Base, ::IClassFactory, ::IUnknown>
{
public:
	hresult::internal_type __stdcall CreateInstance(
		internal_result<in, iunknown>::type Outer, 
		const uuid::c_t &Uuid, 
		void **ppObject)
	{
		// Cannot aggregate.
		if(Outer) return hresult::class_e_noaggregation;
		return QueryInterface(Uuid, ppObject);
	}
	hresult::internal_type __stdcall LockServer(bool_t::value_t fLock)
	{
		if(fLock) this->AddRef(); else this->Release();
		return hresult::s_ok;
	}
};

typedef pointer< ::IClassFactory> iclassfactory;

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
	~group() { this->wait(); }

	void wait()
	{
		boost::mutex::scoped_lock Lock(this->ConditionMutex);
		if(this->Value.read()!=0) this->Condition.wait(Lock);
	}

	template<class T>
	struct new_result 
	{ 
		typedef pointer<detail::implementation_instance<T> > type; 
	};

	template<class T>
	typename new_result<T>::type new_()
	{
		return new_result<T>::type::cpp_in(
			new detail::implementation_instance<T>(*this));
	};

	template<class T, class P>
	typename new_result<T>::type new_(const P &X)
	{
		return new_result<T>::type::cpp_in(
			new detail::implementation_instance<T>(*this, X));
	}

	template<class T, class P1, class P2>
	typename new_result<T>::type new_(const P1 &X1, const P2 &X2)
	{
		return new_result<T>::type::cpp_in(
			new detail::implementation_instance<T>(*this, X1, X2));
	}

	template<class T, class P1, class P2, class P3>
	typename new_result<T>::type new_(const P1 &X1, const P2 &X2, const P3 &X3)
	{
		return new_result<T>::type::cpp_in(
			new detail::implementation_instance<T>(*this, X1, X2, X3));
	}

	template<class T, class P1, class P2, class P3, class P4>
	typename new_result<T>::type new_(
		const P1 &X1, const P2 &X2, const P3 &X3, const P4 &X4)
	{
		return new_result<T>::type::cpp_in(
			new detail::implementation_instance<T>(*this, X1, X2, X3, X4));
	}

	template<class T, class P1, class P2, class P3, class P4, class P5>
	typename new_result<T>::type new_(
		const P1 &X1, const P2 &X2, const P3 &X3, const P4 &X4, const P5 &X5)
	{
		return new_result<T>::type::cpp_in(
			new detail::implementation_instance<T>(*this, X1, X2, X3, X4, X5));
	}

	//typedef std::vector<itypelib> typelibs_type;
	//typelibs_type typelibs;

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

	friend class detail::implementation_counter;

	//itypelib TypeLib;
};

template<class Base>
class implementation<Base, ::ISupportErrorInfo>:
	public implementation_base<Base, ::ISupportErrorInfo, ::IUnknown>
{
public:
	hresult::internal_type __stdcall InterfaceSupportsErrorInfo(const IID &)
	{
		return hresult::s_ok;
	}
	implementation() {}
private:
	// Against VC warnings.
	implementation(const implementation &);
	implementation &operator=(const implementation &);
};

typedef pointer< ::ISupportErrorInfo> isupporterrorinfo;

namespace detail
{

class implementation_counter: 
	private atomic::wrap<ulong_t>,
	private virtual implementation_info
{
protected:

	typedef atomic::wrap<ulong_t>::internal_type internal_type;

	implementation_counter(dynamic::group &Group)
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
	public dynamic::implementation<isupporterrorinfo::interface_t>
{
public:
	// IUnknown

  ulong_t __stdcall AddRef() { return implementation_counter::add_ref(); }
  ulong_t __stdcall Release() { return implementation_counter::release(); }

	hresult::internal_type __stdcall QueryInterface(
		const uuid::c_t &U, void **PP)
  { 
     return implementation_info::query_interface(U, PP); 
  }

private:

	friend class group;

	implementation_instance(dynamic::group &Group): implementation_counter(Group) {}

  template<class P>
	implementation_instance(dynamic::group &Group, const P &X): 
		implementation_counter(Group), T(X) 
	{
	}

  template<class P1, class P2>
	implementation_instance(dynamic::group &Group, const P1 &X1, const P2 &X2): 
		implementation_counter(Group), T(X1, X2)
	{
	}

  template<class P1, class P2, class P3>
	implementation_instance(
		dynamic::group &Group, const P1 &X1, const P2 &X2, const P3 &X3):
		implementation_counter(Group), T(X1, X2, X3)
	{
	}

  template<class P1, class P2, class P3, class P4>
	implementation_instance(
		dynamic::group &Group, 
		const P1 &X1, 
		const P2 &X2, 
		const P3 &X3, 
		const P4 &X4):
		implementation_counter(Group), T(X1, X2, X3, X4)
	{
	}

  template<class P1, class P2, class P3, class P4, class P5>
	implementation_instance(
		dynamic::group &Group, 
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
}

#endif
