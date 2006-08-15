#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_VARTYPE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_VARTYPE_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class vartype_t
{
public:
	enum enum_t
	{
		empty = ::VT_EMPTY,
		bool_ = ::VT_BOOL,
		int_ = ::VT_INT,
		uint = ::VT_UINT,
		i1 = ::VT_I1,
		ui1 = ::VT_UI1,
		i2 = ::VT_I2,
		ui2 = ::VT_UI2,
		i4 = ::VT_I4,
		ui4 = ::VT_UI4,
		i8 = ::VT_I8,
		ui8 = ::VT_UI8,
		r4 = ::VT_R4,
		r8 = ::VT_R8,
		date = ::VT_DATE,
		bstr = ::VT_BSTR,
		array = ::VT_ARRAY,
		ptr = ::VT_PTR,
		unknown = ::VT_UNKNOWN,
		dispatch = ::VT_DISPATCH,
		userdefined = ::VT_USERDEFINED,
		record = ::VT_RECORD,
	};

	template<enum_t A, enum_t B>
	struct or_
	{
		static enum_t const value = static_cast<enum_t>(A | B);
	};

	enum_t enum_()
	{
		return static_cast<enum_t>(this->V);
	}

private:
	::VARTYPE V;
};

}
}
}

#endif
