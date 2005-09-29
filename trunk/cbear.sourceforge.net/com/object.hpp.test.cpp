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

#include <cbear.sourceforge.net/com/object.hpp>

#include <boost/test/minimal.hpp>

namespace Com = cbear_sourceforge_net::com;

template<class T>
class MyBase: public T //Com::iunknown::interface_type
{
public:
	MyBase(): L(0) {}
	::HRESULT __stdcall QueryInterface(
		const Com::uuid::internal_type &I, void **PP)
	{     
		if(I!=
			Com::uuid::of<Com::iunknown::interface_type>().internal())
		{ 
			*PP = 0;
			return E_NOINTERFACE;
		}
		Com::iunknown::internal_policy::construct_copy(
			*reinterpret_cast<Com::iunknown::internal_type*>(PP), this);
		return S_OK;
	}	
	::ULONG __stdcall AddRef() 
	{ 
		return ++(this->L); 
	}
	::ULONG __stdcall Release()
	{
		::ULONG Result = --(this->L); 
		if(Result==0) delete this; 
		return Result;
	}
private:
	::ULONG L;
};

class My_IDMy: public IUnknown
{
public:
	virtual ::HRESULT A(/*result out*/int *P) = 0;
};

class My_IDMy2: public My_IDMy
{
};

static const UUID IID_My_IDMy =
{
	0x01234567, 
	0x89AB, 
	0xCDEF, 
	{ 0x01, 0x23, 0x34, 0x56, 0x67, 0x78, 0x9A, 0xBC }
};

static const UUID IID_My_IDMy2 =
{ 
	0x01234567, 
	0x89AB, 
	0xCDEF, 
	{ 0x01, 0x23, 0x34, 0x56, 0x67, 0x78, 0x9A, 0xBD } 
};

//

NET_SOURCEFORGE_CBEAR_COM_UUID_DECLARE(My_IDMy);
NET_SOURCEFORGE_CBEAR_COM_UUID_DECLARE(My_IDMy2);

namespace net
{
namespace sourceforge
{
namespace cbear
{
namespace com
{

template<class Base>
class object_contetn< ::My_IDMy, Base>: public object_contetn< ::IUnknown, Base>
{
public:
	int A() const
	{
		int Result;
		::HRESULT HResult = this->internal_this().A(&Result);
		if(HResult!=S_OK) throw "unknown";
		return Result;
	}
};

}
}
}
}

namespace My
{

typedef Com::object< ::My_IDMy> IDMy;
typedef Com::object< ::My_IDMy2> IDMy2;

}

//

class DMy: public MyBase<My::IDMy::interface_type>
{
public:
	virtual ::HRESULT A(int *P) { *P = 2005; return S_OK; }
};

int test_main(int, char *[])
{
	/*
	BOOST_CHECK(Com::traits<Com::object< ::IUnknown> >::variant_type_id==::VT_UNKNOWN);
	BOOST_CHECK(Com::traits<Com::object< ::IDispatch> >::variant_type_id==::VT_DISPATCH);
	BOOST_CHECK(Com::traits<Com::object<IMy> >::variant_type_id==::VT_UNKNOWN);
	BOOST_CHECK(Com::traits<Com::object<IDMy> >::variant_type_id==::VT_DISPATCH);
	BOOST_CHECK(Com::traits<Com::object<IDMy2> >::variant_type_id==::VT_DISPATCH);
	*/

	Com::iunknown P;
	BOOST_CHECK(P.QueryInterface<My_IDMy>()==My::IDMy());

	Com::iunknown P1(new MyBase<Com::iunknown::interface_type>());
	BOOST_CHECK(P1.QueryInterface<IUnknown>()!=Com::iunknown());

	My::IDMy my(new DMy());
	BOOST_CHECK(my.A()==2005);
	return 0;
}
