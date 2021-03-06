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
	static const vartype_t vt = ::VT_INT;
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
