#ifndef CBEAR_BERLIOS_DE_REMOTE_INTERFACE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_REMOTE_INTERFACE_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace remote
{

template<class T>
class interface_
{
public:

	interface_()
	{
		static virtual_table Table;
		this->virtual_table_pointer = virtual_table::begin();
	}	

private:

	static T *this_(interface_ *I)
	{
		return static_cast<T *>(I);	
	}

	static ::HRESULT __stdcall query_interface(
		interface_ *I, ::UUID const* Uuid, void **P)
	{
		return this_(I)->query_interface(uuid::cpp_in(Uuid), P).c_in();
	}

	static ::ULONG __stdcall add_ref(interface_ *I)
	{
		return this_(I)->add_ref();
	}

	static ::ULONG __stdcall release(interface_ *I)
	{
		return this_(I)->release();
	}

	template<std::size_t N>
	static ::HRESULT __cdecl universal(interface_ *I)	
	{
		return this_(I)->universal(N, reinterpret_cast<char *>(&I)).c_in();
	}

	typedef void function();

	function *const *virtual_table_pointer;

	class virtual_table
	{
	public:

		static const std::size_t size = 1000;

		static function *const begin()
		{
			static function *const Instance[size];
			return Instance;
		}

		template<std::size_t N>
		class constructor_traits
		{
		public:

			static void do_()
			{
				constructor_traits<N - 1>::do_();
				begin()[N - 1] = univeral<N - 1>;
			}
		};

		template<>
		class constructor_traits<0>
		{
		};

		template<>
		class constructor_traits<1>
		{
		};

		template<>
		class constructor_traits<2>
		{
		};

		template<>
		class constructor_traits<3>
		{
		public:
			static void do_()
			{
				begin()[0] = query_interface;
				begin()[1] = add_ref;
				begin()[2] = release;
			}
		};

		virtual_table()
		{
			constructor_traits<size>::do_();
		}
	};
};

}
}

#endif
