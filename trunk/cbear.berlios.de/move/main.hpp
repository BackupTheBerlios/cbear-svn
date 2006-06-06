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
class t
{
public:

	t() {}

	t(const t &B) { move::assign(this->A, *B); }

	template<class T1>
	t(const t<T1> &B) { move::assign(this->A, *B); }

	explicit t(T &B) { move::assign(this->A, B); }

	const t &operator=(const t &B) const { move::assign(this->A, *B); }

	template<class T1>
	const t &operator=(const t<T1> &B) const { move::assign(this->A, *B); }

	template<class T1>
	void assign(T &B) const { move::assign(this->A, B); }

	template<class T1>
	void assign(const t<T1> &B) const { move::assign(this->A, *B); }

	T &get() const { return this->A; }
	T &operator*() const { return this->A; }
	T *operator->() const { return &this->A; }

private:
	mutable T A;
};

template<class T>
t<T> copy(const T &B) 
{ 
	t<T> C;
	*C = B;
	return C;
}

}
}

#endif
