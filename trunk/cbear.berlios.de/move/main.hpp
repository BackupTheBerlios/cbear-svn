#ifndef CBEAR_BERLIOS_DE_MOVE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_MOVE_HPP_INCLUDED

#include <cbear.berlios.de/base/swap.hpp>
#include <cbear.berlios.de/meta/if.hpp>

namespace cbear_berlios_de
{
namespace move
{

class class_traits
{
public:
	template<class To, class From>
	static void assign(To &T, From &F)
	{
		T.move_assign(F);
	}
};

class assign_traits
{
public:
	template<class To, class From>
	static void assign(To &T, From &F)
	{
		T = F;
	}
};

template<class To>
class traits: 
	public meta::if_<boost::is_class<To>, class_traits, assign_traits>::type
{
};

template<class To, class From>
void assign(To &T, From &F)
{
	traits<To>::assign(T, F);
}

template<class T>
class t_base
{
public:
	typedef T &reference;
	typedef T *pointer;
	T &get() const throw()
	{ 
		return this->A; 
	}
protected:
	t_base() {}
	t_base(const t_base &B) 
	{ 
		move::assign(this->A, B.A);
	}
	template<class T1>
	t_base(const t_base<T1> &B) 
	{ 
		move::assign(this->A, B->get()); 
	}
	explicit t_base(T &B) 
	{ 
		move::assign(this->A, B);
	}
private:
	mutable T A;
};

template<class T>
class t_base<T &>
{
public:
	typedef T &reference;
	typedef T *pointer;
	T &get() const 
	{ 
		return this->A; 
	}
protected:
	t_base(T &A): 
		A(A) 
	{
	}
private:
	mutable T &A;
	// anti VC 8.0 warning
	t_base &operator=(const t_base &);
};

template<class T>
class t: public t_base<T>
{
private:

	typedef t_base<T> base_t;

public:

	typedef typename base_t::reference reference;
	typedef typename base_t::pointer pointer;

	t() {}

	template<class T1>
	t(const t<T1> &B):
		base_t(B) 
	{
	}

	explicit t(reference B): 
		base_t(B) 
	{
	}

	const t &operator=(const t &B) const 
	{ 
		move::assign(this->get(), *B); 
	}

	template<class T1>
	const t &operator=(const t<T1> &B) const 
	{ 
		move::assign(this->get(), *B); 
	}

	template<class T1>
	void assign(const t<T1> &B) const 
	{ 
		move::assign(this->get(), *B); 
	}

	template<class T1>
	void assign(T1 &B) const 
	{ 
		move::assign(this->get(), B); 
	}

	using base_t::get;

	reference operator*() const 
	{ 
		return this->get(); 
	}
	pointer operator->() const 
	{ 
		return &this->get();
	}
};

template<class T>
t<T> copy(const T &B) 
{ 
	t<T> C;
	*C = B;
	return C;
}

template<class T>
t<T &> ref(T &B)
{
	return t<T &>(B);
}

}
}

#endif
