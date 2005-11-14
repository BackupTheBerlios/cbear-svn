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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_PATH_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_PATH_HPP_INCLUDED

#include <cbear.berlios.de/windows/registry/key.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

template<class Char>
class path;

template<class Char>
class path_base: public key_base<Char>
{
public:
	typedef key_base<Char> base_type;
	typedef typename base_type::value_list_type value_list_type;
	typedef typename base_type::key_list_type key_list_type;

	typedef path<Char> path_type;
	typedef std::vector<path_type> path_list_type;
	path_list_type path_list;
protected:
	path_base() {}

	template<class ValueList, class KeyList, class PathList>
	path_base(
		const ValueList &value_list, 
		const KeyList &key_list,
		const PathList &path_list):
		base_type(value_list, key_list), path_list(path_list)
	{
	}
};

template<class Char>
class path: public path_base<Char>
{
public:
	typedef std::basic_string<Char> string_type;
	string_type name;
};

}
}
}

#endif
