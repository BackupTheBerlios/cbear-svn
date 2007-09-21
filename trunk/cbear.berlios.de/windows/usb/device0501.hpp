#ifndef CBEAR_BERLIOS_DE_WINDOWS_USB_DEVICE0501_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_USB_DEVICE0501_HPP_INCLUDED

#include <cbear.berlios.de/windows/usb/device.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace usb
{

// _WIN32_WINNT >= 0x0501

typedef ::USB_NODE_CONNECTION_INFORMATION_EX node_connection_information_ex;

typedef ioctl::const_<IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX>
	get_node_connection_information_ex;

}
}
}

#endif
