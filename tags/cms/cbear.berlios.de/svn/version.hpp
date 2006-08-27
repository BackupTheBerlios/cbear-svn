#ifndef CBEAR_BERLIOS_DE_SVN_VERSION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_SVN_VERSION_HPP_INCLUDED

#include <cbear.berlios.de/base/safe_reinterpret_cast.hpp>
#include <cbear.berlios.de/base/select.hpp>

#include <svn_version.h>

namespace cbear_berlios_de
{
namespace svn
{

/// Version information. Each library contains a function called
/// svn_<i>libname</i>_version() that returns a pointer to a statically
/// allocated object of this type.
class version_t: public ::svn_version_t
{
public:
	static version_t &make_ref(::svn_version_t &V) 
	{ 
		return base::safe_reinterpret_cast<version_t &>(V);
	}
	static const version_t &make_ref(const ::svn_version_t &V) 
	{ 
		return base::safe_reinterpret_cast<const version_t &>(V);
	}
	template<class OStream>
	void write(OStream &O) const
	{
		typedef typename OStream::value_type char_type;
		O << 
			this->major << CBEAR_BERLIOS_DE_BASE_SELECT(char_type, '.') << 
			this->minor << CBEAR_BERLIOS_DE_BASE_SELECT(char_type, '.') << 
			this->patch /*<<
			this->tag*/;
	}
};

}
}

#endif

