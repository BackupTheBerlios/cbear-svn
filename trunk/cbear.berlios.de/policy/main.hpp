/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef CBEAR_BERLIOS_DE_POLICY_MAIN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_POLICY_MAIN_HPP_INCLUDED

#include <iostream>

// boost::equality_comparable, boost::less_than_comparable, 
// boost::dereferenceable
#include <boost/operators.hpp>
// boost::add_reference
#include <boost/type_traits/add_reference.hpp>
// boost::add_pointer
#include <boost/type_traits/add_pointer.hpp>
// boost::remove_pointer
#include <boost/type_traits/remove_pointer.hpp>

namespace cbear_berlios_de
{
namespace policy
{

template<class Type>
struct standard_policy
{
	typedef Type type;

	static void construct(type &This)
	{ 
		This = type();
	}

	static void construct_copy(type &This, const type &Source) 
	{ 
		This = Source; 
	}

	static void destroy(type &) 
	{
	}

	static void assign(type &This, const type &Source)
	{ 
		This = Source; 
	}

	static void swap(type &A, type &B)
	{
		type T = A; A = B; B = T;
	}

	static bool equal(const type &A, const type &B)
	{
		return A==B;
	}

	static bool less(const type &A, const type &B)
	{
		return A<B;
	}

	static void increment(type &A) { A++; }
	static void decrement(type &A) { A--; }

	typedef typename boost::remove_pointer<type>::type value_type;
	typedef typename boost::add_reference<value_type>::type reference;
	typedef typename boost::add_pointer<value_type>::type pointer;

	static reference reference_of(const type &This) { return *This; }

	template<class Stream>
	static void output(Stream &S, const type &This) { S << This; }
};

#pragma pack(push, 1)

template<
	class Type, 
	class InternalType, 
	class InternalPolicy = standard_policy<InternalType> >
class wrap: public boost::operators<Type>
{
public:

	typedef Type type;
	typedef InternalType internal_type;
	typedef InternalPolicy internal_policy;

	internal_type &internal() { return this->Internal; }
	const internal_type &internal() const { return this->Internal; }

	void swap(type &X) { internal_policy::swap(this->Internal, X.Internal); }

	friend bool operator==(const type &A, const type &B)
	{
		return internal_policy::equal(A.Internal, B.Internal);
	}

	friend bool operator<(const type &A, const type &B)
	{
		return internal_policy::less(A.Internal, B.Internal);
	}

	typename internal_policy::reference operator*() const
	{
		return internal_policy::reference_of(this->Internal);
	}

	typename internal_policy::pointer operator->() const
	{
		return &internal_policy::reference_of(this->Internal);
	}

	friend ::std::basic_ostream<char> &operator<<(
		::std::basic_ostream<char> &S, const type &A)
	{
		internal_policy::output(S, A.Internal);
		return S;
	}

	friend ::std::basic_ostream<wchar_t> &operator<<(
		::std::basic_ostream<wchar_t> &S, const type &A)
	{
		internal_policy::output(S, A.Internal);
		return S;
	}

	wrap &operator++()
	{
		internal_policy::increment(this->Internal);
		return *this;
	}

	wrap &operator--()
	{
		internal_policy::decrement(this->Internal);
		return *this;
	}

protected:

	wrap() 
	{ 
		internal_policy::construct(this->Internal); 
	}

	wrap(const wrap &Source)
	{
		internal_policy::construct_copy(this->Internal, Source.Internal);
	}

	wrap(const internal_type &Source) 
	{
		internal_policy::construct_copy(this->Internal, Source);
	}

	template<class SourceType>
	wrap(const SourceType &Source, int)
	{
		internal_policy::construct_copy(this->Internal, Source);
	}

	~wrap() 
	{
		internal_policy::destroy(this->Internal); 
	}

	wrap &operator=(const wrap &Source)
	{
		internal_policy::assign(this->Internal, Source.Internal);
		return *this;
	}

private:

	internal_type Internal;
};

template<class T>
class std_wrap: public wrap<std_wrap<T>, T>
{
	typedef wrap<std_wrap<T>, T> wrap_base;
public:
	std_wrap() {}
	explicit std_wrap(const T &X): wrap_base(X) {}
};

#pragma pack(pop)

}
}

#endif
