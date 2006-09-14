#ifndef CBEAR_BERLIOS_DE_WINDOWS_MSG_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_MSG_HPP_INCLUDED

#include <cbear.berlios.de/windows/bool.hpp>
#include <cbear.berlios.de/windows/select.hpp>
#include <cbear.berlios.de/windows/hwnd.hpp>

namespace cbear_berlios_de
{
namespace windows
{

class msg;

namespace detail
{

typedef policy::wrap<msg, ::MSG> msg_wrap;

}

class msg: public detail::msg_wrap
{
public:
	msg() {}
	explicit msg(const internal_type &X): detail::msg_wrap(X) {}

	template<class Char>
	bool_t get(const hwnd &Wnd, uint_t FilterMin, uint_t FilterMax)
	{
		exception::scope_last_error ScopeLastError;
		return bool_t(CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::GetMessage)(
			&this->internal(), Wnd.get(), FilterMin, FilterMax));
	}

	bool_t translate() const
	{
		return bool_t(::TranslateMessage(&this->internal()));
	}

	lresult_t dispatch() const
	{
		return ::DispatchMessage(&this->internal());
	}

	template<class Char>
	static void loop(const hwnd &Wnd, uint_t FilterMin, uint_t FilterMax)
	{
		msg This;
		while(This.get<Char>(Wnd, FilterMin, FilterMax))
		{
			This.translate();
			This.dispatch();
		}
	}
};

}
}

#endif
