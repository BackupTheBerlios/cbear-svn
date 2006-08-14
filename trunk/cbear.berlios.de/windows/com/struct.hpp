#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STRUCT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STRUCT_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/traits.hpp>
#include <cbear.berlios.de/windows/com/pointer.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

typedef pointer< ::IRecordInfo> irecordinfo;

template<class Type, class ValueType>
class struct_t
{
public:

	class internal_policy
	{
	public:
		typedef ValueType type;
		static void construct(type &X)
		{
			new(&X) struct_t();
		}
	};

	typedef move::t<Type> move_type;

	static const vartype_t::enum_t vt = vartype_t::record;

	typedef void *extra_result;

	static irecordinfo record_info;

	class scoped_info
	{
	public:
		scoped_info()
		{
			exception::throw_unless(::GetRecordInfoFromTypeInfo(
				Type::library_info::typelib().gettypeinfoofguid<ValueType>().c_in(),
				com::internal<out>(record_info)));
		}
	};

	static extra_result extra() 
	{ 
		BOOST_STATIC_ASSERT(sizeof(Type)==sizeof(ValueType));
		return record_info.c_in();
	}

	ValueType &internal()
	{
		return *cast::traits<ValueType *>::reinterpret(static_cast<Type *>(this));
	}

	const ValueType &internal() const
	{
		return *cast::traits<const ValueType *>::reinterpret(
			static_cast<const Type *>(this));
	}

	static Type &wrap_ref(ValueType &X)
	{
		return *cast::traits<Type *>::reinterpret(static_cast<ValueType *>(&X));
	}

protected:
	~struct_t() 
	{
		BOOST_STATIC_ASSERT(sizeof(Type)==sizeof(ValueType));
	}
};

template<class Type, class ValueType>
irecordinfo struct_t<Type, ValueType>::record_info;

}
}
}

#endif
