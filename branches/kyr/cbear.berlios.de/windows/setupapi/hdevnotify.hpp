#ifndef CBEAR_BERLIOS_DE_WINDOWS_SETUPAPI_HDEVNOTIFY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_SETUPAPI_HDEVNOTIFY_HPP_INCLUDED

#include <windows.h>
#include <setupapi.h>

#include <cbear.berlios.de/windows/dbt.h>
#include <cbear.berlios.de/windows/winuser.h>

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/select.hpp>
#include <cbear.berlios.de/windows/handle.hpp>
#include <cbear.berlios.de/windows/com/uuid.hpp>

#include <boost/static_warning.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace setupapi
{

namespace detail
{

template<class T, class I, dword_t Devicetype>
class basic_dev_broadcast: 
	public policy::wrap<basic_dev_broadcast<T, I, Devicetype>, I>
{
public:

	typedef I internal_type;

	basic_dev_broadcast()
	{
		::DEV_BROADCAST_HDR &Header = reinterpret_cast< ::DEV_BROADCAST_HDR &>(
			this->internal());
		Header.dbch_size = sizeof(internal_type);
		Header.dbch_devicetype = Devicetype;
	}
};

}

template<class Char>
class dev_broadcast_deviceinterface: 
	public detail::basic_dev_broadcast<
		dev_broadcast_deviceinterface<Char>,
		typename CBEAR_BERLIOS_DE_WINDOWS_TYPE(
			Char, ::_DEV_BROADCAST_DEVICEINTERFACE_),
		DBT_DEVTYP_DEVICEINTERFACE>
{
public:
	com::uuid &classguid() 
	{ 
		return com::uuid::cpp_in_out(&this->internal().dbcc_classguid); 
	}
	const com::uuid &classguid() const
	{ 
		return com::uuid::wrap_ref(this->internal().dbcc_classguid); 
	}
};

class hdevnotify: 
	public base::initialized< ::HDEVNOTIFY>,
	boost::noncopyable
{
public:

	typedef base::initialized< ::HDEVNOTIFY> wrap;


	class flag: public base::initialized<dword_t>
	{
	public:

		typedef base::initialized<dword_t> wrap;

		enum enum_
		{
			window_handle = DEVICE_NOTIFY_WINDOW_HANDLE,
			service = DEVICE_NOTIFY_SERVICE_HANDLE,
			// all_interface_classes = DEVICE_NOTIFY_ALL_INTERFACE_CLASSES,
		};

		flag() {}
		flag(enum_ E): wrap(E) {}
	};

	~hdevnotify() { this->Unregister(); }

	void Unregister()
	{
		if(!this->get()) return;
		{
			exception::scope_last_error ScopeLastError;
			::UnregisterDeviceNotification(this->get());
		}
		this->get() = 0;
	}

	template<class Char>
	void Register(
		const hwnd &Recipient, 
		dev_broadcast_deviceinterface<Char> &NotificationFilter,
		const flag &Flags)
	{
		this->Unregister();
		exception::scope_last_error ScopeLastError;
		this->get() = CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(
			Char, ::RegisterDeviceNotification)(
				Recipient.get(),
				&NotificationFilter.internal(),
				Flags.get());
	}
};

}
}
}

#endif
