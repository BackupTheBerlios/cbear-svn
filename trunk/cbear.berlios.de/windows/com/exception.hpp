#ifndef CBEAR_BERLIOS_DE_COM_EXCEPTION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_COM_EXCEPTION_HPP_INCLUDED

#include <sstream>

#include <boost/preprocessor/wstringize.hpp>

#include <cbear.berlios.de/windows/com/exception_base.hpp>
#include <cbear.berlios.de/base/exception.hpp>
#include <cbear.berlios.de/base/integer.hpp>
#include <cbear.berlios.de/base/lexical_cast.hpp>
#include <cbear.berlios.de/locale/cast.hpp>
#include <cbear.berlios.de/windows/hresult.hpp>
#include <cbear.berlios.de/windows/com/uint.hpp>
#include <cbear.berlios.de/windows/com/bstr.hpp>
#include <cbear.berlios.de/windows/com/uuid.hpp>
#include <cbear.berlios.de/windows/com/pointer.hpp>
#include <cbear.berlios.de/windows/com/ulong.hpp>
#include <cbear.berlios.de/pp/cat.hpp>
#include <cbear.berlios.de/pp/widen.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

template<class Base>
class pointer_content<Base, ::IErrorInfo>: 
	public pointer_content<Base, ::IUnknown>
{
public:
	bstr_t GetDescription() const
	{
		bstr_t Result;
		this->reference().GetDescription(com::internal<out>(Result));
		return Result;
	}
	com::uuid GetGUID() const
	{
		com::uuid Result;
		this->reference().GetGUID(Result.c_out());
		return Result;
	}
	dword_t GetHelpContext() const
	{
		dword_t Result;
		this->reference().GetHelpContext(com::internal<out>(Result));
		return Result;
	}
	bstr_t GetHelpFile() const
	{
		bstr_t Result;
		this->reference().GetHelpFile(com::internal<out>(Result));
		return Result;
	}
	bstr_t GetSource() const
	{
		bstr_t Result;
		this->reference().GetSource(com::internal<out>(Result));
		return Result;
	}
};

typedef pointer< ::IErrorInfo> ierrorinfo_t;

template<class Base>
class pointer_content<Base, ::ICreateErrorInfo>:
	public pointer_content<Base, ::IUnknown>
{
public:
	void SetDescription(lpcwstr_t X) const
	{
		this->reference().SetDescription(
			const_cast<lpwstr_t::internal_type>(const_cast<wchar_t *>(X.get())));
	}
	void SetGUID(const com::uuid &X) const
	{
		this->reference().SetGUID(*X.c_in());
	}
	void SetHelpContext(dword_t X) const
	{
		this->reference().SetHelpContext(X);
	}
	void SetHelpFile(lpcwstr_t X) const
	{
		this->reference().SetHelpFile(const_cast<wchar_t *>(X.get()));
	}
	void SetSource(lpcwstr_t X) const
	{
		this->reference().SetSource(const_cast<wchar_t *>(X.get()));
	}
};

typedef pointer< ::ICreateErrorInfo> icreateerrorinfo;

