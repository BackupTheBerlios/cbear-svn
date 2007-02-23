#ifndef CBEAR_BERLIOS_DE_WINDOWS_HANDLE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_HANDLE_HPP_INCLUDED

#include <windows.h>

// FILE_ATTRIBUTE_ENCRYPTED
// FILE_ATTRIBUTE_NOT_CONTENT_INDEXED
#include <winnt.h>

#ifndef FILE_ATTRIBUTE_ENCRYPTED
#define FILE_ATTRIBUTE_ENCRYPTED 0x00004000
#endif

#ifndef FILE_ATTRIBUTE_NOT_CONTENT_INDEXED
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED 0x00002000 
#endif

// FILE_FLAG_OPEN_NO_RECALL
// FILE_FLAG_OPEN_REPARSE_POINT
#include <winbase.h>

#ifndef FILE_FLAG_OPEN_NO_RECALL
#define FILE_FLAG_OPEN_NO_RECALL 0x00100000
#endif

#ifndef FILE_FLAG_OPEN_REPARSE_POINT
#define FILE_FLAG_OPEN_REPARSE_POINT 0x00200000
#endif

//

#include <cbear.berlios.de/range/iterator_range.hpp>
#include <cbear.berlios.de/windows/optional_ref.hpp>
#include <cbear.berlios.de/windows/base.hpp>
#include <cbear.berlios.de/windows/overlapped.hpp>
#include <cbear.berlios.de/windows/exception.hpp>
#include <cbear.berlios.de/windows/select.hpp>
#include <cbear.berlios.de/windows/lpstr.hpp>
#include <cbear.berlios.de/windows/security_attributes.hpp>

namespace cbear_berlios_de
{
namespace windows
{

template<class Char>
class win32_find_data: 
	public CBEAR_BERLIOS_DE_WINDOWS_TYPE(Char, ::WIN32_FIND_DATA)
{
};

class desired_access: public base::initialized<dword_t>
{
public:
	typedef base::initialized<dword_t> base_t;

	enum enum_
	{
		file_and_file = FILE_ADD_FILE,
		file_and_subdirectory = FILE_ADD_SUBDIRECTORY,
		file_all_access = FILE_ALL_ACCESS,
		file_append_data = FILE_APPEND_DATA,
		file_create_pipe_instance = FILE_CREATE_PIPE_INSTANCE,
		file_delete_child = FILE_DELETE_CHILD,
		file_execute = FILE_EXECUTE,
		file_list_directory = FILE_LIST_DIRECTORY,
		file_read_attributes = FILE_READ_ATTRIBUTES,
		file_read_data = FILE_READ_DATA,
		file_read_ea = FILE_READ_EA,
		file_traverse = FILE_TRAVERSE,
		file_write_attributes = FILE_WRITE_ATTRIBUTES,
		file_write_data = FILE_WRITE_DATA,
		file_write_ea = FILE_WRITE_EA,
		standard_rights_read = STANDARD_RIGHTS_READ,
		standard_rights_write = STANDARD_RIGHTS_WRITE,
		synchronize = SYNCHRONIZE,

		generic_execute = GENERIC_EXECUTE,
		generic_read = GENERIC_READ,
		generic_write = GENERIC_WRITE,
	};

	desired_access() 
	{
	}

	desired_access(enum_ E): 
		base_t(E) 
	{
	}

	desired_access &operator|=(const desired_access &X)
	{
		this->get() |= X.get();
		return *this;
	}

	desired_access operator|(const desired_access &X) const
	{
		desired_access R(*this);
		R |= X;
		return R;
	}
};

class file_share: public base::initialized<dword_t>
{
public:
	typedef base::initialized<dword_t> base_t;

	enum enum_
	{
		delete_ = FILE_SHARE_DELETE,
		read = FILE_SHARE_READ,
		write = FILE_SHARE_WRITE,
	};

	file_share() 
	{
	}

	file_share(enum_ E): base_t(E) 
	{
	}

	file_share &operator|=(const file_share &X)
	{
		this->get() |= X.get();
		return *this;
	}

	file_share operator|(const file_share &X) const
	{
		file_share R(*this);
		R |= X;
		return R;
	}
};

class creation_disposition: public base::initialized<dword_t>
{
public:

	typedef base::initialized<dword_t> base_t;

	enum enum_
	{
		create_always = CREATE_ALWAYS,
		create_new = CREATE_NEW,
		open_always = OPEN_ALWAYS,
		open_existing = OPEN_EXISTING,
		truncate_existing = TRUNCATE_EXISTING,
	};

	creation_disposition() {}
	creation_disposition(enum_ E): base_t(E) {}
};

class flags_and_attributes: public base::initialized<dword_t>
{
public:

	typedef base::initialized<dword_t> base_t;

