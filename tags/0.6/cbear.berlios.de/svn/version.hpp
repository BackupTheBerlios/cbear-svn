/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
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

