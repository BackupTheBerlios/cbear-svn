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

template<class Char, class Child>
class path_base: public key_base<Char, Child>
{
public:
	typedef key_base<Char, Child> base_type;
	typedef typename base_type::value_list_type value_list_type;
	typedef typename base_type::key_list_type key_list_type;

	using base_type::operator();

	typedef path<Char> path_type;
	typedef list<path_type> path_list_type;
	path_list_type &path_list() { return this->PathList; }
	const path_list_type &path_list() const { return this->PathList; }
	Child &operator()(const path_list_type &PathList)
	{
		this->PathList = PathList; 
		return this->This();
	}
	Child &operator()(const path_type &Path)
	{
		this->PathList.push_back(Path);
		return this->This();
	}

	typedef typename base_type::create_options_type create_options_type;

	void create(const hkey &HKey, const create_options_type &Options)
	{
		this->base_type::create(HKey, Options);
		for(
			range::sub_range<path_list_type>::type R(this->PathList);
			!R.empty();
			R.begin()++)
		{
			R.begin()->create(HKey, Options);
		}
	}

	void delete_(const hkey &HKey, const sam &Sam)
	{
		this->base_type::delete_(HKey, Sam);
		for(
			range::sub_range<path_list_type>::type R(this->PathList);
			!R.empty();
			R.begin()++)
		{
			R.begin()->delete_(HKey, Sam);
		}
	}

protected:
	path_base() {}
private:
	path_list_type PathList;
};

template<class Char>
class path: public path_base<Char, path<Char> >
{
public:
	typedef path_base<Char, path<Char> > base_type;
	typedef base::basic_string<Char> string_type;

	string_type name;

	explicit path(const string_type &name): name(name) {}

	typedef typename base_type::create_options_type create_options_type;

	void create(const hkey &HKey, const create_options_type &Options)
	{
		hkey SubKey = HKey.open<char_type>(name, Options.sam);
		this->base_type::create(SubKey, Options);
		SubKey.close();
	}
	void delete_(const hkey &HKey, const sam &Sam)
	{
		hkey SubKey = HKey.open<char_type>(name, Sam);
		this->base_type::delete_(SubKey, Sam);
		SubKey.close();
	}
};

}
}
}

#endif
