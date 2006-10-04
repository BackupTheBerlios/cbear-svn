#ifndef CBEAR_BERLIOS_DE_TRIMBLE_PARSER_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_TRIMBLE_PARSER_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace trimble
{

class parser_t
{
public:

	class id_t
	{
	public:
		boost::uint8_t value;
		explicit id_t(boost::uint8_t value):
			value(value)
		{
		}
	};

	class data_t
	{
	public:
		boost::uint8_t value;
		explicit data_t(boost::uint8_t value):
			value(value)
		{
		}
	};

	class end_t
	{
	};

	parser_t():
		state(state_t::none)
	{
	}	

	template<class R>
	void push_back(R &r, boost::uint8_t value)
	{
		switch(this->state)
		{
		case state_t::none:
			switch(value)
			{
			case dle:
				this->state = state_t::dle;
				break;
			default:
				r.push_back(data_t(value));
				break;
			}
			break;
		case state_t::dle:
			this->state = state_t::none;
			switch(value)
			{
			case dle:
				r.push_back(data_t(dle));
				break;
			case etx:
				r.push_back(end_t());
				break;
			default:
				r.push_back(id_t(value));
				break;
			}
			break;
		}
	}

private:
	static boost::uint8_t const dle = 0x10;
	static boost::uint8_t const etx = 0x03;
	class state_t
	{
	public:
		enum t
		{
			none,
			dle,
		};
	};
	state_t::t state;
};

}
}

#endif
