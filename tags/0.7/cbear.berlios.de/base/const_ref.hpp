#ifndef CBEAR_BERLIOS_DE_BASE_CONST_REF_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_CONST_REF_INCLUDED

namespace cbear_berlios_de
{
namespace base
{

template<class T>
const T &const_ref(const T &X) { return X; }

}
}

#endif
