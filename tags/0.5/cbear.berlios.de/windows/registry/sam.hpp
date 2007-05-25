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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_SAM_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_SAM_HPP_INCLUDED

#include <cbear.berlios.de/policy/main.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

class sam: public policy::wrap<sam, ::REGSAM>
{
	typedef policy::wrap<sam, ::REGSAM> wrap_type;
public:
	enum enumeration_type
	{
		all_access = KEY_ALL_ACCESS,
		create_link = KEY_CREATE_LINK,
		create_sub_key = KEY_CREATE_SUB_KEY,
		enumerate_sub_keys = KEY_ENUMERATE_SUB_KEYS,
		execute = KEY_EXECUTE,
		notify = KEY_NOTIFY,
		query_value = KEY_QUERY_VALUE,
		read = KEY_READ,
		set_value = KEY_SET_VALUE,
		//wow64_32key = KEY_WOW64_32KEY,
		//wow64_64key = KEY_WOW64_64KEY,
		write = KEY_WRITE,
		
	};
	sam(enumeration_type X = all_access): wrap_type(X) {}
};

}
}
}

#endif
