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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_MUTEX_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_MUTEX_HPP_INCLUDED

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/bool.hpp>
#include <cbear.berlios.de/windows/exception.hpp>
#include <cbear.berlios.de/windows/select.hpp>
#include <cbear.berlios.de/windows/handle.hpp>
#include <cbear.berlios.de/windows/lpstr.hpp>
#include <cbear.berlios.de/windows/security_attributes.hpp>

namespace cbear_berlios_de
{
namespace windows
{

// The function creates or opens a named or unnamed mutex object.
template<class Char>
handle create_mutex(
	security_attributes MutexAttributes, 
	bool_t InitialOwner,
	const basic_lpstr<const Char> &Name)
{
	exception::scope_last_error ScopeLastError;
	return handle(CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::CreateMutex)(
		MutexAttributes.get(), InitialOwner.get(), Name.get()));
}

}
}

#endif
