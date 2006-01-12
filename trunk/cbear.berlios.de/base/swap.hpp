#ifndef CBEAR_BERLIOS_DE_BASE_SWAP_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_SWAP_HPP_INCLUDED

#include <algorithm>
#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>

namespace cbear_berlios_de
{
namespace base
{

namespace detail
{

class class_swap_traits
{
public:
	template<class T>
	static void swap(T &A, T &B) { A.swap(B); }
};

class std_swap_traits
{
public:
	template<class T>
	static void swap(T &A, T &B) { std::swap(A, B); }
};

}

template<class T>
void swap(T &A, T &B) 
{ 
	boost::mpl::if_<
		boost::is_class<T>, detail::class_swap_traits, detail::std_swap_traits>::
		type::swap(A, B);
}

template<class T>
class move_t
{
public:

	move_t() {}

	explicit move_t(T &B) { base::swap(this->A, B); }
	move_t(const move_t &B) { base::swap(this->A, B.A); }

	move_t &operator=(const move_t &B) { base::swap(this->A, B.A); return *this; }

	void swap(T &B) const { base::swap(this->A, B); }

	friend void swap(const move_t &A, T &B) { base::swap(A.A, B); }
	friend void swap(T &A, const move_t &B) { base::swap(A, B.A); }

	T &get() const { return this->A; }
	T &operator*() const { return this->A; }
	T *operator->() const { return &this->A; }

private:
	mutable T A;
};

template<class T>
move_t<T> move(T &B) { return move_t<T>(B); }

template<class T>
move_t<T> move_copy(const T &B) { T Copy(B); return move_t<T>(Copy); }

}
}

#endif
