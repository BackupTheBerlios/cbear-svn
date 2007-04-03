#ifndef CBEAR_BERLIOS_DE_WINDOWS_EXCEPTION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_EXCEPTION_HPP_INCLUDED

#include <boost/noncopyable.hpp>

#include <cbear.berlios.de/stream/virtual_write.hpp>
#include <cbear.berlios.de/policy/main.hpp>
#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/select.hpp>

namespace cbear_berlios_de
{
namespace windows
{

#pragma warning(push)
// 'type' : the copy constructor is inaccessible
#pragma warning(disable: 4671)
// throwing 'identifier' the following types will not be considered at the 
// catch site
#pragma warning(disable: 4673)

// Exception.
class exception:
	public std::exception,
	public stream::virtual_write, 
	public stream::wvirtual_write
{
public:

	const char *what() const throw() 
	{ 
		return "::cbear_berlios_de::windows::exception"; 
	}

	static void throw_if(dword_t X)
	{
		if(X) throw windows::exception(X);
	}

	class scope_last_error: boost::noncopyable
	{
	public:
		scope_last_error() 
		{ 
			::SetLastError(0); 
		}
		static void reset_if(bool X)
		{
			if(X)
			{
				::SetLastError(0);
			}
		}
		~scope_last_error() 
		{
			dword_t LastError = ::GetLastError(); 
			if(LastError) 
			{
				throw exception(LastError);
			}
		}
	};

	enum enum_t
	{
		// 2
		file_not_found = ERROR_FILE_NOT_FOUND,
		// 3
		path_not_found = ERROR_PATH_NOT_FOUND,
		// 4
		too_many_open_files = ERROR_TOO_MANY_OPEN_FILES,
		// 5
		access_denied = ERROR_ACCESS_DENIED,
		// 11, 0xB
		bad_format = ERROR_BAD_FORMAT,
		// 14, 0xE
		outofmemory = ERROR_OUTOFMEMORY,
		// 21, 0x15
		not_ready = ERROR_NOT_READY,
		// 32, 0x20
		sharing_violation = ERROR_SHARING_VIOLATION,
		// 33, 0x21
		lock_violation = ERROR_LOCK_VIOLATION,
		// 38, 0x26
		handle_eof = ERROR_HANDLE_EOF,
		// 53, 0x35
		bad_netpath = ERROR_BAD_NETPATH,
		// 67, 0x43
		bad_net_name = ERROR_BAD_NET_NAME,
		// 87, 0x57
		invalid_parameter = ERROR_INVALID_PARAMETER,
		// 110, 0x6E
		open_failed = ERROR_OPEN_FAILED,
		// 123, 0x7B
		invalid_name = ERROR_INVALID_NAME,
		// 126, 0x7E
		mod_not_found = ERROR_MOD_NOT_FOUND,
		// 182, 0xB6
		invalid_ordinal = ERROR_INVALID_ORDINAL,
		// 192, 0xC0
		exe_marked_invalid = ERROR_EXE_MARKED_INVALID,
		// 193, 0xC1
		bad_exe_format = ERROR_BAD_EXE_FORMAT,
		// 206, 0xCE
		filename_exced_range = ERROR_FILENAME_EXCED_RANGE,
		// 534, 0x216
		arithmetic_overflow = ERROR_ARITHMETIC_OVERFLOW,
		// 998, 0x3E6
		noaccess = ERROR_NOACCESS,
		// 1001, 0x3E9
		stack_overflow = ERROR_STACK_OVERFLOW,
		// 1005, 0x3ED
		unrecognized_volume = ERROR_UNRECOGNIZED_VOLUME,
		// 1006, 0x3EE
		file_invalid = ERROR_FILE_INVALID,
		// 1113, 0x459
		no_unicode_translation = ERROR_NO_UNICODE_TRANSLATION,
		// 1114, 0x45A
		dll_init_failed = ERROR_DLL_INIT_FAILED,
		// 1154, 0x482
		invalid_dll = ERROR_INVALID_DLL,
		// 1157, 0x485
		dll_not_found = ERROR_DLL_NOT_FOUND,
		// 1392, 0x570
		file_corrupt = ERROR_FILE_CORRUPT,
		// 1393, 0x571
		disk_corrupt = ERROR_DISK_CORRUPT,
		// 1396, 0x574
		wrong_target_name = ERROR_WRONG_TARGET_NAME,
		no_more_items = ERROR_NO_MORE_ITEMS,
		insufficient_buffer = ERROR_INSUFFICIENT_BUFFER,
	};

	template<class S>
	void write(S &O) const
	{
		typedef typename S::value_type char_type;
		// policy::std_wrap<char_type *, buffer_policy<char_type> > Buffer;
		buffer<char_type> Buffer;
		dword_t const Size = CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(
			char_type, ::FormatMessage)(
				FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
				0,
				this->result(),
				0,
				(char_type *)&Buffer.get(),
				0,
				0);
		O <<
			CBEAR_BERLIOS_DE_SELECT_STRING(
				char_type, "cbear_berlios_de::windows::exception(0x") <<
			base::hex(this->result()) << 
			CBEAR_BERLIOS_DE_SELECT_STRING(char_type, "):\n") << 
			range::make_iterator_range(Buffer.get(), Size);
	}

	dword_t result() const throw() { return this->Result; }

	explicit exception(dword_t X): Result(X) {}

private:

	template<class Char>
	class buffer: public base::initialized<Char *>
	{
	public:
		~buffer()
		{
			if(!this->get()) return;
			::LocalFree(this->get());
		}
	};

	void detail_write(::cbear_berlios_de::stream::virtual_write::stream &S) const
	{
		this->write(S);
	}

	void detail_write(::cbear_berlios_de::stream::wvirtual_write::stream &S) const
	{
		this->write(S);
	}

	dword_t Result;
};

#pragma warning(pop)

}
}

#endif
