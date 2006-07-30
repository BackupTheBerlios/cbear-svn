#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_THREAD_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_THREAD_HPP_INCLUDED

// boost::mutex
#include <boost/thread/mutex.hpp>
// boost::thread
#include <boost/thread/thread.hpp>

#include <cbear.berlios.de/windows/com/system.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class thread: public boost::thread
{
public:
	
	thread() {}

	template<class Function>
	thread(Function X): boost::thread(function(X)) {}

	template<class Function>
	class function_result
	{
	public:
		function_result(Function X): X(X) {}
		void operator()() const
		{
			system System(system::multithreaded);
			this->X();
		}
	private:
		Function X;
	};

	template<class Function>
	static function_result<Function> function(Function X)
	{
		return function_result<Function>(X);
	}
private:
	thread(const thread &);
	thread &operator=(const thread &);
};

}
}
}

#endif
