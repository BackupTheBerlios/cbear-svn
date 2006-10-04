#ifndef CBEAR_BERLIOS_DE_TRIMBLE_PACKET_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_TRIMBLE_PACKET_HPP_INCLUDED

#include <cbear.berlios.de/stream/binary/big_endian.hpp>

namespace cbear_berlios_de
{
namespace trimble
{

template<class C>
class packet_t
{
public:

	class unknown_t
	{
	};

	class _8FAB_t
	{
	public:

		typedef typename C::child_8FAB_t child_t;

		class time_of_week_t: public stream::binary::big_endian<boost::uint32_t>
		{
		};

		class week_number_t: public stream::binary::big_endian<boost::uint16_t>
		{
		};

		class utc_offset_t: public stream::binary::big_endian<boost::int16_t>
		{
		};

		class timing_flag_t: public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class seconds_t: public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class minutes_t: public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class hours_t: public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class day_of_month_t: public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class month_t: public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class year_t: public stream::binary::big_endian<boost::uint16_t>
		{
		};
	};	

	template<class S>
	void binary_read(S &s)
	{
		boost::uint8_t id;
		s >> id;
		switch(id)
		{
		case 0x8F:
			this->read_8F(s);
			break;
		default:
			this->child()(unknown_t());
			break;
		}
	}

private:
	
	C &child()
	{
		return *static_cast<C *>(this);
	}

	template<class S>
	void read_8F(S &s)
	{
		boost::uint8_t id;
		s >> id;
		switch(id)
		{
		case 0xAB:
			read_8FAB(s);
			break;
		default:
			this->child()(unknown_t());
			break;	
		}
	}

	template<class F, class S, class C>
	static void read_value(S &s, C &c)
	{
		F f;
		s >> f;
		c(f);
	}

	template<class S>
	void read_8FAB(S &s)
	{
		_8FAB_t::child_t p(this->child());
		read_value<_8FAB_t::time_of_week_t>(s, p);
		read_value<_8FAB_t::week_number_t>(s, p);
		read_value<_8FAB_t::utc_offset_t>(s, p);
		read_value<_8FAB_t::timing_flag_t>(s, p);
		read_value<_8FAB_t::seconds_t>(s, p);
		read_value<_8FAB_t::minutes_t>(s, p);
		read_value<_8FAB_t::hours_t>(s, p);
		read_value<_8FAB_t::day_of_month_t>(s, p);
		read_value<_8FAB_t::month_t>(s, p);
		read_value<_8FAB_t::year_t>(s, p);
		this->child()(p);
	}
};

}
}

#endif
