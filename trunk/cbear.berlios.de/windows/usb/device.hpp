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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_USB_DEVICE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_USB_DEVICE_HPP_INCLUDED

#include <cbear.berlios.de/windows/dynamic.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace usb
{

inline const com::uuid &device_uuid()
{
	static const com::uuid Result(
		0xA5DCBF10L, 
		0x6530, 
		0x11D2, 
		0x90, 
		0x1F, 
		0x00, 
		0xC0, 
		0x4F, 
		0xB9, 
		0x51, 
		0xED);
	return Result;
}

inline const com::uuid &hub_uuid()
{
	static const com::uuid Result(
		0xf18a0e88, 
		0xc30c, 
		0x11d0, 
		0x88, 
		0x15, 
		0x00,
    0xa0, 
		0xc9, 
		0x06, 
		0xbe, 
		0xd8);
	return Result;
}

inline const com::uuid &host_controller_uuid()
{
	static const com::uuid Result(
		0x3abf6f2d, 
		0x71c4, 
		0x462a, 
		0x8a, 
		0x92, 
		0x1e,
		0x68, 
		0x61, 
		0xe6, 
		0xaf, 
		0x27);
	return Result;
}

typedef ::USB_NODE_INFORMATION node_information;

typedef ::USB_NODE_CONNECTION_INFORMATION node_connection_information;

/*
typedef ::USB_NODE_CONNECTION_INFORMATION_EX node_connection_information_ex;
*/

class node_connection_driverkey_name: 
	public dynamic< ::USB_NODE_CONNECTION_DRIVERKEY_NAME>
{
public:

	typedef dynamic< ::USB_NODE_CONNECTION_DRIVERKEY_NAME> wrap;

	range::iterator_range<wchar_t *> DriverKeyName()
	{
		static const int remainder_size = 
			sizeof(internal_type) - sizeof(this->internal().DriverKeyName);
		// Ask Microsoft about this constant.
		static const int magic_size_correction = - 1;
		return range::iterator_range<wchar_t *>(
			this->internal().DriverKeyName,
			(this->wrap::size() - remainder_size) / sizeof(wchar_t) - 
				1 + magic_size_correction);
	}
};

// typedef ::USB_NODE_CONNECTION_DRIVERKEY_NAME node_connection_driverkey_name;

}
}
}

#endif
