#ifndef CBEAR_BERLIOS_DE_WINDOWS_THREAD_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_THREAD_HPP_INCLUDED

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/security_attributes.hpp>
#include <cbear.berlios.de/windows/exception.hpp>
#include <cbear.berlios.de/windows/optional_ref.hpp>

namespace cbear_berlios_de
{
namespace windows
{

class thread
{
public:

	thread(): 
		H() 
	{
	}

	~thread()
	{
		this->close();
	}

	void close()
	{
		if(!this->H)
		{
			return;
		}
		{
			exception::scope_last_error S;
			::WaitForSingleObject(this->H, INFINITE);
		}
		{
			exception::scope_last_error S;
			::CloseHandle(this->H);
		}
		this->H = internal_t();
	}

	template<class T>
	dword_t create(
		const security_attributes &Attributes,
		size_t StackSize,
		T &P,
		dword_t Flags)
	{
		this->close();
		exception::scope_last_error S;
		dword_t Id;
		this->H = ::CreateThread(
			Attributes.get(), StackSize, traits<T>::func, &P, Flags, &Id);
		return Id;
	}

private:
	typedef ::HANDLE internal_t;
	internal_t H;

	template<class T>
	class traits
	{
	public:
		static DWORD WINAPI func(LPVOID lpParameter)
		{
			(*reinterpret_cast<T *>(lpParameter))();
			return 0;
		}
	};
};

}
}

#endif
