#ifndef CBEAR_BERLIOS_DE_RANGE_VECTOR_HPP_INCLUDED
#define CBEAR_BERLIOS_DE_RANGE_VECTOR_HPP_INCLUDED

#include <cbear.berlios.de/range/iterator_range.hpp>
#include <cbear.berlios.de/range/move.hpp>
#include <cbear.berlios.de/range/copy.hpp>
#include <cbear.berlios.de/select/traits.hpp>

namespace cbear_berlios_de
{
namespace range
{

template<class T>
class vector_base_t
{
public:
	typedef T *iterator;
	typedef T const *const_iterator;
};

template<class T>
class vector_t: public helper_t<vector_t<T>, vector_base_t<T> >
{
private:
	typedef helper_t<vector_t<T>, vector_base_t<T> > base_t;
	void construct(::std::size_t S)
	{
		this->range = iterator_range_t(new T[S], S);
	}
public:

	typedef typename base_t::iterator iterator;
	typedef typename base_t::const_iterator const_iterator;
	typedef iterator_range<iterator> iterator_range_t;

	vector_t()
	{
	}

	explicit vector_t(::std::size_t S)
	{
		this->construct(S);
	}

	~vector_t()
	{
		delete[] this->range.begin();
	}

	vector_t(vector_t const &x)
	{
		this->construct(x.size());
		range::copy(x, this->begin());
	}

	vector_t &operator=(vector_t const &x)
	{
		this->resize(x.size());
		range::copy(x, this->begin());
		return *this;
	}

	template<class F>
	void move_assign(F &From)
	{
		BOOST_STATIC_ASSERT((boost::is_same<F, vector_t>::value));
		this->swap(From);
	}

	template<class F>
	void swap(F &B)
	{
		BOOST_STATIC_ASSERT((boost::is_same<F, vector_t>::value));
		this->range.swap(B.range);
	}

	iterator begin() throw()
	{
		return this->range.begin();
	}

	iterator end() throw()
	{
		return this->range.end();
	}

	const_iterator begin() const throw()
	{
		return this->range.begin();
	}

	const_iterator end() const throw()
	{
		return this->range.end();
	}

	template<class range_t>
	iterator insert_range(iterator P, range_t const &R)
	{
		if(R.empty())
		{
			return P;
		}
		vector_t New(this->size() + range::size(R));
		iterator result = range::move(
			iterator_range_t(this->begin(), P), New.begin());
		range::move(iterator_range_t(P, this->end()), range::copy(R, result));
		this->move_assign(New);
		return result;
	}

	void erase_range(iterator_range_t const &R)
	{
		if(R.empty())
		{
			return;
		}
		vector_t New(this->size() - R.size());
		range::move(
			iterator_range_t(R.end(), this->end()), 
			range::move(
				iterator_range_t(this->begin(), R.begin()), 
				New.begin()));
		this->move_assign(New);
	}

	template<class stream_t>
	void write(stream_t &stream) const
	{
		typedef typename stream_t::value_type char_t;
		stream << CBEAR_BERLIOS_DE_SELECT_STRING(char_t, "{");
		{
			const_iterator_range_t r(*this);
			if(!r.empty())
			{
				for(;;)
				{
					stream << r.front();
					++r.begin();
					if(r.empty())
					{
						break;
					}
					stream << CBEAR_BERLIOS_DE_SELECT_STRING(char_t, ", ");
				}
			}
		}
		stream << CBEAR_BERLIOS_DE_SELECT_STRING(char_t, "}");
	}

private:
	iterator_range<iterator> range;
};

}
}

#endif
