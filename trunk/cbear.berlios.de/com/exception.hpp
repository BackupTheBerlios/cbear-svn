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
#ifndef CBEAR_BERLIOS_DE_COM_EXCEPTION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_COM_EXCEPTION_HPP_INCLUDED

#include <cbear.berlios.de/base/exception.hpp>
#include <cbear.berlios.de/com/hresult.hpp>

namespace cbear_berlios_de
{
namespace com
{

class exception: public base::exception
{
public:
	exception(hresult Value): Value(Value) {}
	void what(::std::ostream &OStream) const
	{
		OStream << "cbear_berlios_de::com::exception { result() = " << 
			this->result() << "; };";
	}
	hresult result() const throw() { return this->Value; }
	static void throw_unless(hresult Value)
	{
		if(Value.failed()) throw exception(Value);
	}
	static void throw_unless(::HRESULT Value)
	{
		throw_unless(hresult(Value));
	}
	static hresult catch_()
	{
		try
		{
			try
			{
				throw;				
			}
			catch(const com::exception &E)
			{
				return hresult::e_fail;
			}
			catch(const base::exception &E)
			{
				return hresult::e_fail;
			}
			catch(const ::std::exception &E)
			{
				return hresult::e_fail;
			}
		}
		catch(...)
		{
			return hresult::e_fail;
		}
	}
private:
	hresult Value;
};

}
}

#endif
