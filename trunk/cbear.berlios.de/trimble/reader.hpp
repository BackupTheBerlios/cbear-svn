#ifndef CBEAR_BERLIOS_DE_TRIMBLE_READER_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_TRIMBLE_READER_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace trimble
{

template<class C>
class reader
{
public:

	typedef range::iterator_range<char const *> const_range_t;

	reader():
		state(begin)
	{
	}

	void push_back(const_range_t r)
	{
		for(; !r.empty(); ++r.begin())
		{
			char const c = r.front();
			switch(this->state)
			{

			case begin:
				switch(c)
				{
				case dle:
					this->state = id;
					break;
				default:
					this->child().error();
					break;
				}
				break;

			case id:
				switch(c)
				{
				case dle:
					this->child().error();
					break;
				case etx:
					this->child().error();
					this->state = begin;
					break;
				default:
					this->child().begin(c);
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
					this->child().data(c);
					break;
				}
				break;

			case data_dle:
				switch(c)
				{
				case dle:
					this->child().data(dle);
					this->state = data;
					break;
				case etx:
					this->child().end();
					this->state = begin;
					break;
				default:
					this->child().error();
					this->state = begin;
					break;
				}
				break;
			}
		}
	}

private:

	static char const dle = 0x10;
	static char const etx = 0x03;

	enum state_t
	{
		begin,
		id,
		data,
		data_dle,
	};

	state_t state;

	C &child()
	{
		return *static_cast<C *>(this);
	}	
};

}
}

#endif
