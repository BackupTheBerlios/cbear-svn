class IUnknown
{
public:
	virtual int AddRef() = 0;
	virtual int Release() = 0;
	virtual void *QueryInterface(int Uuid) = 0;
};

//

class A: public IUnknown
{
public:
	virtual int F() = 0;
};

class B: public IUnknown
{
public:
	virtual int F() = 0;
};

//

class Base: public IUnknown
{
public:
	virtual int AddRef() { return 0; }
	virtual int Release() { return 0; }
	virtual void *QueryInterface(int Uuid) { return 0; }
protected:
	void add_interface(int Uuid, void *P) {}
};

template<class T>
class WrapBase: public T, public virtual Base
{
public:
	WrapBase() { Base::add_interface(0, static_cast<T *>(this)); }
};

template<class T>
class Wrap: public WrapBase<T> {};

//

template<>
class Wrap<A>: public WrapBase<A>
{
public:
	virtual int A_F() = 0;
	int A() { return A_F(); }
};

template<>
class Wrap<B>: public WrapBase<B>
{
public:
	virtual int B_F() = 0;
	int B() { return B_F(); }
};

//

class I: public Wrap<A>, public Wrap<B>
{
public:
	int A_F() { return 1; }
	int B_F() { return 2; }
};

int main()
{
	I i;
	return 0;
}