#ifndef CBEAR_BERLIOS_DE_WINDOWS_USB_ARCHIVE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_USB_ARCHIVE_HPP_INCLUDED

#include <cbear.berlios.de/windows/handle.hpp>

namespace cbear_berlios_de
{
namespace windows
{
namespace usb
{

namespace detail
{

template<class Archive>
class oarchive_t
{
public:

	typedef boost::mpl::true_ is_saving;

	template<class T>
	oarchive_t &operator &(const T &X)
	{
		this->archive().save(X);
		return *this;
	}

	template<class T>
	oarchive_t &operator<<(const T &X)
	{
		this->archive().save(X);
		return *this;
	}

protected:
	~oarchive_t() {}
private:
	Archive &archive() { return *static_cast<Archive *>(this); }
};

template<class Archive>
class iarchive_t
{
public:

	template<class T>
	iarchive_t &operator &(T &X)
	{
		this->archive().load(X);
		return *this;
	}

	template<class T>
	iarchive_t &operator>>(const T &X)
	{
		this->archive().load(X);
		return *this;
	}

protected:
	~iarchive_t() {}
private:
	Archive &archive() { return *static_cast<Archive *>(this); }
};

}

template<std::size_t InSize, std::size_t OutSize>
class static_store_t
{
public:
	static_store_t() { this->reset(); }	
	void reset() { this->end = buffer.begin(); }
	byte_range iobuffer() { return byte_range_t(this->buffer); }
	byte_range ibuffer()
	{ 		
		return byte_range_t(&this->buffer.front(), &this->buffer[InSize]);
	}
	byte_range obuffer() 
	{ 		
		return byte_range_t(&this->buffer.front(), &this->buffer[OutSize]);
	}
protected:
	template<class T>
	void save_pod(const T &X)
	{
		BOOST_ASSERT(this->buffer.end() - this->end >= sizeof(T));
		reinterpret_cast<T &>(*this->end) = X;
		this->end += sizeof(T);
	}

	template<class T>
	void load_pod(T &X)
	{
		BOOST_ASSERT(this->buffer.end() - this->end >= sizeof(T));
		X = reinterpret_cast<const T &>(*this->end);
		this->end += sizeof(T);
	}
private:
	static const std::size_t Size = InSize < OutSize ? OutSize: InSize;
	typedef boost::array<byte_t, Size> array_t;
	array_t buffer;
	typename array_t::iterator end;
};

template<class Store>
class archive_t: 
	boost::noncopyable,
	public Store,
	public detail::iarchive_t<archive_t<Store> >,
	public detail::oarchive_t<archive_t<Store> >
{
public:

	typedef detail::oarchive_t<archive_t> oarchive_t;
	typedef detail::iarchive_t<archive_t> iarchive_t;

	typedef oarchive_t &oarchive_ref;
	typedef iarchive_t &iarchive_ref;

	oarchive_ref oarchive() { return *this; }
	iarchive_ref iarchive() { return *this; }

	// version

	static const unsigned int version = 0;

	// struct

	template<class T>
	void save(
		const T &X, typename boost::enable_if<boost::is_class<T> >::type *dummy = 0)
	{
		boost::serialization::serialize(
			oarchive_ref(*this), const_cast<T &>(X), version);
	}

	template<class T>
	void load(
		T &X, typename boost::enable_if<boost::is_class<T> >::type *dummy = 0)
	{ 
		boost::serialization::serialize(
			iarchive_ref(*this), X, version);
	}

	// enum

	template<class T>
	void save(
		const T &X, typename boost::enable_if<boost::is_enum<T> >::type *dummy = 0)
	{
		this->save(static_cast<const int &>(X));
	}

	template<class T>
	void load(
		T &X, typename boost::enable_if<boost::is_enum<T> >::type *dummy = 0)
	{
		this->load(static_cast<int &>(X));
	}

	// byte
	void save(windows::byte_t X) { this->Store::save_pod(X); }
	void load(windows::byte_t &X) { this->Store::load_pod(X); }

	// ushort

	void save(windows::ushort_t X)
	{
		// big-endian
		this->save(base::high(X));
		this->save(base::low(X));
	}

	void load(windows::ushort_t &X)
	{
		// big-endian
		this->load(base::high(X));
		this->load(base::low(X));
	}

	// short

	void save(windows::short_t X)
	{
		// big-endian
		this->save(base::high(X));
		this->save(base::low(X));
	}

	void load(windows::short_t &X)
	{
		// big-endian
		this->load(base::high(X));
		this->load(base::low(X));
	}

	// ulong

	void save(windows::ulong_t X)
	{
		// big-endian
		this->save(base::high(X));
		this->save(base::low(X));
	}

	void load(windows::ulong_t &X)
	{
		// big-endian
		this->load(base::high(X));
		this->load(base::low(X));
	}

	// long

	void save(windows::long_t X)
	{
		// big-endian
		this->save(base::high(X));
		this->save(base::low(X));
	}	

	void load(windows::long_t &X)
	{
		// big-endian
		this->load(base::high(X));
		this->load(base::low(X));
	}

	// int

	void save(int X)
	{
		// big-endian
		this->save(base::high(X));
		this->save(base::low(X));
	}	

	void load(int &X)
	{
		// big-endian
		this->load(base::high(X));
		this->load(base::low(X));
	}

	// unsigned int

	void save(unsigned int X)
	{
		// big-endian
		this->save(base::high(X));
		this->save(base::low(X));
	}	

	void load(unsigned int &X)
	{
		// big-endian
		this->load(base::high(X));
		this->load(base::low(X));
	}

	// float
	void save(float X) { this->Store::save_pod(X); }
	void load(float &X) { this->Store::load_pod(X); }

	// double
	void save(double X) { this->Store::save_pod(X); }
	void load(double &X) { this->Store::load_pod(X); }
};

template<std::size_t InSize, std::size_t OutSize>
class static_archive_t: public archive_t<static_archive_t<InSize, OutSize> >
{
};

/*
class io_t: handle_t
{
public:
	io_t(const handle_t &handle): handle(handle) {}

	template<std::size_t InSize, std::size_t OutSize>
	class archive_t: public usb::archive_t<InSize, OutSize> {};

	template<ArchiveT>
	void operator()(ArchiveT &archive) const
	{
		this->DeviceIoControl(archive.in(), archive.out());
		archive.reset();
	}
};
*/

}
}
}

#endif
