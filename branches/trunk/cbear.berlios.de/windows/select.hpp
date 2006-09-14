#ifndef CBEAR_BERLIOS_DE_WINDOWS_SELECT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_SELECT_HPP_INCLUDED

#include <cbear.berlios.de/select/traits.hpp>

#define CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, Name) \
	::cbear_berlios_de::select::get<Char>(&Name ## A, &Name ## W)

#define CBEAR_BERLIOS_DE_WINDOWS_TYPE(Char, Name) \
	::cbear_berlios_de::select::traits<Char, Name ## A, Name ## W>::type

#endif
