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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_OPTIONS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_OPTIONS_HPP_INCLUDED

#include <cbear.berlios.de/windows/base.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

class options: public policy::wrap<options, ::DWORD>
{
	typedef policy::wrap<options, ::DWORD> wrap_type;
public:
	enum enumeration_type
	{
		reserved = REG_OPTION_RESERVED,
		non_volatile = REG_OPTION_NON_VOLATILE,
		volatile_all = REG_OPTION_VOLATILE,
		create_link = REG_OPTION_CREATE_LINK,
		backup_restore = REG_OPTION_BACKUP_RESTORE,
		open_link = REG_OPTION_OPEN_LINK,

		legal = REG_LEGAL_OPTION,
	};
	options() {}
	options(enumeration_type X): wrap_type(X) {}
};

}
}
}

#endif
