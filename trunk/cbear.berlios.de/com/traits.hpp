/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.sourceforge.net)

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
#ifndef CBEAR_SOURCEFORGE_NET_COM_TRAITS_HPP_INCLUDED
#define CBEAR_SOURCEFORGE_NET_COM_TRAITS_HPP_INCLUDED

#include <cbear.sourceforge.net/policy/main.hpp>

// boost::mpl::if_
#include <boost/mpl/if.hpp>
// boost::is_class
#include <boost/type_traits/is_class.hpp>

namespace cbear_sourceforge_net
{
namespace com
{

template<class Type>
struct class_traits
{
	typedef Type type;
	typedef typename type::internal_policy internal_policy;
};

template<class Type>
struct default_traits
{
	typedef Type type;
	typedef policy::standard_policy<type> internal_policy;
};

template<class Type>
struct traits: boost::mpl::if_<
	boost::is_class<Type>, class_traits<Type>, default_traits<Type> >::type
{
};

}
}

#endif
