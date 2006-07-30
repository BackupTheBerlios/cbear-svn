#ifndef CBEAR_BERLIOS_DE_WINDOWS_BOOL_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_BOOL_HPP_INCLUDED

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/policy/main.hpp>

namespace cbear_berlios_de
{
namespace windows
{

// Boolean variable (should be TRUE or FALSE).
class bool_t: public base::initialized< ::BOOL>
{
private:

	typedef base::initialized< ::BOOL> base_t;

public:

	bool_t()
	{
	}

	bool_t(bool X):
		base_t(X ? TRUE: FALSE)
	{
	}

	explicit bool_t(::BOOL X):
		base_t(X)
	{
	}

	operator bool() const throw()
	{ 
		return this->get() != FALSE; 
	}
};

}
}

#endif
