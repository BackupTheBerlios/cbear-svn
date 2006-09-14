#ifndef CPP_OBJECT_ARGUMENTS_TYPE_HPP
#define CPP_OBJECT_ARGUMENTS_TYPE_HPP

#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif // _MSC_VER && _MSC_VER >= 1020

#include "cpp_object/arguments/declare_types.hpp"

namespace cpp_object
{
namespace arguments
{

/// Type base
template
< typename T
, typename Reference
, typename Pointer
>
struct type : declare_types
              <
                  type<T, Reference, Pointer>,
                       T,
                       Reference,
                       Pointer
              >
{
    type(reference t)
        : t_(t)
    {
    }

    operator reference()
    {
        return t_;
    }

    reference get()
    {
        return t_;
    }

    pointer operator->()
    {
        return &t_;
    }

private:
    this_reference operator=(this_reference);

    reference t_;
};

} // namespace arguments
} // namespace cpp_object

#endif // CPP_OBJECT_ARGUMENTS_TYPE_HPP
