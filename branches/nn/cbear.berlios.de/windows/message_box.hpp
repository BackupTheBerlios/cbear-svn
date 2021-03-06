#ifndef CBEAR_BERLIOS_DE_WINDOWS_MESSAGE_BOX_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_MESSAGE_BOX_HPP_INCLUDED

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/lpstr.hpp>
#include <cbear.berlios.de/windows/hwnd.hpp>
#include <cbear.berlios.de/policy/main.hpp>

#pragma comment(lib, "user32.lib")

namespace cbear_berlios_de
{
namespace windows
{

class dialog_box_id: public base::initialized<int>
{
public:
	typedef base::initialized<int> wrap_type;
	enum enumeration_type
	{
		ok = IDOK,
		cancel = IDCANCEL,
		abort = IDABORT,
		retry = IDRETRY,
		ignore = IDIGNORE,
		yes = IDYES,
		no = IDNO,
		close = IDCLOSE,
		help = IDHELP,
#if(WINVER >= 0x0500)
		tryagain = IDTRYAGAIN,
		continue_ = IDCONTINUE,
#endif
	};
	dialog_box_id() {}
	dialog_box_id(enumeration_type X): wrap_type(X) {}
	explicit dialog_box_id(value_t X): wrap_type(X) {}

	bool operator==(const dialog_box_id &X) const
	{
		return this->get()==X.get();
	}
};

class message_box_style: public base::initialized<uint_t>
{
public:
	typedef base::initialized<uint_t> wrap_type;
	enum enumeration_type
	{
		// The message box contains three push buttons: Abort, Retry, and Ignore.
		abort_retry_ignore = MB_ABORTRETRYIGNORE,

#if(WINVER >= 0x0500)
		// Microsoft� Windows� 2000/XP: The message box contains three push buttons:
		// Cancel, Try Again, Continue. Use this message box type instead of 
		// abortretryignore.
		cancel_try_continue = MB_CANCELTRYCONTINUE,
#endif

		// Windows 95/98/Me, Windows NT� 4.0 and later: Adds a Help button to the 
		// message box. When the user clicks the Help button or presses F1, the 
		// system sends a WM_HELP message to the owner.
		help = MB_HELP,

		// The message box contains one push button: OK. This is the default.
		ok = MB_OK,

		// The message box contains two push buttons: OK and Cancel.
		ok_cancel = MB_OKCANCEL,

		// The message box contains two push buttons: Retry and Cancel.	
		retry_cancel = MB_RETRYCANCEL,

		// The message box contains two push buttons: Yes and No.
		yes_no = MB_YESNO,

		// The message box contains three push buttons: Yes, No, and Cancel.
		yes_no_cancel = MB_YESNOCANCEL,

		// An exclamation-point icon appears in the message box.
		icon_exclamation = MB_ICONEXCLAMATION,

		// An exclamation-point icon appears in the message box.
		icon_warning = MB_ICONWARNING,

		// An icon consisting of a lowercase letter i in a circle appears in the 
		// message box.
		icon_information = MB_ICONINFORMATION,

		// An icon consisting of a lowercase letter i in a circle appears in the 
		// message box.
		icon_asterisk = MB_ICONASTERISK,

		// A question-mark icon appears in the message box.
		icon_question = MB_ICONQUESTION,

		// A stop-sign icon appears in the message box.
		icon_stop = MB_ICONSTOP,

		// A stop-sign icon appears in the message box.
		icon_error = MB_ICONERROR,

		// A stop-sign icon appears in the message box.
		icon_hand = MB_ICONHAND,

		// The first button is the default button. 
		def_button1 = MB_DEFBUTTON1,

		// The second button is the default button.
		def_button2 = MB_DEFBUTTON2,

		// The third button is the default button.
		def_button3 = MB_DEFBUTTON3,

		// The fourth button is the default button.
		def_button4 = MB_DEFBUTTON4,

