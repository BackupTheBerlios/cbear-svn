#ifndef CBEAR_BERLIOS_DE_WINDOWS_OPTIONAL_REF_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_OPTIONAL_REF_HPP_INCLUDED

#include <cbear.berlios.de/base/initialized.hpp>

namespace cbear_berlios_de
{
namespace windows
{

template<class T>
class optional_ref: public base::initialized<T *>
{
private:

	typedef base::initialized<T *> base_t;

public:

	optional_ref() {}
	optional_ref(T &X): base_t(&X) {}

	typedef typename T::value_t value_value_t;
	typedef typename boost::mpl::if_<
		boost::is_const<T>, const value_value_t, value_value_t>::type 
		value_t;

	value_t *get() const
	{
		return this->base_t::get() ? &this->base_t::get()->get(): 0;
	}
};

}
}

#endif
