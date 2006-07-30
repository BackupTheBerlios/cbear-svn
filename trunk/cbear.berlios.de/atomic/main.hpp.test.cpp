#include <cbear.berlios.de/atomic/main.hpp>

#include <boost/test/minimal.hpp>

// boost::thread
#include <boost/thread/thread.hpp>

namespace Atomic = cbear_berlios_de::atomic;

template<class T, class T1, class T2, class T3, class T4>
void TestBase(volatile T &X, T1 A1, T2 A2, T3 A3, T4 A4)
{
	BOOST_CHECK(Atomic::read(X)==0);

	BOOST_CHECK(Atomic::exchange(X, A1)==0);
	BOOST_CHECK(Atomic::exchange(X, A2)==A1);

	BOOST_CHECK(Atomic::read(X)==A2);

	BOOST_CHECK(Atomic::compare_exchange(X, A3, A1)==A2);
	BOOST_CHECK(Atomic::compare_exchange(X, A3, A2)==A2);
	BOOST_CHECK(Atomic::compare_exchange(X, A4, A3)==A3);

	BOOST_CHECK(Atomic::read(X)==A4);
}

template<class T, class T1, class T2, class T3, class T4>
void WrapTestBase(T &X, T1 A1, T2 A2, T3 A3, T4 A4)
{
	BOOST_CHECK(X.read()==0);

	BOOST_CHECK(X.exchange(A1)==0);
	BOOST_CHECK(X.exchange(A2)==A1);

	BOOST_CHECK(X.read()==A2);

	BOOST_CHECK(X.compare_exchange(A3, A1)==A2);
	BOOST_CHECK(X.compare_exchange(A3, A2)==A2);
	BOOST_CHECK(X.compare_exchange(A4, A3)==A3);

	BOOST_CHECK(X.read()==A4);
}

template<class T, class T1, class T2, class T3, class T4>
void StaticWrapTestBase(T1 A1, T2 A2, T3 A3, T4 A4)
{
	BOOST_CHECK(T::read()==0);

	BOOST_CHECK(T::exchange(A1)==0);
	BOOST_CHECK(T::exchange(A2)==A1);

	BOOST_CHECK(T::read()==A2);

	BOOST_CHECK(T::compare_exchange(A3, A1)==A2);
	BOOST_CHECK(T::compare_exchange(A3, A2)==A2);
	BOOST_CHECK(T::compare_exchange(A4, A3)==A3);

	BOOST_CHECK(T::read()==A4);
}

template<class T>
void TestInteger(volatile T &X)
{
	TestBase(X, 1, 2, 3, 4);

	BOOST_CHECK(Atomic::exchange_add(X, 2)==4);
	BOOST_CHECK(Atomic::exchange_add(X, 3)==6);

	BOOST_CHECK(Atomic::read(X)==9);

	BOOST_CHECK(Atomic::increment(X)==10);
	BOOST_CHECK(Atomic::decrement(X)==9);
	BOOST_CHECK(Atomic::decrement(X)==8);
	BOOST_CHECK(Atomic::increment(X)==9);

	BOOST_CHECK(Atomic::read(X)==9);
}

template<class T>
void WrapTestInteger(T &X)
{
	WrapTestBase(X, 1, 2, 3, 4);

	BOOST_CHECK(X.exchange_add(2)==4);
	BOOST_CHECK(X.exchange_add(3)==6);

	BOOST_CHECK(X.read()==9);

	BOOST_CHECK(X.increment()==10);
	BOOST_CHECK(X.decrement()==9);
	BOOST_CHECK(X.decrement()==8);
	BOOST_CHECK(X.increment()==9);

	BOOST_CHECK(X.read()==9);
}

template<class T>
void StaticWrapTestInteger()
{
	StaticWrapTestBase<T>(1, 2, 3, 4);

	BOOST_CHECK(T::exchange_add(2)==4);
	BOOST_CHECK(T::exchange_add(3)==6);

	BOOST_CHECK(T::read()==9);

	BOOST_CHECK(T::increment()==10);
	BOOST_CHECK(T::decrement()==9);
	BOOST_CHECK(T::decrement()==8);
	BOOST_CHECK(T::increment()==9);

	BOOST_CHECK(T::read()==9);
}

class StaticStringPointerWrapId;
typedef Atomic::static_wrap<StaticStringPointerWrapId, std::string *> 
	StaticStringPointerWrap;

class StaticUnsignedLongWrapId;
typedef Atomic::static_wrap<StaticUnsignedLongWrapId, unsigned long> 
	StaticUnsignedLongWrap;

