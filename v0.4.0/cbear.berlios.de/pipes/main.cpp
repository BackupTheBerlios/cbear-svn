#pragma warning(push)
#pragma warning(disable: 4996)
#pragma warning(disable: 4510)
#include <iostream>
#include <fstream>
#include <vector>
#pragma warning(pop)

#include <boost/timer.hpp>

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

class check_all_result: public limits
{
public:
	check_all_result(): limits(all, none), VariantListNumber(0) {}
	int VariantListNumber;

	template<int Turn>
	void check(const limits &Limits, value_type V)
	{
		V = turn<Turn>::do_(V);
		if((V & Limits.Low) != Limits.Low || (V & Limits.High) != V) return;
		this->Low &= V;
		this->High |= V;
		++this->VariantListNumber;
	}
};

check_all_result check_all(const limits &Limits, value_type V)
{
	check_all_result Result;
	Result.check<0>(Limits, V);
	Result.check<1>(Limits, V);
	Result.check<2>(Limits, V);
	Result.check<3>(Limits, V);
	return Result;
}

class data
{
public:
	enum state
	{
		unknown = 0,
		unchecked = 1,
		defined = 2,
		colored = 4,
		guess_root = 8,
		guess_defined = 0x10,
	};
	int Color;
	limits Limits;
	limits OldLimits;
	value_type Value;
	unsigned char State;
	unsigned char Variant;
	data(): Color(0), State(unchecked), Variant(1) {}
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

	check_all_result check() const { return check_all(this->Limits, this->Value); }
};

typedef intrusive::list<node> list_base;

template<node::state State>
class list: private list_base
{
public:

	using list_base::begin;
	using list_base::end;
	using list_base::size;
	using list_base::empty;
	using list_base::front;

	typedef list_base::iterator iterator;

	void push_back(reference N)
	{
		this->list_base::push_back(N);
		N.State = State;
	}
};

class solution
{
public:
	typedef std::vector<node> nodes;
	nodes Nodes;
	int N;

	list<node::unchecked> Unchecked;
	list<node::unknown> Unknown;
	list<node::defined> Defined;
	list<node::colored> Colored;
	list<node::guess_root> GuessRoot;
	list<node::guess_defined> GuessDefined;

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

	void set_unchecked(const position &P, value_type High)
	{
		node &N = this->Nodes[this->offset(P)];
		this->Unchecked.push_back(N);
		N.Limits.High = High;
	}

	explicit solution(const std::string &FileName): LastColor(0)
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

	position get_position(node &Node)
	{
		int Offset = int(&Node - &*this->Nodes.begin());
		return position(Offset % this->N, Offset / this->N);
	}

	template<value_type Direction>
	void check_push_back(position P, limits Limits)
	{
		P.move<Direction>();
		node &N = this->Nodes[this->offset(P)];
		switch(N.State)
		{
		case node::defined: case node::colored: case node::guess_root: return;
		}
		Limits.Low &= Direction;
		Limits.High |= all ^ Direction;
		if(Limits.Low==none && Limits.High==all) return;
		N.Limits.Low |= turn<2>::do_(Limits.Low);
		N.Limits.High &= turn<2>::do_(Limits.High);
		if(N.State != node::unchecked) return;
		this->Unchecked.push_back(N);
	}

	void check_around_push_back(node &Node)
	{
		int L = this->N - 1;
		position P = this->get_position(Node);
		if(P.Y < L) this->check_push_back<down>(P, Node.Limits);
		if(P.X < L) this->check_push_back<right>(P, Node.Limits);
		if(P.X > 0) this->check_push_back<left>(P, Node.Limits);
		if(P.Y > 0) this->check_push_back<up>(P, Node.Limits);
	}

	void check()
	{
		while(!this->Unchecked.empty())
		{
			node &Node = this->Unchecked.front();
			check_all_result New = Node.check();
			if(New!=Node.Limits)
			{
				Node.Limits = New;
				this->check_around_push_back(Node);
			}
			if(New.is_defined())
				this->Defined.push_back(Node);
			else
				this->Unknown.push_back(Node);
		}
	}

	int LastColor;

	template<value_type Direction>
	void fill_push_back(position P, value_type Value)
	{
		if((Value & Direction) == 0) return;
		P.move<Direction>();
		node &N = this->Nodes[this->offset(P)];
		if(N.State!=node::defined) return;
		this->Unchecked.push_back(N);
	}

	void fill()
	{
		while(!this->Defined.empty())
		{
			++this->LastColor;
			this->Unchecked.push_back(Defined.front());
			do
			{
				node &Node = this->Unchecked.front();
				position P = this->get_position(Node);
				value_type V = Node.Limits.High;
				this->fill_push_back<up>(P, V);
				this->fill_push_back<right>(P, V);
				this->fill_push_back<down>(P, V);
				this->fill_push_back<left>(P, V);
				Node.Color = this->LastColor;
				this->Colored.push_back(Node);
			} while(!this->Unchecked.empty());
		}
	}

	void guess_check()
	{
		while(!this->Unchecked.empty())
		{
			node &Node = this->Unchecked.front();
			check_all_result New = Node.check();
			if(New!=Node.Limits)
			{
				Node.Limits = New;
				this->check_around_push_back(Node);
			}
			if(New.is_defined())
			{
				this->GuessDefined.push_back(Node);
			}
			else
				this->Unknown.push_back(Node);
		}
	}

	bool guess_push_back(node &Node)
	{
		value_type X = Node.Limits.Low ^ Node.Limits.High;
		while(Node.Variant!=all)
		{
			if((Node.Variant & X) == Node.Variant)
			{
				limits Limits = Node.Limits;
				Limits.Low |= Node.Variant;
				check_all_result Result = check_all(Limits, Node.Value);
				if(Result.VariantListNumber==1)
				{
					++this->LastColor;
					Node.OldLimits = Node.Limits;
					Node.Limits = Result;
					Node.Color = this->LastColor;
					this->GuessRoot.push_back(Node);
					this->check_around_push_back(Node);
					return true;
				}
			}
			++Node.Variant;
		}
		return false;
	}

	void guess()
	{
		while(this->Unknown.empty())
		{
			if(guess_push_back(this->Unknown.front()))
			{
				
			}
			else // pop_back
			{
			}
		}
	}
};

}
}

int main()
{
	namespace Pipes = cbear_berlios_de::pipes;
	int Result = 0;
	try
	{
		boost::timer Timer;
		std::cout << "loading..." << std::endl;
		Pipes::solution Solution("problem.dat");
		std::cout << sizeof(Pipes::node) * Solution.Nodes.size() << " B." << std::endl;
		std::cout << Timer.elapsed() << " s." << std::endl;
		std::cout << "checking..." << std::endl;
		Solution.check();
		std::cout << Timer.elapsed() << " s." << std::endl;
		std::cout << "filling..." << std::endl;
		Solution.fill();
		std::cout << Timer.elapsed() << " s." << std::endl;
		std::cout << Solution.LastColor << std::endl;
		std::cout << "finished." << std::endl;
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