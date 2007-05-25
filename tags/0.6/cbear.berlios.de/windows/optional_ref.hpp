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
