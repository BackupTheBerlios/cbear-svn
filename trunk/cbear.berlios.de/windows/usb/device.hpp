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
#include <boost/array.hpp>

extern "C"
{
#include <usbioctl.h>
}

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

typedef ioctl::const_<IOCTL_USB_GET_NODE_INFORMATION> get_node_information;

typedef ioctl::const_<IOCTL_USB_GET_NODE_CONNECTION_INFORMATION> 
	get_node_connection_information;

typedef ioctl::const_<IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME> 
	get_node_connection_driverkey_name;

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

typedef ioctl::const_<IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION>
	get_descriptor_from_node_connection;

/*
class descriptor_request:
	public dynamic< ::USB_DESCRIPTOR_REQUEST>
{
public:

	typedef dynamic< ::USB_DESCRIPTOR_REQUEST> wrap;
};
*/

template<int Type, std::size_t Length>
class descriptor_request:
	private boost::array<byte_t, sizeof(::USB_DESCRIPTOR_REQUEST) + Length>
{
public:
	typedef boost::array<byte_t, sizeof(::USB_DESCRIPTOR_REQUEST) + Length> 
		array_t;
	typedef ::USB_DESCRIPTOR_REQUEST c_t;
	typedef const c_t c_in_t;
	typedef c_t *c_in_out_t;
	typedef range::iterator_range<byte_t *> range_t;
	explicit descriptor_request(
		ulong_t ConnectionIndex, byte_t Index, word_t LanguageId = 0)
	{
		range::fill(base::const_ref(this->range()), 0);
		c_in_out_t C = this->c_in_out();
		C->ConnectionIndex = ConnectionIndex;
		C->SetupPacket.wValue = (Type << 8) | Index;
		C->SetupPacket.wLength = Length;
		C->SetupPacket.wIndex = LanguageId;
	}
	range_t range()
	{
		return range_t(static_cast<array_t &>(*this));
	}
	c_in_t &c_in() const
	{
		return *reinterpret_cast<c_in_t *>(this->array_t::begin());
	}
	c_in_out_t c_in_out()
	{
		return reinterpret_cast<c_in_out_t>(this->array_t::begin());
	}
	byte_t *buffer_begin()
	{
		return this->array_t::begin() + (sizeof(::USB_DESCRIPTOR_REQUEST));
	}
};

namespace detail
{
typedef descriptor_request<
	USB_STRING_DESCRIPTOR_TYPE, MAXIMUM_USB_STRING_LENGTH>
	string_descriptor_request_base;
}

class string_descriptor: private ::USB_STRING_DESCRIPTOR
{
public:
	typedef ::USB_STRING_DESCRIPTOR c_t;
	typedef range::iterator_range<wchar_t *> string_t;
	string_t bString()
	{
		return string_t(
			this->c_t::bString,
			(sizeof(c_t::bString) + (this->bLength - sizeof(c_t))) / sizeof(wchar_t));
	}
};

class string_descriptor_request: public detail::string_descriptor_request_base
{
public:
	explicit string_descriptor_request(
		ulong_t ConnectionIndex, byte_t Index, word_t LanguageId = 0):
		detail::string_descriptor_request_base(ConnectionIndex, Index, LanguageId)
	{
	}
	string_descriptor &descriptor()
	{
		return *reinterpret_cast<string_descriptor *>(this->buffer_begin());
	}
};

}
}
}

#endif
