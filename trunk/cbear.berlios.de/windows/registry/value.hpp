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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_VALUE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_VALUE_HPP_INCLUDED

#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/windows/base.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

class value
{
public:

	class type: public policy::wrap<type, dword_t>
	{
		typedef policy::wrap<type, dword_t> wrap_type;
	public:
		enum enumeration_type
		{
			// Binary data in any form. 
			binary = REG_BINARY,
			// A 32-bit number. 
			dword = REG_DWORD,
			// A 32-bit number in little-endian format. 
			dword_little_endian = REG_DWORD_LITTLE_ENDIAN,
			// A 32-bit number in big-endian format. 
			dword_big_endian = REG_DWORD_BIG_ENDIAN,
			// Null-terminated string that contains unexpanded references to 
			// environment variables (for example, "%PATH%"). To expand the 
			// environment variable references, use the ExpandEnvironmentStrings
			// function.
			expand_sz = REG_EXPAND_SZ,
			// Reserved for system use. 
			link = REG_LINK,
			// Array of null-terminated strings, terminated by two null characters. 
			multi_sz = REG_MULTI_SZ,
			// No defined value type.
			none = REG_NONE,
			// A 64-bit number. 
			qword = REG_QWORD,
			// A 64-bit number in little-endian format. 
			qword_little_endian = REG_QWORD_LITTLE_ENDIAN,
			// Null-terminated string. It will be a Unicode or ANSI string, depending on
			// whether you use the Unicode or ANSI functions. 
			sz = REG_SZ,
		};
		type(enumeration_type X): wrap_type(X) {}
	};
};

}
}
}

#endif
