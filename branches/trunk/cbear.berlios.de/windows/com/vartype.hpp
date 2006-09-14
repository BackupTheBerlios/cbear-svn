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
		carray = ::VT_CARRAY,
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

	typedef ::VARTYPE c_t;

	template<enum_t V>
	class const_
	{
	public:
		static enum_t const value = V;
		operator vartype_t() const
		{
			return vartype_t(V);
		}
	};

	vartype_t(enum_t E = empty):
		V(c_t(E))
	{
	}

	bool operator==(const vartype_t &B) const
	{
		return this->V == B.V;
	}

	template<class F>
	void apply(F f) const
	{
		switch(this->V)
		{
		case empty:
			f(const_<empty>());
			break;
		case bool_:
			f(const_<bool_>());
			break;
		case int_:
			f(const_<int_>());
			break;
		case uint:
			f(const_<uint>());
			break;
		case i1:
			f(const_<i1>());
			break;
		case ui1:
			f(const_<ui1>());
			break;
		case i2:
			f(const_<i2>());
			break;
		case ui2:
			f(const_<ui2>());
			break;
		case i4:
			f(const_<i4>());
			break;
		case ui4:
			f(const_<ui4>());
			break;
		case i8:
			f(const_<i8>());
			break;
		case ui8:
			f(const_<ui8>());
			break;
		case r4:
			f(const_<r4>());
			break;
		case r8:
			f(const_<r8>());
			break;
		case date:
			f(const_<date>());
			break;
		case bstr:
			f(const_<bstr>());
			break;
		case array:
			f(const_<array>());
			break;
		case carray:
			f(const_<carray>());
			break;
		case ptr:
			f(const_<ptr>());
			break;
		case unknown:
			f(const_<unknown>());
			break;
		case dispatch:
			f(const_<dispatch>());
			break;
		case userdefined:
			f(const_<userdefined>());
			break;
		case record:
			f(const_<record>());
			break;
		default:
			f(*this);
			break;
		}
	}

private:
	c_t V;
};

}
}
}

#endif
