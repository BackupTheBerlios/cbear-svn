#ifndef CBEAR_BERLIOS_DE_BASE_TIME_OUT_LOOP_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_TIME_OUT_LOOP_HPP_INCLUDED

#include <boost/timer.hpp>

namespace cbear_berlios_de
{
namespace base
{

class time_out_loop_t
{
public:

	class result_t
	{
	public:
		double elapsed;
		bool success;
	};

	template<class P>
	static result_t do_(double period, P const &predicate)
	{
		::boost::timer timer;
		result_t result;
		do
		{
			result.elapsed = timer.elapsed();
			result.success = predicate();
		} while (!result.success && result.elapsed < period);
		return result;
	}
};

}
}

#endif
