#ifndef CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_KEY_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_REGISTRY_KEY_HPP_INCLUDED

#pragma warning(push)
// 'class' : assignment operator could not be generated
#pragma warning(disable: 4512)
// 'identifier' : unreferenced formal parameter
#pragma warning(disable: 4100)
// unreachable code
#pragma warning(disable: 4702)
#include <boost/variant.hpp>
#pragma warning(pop)

#include <cbear.berlios.de/windows/registry/hkey.hpp>
#include <cbear.berlios.de/windows/registry/list.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace registry
{

template<class Char>
class key;

template<class Char, class Child>
class key_base
{
public:

	typedef Char char_type;

	typedef value<char_type> value_type;
	typedef list<value_type> value_list_type;
	value_list_type &value_list() { return this->ValueList; }
	const value_list_type &value_list() const { return this->ValueList; }
	Child &operator()(const value_list_type &ValueList)
	{
		this->ValueList = ValueList; 
		return this->This();
	}
	Child &operator()(const value_type &Value)
	{
		this->ValueList.push_back(Value);
		return this->This();
	}

	typedef key<char_type> key_type;
	typedef list<key_type> key_list_type;
	key_list_type &key_list() { return this->KeyList; }
	const key_list_type &key_list() const { return this->KeyList; }
	Child &operator()(const key_list_type &KeyList) 
	{ 
		this->KeyList = KeyList; 
		return this->This();
	}
	Child &operator()(const key_type &Key)
	{
		this->KeyList.push_back(Key);
		return this->This();
	}

	typedef hkey::create_options<char_type> create_options_type;

	void create(hkey HKey, const create_options_type &Options)
	{
		for(
			range::sub_range<value_list_type>::type A(this->ValueList);
			!A.empty();
			A.begin()++)
		{
			HKey.set_value(*A.begin());
		}
		for(
			range::sub_range<key_list_type>::type E(this->KeyList);
			!E.empty();
			E.begin()++)
		{
			E.begin()->create(HKey, Options);
		}
	}

	void delete_(hkey HKey, const sam &Sam) const
	{
		for(
			range::sub_range<const value_list_type>::type A(this->ValueList);
			!A.empty();
			A.begin()++)
		{
			HKey.delete_value<char_type>(A.begin()->first);
		}
		for(
			range::sub_range<const key_list_type>::type E(this->KeyList);
			!E.empty();
			E.begin()++)
		{
			E.begin()->delete_(HKey, Sam);
		}
	}
protected:

	key_base() {}

	Child &This() { return *static_cast<Child *>(this); }
	const Child &This() const { return *static_cast<const Child *>(this); }

private:

	value_list_type ValueList;
	key_list_type KeyList;
};

template<class Char>
class key: public key_base<Char, key<Char> >
{
public:

	typedef Char char_type;
	typedef key_base<char_type, key> base_type;
	typedef base::basic_string<char_type> string_type;

	string_type name;

	typedef hkey::create_options<char_type> create_options_type;

	key() {}
	explicit key(const string_type name): name(name) {}

	void create(hkey HKey, const create_options_type &Options)
	{
		hkey SubKey = HKey.create<char_type>(this->name, Options).hkey;
		this->base_type::create(SubKey, Options);
		SubKey.close();
	}

	void delete_(hkey HKey, const sam &Sam) const
	{
		hkey SubKey = HKey.open<char_type>(this->name, Sam);
		this->base_type::delete_(SubKey, Sam);
		SubKey.close();
		HKey.delete_<char_type>(this->name);
	}
};

}
}
}

#endif
