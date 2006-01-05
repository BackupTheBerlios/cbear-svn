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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STRUCT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STRUCT_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/traits.hpp>
#include <cbear.berlios.de/windows/com/object.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

typedef object< ::IRecordInfo> irecordinfo;

template<class Type, class ValueType>
class struct_t: public policy::wrap<Type, ValueType>
{
public:

	static const vartype_t vt = ::VT_RECORD;

	static irecordinfo record_info()
	{
		irecordinfo Result;
		::GetRecordInfoFromGuids(
			Type::lib_uuid().internal(), 
			1, 
			0, 
			0, 
			uuid::of<ValueType>().internal(),
			com::internal<out>(Result));
		return Result;
	}

	class extra_result: boost::noncopyable
	{
	public:
		operator void*() const { return this->R.internal(); }
	private:
		extra_result(const irecordinfo &R): R(R) {}
		friend class struct_t;
		irecordinfo R;
	};

	static extra_result extra() { return record_info(); }

protected:
	struct_t() {}
	struct_t(ValueType X): policy::wrap<Type, ValueType>(X) {}
};

}
}
}

#endif
