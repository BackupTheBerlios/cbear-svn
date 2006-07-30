#ifndef CBEAR_BERLIOS_DE_BASE_DEFAULT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_DEFAULT_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace base
{

class default_
{
public:
	template<class T>
	operator T() const { return T(); }
};

}
}

#endif
