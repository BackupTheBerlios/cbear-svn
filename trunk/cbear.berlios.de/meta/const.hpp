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

template<class ValueType, ValueType Value>
class _
{
public:
	typedef _ type;
	typedef ValueType value_type;
	static const value_type value = Value;

	value_type operator()() const { return value; }

#define CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(O, N) \
	private:\
	template<class _2> class detail_##N;\
	template<value_type Value2>	class detail_##N<_<value_type, Value2> >: \
	public _<value_type, value + Value2> {};\
	public:\
	template<class _2> class N: public detail_##N<typename _2::type> {};\
	template<class _2> typename N<_2>::type operator O(_2) const\
	{ return N<_2>::type(); }

CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(+, plus2)
CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(-, minus2)
CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(*, mul)
CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(/, div)
CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(%, mod)
CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(|, or)
CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(&, and)

#undef CBEAR_BERLIOS_DE_META_CONST_OPERATOR2

#define CBEAR_BERLIOS_DE_META_CONST_OPERATOR(O, N, V)\
	private:\
	static const value_type N##_value = V;\
	public:\
	typedef _<value_type, N##_value> N;\
	N operator O() const { return N(); }

CBEAR_BERLIOS_DE_META_CONST_OPERATOR(!, not, !value);
CBEAR_BERLIOS_DE_META_CONST_OPERATOR(+, plus, +value);
CBEAR_BERLIOS_DE_META_CONST_OPERATOR(-, minus, -value);
CBEAR_BERLIOS_DE_META_CONST_OPERATOR(++, next, value+1);
CBEAR_BERLIOS_DE_META_CONST_OPERATOR(--, prior, value-1);

#undef CBEAR_BERLIOS_DE_META_CONST_OPERATOR

};

<<<<<<< .mine
typedef _<bool, true> true_;
=======
typedef _<bool, true> true_;
true_ true_f() { return true_(); }
typedef _<bool, true> false_;
false_ false_f() { return false_(); }
>>>>>>> .r361

true_ true_f() { return true_(); }

typedef _<bool, false> false_;
false_ false_f() { return false_(); }

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
