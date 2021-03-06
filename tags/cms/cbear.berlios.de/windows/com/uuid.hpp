#ifndef CBEAR_SOURCEFORGE_NET_WINDOWS_COM_UUID_HPP_INCLUDED
#define CBEAR_SOURCEFORGE_NET_WINDOWS_COM_UUID_HPP_INCLUDED

// ::UUID
#include <windows.h>
// ::boost::uint8_t, ::boost::uint16_t, ::boost::uint32_t
#include <boost/cstdint.hpp>

#include <cbear.berlios.de/windows/com/traits.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class uuid
{
public:

	typedef boost::uint32_t data1_t;
	typedef boost::uint16_t data2_t;
	typedef boost::uint16_t data3_t;
	typedef boost::uint8_t data4_value_t;

	uuid() {}

	uuid(
		const data1_t &D1,
		const data2_t &D2, 
		const data3_t &D3,
		const data4_value_t &D40,
		const data4_value_t &D41,
		const data4_value_t &D42,
		const data4_value_t &D43,
		const data4_value_t &D44,
		const data4_value_t &D45,
		const data4_value_t &D46,
		const data4_value_t &D47)
	{
		this->V.Data1 = D1;
		this->V.Data2 = D2;
		this->V.Data3 = D3;
		this->V.Data4[0] = D40;
		this->V.Data4[1] = D41;
		this->V.Data4[2] = D42;
		this->V.Data4[3] = D43;
		this->V.Data4[4] = D44;
		this->V.Data4[5] = D45;
		this->V.Data4[6] = D46;
		this->V.Data4[7] = D47;
	}

	bool operator==(const uuid &B) const
	{
		return (this->V == B.V) != 0;
	}

public:

	template<class S>
	void write(S &O) const
	{
		// For example: "9051E94D-6A0C-44b8-B163-716CD2117C58"
		// Format:      "11111111-2222-3333-4444-444444444444"
		typedef typename S::value_type char_type;
		typedef range::iterator_range<const boost::uint8_t *> range_type;
		static const char_type Zero = CBEAR_BERLIOS_DE_SELECT_CHAR(char_type, '0');
		static const char_type Minus = CBEAR_BERLIOS_DE_SELECT_CHAR(char_type, '-');
		O << 
			base::hex(this->V.Data1, 8) <<
			Minus <<
			base::hex(this->V.Data2, 4) <<
			Minus <<
			base::hex(this->V.Data3, 4) <<
			Minus;
		for(
			range_type R(this->V.Data4, this->V.Data4 + 2); 
			!R.empty(); 
			++R.begin())
		{
			O << base::hex(R.front(), 2);
		}
		O << Minus;
		for(
			range_type R(this->V.Data4 + 2, this->V.Data4 + 8);
			!R.empty(); 
			++R.begin())
		{
			O << base::hex(R.front(), 2);
		}		
	}

	template<class S>
	void read(S &O)
	{
		typedef typename S::value_type char_type;
		typedef range::iterator_range<boost::uint8_t *> range_type;
		char_type W;
		O >>
			base::const_ref(base::hex(this->V.Data1, 8)) >>
			W >>
			base::const_ref(base::hex(this->V.Data2, 4)) >>
			W >>
			base::const_ref(base::hex(this->V.Data3, 4)) >>
			W;
		for(
			range_type R(this->V.Data4, this->V.Data4 + 2); 
			!R.empty(); 
			++R.begin())
		{
			O >> base::const_ref(base::hex(R.front(), 2));
		}
		O >> W;
		for(
			range_type R(this->V.Data4 + 2, this->V.Data4 + 8);
			!R.empty(); 
			++R.begin())
		{
			O >> base::const_ref(base::hex(R.front(), 2));
		}
	}

	template<class Stream>
	void binary_read(Stream &I)
	{
		I >> this->V.Data1 >> this->V.Data2 >> this->V.Data3 >> this->V.Data4;
	}

	template<class Stream>
	void binary_write(Stream &O) const
	{
		O << this->V.Data1 << this->V.Data2 << this->V.Data3 << this->V.Data4;
	}

public:

	typedef ::UUID c_t;

	typedef const c_t *c_in_t;
	typedef c_t *c_out_t;
	typedef c_t *c_in_out_t;

	c_in_t c_in() const throw()
	{
		return &this->V;
	}

	c_out_t c_out() throw()
	{
		return &this->V;
	}

	c_in_out_t c_in_out() throw()
	{
		return &this->V;
	}

	static const uuid &cpp_in(c_in_t V) throw()
	{
		return *cast::traits<const uuid *>::reinterpret(V);
	}

	static uuid &cpp_out(c_out_t V) throw()
	{
		return *cast::traits<uuid *>::reinterpret(V);
	}

	static uuid &cpp_in_out(c_in_out_t V) throw()
	{
		return *cast::traits<uuid *>::reinterpret(V);
	}

public:

	// should it be renamed to of_t?
	template<class I>
	class of_type
	{
	public:
		static const uuid &create() throw()
#ifdef _MSC_VER
		{
			return cpp_in(&__uuidof(I));
		}
#else
		;
#endif
	};

	template<class I>
	static const uuid &of() throw()
	{
		return of_type<I>::create();
	}

// deprecated
public:

	class internal_policy
	{
	public:
		typedef c_t type;
		static void construct(type &) 
		{
		}
	};

	typedef uuid move_type;

	static const vartype_t::enum_t vt = vartype_t::empty;

	typedef void extra_result;

	typedef c_t internal_type;

	static const uuid &wrap_ref(const c_t &V)
	{
		return cast::traits<const uuid &>::reinterpret(V);
	}

	static uuid &wrap_ref(c_t &V)
	{
		return cast::traits<uuid &>::reinterpret(V);
	}

	typedef c_t value_t;

	::UUID &get()
	{
		return this->V;
	}

	const ::UUID &get() const
	{
		return this->V;
	}

	const internal_type &internal() const
	{
		return this->V;
	}

	internal_type &internal()
	{
		return this->V;
	}

private:

	c_t V;

};

typedef uuid iid_t;

}
}
}

#endif
