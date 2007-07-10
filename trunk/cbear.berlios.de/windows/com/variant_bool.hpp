#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_VARIANT_BOOL_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_VARIANT_BOOL_HPP_INCLUDED

#include <cbear.berlios.de/base/undefined.hpp>
#include <cbear.berlios.de/windows/com/traits.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class variant_bool_t;

namespace detail
{

class variant_bool_policy: policy::standard_policy< ::VARIANT_BOOL>
{
public:
	typedef ::VARIANT_BOOL type;
	typedef policy::standard_policy<type> standard_policy;
	using standard_policy::construct;
	using standard_policy::construct_copy;
	using standard_policy::destroy;
	using standard_policy::assign;
	using standard_policy::swap;
	using standard_policy::equal;

	typedef base::undefined pointer;
	typedef base::undefined reference;

	static bool cast(type This) 
	{ 
		return This != VARIANT_FALSE; 
	}

	template<class Stream>
	static void output(Stream &S, type This) 
	{ 
		S << cast(This); 
	}
};

typedef policy::wrap<variant_bool_t, ::VARIANT_BOOL, variant_bool_policy> 
	variant_bool_wrap;

}

class variant_bool_t: public detail::variant_bool_wrap
{
public:
	typedef void *extra_result;
	static vartype_t::enum_t const vt = vartype_t::bool_;
	typedef detail::variant_bool_wrap::internal_policy internal_policy;
	typedef variant_bool_t move_type;
	variant_bool_t() 
	{
	}
	explicit variant_bool_t(bool X): 
		detail::variant_bool_wrap(X ? VARIANT_TRUE: VARIANT_FALSE)
	{
	}
	static extra_result extra()
	{
		return 0;
	}
	operator bool() const 
	{ 
		return internal_policy::cast(this->internal()); 
	}
	template<class Stream>
	void write(Stream &O) const
	{
		O << internal_policy::cast(this->internal());
	}
	template<class ArchiveT>
	void serialize(ArchiveT &Archive, const unsigned int Version)
	{
		Archive & boost::serialization::make_nvp("bool", this->internal());
	}
	void move_assign(variant_bool_t &F)
	{
		this->internal() = F.internal();
	}
	template<class Stream>
	void binary_write(Stream &S) const
	{
		S << (internal_policy::cast(this->internal()) ? char(1): char(0));
	}
	template<class Stream>
	void binary_read(Stream &S)
	{
		char V;
		S >> V;
		this->internal() = V ? VARIANT_TRUE: VARIANT_FALSE;
	}
};

}
}
}

#endif
