#ifndef CBEAR_BERLIOS_DE_COM_EXCEPTION_BASE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_COM_EXCEPTION_BASE_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/hresult.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class exception_base_t: 
	public ::std::exception,
	public stream::wvirtual_write
{
public:

	explicit exception_base_t(hresult const &R):
		R(R)
	{
	}

	hresult const &result() const throw()
	{
		return this->R;
	}

	char const *what() const throw()
	{ 
		return id<char>().begin();
	}

	template<class Stream>
	void write(Stream &O) const
	{
		typedef typename Stream::value_type char_t;
		O << 
			id<char_t>() <<
			CBEAR_BERLIOS_DE_SELECT_STRING(char_t, "(0x") <<
			base::hex(base::unsigned_(this->R.internal())) << 
			CBEAR_BERLIOS_DE_SELECT_STRING(char_t, ")");
		if(this->R.facility() == hresult::facility_type::win32)
		{
			buffer<char_t> buffer;
			dword_t const size = 
				CBEAR_BERLIOS_DE_WINDOWS_FUNCTION(char_t, ::FormatMessage)(
					FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
					0,
					this->R.code().internal(),
					0,
					reinterpret_cast<char_t *>(&buffer.get()),
					0,
					0);
			O <<
				CBEAR_BERLIOS_DE_SELECT_STRING(char_t, "\n") <<
				range::make_iterator_range(buffer.get(), size);
		}
	}
	
private:

	hresult const R;

	exception_base_t(exception_base_t const &);
	exception_base_t &operator=(exception_base_t const &);

	CBEAR_BERLIOS_DE_SELECT_ID(
		"::cbear_berlios_de::windows::com::exception_base_t");

	template<class C>
	class buffer: public base::initialized<C *>
	{
	public:
		~buffer()
		{
			if(!this->get()) 
			{
				return;
			}
			::LocalFree(this->get());
		}
	};

	void detail_write(::cbear_berlios_de::stream::wvirtual_write::stream &S) const
	{
		this->write(S);
	}
};

}
}
}

#endif
