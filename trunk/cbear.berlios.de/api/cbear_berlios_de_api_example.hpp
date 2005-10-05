#ifndef cbear_berlios_de_api_example_hpp_included
#define cbear_berlios_de_api_example_hpp_included
#include <cbear_berlios_de_api_example.h>
#include <cbear.berlios.de/com/object.hpp>
namespace cbear_berlios_de_api_example
{
	class Mode:
		public ::cbear_berlios_de::policy::wrap< Mode, ::Mode >
	{
	public:
		enum type
		{
			Disabled = 0,
			Enabled = 1,
		};
		Mode();
		Mode(::Mode X): ::cbear_berlios_de::policy::wrap< Mode, ::Mode >(X)
		{
		}
		Mode(type X): ::cbear_berlios_de::policy::wrap< Mode, ::Mode >(X)
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
		class object_content< ::ITime, Base >:
			public object_content< ::IDispatch, Base >
		{
		public:
			date_t get_Date()
			{
				_result;
				exception::handle(this->internal_this().get_Date());
			}
			uint_t get_Clock()
			{
				_result;
				exception::handle(this->internal_this().get_Clock());
			}
		};
		template<class Base>
		class object_content< ::IDeviceInfo, Base >:
			public object_content< ::IDispatch, Base >
		{
		public:
			bstr_t get_Name()
			{
				_result;
				exception::handle(this->internal_this().get_Name());
			}
		};
		template<class Base>
		class object_content< ::IModuleInfo, Base >:
			public object_content< ::IDeviceInfo, Base >
		{
		};
		template<class Base>
		class object_content< ::IModuleInfoList, Base >:
			public object_content< ::IDispatch, Base >
		{
		public:
			long_t get_Count()
			{
				_result;
				exception::handle(this->internal_this().get_Count());
			}
			cbear_berlios_de_api_example::IModuleInfo get_Item(long_t _1)
			{
				_result;
				_result;
				exception::handle(this->internal_this().get_Item());
			}
			void Update()
			{
				exception::handle(this->internal_this().Update());
			}
		};
		template<class Base>
		class object_content< ::IMain, Base >:
			public object_content< ::IDispatch, Base >
		{
		public:
			Create(bstr_t _1)
			{
				_result;
				_result;
				exception::handle(this->internal_this().Create());
			}
			safearray_t< byte_t > Reserved(safearray_t< byte_t > _1)
			{
				_result;
				_result;
				exception::handle(this->internal_this().Reserved());
			}
			cbear_berlios_de_api_example::IModuleInfoList get_A()
			{
				_result;
				exception::handle(this->internal_this().get_A());
			}
		};
		template<class Base>
		class object_content< ::IA, Base >:
			public object_content< ::IDispatch, Base >
		{
		};
		template<class Base>
		class object_content< ::IB, Base >:
			public object_content< ::IDispatch, Base >
		{
		};
		template<class Base>
		class object_content< ::IC, Base >:
			public object_content< ::IA, Base >
		{
		public:
			cbear_berlios_de_api_example::IB get_IB()
			{
				_result;
				exception::handle(this->internal_this().get_IB());
			}
		};
	}
}
#endif
