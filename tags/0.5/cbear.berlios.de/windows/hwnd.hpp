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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_HWND_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_HWND_HPP_INCLUDED

#include <windows.h>

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/exception.hpp>

namespace cbear_berlios_de
{
namespace windows
{

typedef ::HMENU hmenu;
typedef ::HINSTANCE hinstance;

template<class Char>
class basic_wndclass: public policy::wrap<
	basic_wndclass<Char>, 
	typename CBEAR_BERLIOS_DE_WINDOWS_TYPE(Char, ::WNDCLASS)>
{
public:

	basic_wndclass()
	{
		internal_type &I = this->internal();
		I.style = 0;
		I.lpfnWndProc = 0;
		I.cbClsExtra = 0;
		I.cbWndExtra = 0;
		I.hInstance = 0;
		I.hIcon = 0;
		I.hCursor = 0;
		I.hbrBackground = 0;
		I.lpszMenuName = 0;
		I.lpszClassName = 0;
	}

	class style: public policy::wrap<style, uint_t>
	{
	public:
		enum enum_
		{
			bytealignclient = CS_BYTEALIGNCLIENT,
			bytealignwindow = CS_BYTEALIGNWINDOW,
			classdc = CS_CLASSDC,
			dblclk = CS_DBLCLK,
			dropshadow = CS_DROPSHADOW,
			globalclass = CS_GLOBALCLASS,
			hredraw = CS_HREDRAW,
			noclose = CS_NOCLOSE,
			owndc = CS_OWNDC,
			parentdc = CS_PARENTDC,
			savebits = CS_SAVEBITS,
			vredraw = CS_VREDRAW,
		};

		style() {}
		style(enum_ E): wrap(E) {}
	};

	style &Style() { return style::wrap_ref(this->internal().style); }
	const style &Style() const { return style::wrap_ref(this->internal().style); }


	typedef basic_lpstr<const Char> lpcstr;

	lpcstr &ClassName() 
	{ 
		return lpcstr::wrap_ref(this->internal().lpszClassName); 
	}

	const lpcstr &ClassName() const
	{ 
		return lpcstr::wrap_ref(this->internal().lpszClassName); 
	}

	::WNDPROC &WndProc() { return this->internal().lpfnWndProc; }
	const ::WNDPROC &WndProc() const { return this->internal().lpfnWndProc; }

	hinstance &Instance() { return this->internal().hInstance; }
	const hinstance &Instance() const { return this->internal().hInstance; }
};

class atom: public policy::wrap<atom, ::ATOM>
{
public:
	~atom() { this->Unregister(); }

	template<class Char>
	basic_lpstr<const Char> Id() const
	{
		return reinterpret_cast<const Char *>(this->internal());
	}

	void Unregister()
	{
		if(!this->internal()) return;
		{
			exception::scope_last_error ScopeLastError;
			::UnregisterClassW(this->Id<wchar_t>().internal(), 0);
		}
		this->internal() = 0;
	}

