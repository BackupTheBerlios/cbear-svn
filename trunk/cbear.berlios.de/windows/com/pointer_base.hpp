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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_POINTER_BASE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_POINTER_BASE_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class uninitialized {};

template<class I>
class pointer_base
{
protected:

	pointer_base() throw():
		P(0) 
	{
	}

	pointer_base(const pointer_base &O1) throw()
  {
    this->constructor(O1.P);
  }

	template<class I1>
	pointer_base(const pointer_base<I1> &O1) throw()
	{
		this->constructor(O1.P);
	}

  ~pointer_base()
  {
    this->destructor();
  }

	void reset() throw()
	{
		this->destructor();
		this->constructor();
	}

	template<class I1>
	void assign(const pointer_base<I1> &O1) throw()
	{
		this->assign(O1.c_in_cast());
	}

  pointer_base &operator=(const pointer_base &O1) throw()
  {
    this->assign(O1);
		return *this;
  }

  void swap(pointer_base &O1) throw()
  {
    I *const PT = this->P;
    this->P = O1.P;
    O1.P = PT;
  }

public:

	typedef I *c_in_t;
	typedef I **c_out_t;
	typedef I **c_in_out_t;

	c_in_t c_in_cast() const throw()
	{
		return this->P;
	}

	c_out_t c_out_cast() throw()
	{
		this->reset();
		return &this->P;
	}

	c_in_out_t c_in_out_cast() throw()
	{
		return &this->P;
	}

public:

	I &reference() const throw(uninitialized)
	{
		if(this->P) 
		{
			return *this->P;
		}
		else
		{
			throw uninitialized();
		}
	}

	I &operator*() const throw(uninitialized)
	{
		return this->reference();
	}

	I *operator->() const throw(uninitialized)
	{
		return &this->reference();
	}

// deprecated
public: 

	I &internal_reference() const throw(uninitialized)
	{
		return this->reference();
	}

private:

  I *P;

	void constructor() throw()
	{
		this->P = 0;
	}

	template<class I1>
  void constructor(I1 *P1) throw()
  {
    this->P = P1;
    if(this->P) this->P->AddRef();
  }

  void destructor() throw()
  {
    if(!this->P) return;
    this->P->Release();
  }

	template<class I1>
	void assign(I1 *P1) throw()
	{
		this->destructor();
		this->constructor(P1);
	}
};

}
}
}

#endif
