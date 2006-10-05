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

	class _8FAC_t
	{
	public:

		typedef typename C::child_8FAC_t child_t;

		class receiver_mode_t: public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class disciplining_mode_t: public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class self_survey_progress_t: 
			public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class holdover_duration_t:
			public stream::binary::big_endian<boost::uint32_t>
		{
		};

		class critical_alarms_t:
			public stream::binary::big_endian<boost::uint16_t>
		{
		};

		class minor_alarms_t:
			public stream::binary::big_endian<boost::uint16_t>
		{
		};

		class gps_decoding_status_t: 
			public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class disciplining_activity_t:
			public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class spare_status_1_t: public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class spare_status_2_t: public stream::binary::big_endian<boost::uint8_t>
		{
		};

		class pps_offset_t: public stream::binary::float_t
		{
		};

		class _10_mhz_offset_t: public stream::binary::float_t
		{
		};

		class dac_value_t: public stream::binary::big_endian<boost::uint32_t>
		{
		};

		class dac_voltage_t: public stream::binary::float_t
		{
		};

		class temperature_t: public stream::binary::float_t
		{
		};

		class latitude_t: public stream::binary::double_t
		{
		};

		class longitude_t: public stream::binary::double_t
		{
		};

		class altitude_t: public stream::binary::double_t
		{
		};

		class spare_t: public stream::binary::double_t
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
			this->read_8FAB(s);
			break;
		case 0xAC:
			this->read_8FAC(s);
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

	template<class S>
	void read_8FAC(S &s)
	{
		_8FAC_t::child_t p(this->child());
		read_value<_8FAC_t::receiver_mode_t>(s, p);
		read_value<_8FAC_t::disciplining_mode_t>(s, p);
		this->child()(p);
	}
};

}
}

#endif
