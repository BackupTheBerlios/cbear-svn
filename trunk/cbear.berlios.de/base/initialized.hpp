#ifndef CBEAR_BERLIOS_DE_BASE_INITIALIZED_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_INITIALIZED_HPP_INCLUDED

#include <cbear.berlios.de/base/swap.hpp>

namespace cbear_berlios_de
{
namespace base
{

template<class T>
class initialized
{
public:

	typedef T value_t;

	initialized(): V() {}

	explicit initialized(const T &V): V(V) {}

	T &get() throw() { return this->V; }
	const T &get() const throw() { return this->V; }

	T &operator*() throw() { return this->V; }
	const T &operator*() const throw() { return this->V; }

	void swap(initialized &X)
	{
		base::swap(this->V, X.V);
	}

private:
	T V;
};

}
}

#endif
