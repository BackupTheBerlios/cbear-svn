#ifndef CBEAR_BERLIOS_DE_THREAD_STATIC_MUTEX_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_THREAD_STATIC_MUTEX_HPP_INCLUDED

// boost::noncopyable
#include <boost/noncopyable.hpp>
// boost::thread::yield
#include <boost/thread/thread.hpp>

namespace cbear_berlios_de
{
namespace base
{

template<class T>
class static_mutex: boost::noncopyable
{
public:
	class scoped_lock: boost::noncopyable
	{
	public:
		scoped_lock() { while(Lock::exchange(true)) boost::thread::yield(); }
		~scoped_lock() { Lock::exchange(false); }
	};
private:
	class Id;
	typedef static_wrap<Id, bool> Lock; // default value is false.
};

}
}

#endif