template<std::size_t Size>
struct Func
{
	void operator()() const
	{
		for(int i = 0; i<Size; ++i)
		{
			StaticUnsignedLongWrap::increment();
			boost::thread::yield();
		}
	}
};

template<std::size_t Size>
struct FuncDec
{
	void operator()() const
	{
		for(int i = 0; i<Size; ++i)
		{
			StaticUnsignedLongWrap::decrement();
			boost::thread::yield();
		}
	}
};

template<long Flag, long Next>
struct FuncCompareExchange
{
	void operator()() const
	{
		while(StaticUnsignedLongWrap::compare_exchange(Next, Flag)!=Flag)
			boost::thread::yield();
	}
};

int BufferPosition = 0;
std::string Buffer;

struct FuncExchange
{
	FuncExchange(int I, std::string S): I(I), S(S) {}

	void operator()() const
	{
		bool Flag;
		do
		{
			while(StaticUnsignedLongWrap::exchange(1)!=0)	
				boost::thread::yield();
			Flag = BufferPosition==I;
			if(Flag)
			{
				Buffer += S;
				++BufferPosition;
			}
			StaticUnsignedLongWrap::exchange(0);
		} while(!Flag);
	}

	std::string S;
	int I;
};

int test_main(int, char *[])
{
	volatile int Int = 0;
	TestInteger(Int);

	volatile unsigned int UnsignedInt = 0;
	TestInteger(UnsignedInt);

	volatile long Long = 0;
	TestInteger(Long);

	volatile unsigned long UnsignedLong = 0;
	TestInteger(UnsignedLong);

	std::string A1 = "Hello";
	std::string A2 = "world";
	std::string A3 = "Good";
	std::string A4 = "bay";

	std::string *volatile StringPointer = 0;

	TestBase(StringPointer, &A1, &A2, &A3, &A4);

	Atomic::wrap<std::string *> StringPointerWrap;

	WrapTestBase(StringPointerWrap, &A1, &A2, &A3, &A4);

	Atomic::wrap<std::string *> StringPointerWrap1(0);

	WrapTestBase(StringPointerWrap1, &A4, &A3, &A2, &A1);

	Atomic::wrap<long> LongWrap;

	WrapTestInteger(LongWrap);

	StaticWrapTestBase<StaticStringPointerWrap>(&A1, &A2, &A3, &A4);
	StaticWrapTestInteger<StaticUnsignedLongWrap>();

	// increment

	StaticUnsignedLongWrap::exchange(0);

	boost::thread_group Group;
	Group.create_thread(Func<30000>());
	Group.create_thread(Func<20000>());
	Group.create_thread(Func<10000>());
	Group.join_all();

	BOOST_CHECK(StaticUnsignedLongWrap::read()==60000);

	// compare_exchange

	boost::thread_group Group1;
	Group1.create_thread(FuncCompareExchange<   70, 1976>());
	Group1.create_thread(FuncCompareExchange<   10,    5>());
	Group1.create_thread(FuncCompareExchange<    5,   20>());
	Group1.create_thread(FuncCompareExchange<60000,   10>());
	Group1.create_thread(FuncCompareExchange<   20,   70>());
	Group1.create_thread(FuncCompareExchange< 1976,   85>());
	Group1.join_all();

	BOOST_CHECK(StaticUnsignedLongWrap::read()==85);

	// exchange

	StaticUnsignedLongWrap::exchange(0);

	boost::thread_group Group2;
	Group2.create_thread(FuncExchange(6, " "));
	Group2.create_thread(FuncExchange(1, " "));
	Group2.create_thread(FuncExchange(0, A1));
	Group2.create_thread(FuncExchange(7, A4));
	Group2.create_thread(FuncExchange(2, A2));
	Group2.create_thread(FuncExchange(4, " "));
	Group2.create_thread(FuncExchange(5, A3));
	Group2.create_thread(FuncExchange(8, "."));
	Group2.create_thread(FuncExchange(3, "!"));
	Group2.join_all();

	BOOST_CHECK(Buffer=="Hello world! Good bay.");

	// decrement

	StaticUnsignedLongWrap::exchange(60000);

	boost::thread_group Group3;
	Group3.create_thread(FuncDec<30000>());
	Group3.create_thread(FuncDec<25000>());
	Group3.create_thread(FuncDec< 4999>());
	Group3.join_all();

	BOOST_CHECK(StaticUnsignedLongWrap::read()==1);

	//

	return 0;
}
