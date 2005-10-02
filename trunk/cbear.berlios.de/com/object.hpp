/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.sourceforge.net)

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
#ifndef CBEAR_SOURCEFORGE_NET_COM_OBJECT_HPP_INCLUDED
#define CBEAR_SOURCEFORGE_NET_COM_OBJECT_HPP_INCLUDED

#include <cbear.sourceforge.net/com/uuid.hpp>

namespace cbear.sourceforge.net
{
namespace com
{

template<class Interface>
class object;

template<class Interface>
struct object_policy: private policy::standard_policy<Interface *>
{
	typedef policy::standard_policy<Interface *> standard_policy;

	using standard_policy::construct;
	using standard_policy::equal;
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

template<class Interface>
class object_base: public object_policy<Interface>::wrap
{
public:
	typedef Interface interface_type;
	typedef interface_type *internal_type;
	typedef object_policy<interface_type> internal_policy;

	internal_type in() const 
	{ 
		return this->internal(); 
	}
	internal_type *in_out() 
	{ 
		return &this->internal(); 
	}
	internal_type *out()
	{ 
		internal_type &This = this->internal();
		internal_policy::destroy(This);
		internal_policy::construct(This);
		return &This;
	}
	template<class Interface1>
	object<Interface1> QueryInterface() const
	{
		object<Interface1> Result;
		internal_type P = this->internal();
		if(P)
		{
			P->QueryInterface(
				uuid::of<Interface1>().internal(), (void **)Result.out());
		}
		return Result;
	}		

	class uninitialized: public std::exception
	{
	public:
		const char *what() throw() 
		{ 
			return "cbear_sourceforge_net::com::object<...> uninitialized.";
		}
	};

protected:

	interface_type &internal_this() const
	{ 
		internal_type P = this->internal();
		if(!P) throw uninitialized();
		return *P;
	}
};

template<class Interface, class Base>
class object_contetn: public object_base<Base>
{
};

template<class Interface>
class object: public object_contetn<Interface, Interface>
{
public:

	typedef Interface interface_type;
	typedef interface_type *internal_type;
	typedef object_policy<interface_type> internal_policy;

	object() {}

	template<class Interface1>
	explicit object(const object<Interface1> &P)
	{
		internal_policy::construct_copy(this->internal(), P.internal());
	}

	operator bool() const { return this->internal(); }

	explicit object(internal_type X)
	{
		internal_policy::construct_copy(this->internal(), X);
	}
};

typedef object< ::IUnknown> iunknown;

}
}

#endif
