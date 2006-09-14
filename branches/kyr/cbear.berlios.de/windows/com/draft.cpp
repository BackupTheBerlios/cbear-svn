struct IUnknown { virtual void QueryInterface() = 0; };

struct A: IUnknown
{
	virtual int F() = 0;
};

struct B: IUnknown
{
	virtual int F() = 0;
};

struct C: B
{
	virtual int FF() = 0;
};

struct base
{
	void query_interface() {}
};

template<class T, class Base = T>
struct wrap: Base, virtual base
{
	void QueryInterface() { base::query_interface(); }
};

template<class Base>
struct wrap<A, Base>: wrap<IUnknown, Base>
{
	virtual int A_F() = 0;
	int F() { return A_F(); }
};

template<class Base>
struct wrap<B, Base>: wrap<IUnknown, Base>
{
	virtual int B_F() = 0;
	int F() { return B_F(); }
};

template<class Base>
struct wrap<C, Base>: wrap<B, Base>
{
	virtual int C_FF() = 0;
	int FF() { return C_FF(); }
};

struct I: wrap<A>, wrap<C> 
{
	int A_F() { return 1; }
	int B_F() { return 2; }
	int C_FF() { return 3; }
};

int main()
{
	I i;
	A &a = static_cast<A &>(i);
	B &b = static_cast<B &>(i);
	C &c = static_cast<C &>(i);
	return 0;
}
