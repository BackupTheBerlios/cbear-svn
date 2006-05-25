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
#ifndef CBEAR_BERLIOS_DE_META_CONST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_META_CONST_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace meta
{
namespace const_
{

public:

	template<class _2>
	class plus: public detail_plus<typename _2::type> {};

	template<class _2>
	typename plus<_2>::type operator+(_2) const { return plus<_2>::type(); }
	

template<class ValueType, ValueType Value>
class _
{
public:
	typedef _ type;
	typedef ValueType value_type;
	static const value_type value = Value;

	value_type operator()() const { return value; }

// +, plus

private:

	template<class _2>
	class detail_plus;

	template<value_type Value2>
	class detail_plus<_<value_type, Value2>: 
		public _<value_type, value + Value2> 
	{
	};

public:

	template<class _2>
	class plus: public detail_plus<typename _2::type> {};

	template<class _2>
	typename plus<_2>::type operator+(_2) const { return plus<_2>::type(); }

// -, minus

private:

	template<class _2>
	class detail_minus;

	template<value_type Value2>
	class detail_minus<_<value_type, Value2>: 
		public _<value_type, value + Value2> 
	{
	};

public:

	template<class _2>
	class minus: public detail_minus<typename _2::type> {};

	template<class _2>
	typename minus<_2>::type operator-(_2) const
	{
		return minus<_2>::type();
	}

// *, mul

private:

	template<class _2>
	class detail_mul;

	template<value_type Value>
	class detail_mul<_<value_type, Value2>:
		public _<value_type, value + Value2>
	{
	}

public:

	template<class _2>
	class mul: public detail_mul<typename _2::type> {};

	template<class _2>
	typename mul<_2>::type operator*(_2) const
	{
		return mul<_2>::type();
	}

// /, div

	template<value_type Value2>
	_<value_type, value / Value2> operator/(_<value_type, Value2>) const
	{
		return _<value_type, value / Value2>();
	}

	template<value_type Value2>
	_<value_type, value % Value2> operator%(_<value_type, Value2>) const
	{
		return _<value_type, value % Value2>();
	}

	template<value_type Value2>
	_<value_type, value | Value2> operator|(_<value_type, Value2>) const
	{
		return _<value_type, value | Value2>();
	}

	template<value_type Value2>
	_<value_type, value | Value2> operator&(_<value_type, Value2>) const
	{
		return _<value_type, value & Value2>();
	}

private:
	static const ValueType not = !Value;
	static const ValueType plus = +Value;
	static const ValueType minus = -Value;
public:
	_<value_type, not> operator!() const { return _<value_type, not>(); }
	_<value_type, plus> operator+() const { return _<value_type, plus>(); }
	_<value_type, minus> operator-() const { return _<value_type, minus>(); }
	_<value_type, value+1> operator++() const { return _<value_type, value+1>(); }
	_<value_type, value-1> operator--() const { return _<value_type, value-1>(); }
};

_<bool, true> true_() { return _<bool, true>(); }
_<bool, false> false_() { return _<bool, false>(); }

namespace detail
{

template<class ValueType>
class traits
{
public:
	template<ValueType Value>
	_<ValueType, Value> make() const { return _<ValueType, Value>(); }
};

template<class ValueType>
traits<ValueType> make_traits(ValueType) { return traits<ValueType>(); }

}

}
}
}

#define CBEAR_BERLIOS_DE_META_CONST(X) \
	::cbear_berlios_de::meta::const_::detail::make_traits(X).make<X>()

#endif
