#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_COCLASS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_COCLASS_HPP_INCLUDED

#include <boost/lexical_cast.hpp>

#include <cbear.berlios.de/base/swap.hpp>
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
	typedef base::basic_string<Char> string_type;
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

enum server_type
{
	local_server32,
	in_proc_server32,
};

template<class Char>
typename registry::root_list<Char> coclass_registry(
	const coclass_info<Char> &Info,
	const std::basic_string<Char> &FilePath,
	server_type ServerType)
{
	typedef registry::root_list<Char> root_list;
	typedef registry::root<Char> root;
	typedef registry::path<Char> path;
	typedef registry::key<Char> key;
	typedef registry::value<Char> value;
	typedef base::basic_string<Char> string;
	// typedef std::basic_ostringstream<Char> ostream;

	static const Char Dot = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, '.');
	static const Char Open = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, '{');
	static const Char Close = CBEAR_BERLIOS_DE_SELECT_CHAR(Char, '}');
	static const string ClsidKey = CBEAR_BERLIOS_DE_SELECT_STRING(Char, "CLSID");
	static const string CurVerKey = CBEAR_BERLIOS_DE_SELECT_STRING(Char, "CurVer");
	static const string LocalServer32Key = ServerType==local_server32 ? 
		move::copy<string>(CBEAR_BERLIOS_DE_SELECT_STRING(Char, "LocalServer32")):
		move::copy<string>(CBEAR_BERLIOS_DE_SELECT_STRING(Char, "InProcServer32"));
	static const string TypeLibKey = 
		CBEAR_BERLIOS_DE_SELECT_STRING(Char, "TypeLib");
	static const string ViProgIdKey = 
		CBEAR_BERLIOS_DE_SELECT_STRING(Char, "VersionIndependentProgId");
	static const string ProgIdKey = 
		CBEAR_BERLIOS_DE_SELECT_STRING(Char, "ProgId");

	string ViProgId = Info.vendor + Dot + Info.component;
	string ProgId = ViProgId + Dot + Info.version;

	string ClsidStr = Open + base::to_stream<string>(Info.id) + Close;
	string TypeLibStr = Open + base::to_stream<string>(Info.lib_id) + Close;

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