	enum enum_
	{
		file_attribute_archive = FILE_ATTRIBUTE_ARCHIVE,
		file_attribute_encrypted = FILE_ATTRIBUTE_ENCRYPTED,
		file_attribute_hidden = FILE_ATTRIBUTE_HIDDEN,
		file_attribute_normal = FILE_ATTRIBUTE_NORMAL,
		file_attribute_not_content_indexed = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
		file_attribute_offline = FILE_ATTRIBUTE_OFFLINE,
		file_attribute_readonly = FILE_ATTRIBUTE_READONLY,
		file_attribute_system = FILE_ATTRIBUTE_SYSTEM,
		file_attribute_temporary = FILE_ATTRIBUTE_TEMPORARY,

		file_flag_backup_semantics = FILE_FLAG_BACKUP_SEMANTICS,
		file_flag_delete_on_close = FILE_FLAG_DELETE_ON_CLOSE,
		file_flag_no_buffering = FILE_FLAG_NO_BUFFERING,
		file_flag_open_no_recall = FILE_FLAG_OPEN_NO_RECALL,
		file_flag_open_reparse_point = FILE_FLAG_OPEN_REPARSE_POINT,
		file_flag_overlapped = FILE_FLAG_OVERLAPPED,
		file_flag_posix_semantics = FILE_FLAG_POSIX_SEMANTICS,
		file_flag_random_access = FILE_FLAG_RANDOM_ACCESS,
		file_flag_sequential_scan = FILE_FLAG_SEQUENTIAL_SCAN,
		file_flag_write_through = FILE_FLAG_WRITE_THROUGH,

		security_anonymous = SECURITY_ANONYMOUS,
		security_context_tracking = SECURITY_CONTEXT_TRACKING,
		security_delegation = SECURITY_DELEGATION,
		security_effective_only = SECURITY_EFFECTIVE_ONLY,
		security_identification = SECURITY_IDENTIFICATION,
		security_impersonation = SECURITY_IMPERSONATION,
	};

	flags_and_attributes() {}
	flags_and_attributes(enum_ E): base_t(E) {}
};


class ioctl: public base::initialized<dword_t>
{
public:

	typedef base::initialized<dword_t> base_t;

	template<dword_t X>
	class const_
	{
	public:
		static const dword_t value = X;
		operator ioctl() const { return ioctl(X); }
	};

	explicit ioctl(dword_t X): base_t(X) {}
};

// Handle to an object.
class handle: 
	public base::initialized< ::HANDLE>,
	boost::noncopyable
{
public:
	typedef base::initialized< ::HANDLE> base_t;

	handle() {}
	explicit handle(value_t X): base_t(X) {}

	~handle() { this->Close(); }

	dword_t DeviceIoControl(
		const ioctl &IoControlCode,
		const byte_range &In,
		const byte_range &Out,
		const optional_ref<overlapped> &Overlapped) const
	{
		dword_t BytesReturned;
		exception::scope_last_error ScopeLastError;
		::DeviceIoControl(
			this->get(),
			IoControlCode.get(),
			In.begin(),
			dword_t(In.size()),
			Out.begin(),
			dword_t(Out.size()),
			&BytesReturned, 
			Overlapped.get());
		return BytesReturned;
	}

	template<class Char>
	void CreateFile(
		const basic_lpstr<const Char> &fileName,
		desired_access desiredAccess,
		file_share fileShare,
		security_attributes securityAttributes,
		creation_disposition creationDisposition,
		flags_and_attributes flagsAndAttributes,
		const handle &templateFile)
	{
		this->Close();
		exception::scope_last_error ScopeLastError;
		this->get() = CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::CreateFile)(
			fileName.get(),
			desiredAccess.get(),
			fileShare.get(),
			securityAttributes.get(),
			creationDisposition.get(),
			flagsAndAttributes.get(),
			templateFile.get());
	}

	template<class Char>
	void FindFirstFile(
		const basic_lpstr<const Char> &fileName, 
		win32_find_data<Char> &findFileData)
	{
		this->Close();
		exception::scope_last_error ScopeLastError;
		this->get() = CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(Char, ::FindFirstFile)(
			fileName.internal(),
			&findFileData);
	}

	dword_t ReadFile(byte_range const &Out) const
	{
		dword_t result;
		exception::scope_last_error ScopeLastError;
		::ReadFile(
			this->get(), 
			Out.begin(),
			static_cast<dword_t>(Out.size()),
			&result,
			0);
		return result;
	}

	dword_t WriteFile(const_byte_range const &In) const
	{
		dword_t result;
		exception::scope_last_error ScopeLastError;
		::WriteFile(
			this->get(), 
			In.begin(),
			static_cast<dword_t>(In.size()),
			&result,
			0);
		return result;
	}

	void Close()
	{
		::CloseHandle(this->get());
		this->get() = 0;
	}
};

}
}

#endif
