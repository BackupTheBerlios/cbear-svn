#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_ENUM_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_ENUM_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/traits.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

template<class InternalType>
class enum_policy: public policy::standard_policy<InternalType>
{
public:
	static void increment(InternalType &X) { X = InternalType(X + 1); }
};

template<class Type, class ValueType>
class enum_t: public policy::wrap<Type, ValueType, enum_policy<ValueType> >
{
public:
	typedef void *extra_result;
	typedef Type move_type;
	static vartype_t::enum_t const vt = vartype_t::int_;
	template<class ArchiveT>
	void serialize(ArchiveT &Archive, const unsigned int )
	{
		Archive & boost::serialization::make_nvp("enum", this->internal());
	}
	void move_assign(enum_t &F)
	{
		this->internal() = F.internal();
	}
protected:
	enum_t() {}
	enum_t(ValueType X): policy::wrap<Type, ValueType, enum_policy<ValueType> >(X) 
	{
	}
};

}
}
}

#endif
