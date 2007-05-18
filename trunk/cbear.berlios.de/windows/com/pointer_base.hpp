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
		this->assign(O1.c_in());
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

	template<class I1>
	void move_assign(pointer_base<I1> &O1) throw()
	{
		this->destructor();
		this->P = O1.P;
		O1.P = 0;
	}

public:

	template<class T1>
	friend class pointer_base;

	typedef I *c_in_t;
	typedef I **c_out_t;
	typedef I **c_in_out_t;

	c_in_t c_in() const throw()
	{
		return this->P;
	}

	c_out_t c_out() throw()
	{
		this->reset();
		return &this->P;
	}

	c_in_out_t c_in_out() throw()
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
    if(this->P) 
		{
			this->P->AddRef();
		}
  }

  void destructor() throw()
  {
    if(this->P) 
		{
			this->P->Release();
		}    
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
