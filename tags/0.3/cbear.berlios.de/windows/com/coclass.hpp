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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_COCLASS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_COCLASS_HPP_INCLUDED

#include <cbear.berlios.de/base/default.hpp>
#include <cbear.berlios.de/windows/com/uuid.hpp>
#include <cbear.berlios.de/windows/registry/root.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

template<class Char>
class coclass_info
{
public:
	typedef std::basic_string<Char> string_type;
	uuid lib_id;
	uuid id;
	string_type vendor;
	string_type component;
	string_type version;

	coclass_info(
		const uuid &lib_id, 
		const uuid &id, 
		const string_type &vendor,
		const string_type &component,
		const string_type &version):
		lib_id(lib_id), 
		id(id), 
		vendor(vendor), 
		component(component), 
		version(version)
	{
	}
};

template<class Char>
typename registry::root_list<Char> coclass_registry(
	const coclass_info<Char> &Info,
	const std::basic_string<Char> &FilePath)
{
	typedef registry::root_list<Char> root_list;
	typedef registry::root<Char> root;
	typedef registry::path<Char> path;
	typedef registry::key<Char> key;
	typedef registry::value<Char> value;
	typedef std::basic_string<Char> string;
	typedef std::basic_ostringstream<Char> ostream;

	static const Char Dot = select<Char>('.', L'.');
	static const Char Open = select<Char>('{', L'{');
	static const Char Close = select<Char>('}', L'}');
	static const string ClsidKey = select<Char>("CLSID", L"CLSID");
	static const string CurVerKey = select<Char>("CurVer", L"CurVer");
	static const string LocalServer32Key = select<Char>(
		"LocalServer32", L"LocalServer32");
	static const string TypeLibKey = select<Char>("TypeLib", L"TypeLib");
	static const string ViProgIdKey = select<Char>(
		"VersionIndependentProgId", L"VersionIndependentProgId");
	static const string ProgIdKey = select<Char>(
		"ProgId", L"ProgId");

	string ViProgId = Info.vendor + Dot + Info.component;
	string ProgId = ViProgId + Dot + Info.version;

	string ClsidStr = Open + boost::lexical_cast<string>(Info.id) + Close;
	string TypeLibStr = Open + boost::lexical_cast<string>(Info.lib_id) + Close;

	return root_list()
		(root(registry::hkey::classes_root)
			(key(ViProgId)
				(value(ViProgId))
				(key(ClsidKey)
					(value(ClsidStr))
				)
				(key(CurVerKey)
					(value(Info.version))
				)
			)
			(key(ProgId)
				(value(ProgId))
				(key(ClsidKey)
					(value(ClsidStr))
				)
			)
			(path(ClsidKey)
				(key(ClsidStr)
					(key(LocalServer32Key)
						(value(FilePath))
					)
					(key(TypeLibKey)
						(value(TypeLibStr))
					)
					(key(ViProgIdKey)
						(value(ViProgId))
					)
					(key(ProgIdKey)
						(value(ProgId))
					)
				)
			)
		);
}

}
}
}

#endif
