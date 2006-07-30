#ifndef CBEAR_BERLIOS_DE_BASE_NONCREATABLE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_BASE_NONCREATABLE_HPP_INCLUDED

// boost::mpl::bool_
#include <boost/mpl/bool.hpp>

namespace cbear_berlios_de
{
namespace base
{

class noncreatable
{
private:
	noncreatable() {}
	noncreatable(const noncreatable &) {}
	noncreatable &operator=(const noncreatable &) {}
	~noncreatable() {}	
};

}
}

#endif
