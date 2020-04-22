/* 
 * EasySoap++ - A C++ library for SOAP (Simple Object Access Protocol)
 * Copyright (C) 2001 David Crowley; SciTegic, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Id: SOAPArray.h,v 1.3 2002/05/20 16:56:11 jgorlick Exp $
 */


#ifndef __SOAPARRAY_H__
#define __SOAPARRAY_H__

#include <new>

#include <easysoap\SOAPUtil.h>
#include <easysoap\SOAPException.h>

BEGIN_EASYSOAP_NAMESPACE

/**
* Wrapper for 1-dimensional array of type T.
* STL compatibility provided.
*/
template <typename T>
class SOAPArray
{
private:
	T*		m_array;
	size_t	m_allocated;
	size_t	m_size;

	void _realloc(size_t s)
	{
		if (s > m_allocated)
		{
			const size_t minalloc = sp_maximum<size_t>(8, 128/sizeof(T));
			size_t toalloc = m_allocated;
			if (toalloc < minalloc)
				toalloc = minalloc;

			while (toalloc < s)
				toalloc *= 2;

			T* newarray = sp_alloc<T>(toalloc);
			if (!newarray)
				throw SOAPMemoryException(); 

			// Copy/construct new array from old array
			size_t i;
			for (i = 0; i < m_size; ++i)
				new (newarray + i) T(m_array[i]);

			// Initialize rest of new array
			for (i = m_size; i < toalloc; ++i)
				new (newarray + i) T();

			s = m_size;
			Empty();
			m_size = s;
			m_array = newarray;
			m_allocated = toalloc;
		}
	}

public:
	typedef T* Iterator;
	typedef const T* ConstIterator;

	/**
	* constructor.
	* @param s initial size of array, default 0.
	*/
	SOAPArray(size_t s = 0)
		: m_array(0)
		, m_allocated(0)
		, m_size(0)
	{
		Resize(s);
	}

	/**
	* copy constructor.
	* @param x source array to copy.
	*/
	SOAPArray(const SOAPArray& x)
		: m_array(0)
		, m_allocated(0)
		, m_size(0)
	{
		Add(x.m_array, x.Size());
	}

	/**
	* operator =.
	* @param x source array to copy.
	* @return this to enable chaining.
	*/
	SOAPArray<T>& operator=(const SOAPArray<T>& x)
	{
		Resize(x.Size());
		for (size_t i = 0; i < x.Size(); ++i)
			m_array[i] = x[i];

		return *this;
	}

	/**
	* destructor.
	*/
	~SOAPArray()
	{
		Empty();
	}

	/**
	* attach, copy and release source.
	* @param other source array to copy and release.
	*/
	void AttachTo(SOAPArray<T>& other)
	{
		Empty();

		m_allocated = other.m_allocated;
		m_array = other.m_array;
		m_size = other.m_size;

		other.m_allocated = 0;
		other.m_array = 0;
		other.m_size = 0;
	}

	/**
	* add allocation only.
	* @return newly allocated element.
	*/
	T& Add()
	{
		size_t len = Size();
		Resize(len + 1);
		return m_array[len];
	}

	/**
	* add.
	* @param val value of element to be allocated.
	* @return newly allocated element.
	*/
	template <typename X>
	T& Add(const X& val)
	{
		size_t len = Size();
		Resize(len + 1);
		return m_array[len] = val;
	}

	/**
	* add all elements from source array.
	* @param a source array.
	*/
	template <typename X>
	void AddArray(const SOAPArray<X>& a)
	{
		Add((const X*)a, a.Size());
	}

	/**
	* add all elements from C source array.
	* @param vals C array of values.
	* @param numVals number of elements in C array of values.
	* @note vals need not be NULL-terminated.
	*/
	template <typename X>
	void Add(const X* vals, size_t numVals)
	{

		size_t len = Size();
		size_t newlen = Size() + numVals;
		Resize(newlen);
		T *work = m_array + len;
		for (size_t i = 0; i < numVals; ++i)
			*work++ = vals[i];
	}

	/**
	* add a value at a specified index.
	* @param index offset for element to be allocated.
	* @param val value for element to be allocated.
	* @return value of newly allocated element.
	*/
	template <typename X>
	T& AddAt(size_t index, const X &val)
	{

		Resize(Size() + 1);
		for (size_t i = Size() - 1; i > index; i--)
			m_array[i] = m_array[i - 1];

		return m_array[index] = val;
	}

