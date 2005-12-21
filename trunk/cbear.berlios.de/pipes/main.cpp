#pragma warning(push)
#pragma warning(disable: 4996)
#pragma warning(disable: 4510)
#include <iostream>
#include <fstream>
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 4267)
#pragma warning(disable: 4996)
#pragma warning(disable: 4100)
#pragma warning(disable: 4510)
#pragma warning(disable: 4610)
#pragma warning(disable: 4244)
#include <boost/multi_array.hpp>
#include <boost/cstdint.hpp>
#pragma warning(pop)

#include <cbear.berlios.de/intrusive/list.hpp>

namespace cbear_berlios_de
{

template<class T>
T root2(T X)
{
	T I = 1;
	for(; I * I < X; ++I);
	if(I * I > X) throw std::exception("root2");
	return I;
}

namespace pipes
{

typedef unsigned char value_type;

const value_type none = 0;

const value_type up = 1; // (-1, 0)
const value_type right = 2; // (0, 1)
const value_type down = 4; // (1, 0)
const value_type left = 8; // (0, -1)

const value_type horizontal = left | right;
const value_type vertical = up | down;

const value_type all = horizontal | vertical;

//   1        2
// 8 + 2 => 1 + 4
//   4        8
template<int I>
struct turn
{
	static const int D4I = 4 - I;
	static const value_type M = turn<I - 1>::M << 1 | 1;

	static value_type do_(value_type V) 
	{ 
		return (V >> I) | ((V & M) << D4I); 
	}
};

template<>
struct turn<0>
{
	static const value_type M = 0;
	static value_type do_(value_type V) { return V; }
};

class limits
{
public:
	value_type Low, High;

	limits(): Low(none), High(all) {}
	limits(value_type Low, value_type High): Low(Low), High(High) {}

	template<int Turn>
	void check(value_type V, limits &New) const
	{
		V = turn<Turn>::do_(V);
		if((V & this->Low) != this->Low || (V & this->High) != V) return;
		New.Low &= V;
		New.High |= V;
	}

	limits check_all(value_type V) const
	{
		limits Result(all, none);
		this->check<0>(V, Result);
		this->check<1>(V, Result);
		this->check<2>(V, Result);
		this->check<3>(V, Result);
		return Result;
	}

	bool is_defined() const { return this->Low == this->High; }

	bool operator==(const limits &B) const
	{
		return this->Low==B.Low && this->High==B.High;
	}

	bool operator!=(const limits &B) const
	{
		return this->Low!=B.Low || this->High!=B.High;
	}
};

class data
{
public:
	enum state
	{
		unknown,
		unchecked,
		defined,
	};
	state State;
	limits Limits;
	value_type Value;
	data(): State(unchecked) {}
};


class node: public intrusive::node<node>, public data
{
public:

	node() {}

	node(const node &X): data(X) {}

	node &operator=(const node &X)
	{
		static_cast<data*>(this)->operator=(X);
		return *this;
	}

	limits check() const { return this->Limits.check_all(this->Value); }
};

template<node::state State>
class list: private intrusive::list<node>
{
public:
	typedef intrusive::list<node> base_type;
	using base_type::begin;
	using base_type::end;
	void push_back(reference N)
	{
		this->base_type::push_back(N);
		N.State = State;
	}
	void push_front(reference N)
	{
		this->base_type::push_front(N);
		N.State = State;
	}
};

class solution
{
public:
	typedef std::vector<node> nodes;
	nodes Nodes;
	int N;

	//int DefinedSize;

	list<node::unchecked> Unchecked;
	list<node::unknown> Unknown;
	list<node::defined> Defined;

	class position
	{
	public:
		position(): X(0), Y(0) {}
		position(int X, int Y): X(X), Y(Y) {}
		int X, Y;

		template<value_type Direction>
		void move();	
		template<>
		void move<up>() { --this->Y; }
		template<>
		void move<down>() { ++this->Y; }
		template<>
		void move<left>() { --this->X; }
		template<>
		void move<right>() { ++this->X; }
	};

	int offset(const position &P) { return this->N * P.Y + P.X; }

	/*
	void set_unchecked(nodes::reference N)
	{
		N.State = node::unchecked;
	}
	*/

	void set_unchecked(const position &P, value_type High)
	{
		nodes::reference N = this->Nodes[this->offset(P)];
		//this->set_unchecked(N);
		this->Unchecked.push_back(N);
		N.Limits.High = High;
	}

