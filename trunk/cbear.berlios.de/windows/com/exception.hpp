/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef CBEAR_BERLIOS_DE_COM_EXCEPTION_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_COM_EXCEPTION_HPP_INCLUDED

#include <sstream>

#include <cbear.berlios.de/locale/cast.hpp>
#include <cbear.berlios.de/windows/com/hresult.hpp>
#include <cbear.berlios.de/windows/com/bstr.hpp>
#include <cbear.berlios.de/windows/com/uuid.hpp>
#include <cbear.berlios.de/windows/com/object.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace com
{

template<class Base>
class object_content<Base, ::IErrorInfo>: 
	public object_content<Base, ::IUnknown>
{
public:
	bstr_t GetDescription() const
	{
		bstr_t Result;
		this->internal_reference().GetDescription(com::internal<out>(Result));
		return Result;
	}
	com::uuid GetGUID() const
	{
		com::uuid Result;
		this->internal_reference().GetGUID(com::internal<out>(Result));
		return Result;
	}
	dword_t GetHelpContext() const
	{
		dword_t Result;
		this->internal_reference().GetHelpContext(com::internal<out>(Result));
		return Result;
	}
	bstr_t GetHelpFile() const
	{
		bstr_t Result;
		this->internal_reference().GetHelpFile(com::internal<out>(Result));
		return Result;
	}
	bstr_t GetSource() const
	{
		bstr_t Result;
		this->internal_reference().GetSource(com::internal<out>(Result));
		return Result;
	}
};

typedef object< ::IErrorInfo> ierrorinfo;

template<class Base>
class object_content<Base, ::ICreateErrorInfo>:
	public object_content<Base, ::IUnknown>
{
public:
	void SetDescription(lpcwstr_t X) const
	{
		this->internal_reference().SetDescription(X.internal());
	}
	void SetGUID(const com::uuid &X) const
	{
		this->internal_reference().SetGUID(X.internal());
	}
	void SetHelpContext(dword_t X) const
	{
		this->internal_reference().SetGUID(X);
	}
	void SetHelpFile(lpcwstr_t X) const
	{
		this->internal_reference().SetHelpFile(X.internal());
	}
	void SetSource(lpcwstr_t X) const
	{
		this->internal_reference().SetSource(X.internal());
	}
};

typedef object< ::ICreateErrorInfo> icreateerrorinfo;

class exception: public std::exception
{
public:
	exception(hresult Value): Value(Value) 
	{
		::GetErrorInfo(0, com::internal<out>(this->ErrorInfo));
		std::ostringstream Stream;
		Stream << 
			"cbear_berlios_de::com::exception(0x" << std::hex << std::uppercase << 
			this->result() << "):" << std::endl;
		if(this->ErrorInfo!=ierrorinfo())
		{
			Stream <<
				"Description: " << 
				locale::cast<std::string>(this->ErrorInfo.GetDescription()) << 
				std::endl;
			Stream << "GUID: " << this->ErrorInfo.GetGUID() << std::endl;
			Stream << 
				"Help Context: " << this->ErrorInfo.GetHelpContext() << std::endl;
			Stream <<
				"Help File: " << 
				locale::cast<std::string>(this->ErrorInfo.GetHelpFile()) << std::endl;
			Stream <<
				"Source: " << 
				locale::cast<std::string>(this->ErrorInfo.GetSource()) << std::endl;
		}
		this->Message = Stream.str();
	}
	const char *what() const throw()
	{
		return this->Message.c_str();
	}
	hresult result() const throw() { return this->Value; }
	static void throw_unless(hresult Value)
	{
		if(Value.failed()) throw exception(Value);
	}
	static void throw_unless(::HRESULT Value)
	{
		throw_unless(hresult(Value));
	}
	static hresult catch_()
	{
		try
		{
			try
			{
				throw;				
			}
			catch(const com::exception &E)
			{
				set_error_info(E.ErrorInfo);
				return E.result();
			}
			catch(const ::std::exception &E)
			{
				icreateerrorinfo CreateErrorInfo;
				::CreateErrorInfo(com::internal<out>(CreateErrorInfo));
				set_error_info(CreateErrorInfo.query_interface<ierrorinfo>());
				return hresult(
					true, 
					hresult::facility_type::itf, 
					hresult::code_type::min);
			}
		}
		catch(...)
		{
			return hresult::e_fail;
		}
	}
private:
	hresult Value;
	std::string Message;
	ierrorinfo ErrorInfo;
	static void set_error_info(const ierrorinfo &X)
	{
		::SetErrorInfo(0, com::internal<in>(X));
	}
};

}
}
}

#endif
