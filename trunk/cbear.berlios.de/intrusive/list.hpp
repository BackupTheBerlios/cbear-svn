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
#ifndef CBEAR_BERLIOS_DE_INTRUSIVE_LIST_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_INTRUSIVE_LIST_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace intrusive
{

template<class Key, class T>
class list
{
public:

	typedef Key key_type;
	typedef T value_type;

	class node_type;

	template<class VT>
	class basic_iterator_policy: private policy::std_policy<VT *>
	{
	public:
		typedef policy::std_policy<VT *> std_policy;
		using std_policy::construct;
		using std_policy::construct_copy;
		using std_policy::destruct;
		using std_policy::assign;
	};

	template<class VT>
	class basic_iterator: 
		public policy::wrap<basic_iterator<VT>, VT *, basic_iterator_policy<VT> >
	{
	};

	typedef basic_iterator<T> iterator;
	typedef basic_iterator<const T> const_iterator;

	typedef value_type &reference;
	typedef const value_type &const_reference;

	typedef value_type *pointer;
	typedef const value_type *const_pointer;

	typedef std::size_t size_type;	
	typedef std::ptrdiff_t difference_type;

	class node_type: boost::noncopyable
	{
	protected:
		node_type(const key_type &Key): Key(Key) {}
		~node_type() {}
	private:		
		key_type Key;
		policy::std_wrap<list *> List;
		iterator Next, Prev;

		void disconnect(list &List, iterator P)
		{
			if(List.begin()==P)
			{
			}
			else if(List.end()==P)
			{
			}
			else
			{
			}
		}

		void connect(list &List, iterator P, reference X)
		{
			if(List.begin()==P)
			{
			}
			else if(List.end()==P)
			{
			}
			else
			{
			}
		}
	};

	bool empty() const;
	std::size_t size() const;

	T& operator[](const key_type &K);

	void insert(iterator P, reference X)
	{
	}
};

}
}

#endif
