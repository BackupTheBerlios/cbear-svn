#ifndef CBEAR_BERLIOS_DE_WINDOWS_SPECSTRINGS_H_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_SPECSTRINGS_H_INCLUDED

#ifdef _MSC_VER
#include <specstrings.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MSC_VER

#define __pre
#define __valid
#define __deref
#define __readonly

// __in
#define CBEAR_BERLIOS_DE_WINDOWS_IN __pre __valid __pre __deref __readonly

#endif

#ifdef __cplusplus
}
#endif

#endif
