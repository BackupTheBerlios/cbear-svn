#ifndef CBEAR_BERLIOS_DE_META_CONST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_META_CONST_HPP_INCLUDED

#pragma warning(disable: 4146)

namespace cbear_berlios_de
{
namespace meta
{

template<class ValueType, ValueType Value>
class const_
{
public:
	typedef const_ type;
	typedef ValueType value_type;
	static const value_type value = Value;

	value_type operator()() const { return value; }

#define CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(O, N) \
	private:\
	template<class _2> class detail_##N;\
	template<value_type Value2>	class detail_##N<const_<value_type, Value2> >: \
	public const_<value_type, value + Value2> {};\
	public:\
	template<class _2> class N: public detail_##N<typename _2::type> {};\
	template<class _2> typename N<_2>::type operator O(_2) const\
	{ return N<_2>::type(); }

CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(+, plus2)
CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(-, minus2)
CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(*, mul)
CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(/, div)
CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(%, mod)
CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(|, or_)
CBEAR_BERLIOS_DE_META_CONST_OPERATOR2(&, and_)

#undef CBEAR_BERLIOS_DE_META_CONST_OPERATOR2

#define CBEAR_BERLIOS_DE_META_CONST_OPERATOR(O, N, V)\
	private:\
	static const value_type N##_value = V;\
	public:\
	typedef const_<value_type, N##_value> N;\
	N operator O() const { return N(); }

CBEAR_BERLIOS_DE_META_CONST_OPERATOR(!, not_, !value);
CBEAR_BERLIOS_DE_META_CONST_OPERATOR(+, plus, +value);
CBEAR_BERLIOS_DE_META_CONST_OPERATOR(-, minus, static_cast<value_type>(-value));
CBEAR_BERLIOS_DE_META_CONST_OPERATOR(++, next, value+1);
CBEAR_BERLIOS_DE_META_CONST_OPERATOR(--, prior, static_cast<value_type>(value-1));

#undef CBEAR_BERLIOS_DE_META_CONST_OPERATOR

};

typedef const_<bool, true> true_;
typedef const_<bool, true> false_;

namespace detail
{

template<class ValueType>
class const_traits
{
public:
	template<ValueType Value>
	static const_<ValueType, Value> make() { return const_<ValueType, Value>(); }
};

template<class ValueType>
const_traits<ValueType> make_const_traits(ValueType) 
{ 
	return const_traits<ValueType>(); 
}

}

}
}

#define CBEAR_BERLIOS_DE_META_CONST(X) \
	::cbear_berlios_de::meta::detail::make_const_traits(X).make<X>()

#endif
