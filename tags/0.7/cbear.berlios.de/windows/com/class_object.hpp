#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_CLASS_OBJECT_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_CLASS_OBJECT_HPP_INCLUDED

#include <cbear.berlios.de/windows/com/pointer.hpp>
#include <cbear.berlios.de/windows/com/exception.hpp>
#include <cbear.berlios.de/windows/com/clsctx.hpp>
#include <cbear.berlios.de/windows/com/regcls.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

class class_object
{
public:
	class_object(
		const uuid &Uuid, 
		const iunknown &Unk, 
		const clsctx &Clsctx, 
		const regcls &Regcls)
	{
		exception::throw_unless(::CoRegisterClassObject(
			*Uuid.c_in(),
			internal<in>(Unk),
			internal<in>(Clsctx),
			internal<in>(Regcls),
			internal<out>(this->Register)));
	}
	~class_object()
	{
		exception::throw_unless(::CoRevokeClassObject(this->Register));
	}
private:
	dword_t Register;
};

}
}
}

#endif