	/*
	void set_defined(nodes::reference N)
	{
		N.State = node::defined;
		N.Value = N.Limits.High;
		++this->DefinedSize;
	}

	void set_unknown(nodes::reference N)
	{
		N.State = node::unknown;
	}
	*/

	explicit solution(const std::string &FileName)//: DefinedSize(0)
	{
		std::ifstream File(
			FileName.c_str(), std::ios::in|std::ios::binary|std::ios::ate);
		if(!File.is_open()) throw std::exception("the file couldn't be open.");
		std::size_t Size = File.tellg();
		this->N = int(root2(Size));
		this->Nodes.resize(Size);
		File.seekg(0, std::ios::beg);
		for(
			nodes::iterator I(this->Nodes.begin()); 
			I!=this->Nodes.end(); 
			++I)
		{
			char C;
			File.get(C);
			I->Value = C;			
		}
		File.close();

		// initializing

		int L = N - 1;

		this->set_unchecked(position(0, 0), right | down);
		this->set_unchecked(position(L, 0), left | down);
		this->set_unchecked(position(0, L), right | up);
		this->set_unchecked(position(L, L), left | up);

		position P;
		for(P.Y=1; P.Y<L; ++P.Y)
		{
			this->set_unchecked(position(P.Y, 0), horizontal | down);
			this->set_unchecked(position(P.Y, L), horizontal | up);
			this->set_unchecked(position(0, P.Y), vertical | right);
			this->set_unchecked(position(L, P.Y), vertical | left);
			for(P.X=1; P.X<L; ++P.X)
			{
				nodes::reference N = this->Nodes[this->offset(P)];
				if(N.Value==none || N.Value==all)
					this->Unchecked.push_back(N);
				else
					this->Unknown.push_back(N);
			}
		}
	}

	template<value_type Direction>
	int add(position P, limits Limits, int Offset)
	{
		P.move<Direction>();
		int NewOffset = this->offset(P);
		node &N = this->Nodes[NewOffset];
		if(N.State == node::defined) return Offset;
		Limits.Low &= Direction;
		Limits.High |= all ^ Direction;
		if(Limits.Low==none && Limits.High==all) return Offset;
		N.Limits.Low |= turn<2>::do_(Limits.Low);
		N.Limits.High &= turn<2>::do_(Limits.High);
		if(N.State != node::unknown) return Offset;
		this->Unchecked.push_front(N);
		return NewOffset - 1;
	}

	void check()
	{
		int L = this->N - 1;

		for(int Offset = 0; Offset < int(this->Nodes.size()); ++Offset)
		{
			node &Node = this->Nodes[Offset];
			if(Node.State==node::unchecked)
			{
				limits New = Node.check();
				if(New!=Node.Limits)
				{
					Node.Limits = New;
					position P(Offset % this->N, Offset / this->N);
					if(P.Y < L) this->add<down>(P, New, 0);
					if(P.X < L) this->add<right>(P, New, 0);
					if(P.X > 0) Offset = this->add<left>(P, New, Offset);
					if(P.Y > 0) Offset = this->add<up>(P, New, Offset);
				}						
				if(New.is_defined())
					this->Defined.push_front(Node);
				else
					this->Unknown.push_front(Node);
			}
		}
	}

	/*
	class guess
	{
	public:
		int Offset;
		int I;
		int M;
	};

	void fill()
	{
		std::vector<guess> Guess;
		for(int Offset = 0; Offset < this->Nodes.size(); ++Offset)
		{
			node &Node = this->Nodes[Offset];
			switch(Node.State)
			{
			case node::defined:

				break;
			case node::unknown:
				break;
			}
		}
	}
	*/
};

}
}

int main()
{
	namespace Pipes = cbear_berlios_de::pipes;
	int Result = 0;
	try
	{
		std::cout << "loading..." << std::endl;
		Pipes::solution Solution("problem.dat");
		std::cout << "checking..." << std::endl;
		Solution.check();
		std::cout << "finished" << std::endl;
	}
	catch(const std::exception &E)
	{
		std::cout << "error: " << E.what() << std::endl;
		Result = -1;
	}
	std::cout << "press 'enter' to exit" << std::endl;
	std::cin.get();
	return Result;
}