	/**
	* begin const iterator.
	* @return const iterator marking beginning of array.
	*/
	ConstIterator Begin() const
	{
		return m_array;
	}

	/**
	* end const interator.
	* @return const iterator marking ending of array.
	*/
	ConstIterator End() const
	{
		return m_array + Size();
	}

	/**
	* begin iterator.
	* @return iterator marking beginning of array.
	*/
	Iterator Begin()
	{
		return m_array;
	}

	/**
	* end iterator.
	* @return iterator marking ending of array.
	*/
	Iterator End()
	{
		return m_array + Size();
	}

	/**
	* empty, clear the array.
	* free all allocated elements, resize to initial allocation.
	*/
	void Empty()
	{
		for (size_t i = 0; i < m_allocated; ++i)
			m_array[i].~T();

		sp_free(m_array);
		m_allocated = 0;
		m_size = 0;
	}
	
	/**
	* test for empty.
	* @return true if the array is empty.
	*/
	bool IsEmpty() const
	{
		return (Size() == 0);
	}

	/**
	* funtional cast to C array.
	* @return head of C array.
	*/
	T* Ptr()
	{
		return m_array;
	}

	/**
	* functional cast to const C array.
	* @return const head of C array.
	*/
	const T* Ptr() const
	{
		return m_array;
	}

	/**
	* cast to C array.
	* @return head of C array.
	*/
	operator T* ()
	{
		return Ptr();
	}

	/**
	* cast to const C array.
	* @return const head of C array.
	*/
	operator const T* () const
	{
		return Ptr();
	}

	/**
	* add multiple items with a single value, similar to a malloc/memset.
	* @param numItems number of items to be allocated.
	* @param value value of items to be allocated.
	*/
	template <typename X>
	void Assign(size_t numItems, const X &value)
	{
		Resize(numItems); 
		for(size_t i = 0; i < Size(); i++)
			m_array[i] = value;
	}

	/**
	* remove element at index.
	* @param index offset for element to be removed.
	*/
	void RemoveAt(size_t index)
	{
		for(size_t i = index; i < Size() - 1; i++)
			m_array[i] = m_array[i + 1]; 

		Resize(Size() - 1); 
	}

	/**
	* current allocation size.
	* @return number of elements.
	*/
	size_t Size() const
	{
		return m_size;
	}

	/**
	* resize the array.
	* @param s requested allocation size.
	* @bug jgorlick>>leaks for s<m_size.  SHOULD free memory for
	* 	m_array[s+1..m_size] prior to setting m_size to s.  Or create
	* 	a scheme where m_allocated is managed separately from m_size.
	*/
	void Resize(size_t s)
	{

		if (s > Size())
			_realloc(s);
		m_size = s;
	}

	/**
	* get element at index.
	* @param index offset of element to be fetched.
	* @return element at index.
	*/
	T& GetAt(size_t index)
	{
		return m_array[index];
	}

	/**
	* get const element at index.
	* @param index offset of element to be fetched.
	* @return const element at index.
	*/
	const T& GetAt(size_t index) const
	{
		return m_array[index];
	}

	/**
	* operator [], treat like C array.
	* @param index offset of element to be fetched.
	* @return element at index.
	*/
	T& operator[](int index)
	{
		return m_array[index];
	}

	/**
	* const operator [], treat like C array.
	* @param index offset of element to be fetched.
	* @return const element at index.
	*/
	const T& operator[](int index) const
	{
		return m_array[index];
	}

	/**
	* operator [], treat like C array.
	* @param index offset of element to be fetched.
	* @return element at index.
	*/
	T& operator[](size_t index)
	{
		return m_array[index];
	}

	/**
	* const operator [], treat like C array.
	* @param index offset of element to be fetched.
	* @return const element at index.
	*/
	const T& operator[](size_t index) const
	{
		return m_array[index];
	}

	/**
	* operator ==.
	* @internal bool return, tests only exact equality, compare to string
	* 	operator ==, which returns int like strcmp indicating the
	* 	first element of difference and uses the sign to indicate
	* 	which string is alphabetically nearer to "A".
	* @param x array to be compared.
	* @return true if arrays are exactly equal.
	*/
	template<typename X>
	bool operator==(const SOAPArray<X>& x) const
	{
		if (m_size != x.m_size)
			return false;
		for (size_t i = 0; i < m_size; ++i)
			if (m_array[i] != x[i])
				return false;
		return true;
	}

