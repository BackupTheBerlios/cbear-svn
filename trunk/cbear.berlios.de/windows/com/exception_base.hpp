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
		return "::cbear_berlios_de::windows::com::exception_base_t";
	}

	template<class Stream>
	void write(Stream &O) const
	{
		O << 
			L"::cbear_berlios_de::com::exception_base_t(0x" << 
			base::hex(base::unsigned_(this->R.internal())) << 
			L")";
	}
	
private:
	hresult const R;
	exception_base_t &operator=(exception_base_t const &);
};

}
}
}

#endif
