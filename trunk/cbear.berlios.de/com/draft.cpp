struct IUnknown { virtual void QueryInterface() = 0; };

struct A: IUnknown
{
	virtual int F() = 0;
};

struct B: IUnknown
{
	virtual int F() = 0;
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

struct I: wrap<A>, wrap<B> 
{
	int A_F() { return 1; }
	int B_F() { return 1; }
};

int main()
{
	I i;
	A &a = static_cast<A &>(i);
	B &b = static_cast<B &>(i);
	return 0;
}