	/**
	* operator !=.
	* @param x array to be compared.
	* @return true if arrays are different, by size or by element.
	*/
	template<typename X>
	bool operator!=(const SOAPArray<X>& x) const
	{
		return !(*this == x);
	}

	//
	// For some STL compatibility
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef T value_type;

	/**
	* STL compatibility, const begin.
	* @return const iterator marking beginning of array.
	*/
	const_iterator begin() const	{return Begin();}

	/**
	* STL compatibility, const end.
	* @return const iterator marking ending of array.
	*/
	const_iterator end() const		{return End();}

	/**
	* STL compatibility, begin.
	* @return iterator marking beginning of array.
	*/
	iterator begin()				{return Begin();}

	/**
	* STL compatibility, end.
	* @return iterator marking ending of array.
	*/
	iterator end()					{return End();}

	/**
	* STL compatibility, size.
	* Current allocation size.
	* @return const number of elements.
	*/
	size_t size() const				{return Size();}

	/**
	* STL compatibility, resize.
	* Resize the array.
	* @param s requested allocation size.
	*/
	void resize(size_t s)			{Resize(s);}
};

/**
* Wrapper for 2-dimension array of type T.
*/
template <typename T>
class SOAP2DArray
{
private:
	SOAPArray<T>	m_array;
	size_t			m_rows;
	size_t			m_cols;

	/**
	* @todo implement copy constructor.
	*/
	SOAP2DArray(const SOAP2DArray&);

	/**
	* @todo implement operator =
	*/
	SOAP2DArray& operator=(const SOAP2DArray&);

public:
	/**
	* constructor.
	*/
	SOAP2DArray()
	{
	}

	/**
	* constructor.
	* @param rows number of rows.
	* @param cols number of columns.
	*/
	SOAP2DArray(size_t rows, size_t cols)
	{
		Resize(rows, cols);
	}

	/**
	* resize array.
	* @bug jgorlick>>original contents are overwritten during resize.
	* @param rows number of rows requested for allocation.
	* @param cols number of columns requested for allocation.
	*/
	void Resize(size_t rows, size_t cols)
	{
		m_rows = rows;
		m_cols = cols;
		m_array.Resize(m_rows * m_cols);
	}

	/**
	* accessor for rows.
	* @return const number of rows.
	*/
	size_t GetNumRows() const {return m_rows;}

	/**
	* accessor for columns.
	* @return const number of columns.
	*/
	size_t GetNumCols() const {return m_cols;}

	/**
	* operator [].
	* @param row offset of row to be fetched.
	* @return C array at row.
	* @note client MUST remain within underlying 2-dimensional array bounds.
	*/
	T* operator[](size_t row)
	{
		return m_array.Ptr() + (row * m_cols);
	}

	/**
	* const operator [].
	* @param row offset of row to be fetched.
	* @return const C array at row.
	* @note client MUST remain within underlying 2-dimensional array bounds.
	*/
	const T* operator[](size_t row) const
	{
		return m_array.Ptr() + (row * m_cols);
	}

	/**
	* operator ==.
	* @internal see internal for SOAPArray::operator==
	* @param other array to be compared.
	* @return true if arrays are exactly equal.
	*/
	bool operator==(const SOAP2DArray& other)
	{
		return GetNumRows() == other.GetNumRows() &&
			GetNumCols() == other.GetNumCols() &&
			m_array == other.m_array;
	}

	/**
	* operator !=.
	* @param other array to be compared.
	* @return true if arrays are different, by row, by column,
	* 	or by element.
	*/
	bool operator!=(const SOAP2DArray& other)
	{
		return !(*this == other);
	}


	//
	// For some STL compatibilty
	typedef T value_type;

	/**
	* STL compatibility, resize.
	* @param rows number of rows requested for allocation.
	* @param cols nubmer of columns requested for allocation.
	*/
	void resize(size_t rows, size_t cols)	{Resize(rows, cols);}
};

END_EASYSOAP_NAMESPACE

#endif // __SOAPARRAY_H__

