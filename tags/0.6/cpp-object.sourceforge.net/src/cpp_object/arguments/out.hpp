#ifndef CPP_OBJECT_ARGUMENTS_OUT_HPP
#define CPP_OBJECT_ARGUMENTS_OUT_HPP

#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif // _MSC_VER && _MSC_VER >= 1020

#include "cpp_object/arguments/declare_types.hpp"

namespace cpp_object
{
namespace arguments
{

/// Output arguments passing
/// Arguments are passed by reference for all types
template<typename T>
struct out : type<out<T>, T>
{
    out(reference t)
        : t_(t)
    {
    }

    this_reference operator=(const_reference right)
    {
        get() = right;
        return *this;
    }

    operator param_type()
    {
        return t_;
    }

private:
    reference t_;
};

} // namespace arguments
} // namespace cpp_object

#endif // CPP_OBJECT_ARGUMENTS_OUT_HPP
