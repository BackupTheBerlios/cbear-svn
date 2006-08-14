#ifndef CBEAR_BERLIOS_DE_REMOTE_CLASS_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_REMOTE_CLASS_HPP_INCLUDED

#include <cbear.berlios.de/remote/ioctl.hpp>
#include <cbear.berlios.de/remote/interface.hpp>
#include <cbear.berlios.de/windows/com/itypeinfo.hpp>
#include <cbear.berlios.de/windows/com/safearray.hpp>
#include <cbear.berlios.de/atomic/main.hpp>
#include <cbear.berlios.de/stream/binary/irange.hpp>
#include <cbear.berlios.de/stream/binary/orange.hpp>
#include <cbear.berlios.de/stream/binary/size.hpp>

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
	typedef typename windows::com::safearray_t<windows::com::itypeinfo_t> 
		typeinfo_list_t;

	explicit class_(const Io &I, const typeinfo_list_t &List):
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
			In[1] = windows::byte_t(I);
			Out.resize(17);
			this->control(In, Out);
			stream::binary::irange IRange = stream::binary::irange::const_range_type(
				cast::traits<const char *>::reinterpret(Out.begin()), Out.size());
			windows::com::uuid Uuid;
			windows::byte_t Offset;
			IRange >> Uuid >> Offset;

			for(typeinfo_list_t::iterator_range_t R(List); !R.empty(); ++R.begin())
			{
				Com::typeattr_t Ra(R.front());
				if(Uuid == Ra.guid())
				{
					this->List.push_back(implementation(this, R.front()));
					break;
				}
			}
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
			std::size_t const N = TypeAttr.cfuncs();
			this->Functions.resize(N);
			for(std::size_t I = 0; I < N; ++I)
			{
				windows::com::funcdesc_t FuncDesc(
					static_cast<unsigned int>(I), TypeInfo);
				this->Functions[I].assign(FuncDesc);
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

		static std::size_t const aligment = 4;

		class in
		{
		public:
			function &f;
			parameters const p;
			in(function &f, parameters const &p):
				f(f),
				p(p)
			{
			}
			template<class Stream>
			void binary_write(Stream &S) const
			{
				S << (unsigned char)(this->p.number + 2);
				char *P = this->p.pointer;
				P += aligment;
				for(
					range::sub_range<parameter_list_t>::type R(this->f.parameters); 
					!R.empty(); 
					++R.begin())
				{
					if(R.front().flags.has(windows::com::paramflags_t::in))
					{
						windows::com::vartype_t::enum_t const V = R.front().vt.enum_();
						switch(V)
						{
						case windows::com::vartype_t::bool_:
							S << 
								(*reinterpret_cast<windows::com::variant_bool_t *>(P) ? 
									(char)1: 
									(char)0);
							P += aligment;
							break;
						case windows::com::vartype_t::i1:
						case windows::com::vartype_t::ui1:
							S << *P;
							P += aligment;
							break;
						case windows::com::vartype_t::i2:
						case windows::com::vartype_t::ui2:
							S << *reinterpret_cast<windows::ushort_t *>(P);
							P += aligment;
							break;
						case windows::com::vartype_t::i4:
						case windows::com::vartype_t::ui4:
							S << *reinterpret_cast<windows::ulong_t *>(P);
							P += aligment;
							break;
						default:
							S << *reinterpret_cast<int *>(P);
							P += aligment;
						}
					}
				}
			}
		private:
			in(const in &);
			in &operator=(const in &);
		};

		class out
		{
		public:
			function &f;
			parameters const p;

			out(function &f, parameters const &p):
				f(f),
				p(p)
			{
			}
			template<class Stream>
			void binary_read(Stream &)
			{
			}
		private:
			out(const out &);
			out &operator=(const out &);
		};

		windows::com::hresult universal(parameters const &P)
		{
			try
			{
				class_ &C = *this->Class.get();

				in In(this->Functions[P.number], P);
				out Out(this->Functions[P.number], P);

				stream::binary::size InSize, OutSize;

				InSize << In;
				OutSize >> Out;

				typename Io::store_t InStore, OutStore;
				InStore.resize(InSize());
				OutStore.resize(OutSize());

				// Serialize To In.

				stream::binary::orange InRange = 
					stream::binary::orange::range_type(
						cast::traits<char *>::reinterpret(InStore.begin()), 
						cast::traits<char *>::reinterpret(InStore.end()));
				InRange << In;

				// Call

				C.control(InStore, OutStore);

				// Deserialize From Out.

				stream::binary::irange OutRange = 
					stream::binary::irange::const_range_type(
						cast::traits<const char *>::reinterpret(OutStore.begin()), 
						cast::traits<const char *>::reinterpret(OutStore.end()));
				OutRange >> Out;

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

		class parameter
		{
		public:
			windows::com::paramflags_t flags;
			windows::com::vartype_t vt;
			void assign(windows::com::elemdesc_t &Elemdesc)
			{
				this->flags = Elemdesc.paramdesc().paramflags();
				this->vt = Elemdesc.tdesc().vt();
			}
		};

		typedef std::vector<parameter> parameter_list_t;

		class function
		{
		public:
			parameter_list_t parameters;
			void assign(windows::com::funcdesc_t &Desc)
			{
				std::size_t const N = Desc.cparams();
				windows::com::elemdesc_t *Elemdesc = Desc.elemdescparam();
				this->parameters.resize(N);
				for(std::size_t I = 0; I < N; ++I)
				{					
					this->parameters[I].assign(Elemdesc[I]);
				}
			}
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
