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
#ifndef CBEAR_BERLIOS_DE_WINDOWS_USB_ARCHIVE_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_USB_ARCHIVE_HPP_INCLUDED

namespace cbear_berlios_de
{
namespace windows
{
namespace usb
{

template<std::size_t InSize, std::size_t OutSize>
class archive_t;

namespace detail
{

template<std::size_t InSize, std::size_t OutSize>
class oarchive_t
{
public:

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

	typedef archive_t<InSize, OutSize> archive_t;

protected:
	~oarchive_t() {}
private:
	archive_t &archive() { return static_cast<archive_t *>(this); }
};

template<std::size_t InSize, std::size_t OutSize>
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

	typedef archive_t<InSize, OutSize> archive_t;

protected:
	~oarchive_t() {}
private:
	archive_t &archive() { return static_cast<archive_t *>(this); }
};

}

template<std::size_t InSize, std::size_t OutSize>
class archive_t: 
	boost::noncopyable,
	public detail::iarchiv_t<InSize, OutSize>,
	public detail::oarchiv_t<InSize, OutSize>
{
public:

	archive_t() { this->clear(); }	

	byte_range iobuffer() { return byte_range(this->buffer); }

	byte_range ibuffer()
	{ 		
		return byte_range(&this->buffer.front(), &this->buffer[InSize]);
	}

	byte_range obuffer() 
	{ 		
		return byte_range(&this->buffer.front(), &this->buffer[OutSize]);
	}

	void reset() { this->end = buffer.begin(); }

	typedef detail::oarchive_t<InSize, OutSize> oarchive_t;
	typedef detail::iarchive_t<InSize, OutSize> iarchive_t;

	typedef oarchive_t &oarchive_ref;
	typedef iarchive_t &iarchive_ref;

	oarchive_ref oarchive() { return *this; }
	iarchive_ref iarchive() { return *this; }

	// struct

	template<class T>
	void save(const T &X) 
	{ 
		boost::serialization::serialize(oarchive_ref(*this), X);
	}

	template<class T>
	void load(T &X) 
	{ 
		boost::serialization::serialize(iarchive_ref(*this), X);
	}

	// byte
	
	void save(windows::byte_t X) { this->save_pod(X); }
	void load(windows::byte_t &X) { this->load_pod(X); }

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

	// float

	void save(float X) { this->save_pod(X); }
	void load(float &X) { this->load_pod(X); }

	// double

	void save(double X) { this->save_pod(X); }
	void load(double &X) { this->load_pod(X); }

private:
	static const std::size_t Size = InSize < OutSize ? OutSize: InSize;
	typedef boost::array<X, Size> array_t;
	array_t buffer;
	array_y::iterator end;

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
};

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

}
}
}

#endif
