#include <iostream>

// cpp_object_arguments functionality
#include "cpp_object/arguments/in.hpp"

namespace in_test
{

// Regular functionality
namespace regular_test
{

void fin(int i)
{
    std::cout << i << "\n";
}

__declspec(noinline) void test()
{
    int i = 0;
    fin(i);
}

} // regular_test

namespace cpp_object_arguments_test
{

using namespace cpp_object::arguments;

void fin(in<int> i)
{
    // std::cout << static_cast<int>(i);
    std::cout << static_cast<int>(i) << "\n";
}

__declspec(noinline) void test()
{
    int i = 0;
    fin(i);
}

} // cpp_object_arguments_test

void test()
{
    std::cout << "in_test::test:\n";
    regular_test::test();
    cpp_object_arguments_test::test();

#ifdef NDEBUG
    if(&regular_test::test != &cpp_object_arguments_test::test)
        std::cout << "\tFailed !\n";
    else
        std::cout << "\tSucceeded !\n";
#endif
}

} // namespace in_test
