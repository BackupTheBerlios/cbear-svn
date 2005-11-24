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
		::SetLastError(0);
		bool_t Result = bool_t(select<Char>(::GetMessageA, ::GetMessageW)(
			&this->internal(), Wnd.internal(), FilterMin, FilterMax));
		exception::throw_if_last_error();
		return Result;
	}

	template<class Char>
	bool_t translate() const
	{
		return bool_t(::TranslateMessage(&this->internal()));
	}

	template<class Char>
	lresult_t dispatch() const
	{
		return ::DispatchMessage(&this->internal());
	}

	template<class Char>
	void loop(const hwnd &Wnd, uint_t FilterMin, uint_t FilterMax)
	{
		while(this->get<Char>(Wnd, FilterMin, FilterMax))
		{
			this->translate<Char>();
			this->dispatch<Char>();
		}
	}
};

}
}

#endif
