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

#include <cbear.sourceforge.net/com/dynamic_adapter.hpp>

#include <boost/test/minimal.hpp>

namespace Com = cbear_sourceforge_net::com;

//

class My_IA: public ::IUnknown
{
public:
	virtual ::HRESULT A() = 0;
};

class My_IB: public ::IUnknown
{
public:
	virtual ::HRESULT B() = 0;
};

//

namespace cbear_sourceforge_net
{
namespace com
{

template<class Interface>
class dynamic_adapter<Interface, My_IA>: 
	public dynamic_adapter_base<Interface, My_IA, Com::iunknown::interface_type>
{
public:
	virtual void My_IA_A() = 0;	
	Com::hresult::internal_type A()
	{
		try
		{
			this->My_IA_A();
		}
		catch(...)
		{
			return Com::hresult::e_fail;
		}
	}
};

template<class Interface>
class dynamic_adapter<Interface, My_IB>: 
	public dynamic_adapter_base<Interface, My_IB, Com::iunknown::interface_type>
{
public:
	virtual void My_IB_B() = 0;	
	Com::hresult::internal_type B()
	{
		try
		{
			this->My_IB_B();
		}
		catch(...)
		{
			return Com::hresult::e_fail;
		}
	}
};

}
}

// object

namespace My
{

typedef Com::object< ::My_IA> IA;
typedef Com::object< ::My_IB> IB;

}

int test_main(int, char *[])
{
	return 0;
}
