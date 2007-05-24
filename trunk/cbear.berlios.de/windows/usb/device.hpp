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

inline com::uuid const &device_uuid()
{
	static com::uuid const Result(
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

inline com::uuid const &hub_uuid()
{
	static com::uuid const Result(
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

inline com::uuid const &host_controller_uuid()
{
	static com::uuid const Result(
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

namespace detail
{

static const std::size_t descriptor_request_length = MAXIMUM_USB_STRING_LENGTH;

typedef boost::array<
	byte_t, sizeof(::USB_DESCRIPTOR_REQUEST) + descriptor_request_length>
	descriptor_request_array;

template<class Char>
class descriptor_request: private descriptor_request_array
{
public:
	static const int type = USB_STRING_DESCRIPTOR_TYPE;
	typedef descriptor_request_array array_t;
	typedef ::USB_DESCRIPTOR_REQUEST c_t;
	typedef const c_t c_in_t;
	typedef c_t *c_in_out_t;
	typedef range::iterator_range<byte_t *> range_t;

	class descriptor_t: private ::USB_STRING_DESCRIPTOR
	{
	public:
		typedef ::USB_STRING_DESCRIPTOR c_t;
		typedef range::iterator_range<Char *> range_t;
		range_t bString()
		{
			return range_t(
				cast::traits<Char *>::reinterpret(this->c_t::bString),
				this->bLength < sizeof(c_t) ? 
					0: 
					(this->bLength - (sizeof(c_t) - sizeof(c_t::bString))) / 
						sizeof(Char));
		}
	};

	explicit descriptor_request(
		ulong_t ConnectionIndex, byte_t Index, word_t LanguageId = 0)
	{
		range::fill(base::const_ref(this->range()), 0);
		c_in_out_t C = this->c_in_out();
		C->ConnectionIndex = ConnectionIndex;
		C->SetupPacket.wValue = (type << 8) | Index;
		C->SetupPacket.wLength = descriptor_request_length;
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

	descriptor_t &descriptor()
	{
		return *reinterpret_cast<descriptor_t *>(this->buffer_begin());
	}
};

}

class language_list_descriptor_request: 
	public detail::descriptor_request<ushort_t>
{
public:
	explicit language_list_descriptor_request(ulong_t ConnectionIndex):
		detail::descriptor_request<ushort_t>(ConnectionIndex, 0, 0)
	{
	}
};

class string_descriptor_request: public detail::descriptor_request<wchar_t>
{
public:
	explicit string_descriptor_request(
		ulong_t ConnectionIndex, byte_t Index, word_t LanguageId):
		detail::descriptor_request<wchar_t>(ConnectionIndex, Index, LanguageId)
	{
	}
};

}
}
}

#endif