class exception: 
	public ::std::exception,
	public stream::wvirtual_write
{
public:

	const char *what() const throw() 
	{ 
		return "::cbear_berlios_de::windows::com::exception"; 
	}

	// hresult.
	hresult result() const throw() 
	{ 
		return this->Result; 
	}

	// error info.
	const ierrorinfo_t &errorinfo() const throw() 
	{ 
		return this->ErrorInfo; 
	}
	
	// print.
	template<class Stream>
	void write(Stream &O) const
	{
		O << 
			L"cbear_berlios_de::com::exception(0x" << 
			base::hex(base::unsigned_(this->Result.internal())) << 
			L"):\n";
		if(this->ErrorInfo)
		{
			O << 
				L"Description: " << this->ErrorInfo.GetDescription() << L"\n" <<
				L"GUID: " << this->ErrorInfo.GetGUID() << L"\n" <<
				L"Help Context: " << this->ErrorInfo.GetHelpContext() << L"\n" <<
				L"Help File: " << this->ErrorInfo.GetHelpFile() << L"\n" <<
				L"Source: " << this->ErrorInfo.GetSource() << L"\n";
		}
	}

	// It throws an exception initialized by a system COM error info.
	static void throw_unless(hresult Value)
	{
		if(!Value.failed()) 
		{
			return;
		}
		ierrorinfo_t ErrorInfo;
		::GetErrorInfo(0, com::internal<out>(ErrorInfo));
		throw exception(Value, ErrorInfo);
	}

	// It throws an exception initialized by system COM error info.
	static void throw_unless(::HRESULT Value)
	{
		throw_unless(hresult(Value));
	}

	static hresult user() 
	{ 
		return hresult(true, hresult::facility_type::itf, hresult::code_type::min); 
	}

	explicit exception(
		hresult Result = user(), ierrorinfo_t const &ErrorInfo = ierrorinfo_t()):
		Result(Result), ErrorInfo(ErrorInfo)
	{
	}

private:

	friend class create_exception;

	hresult Result;
	ierrorinfo_t ErrorInfo;

	hresult const &set() const
	{
		if(this->ErrorInfo) 
		{
			::SetErrorInfo(0, com::internal<in>(this->ErrorInfo));
		}
		return this->Result;
	}

	void detail_write(cbear_berlios_de::stream::wvirtual_write::stream &S) const
	{
		this->write(S);
	}
};

class create_exception: public com::exception
{
public:

	create_exception(const hresult &X = user()): com::exception(X)
	{
		::CreateErrorInfo(com::internal<out>(this->CreateErrorInfo));
		this->com::exception::ErrorInfo = *CreateErrorInfo.
			query_interface<ierrorinfo_t::interface_t>();
	}

	const create_exception &Description(lpcwstr_t X) const
	{
		this->CreateErrorInfo.SetDescription(X);
		return *this;
	}

	const create_exception &Guid(const com::uuid &X) const
	{
		this->CreateErrorInfo.SetGUID(X);
		return *this;
	}

	const create_exception &HelpContext(dword_t X) const
	{
		this->CreateErrorInfo.SetHelpContext(X);
		return *this;
	}

	const create_exception &HelpFile(lpcwstr_t X) const
	{
		this->CreateErrorInfo.SetHelpFile(X);
		return *this;
	}

	const create_exception &Source(lpcwstr_t X) const
	{
		this->CreateErrorInfo.SetSource(X);
		return *this;
	}

	// It catchs all exceptions and sets the system COM error info.
	static hresult catch_()
	{
		try
		{
			try
			{
				throw;				
			}
			catch(com::exception const &B)
			{
				return B.set();
			}
			catch(windows::exception const &W)
			{
				return hresult(
					true, 
					hresult::facility_type::win32, 
					hresult::code_type(static_cast<hresult::code_type::internal_type>(
						W.result())));
			}
			catch(::cbear_berlios_de::stream::wvirtual_write const &W)
			{			
				return create_exception().Description(base::to_stream<bstr_t>(W)).set();
			}
			catch(::std::exception const &S)
			{
				return create_exception().
					Description(locale::cast<bstr_t>(std::string(S.what()))).
					set();
			}
		}
		catch(...)
		{
			return hresult::e_fail;
		}
	}

private:
	icreateerrorinfo CreateErrorInfo;
};

}
}
}

#define CBEAR_BERLIOS_DE_WINDOWS_COM_EXCEPTION_THROW(Message) \
	throw ::cbear_berlios_de::windows::com::create_exception(). \
		Description(Message). \
		Source(CBEAR_BERLIOS_DE_PP_CAT6( \
			L"File: ", CBEAR_BERLIOS_DE_PP_WIDEN(__FILE__), \
			L", Line: ", BOOST_PP_WSTRINGIZE(__LINE__), \
			L", Function: ", CBEAR_BERLIOS_DE_PP_WIDEN(__FUNCTION__)))

#endif
