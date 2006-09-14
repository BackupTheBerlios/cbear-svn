#ifndef CBEAR_BERLIOS_DE_WINDOWS_SECURITY_ATTRIBUTES_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_SECURITY_ATTRIBUTES_HPP_INCLUDED

#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/windows/base.hpp>

namespace cbear_berlios_de
{
namespace windows
{

// Security descriptor.
class security_attributes: 
	public base::initialized< ::SECURITY_ATTRIBUTES *>
{
public:
	typedef base::initialized< ::SECURITY_ATTRIBUTES *> base_t;
	security_attributes() {}
	explicit security_attributes(value_t X): base_t(X) {}
};

}
}

#endif
