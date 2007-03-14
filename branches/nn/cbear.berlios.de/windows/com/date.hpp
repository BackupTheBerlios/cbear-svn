#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_DATE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_DATE_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/traits.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class date_t: public policy::wrap<date_t, ::DATE> 
{
public:
	typedef void *extra_result;
	typedef date_t move_type;
	static vartype_t::enum_t const vt = vartype_t::date;

	date_t() 
	{
	}

	explicit date_t(systemtime_t const &SystemTime) 
	{
		if(::SystemTimeToVariantTime(
			const_cast<systemtime_t*>(&SystemTime), &this->internal())==0)
			throw std::exception("wrong system time");
	}

	void move_assign(date_t &F)
	{
		this->internal() = F.internal();
	}
};

}
}
}

#endif
