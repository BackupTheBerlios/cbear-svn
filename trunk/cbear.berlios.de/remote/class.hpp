#ifndef CBEAR_BERLIOS_DE_REMOTE_CLASS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_REMOTE_CLASS_HPP_INCLUDED

#include <cbear.berlios.de/remote/ioctl.hpp>
#include <cbear.berlios.de/remote/interface.hpp>
#include <cbear.berlios.de/windows/com/itypeinfo.hpp>
#include <cbear.berlios.de/atomic/main.hpp>

#include <vector>

namespace cbear_berlios_de
{
namespace remote
{

template<class Io>
class class_: public windows::com::iunknown_t::interface_t
{
public:

	typedef typename Io::store_t store_t;

	explicit class_(const Io &I):
		I(I)
	{
		store_t In, Out;
		// 0
		In.resize(1);
		Out.resize(1);
		In[0] = 0;
		this->control(In, Out);
		std::size_t InterfaceListCount = Out[0];
		// 1
		for(std::size_t I = 0; I < InterfaceListCount; ++I)
		{
			In.resize(2);
			In[0] = 1;
			In[1] = I;
			Out.resize(17);
			this->control(In, Out);
		}
	}

	virtual ::HRESULT __stdcall QueryInterface(::UUID const &Uuid, void **P)
	{
		return 
			this->
			query_interface(
				windows::com::uuid::cpp_in(&Uuid), 
				windows::com::iunknown_t::cpp_out(
					cast::traits<windows::com::iunknown_t::c_out_t>::reinterpret(P))).
			c_in();
	}

	virtual ::ULONG __stdcall AddRef()
	{
		return this->add_ref();
	}

	virtual ::ULONG __stdcall Release()
	{
		return this->release();
	}

	void push_back(windows::com::itypeinfo_t const &TypeInfo)
	{
		implementation I(this, TypeInfo);
		this->List.push_back(I);
	}

private:

	class implementation: public interface_<implementation>
	{
	public:

		implementation(
			class_ *const Class, 
			windows::com::itypeinfo_t const &TypeInfo)
		{
			this->Class.get() = Class;
			windows::com::typeattr_t TypeAttr(TypeInfo);
			this->Uuid = TypeAttr.guid();
			std::size_t N = TypeAttr.cfuncs();
			this->Functions.resize(N);
			for(std::size_t I = 0; I < N; ++I)
			{
				windows::com::funcdesc_t FuncDesc(
					static_cast<unsigned int>(I), TypeInfo);
			}
		}	

		windows::com::hresult query_interface(
			windows::com::uuid const &Uuid, 
			windows::com::iunknown_t &P)
		{
			return this->Class.get()->query_interface(Uuid, P);
		}

		windows::com::ulong_t add_ref()
		{
			return this->Class.get()->add_ref();
		}

		windows::com::ulong_t release()
		{
			return this->Class.get()->release();
		}

		windows::com::hresult universal(std::size_t, char *)
		{
			try
			{
				class_ &C = *this->Class.get();

				std::size_t InSize = 0;
				std::size_t OutSize = 0;			

				typename Io::store_t In, Out;
				In.resize(InSize);
				Out.resize(OutSize);

				// Serialize To In.

				// Call

				C.control(In, Out);

				// Deserialize From Out.

				//

				return windows::com::hresult::s_ok;
			}
			catch(...)
			{
				return windows::com::create_exception::catch_();
			}
		}

		windows::com::uuid const &uuid() const
		{
			return this->Uuid;
		}

	private:
		base::initialized<class_ *> Class;
		windows::com::uuid Uuid;

		class function
		{
		};

		typedef std::vector<function> function_list;

		std::vector<function> Functions;
	};

	windows::com::hresult query_interface(
		windows::com::uuid const &Uuid, windows::com::iunknown_t &P)
	{
		if(Uuid == windows::com::uuid::of<windows::com::iunknown_t>())
		{
			P = 
				windows::com::iunknown_t::cpp_in(
				static_cast<windows::com::iunknown_t::c_in_t>(this));
			return windows::com::hresult::s_ok;			
		}
		for(range::sub_range<ListT>::type R(this->List); !R.empty(); ++R.begin())
		{
			if(Uuid == R.front().uuid())
			{
				P = R.front().iunknown();
				return windows::com::hresult::s_ok;
			}
		}
		return windows::com::hresult::e_nointerface;
	}

	windows::com::ulong_t add_ref()
	{
		return this->Counter.increment();
	}

	windows::com::ulong_t release()
	{
		windows::com::ulong_t R = this->Counter.decrement();
		if(!R)
		{
			delete this;
			return 0;
		}
		return R;
	}

	atomic::wrap<windows::com::ulong_t> Counter;

	typedef std::vector<implementation> ListT;
	ListT List;

	void control(const store_t &In, store_t &Out)
	{
		this->I.control(ioctl(), In, Out);
	}

	Io I;
};

}
}

#endif
