#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_POINTER_LOCK_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_POINTER_LOCK_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

template<class T>
class pointer_lock: public T::scoped_lock
{
public:

	typedef typename T::scoped_lock scoped_lock_t;

	pointer_lock(T *P):
		scoped_lock_t(*P),
		P(P)
	{
	}

	T *operator->() const throw()
	{
		return this->P;
	}

	T &operator*() const throw()
	{
		return *this->P;
	}

private:
	T *P;
};

}
}
}
}

#endif
