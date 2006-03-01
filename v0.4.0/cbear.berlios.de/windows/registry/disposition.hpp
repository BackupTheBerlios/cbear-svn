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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_DISPOSITION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_DISPOSITION_HPP_INCLUDED

#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/windows/base.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

class disposition: public policy::wrap<disposition, ::DWORD>
{
	typedef policy::wrap<disposition, ::DWORD> wrap_type;
public:
	enum enumeration_type
	{
		created_new_key = REG_CREATED_NEW_KEY,
		opened_existing_key = REG_OPENED_EXISTING_KEY,
	};
	disposition() {}
	disposition(enumeration_type X): wrap_type(X) {}
};

}
}
}

#endif
