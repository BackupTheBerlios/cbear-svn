#ifndef CBEAR_BERLIOS_DE_BASE_ENUM_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_ENUM_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace base
{

template<class T>
class enum_: public T
{
public:
	typedef typename T::type type;
	typedef typename T::internal internal;
	enum_(type x): 
		x(static_cast<internal>(x))
	{
	}
private:
	internal x;
};

}
}

#endif

