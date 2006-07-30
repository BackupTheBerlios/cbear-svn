#ifndef CBEAR_BERLIOS_DE_BASE_SINGLETON_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_SINGLETON_HPP_INCLUDED

// boost::noncopyable
#include <boost/noncopyable.hpp>
// boost::thread::yield
#include <boost/thread/thread.hpp>

namespace cbear_berlios_de
{
namespace base
{

namespace detail
{

class singleton_base
{
public:

	singleton_base(): Prev(0) 
	{
		Mutex::scoped_lock Lock;
		this->Prev = Last;
		Last = this;
	}
	virtual ~singleton_base() = 0;

private:

	singleton_base *Prev;

	class MutexId;
	typedef static_mutex<MutexId> Mutex;

	static singleton_base *Last = 0;

	class destructor
	{
	public:
		~destructor()
		{
			singleton_base *P = Last;
			while(P)
			{
				singleton_base *PP = P->Prev;
				delete P;				
				P = PP;
			}
		}
	};

	static destructor Destructor;
};

}

template<class T>
class singleton: boost::noncopyable
{
public:
	static T &instance()
	{
		T *Result = Pointer::read();
		if(!Result)
		{
			if(!HasStrated::compare_exchange(true, false))
			{			
				Result = (new(&Storage) wrap())->Instance;
				Pointer::exchange(Result);
			}
			else
			{
				do
				{
					boost::thread::yield();
					Result = Pointer::read();
				} while(!Result);
			}
		}
		return *Result;
	}
private:

	class HasStartedId;
	// false by default.
	typedef atomic::static_wrap<StartedId, bool> HasStarted;

	class PointerId;
	// 0 by defult.
	typedef atomic::static_wrap<PointerId, T *> Pointer;

	class wrap: detail::singleton_base
	{
	public:
		T Instance;
	};

	static boost::aligned_storage<wrap>::type Storage;

	singleton() {}
	~singleton() {}
};

}
}

#endif