		// The user must respond to the message box before continuing work in the 
		// window identified by the hWnd parameter. However, the user can move to 
		// the windows of other threads and work in those windows. 
		// Depending on the hierarchy of windows in the application, the user may 
		// be able to move to other windows within the thread. All child windows of 
		// the parent of the message box are automatically disabled, but popup 
		// windows are not.
		app_modal = MB_APPLMODAL,

		// Same as MB_APPLMODAL except that the message box has the WS_EX_TOPMOST 
		// style. Use system-modal message boxes to notify the user of serious, 
		// potentially damaging errors that require immediate attention (for 
		// example, running out of memory). This flag has no effect on the user's 
		// ability to interact with windows other than those associated with hWnd.
		system_modal = MB_SYSTEMMODAL,

		// Same as MB_APPLMODAL except that all the top-level windows belonging to 
		// the current thread are disabled if the hWnd parameter is NULL. Use this 
		// flag when the calling application or library does not have a window 
		// handle available but still needs to prevent input to other windows in the
		// calling thread without suspending other threads.
		task_modal = MB_TASKMODAL,

		// - Windows NT/2000/XP: Same as 'service_notification' except that the 
		// system will display the message box only on the default desktop of the 
		// interactive window station. For more information, see Window Stations. 
		// - Windows NT 4.0 and earlier: If the current input desktop is not the 
		// default desktop, MessageBoxEx fails. 
		// - Windows 2000/XP: If the current input desktop is not the default desktop,
		// 'message_box_ex' does not return until the user switches to the default 
		// desktop. 
		// - Windows 95/98/Me: This flag has no effect.
		default_desktop_only = MB_DEFAULT_DESKTOP_ONLY,

		// The text is right-justified.
		right = MB_RIGHT,

		// Displays message and caption text using right-to-left reading order on 
		// Hebrew and Arabic systems.
		rtl_reading = MB_RTLREADING,

		// The message box becomes the foreground window. Internally, the system 
		// calls the SetForegroundWindow function for the message box.
		set_foreground = MB_SETFOREGROUND,

		// The message box is created with the WS_EX_TOPMOST window style.
		top_most = MB_TOPMOST,

#ifdef _WIN32_WINNT
		// - Windows NT/2000/XP: The caller is a service notifying the user of an 
		// event. The function displays a message box on the current active desktop, 
		// even if there is no user logged on to the computer. 
		// - Terminal Services: If the calling thread has an impersonation token, 
		// the function directs the message box to the session specified in the 
		// impersonation token. 
		//   If this flag is set, the hWnd parameter must be NULL. This is so the 
		// message box can appear on a desktop other than the desktop corresponding 
		// to the hWnd.
		// _WIN32_WINNT
		service_notification = MB_SERVICE_NOTIFICATION,

		// Windows NT/2000/XP: This value corresponds to the value defined for 
		// 'service_notification' for Windows NT version 3.51. 
		// _WIN32_WINNT
		service_notification_nt3x = MB_SERVICE_NOTIFICATION_NT3X,
#endif
	};
	message_box_style() {}
	message_box_style(enumeration_type X): wrap_type(X) {}
	explicit message_box_style(value_t X): wrap_type(X) {}
};

template<class Char>
dialog_box_id message_box(
	const hwnd &Wnd, 
	const basic_lpstr<const Char> &Text,
	const basic_lpstr<const Char> &Caption,
	const message_box_style &Type)
{
	exception::scope_last_error ScopeLastError;
	return dialog_box_id(CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, MessageBoxEx)(
		Wnd.get(),
		Text.get(),
		Caption.get(),
		Type.get(),
		0));
}

template<class Char>
dialog_box_id message_box(
	const basic_lpstr<const Char> &Text,
	const basic_lpstr<const Char> &Caption,
	const message_box_style &Type)
{
	return message_box(hwnd(), Text, Caption, Type);
}

}
}

#endif
