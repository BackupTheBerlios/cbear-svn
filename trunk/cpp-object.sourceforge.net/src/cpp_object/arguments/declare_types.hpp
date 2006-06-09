#ifndef CPP_OBJECT_ARGUMENTS_DECLARE_TYPES_HPP
#define CPP_OBJECT_ARGUMENTS_DECLARE_TYPES_HPP

#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif // _MSC_VER && _MSC_VER >= 1020

#include <boost/call_traits.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_pointer.hpp>

namespace cpp_object
{
namespace arguments
{

/// Declares basic types
template
< typename This
, typename T
>
struct declare_types
{
    typedef typename boost::call_traits<T>::value_type value_type;
    typedef typename boost::call_traits<T>::reference reference;
    typedef typename boost::call_traits<T>::const_reference const_reference;
    typedef typename boost::add_pointer<value_type>::type pointer;
    typedef typename boost::add_pointer
                     < typename boost::add_const<value_type>::type
                     >::type const_pointer;
    typedef typename boost::call_traits<T>::param_type param_type;

    // This type
    typedef This this_type;
    typedef This& this_reference;
    typedef This const& this_const_reference;

    // Base type
    typedef declare_types<This, T> base_type;
};

} // namespace arguments
} // namespace cpp_object

#endif // CPP_OBJECT_ARGUMENTS_DECLARE_TYPES_HPP
