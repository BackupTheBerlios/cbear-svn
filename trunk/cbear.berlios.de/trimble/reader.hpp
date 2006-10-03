#ifndef CBEAR_BERLIOS_DE_TRIMBLE_READER_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_TRIMBLE_READER_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace trimble
{

typedef range::iterator_range<boost::uint8_t const *> const_range_t;

class reader_t
{
public:

	// errors

	class unknown_symbol_t
	{
	public:
		boost::uint8_t value;
		explicit unknown_symbol_t(boost::uint8_t value):
			value(value)
		{
		}
	};

	class id_expected_t
	{
	public:
		boost::uint8_t value;
		explicit id_expected_t(boost::uint8_t value):
			value(value)
		{
		}
	};

	class single_dle_t
	{
	public:
	};

	// tokens

	class command_t
	{
	public:
		boost::uint8_t number;
		explicit command_t(boost::uint8_t number):
			number(number)
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

	reader_t():
		state(begin)
	{
	}

	template<class Receiver>
	void push(Receiver &receiver, boost::uint8_t const c)
	{
		switch(this->state)
		{

		case begin:
			switch(c)
			{
			case dle:
				this->state = id;
				break;
			default:
				receiver.error(unknown_symbol_t(c));
				break;
			}
			break;

		case id:
			switch(c)
			{
			case dle:
				receiver.error(id_expected_t(c));
				break;
			case etx:
				receiver.error(id_expected_t(c));
				this->state = begin;
				break;
			default:
				receiver.process(command_t(c));
				this->state = data;
				break;
			}
			break;

		case data:
			switch(c)				
			{
			case dle:
				this->state = data_dle;
				break;
			default:
				receiver.process(data_t(c));
				break;
			}
			break;

		case data_dle:
			switch(c)
			{
			case dle:
				receiver.process(data_t(dle));
				this->state = data;
				break;
			case etx:
				receiver.process(end_t());
				this->state = begin;
				break;
			default:
				receiver.error(single_dle_t());
				this->state = begin;
				break;
			}
			break;
		}
	}

	static boost::uint8_t const dle = 0x10;
	static boost::uint8_t const etx = 0x03;

private:

	enum state_t
	{
		begin,
		id,
		data,
		data_dle,
	};

	state_t state;
};

class packet_reader_t
{
public:

	packet_reader_t():
		command(reader_t::dle)
	{
	}

	class unknown_command_t: public reader_t::command_t
	{
	public:

		explicit unknown_command_t(reader_t::command_t const &command):
			reader_t::command_t(command)
		{
		}

		template<class R>
		static void process(R &receiver, reader_t::command_t const &command)
		{
			receiver.error(unknown_command_t(command));
		}

		template<class R>
		static void process(R &, reader_t::data_t const &)
		{
			// ignore
		}

		template<class R>
		static void process(R &, reader_t::end_t const &)
		{
			// ignore
		}	
	};

	template<boost::uint8_t Number>
	class command_t;

	template<>
	class command_t<0x8F>
	{
	public:

		class begin_t
		{
		};

		class end_t
		{
		};

		template<class R>
		static void process(R &receiver, reader_t::command_t const &)
		{
			receiver.process(begin_t());
		}

		template<class R>
		static void process(R &, reader_t::data_t const &)
		{
			// ...
		}

		template<class R>
		static void process(R &receiver, reader_t::end_t const &)
		{
			receiver.process(end_t());
		}	
	};

	template<class Receiver>
	void push(Receiver &receiver, boost::uint8_t value)
	{
		reader_receiver_t<Receiver> reader_receiver(*this, receiver);
		this->reader.push(reader_receiver, value);
	}

private:

	template<class R>
	class reader_receiver_t
	{
	public:

		reader_receiver_t(packet_reader_t &packet_reader, R &receiver):
			packet_reader(packet_reader),
			receiver(receiver)
		{
		}

		void set_command(reader_t::command_t const &t)
		{
			this->packet_reader.command = t;
		}

		template<class T>
		void set_command(T const &)
		{
		}

		template<class T>
		void process(T const &t)
		{
			set_command(t);
			switch(this->packet_reader.command.number)
			{
			case 0x8F:
				command_t<0x8F>::process(this->receiver, t);
				break;
			default:
				unknown_command_t::process(this->receiver, t);
			}
		}

		template<class T>
		void error(T const &t)
		{
			this->receiver.error(t);
		}

	private:
		packet_reader_t &packet_reader;
		R &receiver;
		reader_receiver_t(reader_receiver_t const &);
		reader_receiver_t &operator=(reader_receiver_t const &);
	};

	reader_t::command_t command;
	reader_t reader;
};

}
}

#endif