	template<class Char>
	void Register(const basic_wndclass<Char> &WndClass)
	{
		this->Unregister();
		{
			exception::scope_last_error ScopeLastError;
			this->internal() = ::RegisterClass(&WndClass.internal());
			// to fix MS design bug.
			if(this->internal()) ::SetLastError(0);
		}
	}
};

class hwnd: 
	public policy::wrap<hwnd, ::HWND>,
	boost::noncopyable
{
public:
	typedef policy::wrap<hwnd, ::HWND> wrap_type;
	typedef wrap_type::internal_type internal_type;

	hwnd() {}
	// explicit hwnd(internal_type X): wrap_type(X) {}

	~hwnd() { this->Destroy(); }

	void Destroy()
	{
		if(!this->internal()) return;
		{
			exception::scope_last_error ScopeLastError;
			::DestroyWindow(this->internal());
		}
		this->internal() = 0;
	}

	class style: public policy::wrap<style, dword_t>
	{
	public:

		typedef policy::wrap<style, dword_t> wrap;

		enum enum_
		{
			border = WS_BORDER,
			caption = WS_CAPTION,
			child = WS_CHILD,
			childwindow = WS_CHILDWINDOW,
			clipchildren = WS_CLIPCHILDREN,
			clipsiblings = WS_CLIPSIBLINGS,
			disabled = WS_DISABLED,
			dlgframe = WS_DLGFRAME,
			group = WS_GROUP,
			hscroll = WS_HSCROLL,
			iconic = WS_ICONIC,
			maximize = WS_MAXIMIZE,
			maximizebox = WS_MAXIMIZEBOX,
			minimize = WS_MINIMIZE,
			minimizebox = WS_MINIMIZEBOX,
			overlapped = WS_OVERLAPPED,
			overlappedwindow = WS_OVERLAPPEDWINDOW,
			sizebox = WS_SIZEBOX,
			sysmenu = WS_SYSMENU,
			tabstop = WS_TABSTOP,
			thickframe = WS_THICKFRAME,
			visible = WS_VISIBLE,
			vscroll = WS_VSCROLL,
		};

		style() {}
		style(enum_ E): wrap(E) {}
	};

	class ex_style: public policy::wrap<ex_style, dword_t>
	{
	public:
		typedef policy::wrap<ex_style, dword_t> wrap;

		enum enum_
		{
			acceptfiles = WS_EX_ACCEPTFILES,
			appwindow = WS_EX_APPWINDOW,
			clientedge = WS_EX_CLIENTEDGE,
			// Windows XP
			// composited = WS_EX_COMPOSITED,
			contexthelp = WS_EX_CONTEXTHELP,
			controlparent = WS_EX_CONTROLPARENT,
			dlgmodalframe = WS_EX_DLGMODALFRAME,
			layered = WS_EX_LAYERED,
			layoutrtl = WS_EX_LAYOUTRTL,
			left = WS_EX_LEFT,
			leftscrollbar = WS_EX_LEFTSCROLLBAR,
			ltrreading = WS_EX_LTRREADING,
			mdichild = WS_EX_MDICHILD,
			noactive = WS_EX_NOACTIVATE,
			noinheritlayout = WS_EX_NOINHERITLAYOUT,
			noparentnotify = WS_EX_NOPARENTNOTIFY,
			overlappedwindow = WS_EX_OVERLAPPEDWINDOW,
			palettewindow = WS_EX_PALETTEWINDOW,
			right = WS_EX_RIGHT,
			rightscrollbar = WS_EX_RIGHTSCROLLBAR,
			rtlreading = WS_EX_RTLREADING,
			staticedge = WS_EX_STATICEDGE,
			toolwindow = WS_EX_TOOLWINDOW,
			topmost = WS_EX_TOPMOST,
			transparent = WS_EX_TRANSPARENT,
		};

		ex_style() {}
		ex_style(enum_ E): wrap(E) {}
	};

	class create_exception: public std::exception
	{
	public:
		const char *what() const throw()
		{ 
			return "cbear_berlios_de::windows::hwnd::create_exception";
		}
	};

	template<class Char>
	void Create(
		const ex_style &ExStyle,
		const basic_lpstr<const Char> &ClassName,
		const basic_lpstr<const Char> &WindowName,
		const style &Style,
		int X,
		int Y,
		int Width,
		int Height,
		const hwnd &Parent,
		const hmenu &Menu,
		const hinstance &Instance,
		void *Param)
	{
		this->Destroy();
		{
			exception::scope_last_error ScopeLastError;
			this->internal() = CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(
				Char, ::CreateWindowEx)(
					ExStyle.internal(),
					ClassName.internal(),
					WindowName.internal(),
					Style.internal(),
					X,
					Y,
					Width,
					Height,
					Parent.internal(),
					Menu,
					Instance,
					Param);
		}
		// to fix MS design bug.
		if(!this->internal()) throw create_exception();
	}
};

}
}

#endif
