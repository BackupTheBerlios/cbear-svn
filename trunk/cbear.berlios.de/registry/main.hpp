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
#ifndef CBEAR_BERLIOS_DE_REGISTRY_MAIN_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_REGISTRY_MAIN_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace registry
{

class sam: public policy::wrap<sam, ::REGSAM>
{
	typedef policy::wrap<sam, ::REGSAM> wrap_type;
public:
	enum enumeration_type
	{
		all_access = KEY_ALL_ACCESS,
		create_link = KEY_CREATE_LINK,
		create_sub_key = KEY_CREATE_SUB_KEY,
		enumerate_sub_keys = KEY_ENUMERATE_SUB_KEYS,
		execute = KEY_EXECUTE,
		notify = KEY_NOTIFY,
		query_value = KEY_QUERY_VALUE,
		read = KEY_READ,
		set_value = KEY_SET_VALUE,
		wow64_32key = KEY_WOW64_32KEY,
		wow64_64key = KEY_WOW64_64KEY,
		write = KEY_WRITE,
		
	};
	sam(enumeration_type X): wrap_type(X) {}
};

typedef LONG long_t;

class exception: public base::exception
{
public:
	enum enumeration_type 
	{ 
		success = ::ERROR_SUCCESS; 
	};
	exception(long_t Result): Result(Result) {}
	virtual void what(::std::ostream &O) const
	{
		O << "cbear_berlios_de::registry::exception { result = " << this->Result << 
			" }";
	}
	long_t result() const { return this->Result; }
	static void throw_unless(long_t Result)
	{
		if(Result != success) throw exception(Result);
	}
private:
	long_t Result;
};

class hkey: public policy::wrap<hkey, ::HKEY>
{
	typedef policy::wrap<hkey, ::HKEY> wrap_type;
public:
	enum enumeration_type
	{
		classes_root = HKEY_CLASSES_ROOT,
		current_config = HKEY_CURRENT_CONFIG,
		current_user = HKEY_CURRENT_USER,
		users = HKEY_USERS,
	};

	hkey(enumeration_type X): wrap_type(X) {}

	hkey create(const wchar_t *X, sam Sam)
	{
		hkey Result;
		exception::throw_unless(RegCreateKeyExW(
			this->internal(), X, 0, Sam.internal(), Result));
		return Result;
	}
};

}
}

#endif
