#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_INTERFACE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_INTERFACE_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/static/interface_content.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

template<class T, class B, class I = B>
class interface_: public interface_content<T, B, I>
{
private:
	typedef interface_content<T, B, I> base_t;
protected:
	iunknown_t::move_t query_interface(const uuid &U) throw()
	{
		if(uuid::of<I>()==U)
		{
			return move::copy(iunknown_t::cpp_in(static_cast<I *>(this)));
		}
		return base_t::query_interface(U);
	}
};

}
}
}
}

#endif
