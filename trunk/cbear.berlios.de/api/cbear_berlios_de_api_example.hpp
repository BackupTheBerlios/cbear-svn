#ifndef cbear_berlios_de_api_example_hpp_included
#define cbear_berlios_de_api_example_hpp_included
#include <cbear_berlios_de_api_example.h>
#include <cbear.berlios.de/com/enum.hpp>
#include <cbear.berlios.de/com/variant_bool.hpp>
#include <cbear.berlios.de/com/int.hpp>
#include <cbear.berlios.de/com/byte.hpp>
#include <cbear.berlios.de/com/ushort.hpp>
#include <cbear.berlios.de/com/long.hpp>
#include <cbear.berlios.de/com/ulong.hpp>
#include <cbear.berlios.de/com/double.hpp>
#include <cbear.berlios.de/com/bstr.hpp>
#include <cbear.berlios.de/com/date.hpp>
#include <cbear.berlios.de/com/safearray.hpp>
#include <cbear.berlios.de/com/object.hpp>
#include <cbear.berlios.de/com/exception.hpp>
#include <cbear.berlios.de/com/implementation.hpp>
namespace cbear_berlios_de_api_example
{
	class Mode:
		public ::cbear_berlios_de::com::enum_t< Mode, ::Mode >
	{
	public:
		enum type
		{
			Disabled = 0,
			Enabled = 1,
		};
		Mode()
		{
		}
		Mode(::Mode X): ::cbear_berlios_de::com::enum_t< Mode, ::Mode >(X)
		{
		}
		Mode(type X): ::cbear_berlios_de::com::enum_t< Mode, ::Mode >(::Mode(X))
		{
		}
	};
	typedef ::cbear_berlios_de::com::object< ::ITime > ITime;
	typedef ::cbear_berlios_de::com::object< ::IDeviceInfo > IDeviceInfo;
	typedef ::cbear_berlios_de::com::object< ::IModuleInfo > IModuleInfo;
	typedef ::cbear_berlios_de::com::object< ::IModuleInfoList > IModuleInfoList;
	typedef ::cbear_berlios_de::com::object< ::IMain > IMain;
	typedef ::cbear_berlios_de::com::object< ::IA > IA;
	typedef ::cbear_berlios_de::com::object< ::IB > IB;
	typedef ::cbear_berlios_de::com::object< ::IC > IC;
}
namespace cbear_berlios_de
{
	namespace com
	{
		template<class Base>
		class object_content< Base, ::ITime >:
			public object_content< Base, ::IUnknown >
		{
		public:
			date_t Date() const
			{
				date_t _result;
				exception::throw_unless(this->internal_reference().get_Date(com::internal< out >(_result)));
				return _result;
			}
			uint_t Clock() const
			{
				uint_t _result;
				exception::throw_unless(this->internal_reference().get_Clock(com::internal< out >(_result)));
				return _result;
			}
		};
		template<class Base>
		class implementation< Base, ::ITime >:
			public implementation_base< Base, ::ITime, ::IUnknown >
		{
		public:
			virtual date_t ITime_Date() = 0;
			hresult::internal_type __stdcall get_Date(internal_result< out, date_t >::type _result)
			{
				try
				{
					wrap< out, date_t >(_result)=this->ITime_Date();
					return hresult::s_ok;
				}
				catch(...)
				{
					return exception::catch_().internal();
				}
			}
			virtual uint_t ITime_Clock() = 0;
			hresult::internal_type __stdcall get_Clock(internal_result< out, uint_t >::type _result)
			{
				try
				{
					wrap< out, uint_t >(_result)=this->ITime_Clock();
					return hresult::s_ok;
				}
				catch(...)
				{
					return exception::catch_().internal();
				}
			}
		};
		template<class Base>
		class object_content< Base, ::IDeviceInfo >:
			public object_content< Base, ::IUnknown >
		{
		public:
			bstr_t Name() const
			{
				bstr_t _result;
				exception::throw_unless(this->internal_reference().get_Name(com::internal< out >(_result)));
				return _result;
			}
		};
		template<class Base>
		class implementation< Base, ::IDeviceInfo >:
			public implementation_base< Base, ::IDeviceInfo, ::IUnknown >
		{
		public:
			virtual bstr_t IDeviceInfo_Name() = 0;
			hresult::internal_type __stdcall get_Name(internal_result< out, bstr_t >::type _result)
			{
				try
				{
					wrap< out, bstr_t >(_result)=this->IDeviceInfo_Name();
					return hresult::s_ok;
				}
				catch(...)
				{
					return exception::catch_().internal();
				}
			}
		};
		template<class Base>
		class object_content< Base, ::IModuleInfo >:
			public object_content< Base, ::IDeviceInfo >
		{
		};
		template<class Base>
		class implementation< Base, ::IModuleInfo >:
			public implementation_base< Base, ::IModuleInfo, ::IDeviceInfo >
		{
		};
		template<class Base>
		class object_content< Base, ::IModuleInfoList >:
			public object_content< Base, ::IUnknown >
		{
		public:
			long_t Count() const
			{
				long_t _result;
				exception::throw_unless(this->internal_reference().get_Count(com::internal< out >(_result)));
				return _result;
			}
			cbear_berlios_de_api_example::IModuleInfo Item(const long_t & _0) const
			{
				cbear_berlios_de_api_example::IModuleInfo _result;
				exception::throw_unless(this->internal_reference().get_Item(com::internal< in >(_0), com::internal< out >(_result)));
				return _result;
			}
			void Update() const
			{
				exception::throw_unless(this->internal_reference().Update());
			}
		};
		template<class Base>
		class implementation< Base, ::IModuleInfoList >:
			public implementation_base< Base, ::IModuleInfoList, ::IUnknown >
		{
		public:
			virtual long_t IModuleInfoList_Count() = 0;
			hresult::internal_type __stdcall get_Count(internal_result< out, long_t >::type _result)
			{
				try
				{
					wrap< out, long_t >(_result)=this->IModuleInfoList_Count();
					return hresult::s_ok;
				}
				catch(...)
				{
					return exception::catch_().internal();
				}
			}
			virtual cbear_berlios_de_api_example::IModuleInfo IModuleInfoList_Item(const long_t & _0) = 0;
			hresult::internal_type __stdcall get_Item(internal_result< in, long_t >::type _0, internal_result< out, cbear_berlios_de_api_example::IModuleInfo >::type _result)
			{
				try
				{
					wrap< out, cbear_berlios_de_api_example::IModuleInfo >(_result)=this->IModuleInfoList_Item(wrap< in, long_t >(_0));
					return hresult::s_ok;
				}
				catch(...)
				{
					return exception::catch_().internal();
				}
			}
			virtual void IModuleInfoList_Update() = 0;
			hresult::internal_type __stdcall Update()
			{
				try
				{
					this->IModuleInfoList_Update();
					return hresult::s_ok;
				}
				catch(...)
				{
					return exception::catch_().internal();
				}
			}
		};
		template<class Base>
		class object_content< Base, ::IMain >:
			public object_content< Base, ::IUnknown >
		{
		public:
			cbear_berlios_de_api_example::IModuleInfo Create(const bstr_t & _0) const
			{
				cbear_berlios_de_api_example::IModuleInfo _result;
				exception::throw_unless(this->internal_reference().Create(com::internal< in >(_0), com::internal< out >(_result)));
				return _result;
			}
			safearray_t< byte_t > Reserved(const safearray_t< byte_t > & _0) const
			{
				safearray_t< byte_t > _result;
				exception::throw_unless(this->internal_reference().Reserved(com::internal< in >(_0), com::internal< out >(_result)));
				return _result;
			}
			cbear_berlios_de_api_example::IModuleInfoList A() const
			{
				cbear_berlios_de_api_example::IModuleInfoList _result;
				exception::throw_unless(this->internal_reference().get_A(com::internal< out >(_result)));
				return _result;
			}
		};
		template<class Base>
		class implementation< Base, ::IMain >:
			public implementation_base< Base, ::IMain, ::IUnknown >
		{
		public:
			virtual cbear_berlios_de_api_example::IModuleInfo IMain_Create(const bstr_t & _0) = 0;
			hresult::internal_type __stdcall Create(internal_result< in, bstr_t >::type _0, internal_result< out, cbear_berlios_de_api_example::IModuleInfo >::type _result)
			{
				try
				{
					wrap< out, cbear_berlios_de_api_example::IModuleInfo >(_result)=this->IMain_Create(wrap< in, bstr_t >(_0));
					return hresult::s_ok;
				}
				catch(...)
				{
					return exception::catch_().internal();
				}
			}
			virtual safearray_t< byte_t > IMain_Reserved(const safearray_t< byte_t > & _0) = 0;
			hresult::internal_type __stdcall Reserved(internal_result< in, safearray_t< byte_t > >::type _0, internal_result< out, safearray_t< byte_t > >::type _result)
			{
				try
				{
					wrap< out, safearray_t< byte_t > >(_result)=this->IMain_Reserved(wrap< in, safearray_t< byte_t > >(_0));
					return hresult::s_ok;
				}
				catch(...)
				{
					return exception::catch_().internal();
				}
			}
			virtual cbear_berlios_de_api_example::IModuleInfoList IMain_A() = 0;
			hresult::internal_type __stdcall get_A(internal_result< out, cbear_berlios_de_api_example::IModuleInfoList >::type _result)
			{
				try
				{
					wrap< out, cbear_berlios_de_api_example::IModuleInfoList >(_result)=this->IMain_A();
					return hresult::s_ok;
				}
				catch(...)
				{
					return exception::catch_().internal();
				}
			}
		};
		template<class Base>
		class object_content< Base, ::IA >:
			public object_content< Base, ::IUnknown >
		{
		};
		template<class Base>
		class implementation< Base, ::IA >:
			public implementation_base< Base, ::IA, ::IUnknown >
		{
		};
		template<class Base>
		class object_content< Base, ::IB >:
			public object_content< Base, ::IUnknown >
		{
		};
		template<class Base>
		class implementation< Base, ::IB >:
			public implementation_base< Base, ::IB, ::IUnknown >
		{
		};
		template<class Base>
		class object_content< Base, ::IC >:
			public object_content< Base, ::IA >
		{
		public:
			cbear_berlios_de_api_example::IB IB() const
			{
				cbear_berlios_de_api_example::IB _result;
				exception::throw_unless(this->internal_reference().get_IB(com::internal< out >(_result)));
				return _result;
			}
		};
		template<class Base>
		class implementation< Base, ::IC >:
			public implementation_base< Base, ::IC, ::IA >
		{
		public:
			virtual cbear_berlios_de_api_example::IB IC_IB() = 0;
			hresult::internal_type __stdcall get_IB(internal_result< out, cbear_berlios_de_api_example::IB >::type _result)
			{
				try
				{
					wrap< out, cbear_berlios_de_api_example::IB >(_result)=this->IC_IB();
					return hresult::s_ok;
				}
				catch(...)
				{
					return exception::catch_().internal();
				}
			}
		};
	}
}
#endif
