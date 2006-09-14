#ifndef CBEAR_BERLIOS_DE_WINDOWS_COMMAND_LINE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COMMAND_LINE_HPP_INCLUDED

#include <cbear.berlios.de/windows/lpstr.hpp>
#include <cbear.berlios.de/windows/select.hpp>

namespace cbear_berlios_de
{
namespace windows
{

template<class Char>
basic_lpstr<Char> command_line()
{
	return make_lpstr(CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(
		Char, ::GetCommandLine)());
}

}
}

#endif
