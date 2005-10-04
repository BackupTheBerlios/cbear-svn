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
#ifndef CBERA_BERLIOS_DE_COM_DYNAMIC_ADAPTER_HPP_INCLUDED
#define CBERA_BERLIOS_DE_COM_DYNAMIC_ADAPTER_HPP_INCLUDED

// std::map
#include <map>                                    

#include <cbear.berlios.de/atomic/main.hpp>
#include <cbear.berlios.de/com/hresult.hpp>
#include <cbear.berlios.de/com/object.hpp>

namespace cbear_berlios_de
{
namespace com
{

namespace detail
{

class base
{
public:

	virtual ~base() {}

	template<class Interface>
	void add(Interface *P)
	{
		uuid Uuid = uuid::of<Interface>();
		if(this->Map.find(Uuid)!=this->Map.end()) return;
		this->Map[Uuid] = P;
	}

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

	typedef atomic::wrap<ULONG> counter_type;
	typedef counter_type::type counter_internal_type;

	counter_internal_type add_ref() 
	{ 
		return this->Counter.increment(); 
	}

	counter_internal_type release() 
	{ 
		counter_internal_type Result = this->Counter.decrement();
		if(!Result) delete this;
		return Result;
	}

private:
	counter_type Counter;		

	typedef std::map<uuid, iunknown::internal_type> map_type;
	map_type Map;
};

}

class dynamic_base: public virtual detail::base {};

template<class Interface, class Part = Interface>
class dynamic_adapter: public dynamic_base, public Interface
{
};

template<class Interface, class Part, class Parent>
class dynamic_adapter_base: public dynamic_adapter<Interface, Parent>
{
protected:
	dynamic_adapter_base() { ((detail::base *)this)->add<Part>(this); }
};

template<class Interface>
class dynamic_adapter<Interface, iunknown::internal_type>:
	public dynamic_adapter_base<Interface, iunknown::internal_type, void>
{
};

}
}

#endif
