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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_OVERLAPPED_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_OVERLAPPED_HPP_INCLUDED

// VC: winnt.h.
#include <windows.h>
// MINGW: winnt.h: CONST
#include <windef.h>
// MINGW: psapi.h: LPVOID
#include <winnt.h>
// DMC: psapi.h: SIZE_T
#include <basetsd.h>
#include <psapi.h>

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/exception.hpp>

namespace cbear_berlios_de
{
namespace windows
{

/*
class overlapped: public policy::wrap<overlapped, ::OVERLAPPED>
{
};
*/

typedef base::initialized< ::OVERLAPPED> overlapped;

}
}

#endif
