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

//#pragma warning(push)
//#pragma warning(disable: 4512)
//#include <boost/assign.hpp>
//#include <boost/assign/std/vector.hpp>
//#pragma warning(pop)

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
typename registry::root_list<Char> coclass_registry(
	const uuid &TypeLib,
	const uuid &Clsid,
	const std::basic_string<Char> &Vendor, 
	const std::basic_string<Char> &Component,
	const std::basic_string<Char> &Version,
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

	string ViProgId = Vendor + Dot + Component;
	string ProgId = ViProgId + Dot + Version;

	ostream ClsidStream;
	ClsidStream << Clsid;
	string ClsidStr = Open + ClsidStream.str() + Close;

	ostream TypeLibStream;
	TypeLibStream << TypeLib;
	string TypeLibStr = Open + TypeLibStream.str() + Close;

	return root_list()
		(root(registry::hkey::classes_root)
			(key(ViProgId)
				(value(ViProgId))
				(key(ClsidKey)
					(value(ClsidStr))
				)
				(key(CurVerKey)
					(value(Version))
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
