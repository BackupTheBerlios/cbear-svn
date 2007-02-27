#ifndef CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_IERRORINFO_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_COM_STATIC_IERRORINFO_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{
namespace static_
{

class error_info_t
{
public:
	bstr_t description;
	uuid guid;
	dword_t help_context;	
	bstr_t help_file;
	bstr_t source;
};

template<class T, class B>
class interface_content<T, B, ::IErrorInfo>:
	public interface_<T, B, ::IUnknown>
{
public:

	error_info_t error_info;

	::HRESULT __stdcall GetGUID(::GUID *guid)
	{
		try
		{
			c::cpp_out<uuid>(guid) = this->error_info.guid;
			return S_OK;
		}
		catch(...)
		{
			return create_exception::catch_().internal();
		}
	}

	::HRESULT __stdcall GetSource(::BSTR *source)
	{
		try
		{
			c::cpp_out<bstr_t>(source) = this->error_info.source;
			return S_OK;
		}
		catch(...)
		{
			return create_exception::catch_().internal();
		}
	}

	::HRESULT __stdcall GetDescription(::BSTR *description)
	{
		try
		{
			c::cpp_out<bstr_t>(description) = this->error_info.description;
			return S_OK;
		}
		catch(...)
		{
			return create_exception::catch_().internal();
		}
	}

	::HRESULT __stdcall GetHelpFile(::BSTR *help_file)
	{
		try
		{
			c::cpp_out<bstr_t>(help_file) = this->error_info.help_file;
			return S_OK;
		}
		catch(...)
		{
			return create_exception::catch_().internal();
		}
	}

	::HRESULT __stdcall GetHelpContext(::DWORD *help_context)
	{
		try
		{
			c::cpp_out<dword_t>(help_context) = this->error_info.help_context;
			return S_OK;
		}
		catch(...)
		{
			return create_exception::catch_().internal();
		}
	}
};

}
}
}
}

#endif
