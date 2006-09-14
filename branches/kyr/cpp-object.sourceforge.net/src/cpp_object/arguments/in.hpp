#ifndef CPP_OBJECT_ARGUMENTS_IN_HPP
#define CPP_OBJECT_ARGUMENTS_IN_HPP

#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif // _MSC_VER && _MSC_VER >= 1020

#include "cpp_object/arguments/declare_types.hpp"

namespace cpp_object
{
namespace arguments
{

/// Input arguments passing
/// Arguments are passed by reference to const for non-primitive types and
/// by value for primitive types
template<typename T>
struct in : declare_types<in<T>, T>
{
    in(reference t)
        : t_(t)
    {
    }

    operator param_type()
    {
        return t_;
    }

private:
    this_reference operator=(this_const_reference);

    param_type t_;
};

} // namespace arguments
} // namespace cpp_object

#endif // CPP_OBJECT_ARGUMENTS_IN_HPP
