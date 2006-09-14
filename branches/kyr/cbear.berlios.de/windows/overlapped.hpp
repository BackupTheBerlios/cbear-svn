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
