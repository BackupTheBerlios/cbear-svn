#ifndef CBEAR_BERLIOS_DE_WINDOWS_THREAD_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_THREAD_HPP_INCLUDED

#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/security_attributes.hpp>
#include <cbear.berlios.de/windows/exception.hpp>
#include <cbear.berlios.de/windows/optional_ref.hpp>

#include <process.h>

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

	typedef dword_t id_t;

	template<class T>
	id_t create(
		const security_attributes &Attributes,
		size_t StackSize,
		T &P,
		dword_t Flags)
	{
		this->close();
		exception::scope_last_error S;
		id_t Id;
		this->H = ::CreateThread(
			Attributes.get(), StackSize, traits<id_t, T>::func, &P, Flags, &Id);
		return Id;
	}

	template<class T>
	id_t begin(
		const security_attributes &Attributes,
		size_t StackSize,
		T &P,
		dword_t Flags)
	{
		this->close();
		exception::scope_last_error S;
		unsigned int Id;
		this->H = reinterpret_cast<internal_t>(::_beginthreadex(
			Attributes.get(), 
			static_cast<unsigned int>(StackSize), 
			traits<unsigned int, T>::func, 
			&P, 
			Flags, 
			&Id));
		return Id;
	}

private:
	typedef ::HANDLE internal_t;
	internal_t H;

	template<class Result, class T>
	class traits
	{
	public:
		static Result WINAPI func(LPVOID lpParameter)
		{
			(*reinterpret_cast<T *>(lpParameter))();
			return 0;
		}
	};
};

}
}

#endif
