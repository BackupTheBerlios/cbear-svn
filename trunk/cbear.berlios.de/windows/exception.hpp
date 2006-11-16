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
		~scope_last_error() 
		{
			dword_t LastError = ::GetLastError(); 
			if(LastError) throw exception(LastError);
		}
	};

	enum enum_t
	{
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
