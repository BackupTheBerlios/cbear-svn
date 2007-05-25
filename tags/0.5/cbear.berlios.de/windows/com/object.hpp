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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_OBJECT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_OBJECT_HPP_INCLUDED

#include <cbear.berlios.de/windows/syskind.hpp>
#include <cbear.berlios.de/windows/com/uuid.hpp>
#include <cbear.berlios.de/windows/com/bstr.hpp>
#include <cbear.berlios.de/windows/com/enum.hpp>
#include <cbear.berlios.de/windows/com/ulong.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class exception;

template<class Base, class Interface = Base>
class implementation;

template<class Interface>
class object;

template<class Interface>
struct object_policy: private policy::standard_policy<Interface *>
{
	typedef policy::standard_policy<Interface *> standard_policy;

	using standard_policy::construct;
	using standard_policy::equal;
	using standard_policy::less;
	using standard_policy::swap;
	using standard_policy::reference_of;

	typedef typename standard_policy::pointer pointer;
	typedef typename standard_policy::reference reference;

	typedef Interface interface_type;
	typedef object<interface_type> object_type;
	typedef Interface *type;

	static void add_ref(type X) { if(X) X->AddRef(); }
	static void release(type X) { if(X) X->Release(); }

	static void construct_copy(type &This, const type &Source)
	{
		This = Source;
		add_ref(This);
	}

	static void assign(type &This, const type &Source) 
	{
		add_ref(Source);
		release(This);
		This = Source; 
	}

	static void destroy(type &This)
	{
		release(This);
	}

	typedef policy::wrap<object_type, type, object_policy> wrap;
};

template<class Interface1>
struct add_object { typedef object<Interface1> type; };

template<class Interface1>
struct add_object<object<Interface1> > { typedef object<Interface1> type; };

template<class Interface>
class object_base: public object_policy<Interface>::wrap
{
public:
	typedef Interface interface_type;
	typedef implementation<interface_type> implementation_type;
	typedef interface_type *internal_type;
	typedef object_policy<interface_type> internal_policy;

	static const vartype_t vt = 
		boost::is_base_of< ::IDispatch, Interface>::value ?
			::VT_DISPATCH: ::VT_UNKNOWN;

	typedef void *extra_result;

	static void *extra() 
	{ 
		return const_cast<uuid::internal_type*>(
			&uuid::of<interface_type>().internal());
	}

	template<class Type>
	typename add_object<Type>::type query_interface() const
	{
		typedef typename add_object<Type>::type object_type;
		object_type Result;
		internal_type P = this->internal();
		if(P)
		{
			P->QueryInterface(
				com::internal<in>(object_type::uuid()), 
				(void **)com::internal<out>(Result));
		}
		return Result;
	}		

	template<class Type>
	typename add_object<Type>::type dynamic_cast_() const
	{
		typedef typename add_object<Type>::type object_type;
		return object_type(dynamic_cast<typename object_type::internal_type>(
				this->internal()));
	}

	static const com::uuid &uuid() { return uuid::of<interface_type>(); }

	class uninitialized: public std::exception
	{
	public:
		const char *what() const throw()
		{ 
			return this->Message.c_str();
		}
		uninitialized()
		{
			std::ostringstream O;
			O << "cbear_berlios_de::com::object<" << typeid(Interface).name() << 
				"> is uninitialized.";
			this->Message = O.str();
		}
	private:
		std::string Message;
	};

protected:

	interface_type &internal_reference() const
	{ 
		internal_type P = this->internal();
		if(!P) throw uninitialized();
		return *P;
	}
};

template<class Base, class Interface>
class object_content: public object_base<Base>
{
};

template<class Interface>
class object: public object_content<Interface, Interface>
{
public:

	typedef Interface interface_type;
	typedef interface_type *internal_type;
	typedef object_policy<interface_type> internal_policy;
	typedef object move_type;

	object() {}

	template<class Interface1>
	object(const object<Interface1> &P)
	{
		internal_policy::construct_copy(this->internal(), P.internal());
	}

	object(const base::move_t<object> &C) { C.swap(*this); }
	object &operator=(const base::move_t<object> &C) { C.swap(*this); }

	explicit object(internal_type X)
	{
		internal_policy::construct_copy(this->internal(), X);
	}

	operator bool() const { return this->internal() != 0; }
	bool operator!() const { return this->internal() == 0; }
};

template<class T>
object<T> make_object(T *P) { return object<T>(P); }

typedef object< ::IUnknown> iunknown;
typedef object< ::IDispatch> idispatch;
typedef object< ::IClassFactory> iclassfactory;

}
}
}

#endif
