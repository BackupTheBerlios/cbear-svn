#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_ROOT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_ROOT_HPP_INCLUDED

#include <cbear.berlios.de/windows/registry/path.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

template<class Char>
class root: public path_base<Char, root<Char> >
{
public:
	typedef Char char_type;
	typedef path_base<char_type, root> base_type;
	typedef typename base_type::value_list_type value_list_type;
	typedef typename base_type::key_list_type key_list_type;

	registry::hkey hkey;

	root() {}

	explicit root(const registry::hkey &hkey): hkey(hkey) {}

	typedef typename base_type::create_options_type create_options_type;

	void create(const create_options_type &Options)
	{
		this->base_type::create(this->hkey, Options);
	}

	void delete_(const sam &Sam)
	{
		this->base_type::delete_(this->hkey, Sam);
	}
};

template<class Char>
class root_list: public std::vector<root<Char> >
{ 
public: 
	typedef Char char_type;
	typedef root<char_type> root_type;
	root_list &operator()(const root_type &R)
	{
		this->push_back(R);
		return *this;
	}

	typedef typename root_type::create_options_type create_options_type;

	void create(const create_options_type &Options)
	{
		for(range::sub_range<root_list>::type R(*this); !R.empty(); R.begin()++)
		{
			R.begin()->create(Options);
		}
	}

	void delete_(const sam &Sam)
	{
		for(range::sub_range<root_list>::type R(*this); !R.empty(); R.begin()++)
		{
			R.begin()->delete_(Sam);
		}
	}
};

}
}
}

#endif
