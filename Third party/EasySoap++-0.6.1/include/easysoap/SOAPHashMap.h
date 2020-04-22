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
 * $Id: SOAPHashMap.h,v 1.3 2002/04/10 07:03:41 dcrowley Exp $
 */


#ifndef __SOAPHASHMAP_H__
#define __SOAPHASHMAP_H__

#ifdef _MSC_VER
#pragma warning(disable: 4284)
#endif // _MSC_VER

BEGIN_EASYSOAP_NAMESPACE

/**
 * Functor used by SOAPHashMap class to generate
 * a hashcode for an object of type T.
 *
 * It must be specialized for your own class.
 *
 * Specialized only for SOAPString.
 */
template<typename T>
struct SOAPHashCodeFunctor;

/**
 * Functor used by SOAPHashMap class to compare
 * for equality two objects of type T.
 *
 * It can be specialized for your own class, by
 * default it simply uses operator==.
 */
template<typename T>
struct SOAPEqualsFunctor
{
	bool operator()(const T& a, const T& b) const
	{
		return a == b;
	}
};


/**
 * Functor to be specialized for use with SOAPHashMapNoCase.
 * Specialized only for SOAPString.
 */
template<typename T>
struct SOAPHashCodeFunctorNoCase;

/**
 * Functor to be specialized for use with SOAPHashMapNoCase.
 * Specialized only for SOAPString.
 */
template<typename T>
struct SOAPEqualsFunctorNoCase;

END_EASYSOAP_NAMESPACE

#include <easysoap\SOAPUtil.h>
#include <easysoap\SOAPPool.h>

BEGIN_EASYSOAP_NAMESPACE

/**
 * SOAPHashMap is a general purpose templated hash table class.
 */
template <typename K, typename I,
	typename H = SOAPHashCodeFunctor<K>,
	typename E = SOAPEqualsFunctor<K> >
class SOAPHashMap
{
private:
	// structure for keeping a linked-list of elements
	struct HashElement {
		HashElement(): m_next(0), m_hash(0)
		{
		}

		HashElement	*m_next;
		size_t		m_hash;
		K			m_key;
		I			m_item;
	};

	H hashcode;
	E equals;

	typedef SOAPArray<HashElement*>	Elements;

	Elements				m_elements;
	SOAPPool<HashElement>	m_pool;
	size_t					m_numElements;
	float					m_fillfactor;
	size_t					m_resizeThreshold;

	/**
	 * Iterator class for SOAPHashMap
	 */
	class ForwardHashMapIterator
	{
	private:
		const SOAPHashMap		*m_map;
		typename Elements::Iterator		m_index;
		HashElement				*m_he;
		
		friend class SOAPHashMap<K,I,H,E>;

		// private constuctor that can only be called by SOAPHashMap
		ForwardHashMapIterator(const SOAPHashMap *map, typename Elements::Iterator index)
			: m_map(map), m_index(index), m_he(0)
		{
			if (m_map)
			{
				// Find first bucket with an element
				while (m_index != m_map->m_elements.End() && !(m_he = *m_index))
						++m_index;
			}
		}

		ForwardHashMapIterator(const SOAPHashMap *map, typename Elements::Iterator index, HashElement *he)
			: m_map(map), m_index(index), m_he(he)
		{
		}

	public:
		/**
		 * Default constructor for the SOAPHashMap iterator.
		 */
		ForwardHashMapIterator()
			: m_map(0), m_index(0)
		{
		}

		/**
		 * Copy constructor for the SOAPHashMap iterator.
		 */
		ForwardHashMapIterator(const ForwardHashMapIterator& r)
			: m_map(r.m_map), m_index(r.m_index), m_he(r.m_he)
		{
		}

		/**
		 * Assignment operator for the SOAPHashMap iterator.
		 */
		ForwardHashMapIterator& operator=(const ForwardHashMapIterator& r)
		{
			m_map = r.m_map;
			m_index = r.m_index;
			m_he = r.m_he;
			return *this;
		}

		/**
		 * Equals operator for the SOAPHashMap iterator.
		 *
		 * Returns true iff the two iterators point at the
		 * same object in the same hash table.
		 */
		bool operator==(const ForwardHashMapIterator& r) const
		{
			// make sure we're pointing to the exact same element
			return m_he == r.m_he;
		}

		/**
		 * Not equals operator for the SOAPHashMap iterator.
		 *
		 * Returns false iff the two iterators point at the
		 * same object in the same hash table.
		 */
		bool operator!=(const ForwardHashMapIterator& r) const
		{
			// can't be pointing to the same element...
			return m_he != r.m_he;
		}

		/**
		 * Increment iterator to point at the next element
		 * in the SOAPHashMap.
		 */
		ForwardHashMapIterator& Next()
		{
			if (m_index != m_map->m_elements.End() && !(m_he = m_he->m_next))
				while (++m_index != m_map->m_elements.End() && !(m_he = *m_index))
					;
			return *this;
		}

		/**
		 * Pre-increment
		 */
		ForwardHashMapIterator& operator++()
		{
			return Next();
		}

		/**
		 * Post-increment
		 */
		ForwardHashMapIterator operator++(int)
		{
			// copy our current position
			ForwardHashMapIterator ret(*this);
			// move to the next item
			Next();
			// return the old position
			return ret;
		}

		/**
		 * operator bool returns true if the iterator
		 * points to a valid element in the SOAPHashMap
		 *
		 * This is so you can do tests like this:
		 *
		 * SOAPHashMap<SOAPString,int>::Iterator i = map.Find("Hello");
		 * if (i)
		 * {
		 *    // we found the element
		 * }
		 */
		operator bool()
		{
			return m_index != m_map->m_elements.End();
		}

		/**
		 * operator ! returns true if the iterator
		 * does not point to a valid element in the SOAPHashMap.
		 *
		 * This is so you can do tests like this:
		 *
		 * SOAPHashMap<SOAPString,int>::Iterator i = map.Find("Hello");
		 * if (!i)
		 * {
		 *    // We didn't find the element
		 * }
		 */
		bool operator!()
		{
			return m_index == m_map->m_elements.End();
		}

		/**
		 * The iterator can be used like a pointer
		 * which points to the value portion of
		 * the element.  Thus *i returns a reference
		 * to the value and i->member can be used to
		 * access a member of the value.
		 */
		I& operator*()
		{
			return m_he->m_item;
		}

		const I& operator*() const
		{
			return m_he->m_item;
		}

		I* operator->()
		{
			return &m_he->m_item;
		}

		const I* operator->() const
		{
			return &m_he->m_item;
		}

		/**
		 *
		 * Explicit method used to access the value
		 * portion of the current element pointed to
		 * by the iterator.
		 */
		const I& Item() const
		{
			return m_he->m_item;
		}

		I& Item()
		{
			return m_he->m_item;
		}

		/**
		 * Explicit method to access the key portion of the current
		 * element.  The key cannot be modified!
		 */
		const K& Key() const
		{
			return m_he->m_key;
		}
	};

public:
	typedef ForwardHashMapIterator Iterator;

	/**
	 * Destructor
	 */
	~SOAPHashMap()
	{
		Empty();
	}
	
	/**
	 * Default constructor
	 *
	 * @param s Initial number of buckets in the hash table.
	 * @param fillfactor As a percentage how full hash table must
	 * become before the size is increased.
	 */
	SOAPHashMap(size_t s = 31, float fillfactor = 0.75) :
		m_numElements(0), m_fillfactor(fillfactor), m_resizeThreshold(0)
	{
		Resize(s); // this sets m_resizeThreshold
	}

	/**
	 * Copy constructor
	 */
	template<typename A, typename B, typename C, typename D>
	SOAPHashMap(const SOAPHashMap<A,B,C,D>& r) :
		m_numElements(0), m_fillfactor(r.GetFillFactor()), m_resizeThreshold(0)
	{
		Resize(r.GetNumBuckets()); // this sets m_resizeThreshold
		*this = r;
	}

	/**
	 * Copy constructor
	 */
	SOAPHashMap(const SOAPHashMap& r) :
		m_numElements(0), m_fillfactor(r.GetFillFactor()), m_resizeThreshold(0)
	{
		Resize(r.GetNumBuckets()); // this sets m_resizeThreshold
		*this = r;
	}

	/**
	 * Assignment operator.
	 */
	template<typename A, typename B, typename C, typename D>
	SOAPHashMap& operator=(const SOAPHashMap<A,B,C,D>& r)
	{
		if ((void *)this != (void *)&r)
		{
			Clear();
			Resize(r.GetNumBuckets());
			SOAPHashMap<A,B,C,D>::Iterator e = r.End();
			for (SOAPHashMap<A,B,C,D>::Iterator it = r.Begin(); it != e; ++it)
				Add(it.Key(), it.Item());
		}
		return *this;
	}

	/**
	 * Assignment operator.
	 */
	SOAPHashMap& operator=(const SOAPHashMap& r)
	{
		if (this != &r)
		{
			Clear();
			Resize(r.GetNumBuckets());
			Iterator e = r.End();
			for (Iterator it = r.Begin(); it != e; ++it)
				Add(it.Key(), it.Item());
		}
		return *this;
	}

	/**
	 * Returns an iterator which points to the
	 * first element in the hash table.  As the
	 * iterator is incremented elements are returned
	 * in hash order, not sorted like an STL map.
	 */
	Iterator Begin() const
	{
		return Iterator(this, (Elements::Iterator)m_elements.Begin());
	}

	/**
	 * Returns an iterator which points to
	 * an invalid element, one past the last
	 * valid element.
	 */
	Iterator End() const
	{
		return Iterator(this, (Elements::Iterator)m_elements.End());
	}


	/**
	 * Adds an element to the SOAPHashMap with the
	 * given key and value.  If an element with the
	 * given key already exists then the value is
	 * changed to the given value.
	 *
	 * @param key The key lookup value.
	 * @param item The value associated with the key.
	 */
	template <typename X, typename Y>
	I& Add(const X& key, const Y& item)
	{
		// see if we can find it
		size_t hash = hashcode(key);
		Iterator found = Find(key, hash);
		if (found)
			return *found = item;
		return Put(hash, key, item);
	}

	/**
	 * Returns a reference to the the value in the
	 * SOAPHashMap with the give key.  If the key
	 * value does not exist then one is inserted
	 * and a (potentially) uninitialized value
	 * is returned.
	 *
	 * @param key The key lookup value.
	 */
	template <typename X>
	I& operator[](const X& key)
	{
		// see if we can find it
		size_t hash = hashcode(key);
		Iterator found = Find(key, hash);
		if (found)
			return *found;
		return Put(hash, key);
	}


	/**
	 * Removes the value with the give key
	 * from the SOAPHashMap and returns true
	 * or returns false if no value with the
	 * given key was found.
	 */
	template <typename X>
	bool Remove(const X& key)
	{
		if (m_elements.Size() > 0)
		{
			size_t hash = hashcode(key);
			// we use ** here so we can treat the first element the
			// same was as the other elements in the linked list
			HashElement **he = &m_elements[hash % m_elements.Size()];
			while (*he)
			{
				if ((*he)->m_hash == hash && equals((*he)->m_key, key))
				{
					HashElement *temp = (*he)->m_next;
					PutBackHashElement(*he);
					*he = temp;
					return true;
				}
				he = &((*he)->m_next);
			}
		}
		return false;
	}

	/**
	 * Clears out the SOAPHashTable and
	 * all values are removed.
	 *
	 * Actual instances of objects are NOT
	 * deleted but saved to be reused later.
	 */
	void Clear()
	{
		for (Elements::Iterator i = m_elements.Begin(); i != m_elements.End(); ++i)
		{
			HashElement *he = *i;
			while (he)
			{
				HashElement *next = he->m_next;
				PutBackHashElement(he);
				he = next;
			}
			*i = 0;
		}
	}

	/**
	 * Clears out the SOAPHashTable and
	 * all values are removed.
	 *
	 * Actual instances of objects are deleted.
	 */
	void Empty()
	{
		Elements::Iterator i;
		for (i = m_elements.Begin(); i != m_elements.End(); ++i)
		{
			HashElement *he = *i;
			while (he)
			{
				HashElement *next = he->m_next;
				delete he;
				he = next;
			}
		}

		m_pool.Empty();
	}

	/**
	 * Returns the number of elements in the SOAPHashTable.
	 */
	size_t Size() const
	{
		return m_numElements;
	}

	/**
	 * Finds and returns an iterator which points
	 * to the element with the given key value.
	 * If no element with the given key is found
	 * then the value of End() is returned.
	 */
	template <typename X>
	Iterator Find(const X& key) const
	{
		size_t hash = hashcode(key);
		return Find(key, hash);
	}

	/**
	 * Returns how many internal hash buckets
	 * are being used.
	 */
	size_t GetNumBuckets() const {return m_elements.Size();}

	/**
	 * Returns the fill factor.
	 */
	float GetFillFactor() const {return m_fillfactor;}


	/**
	 * These typedefs are supplied to make
	 * the SOAPHashMap class more STL friendly.
	 */
	typedef K key_type;
	typedef Iterator iterator;
	typedef Iterator const_iterator;

	/**
	 * These methods are supplied to make
	 * the SOAPHashMap class more STL friendly.
	 */
	iterator begin() const {return Begin();}
	iterator end() const {return End();}

private:
	// Does the actual find.  We pass in the hashcode so we don't have
	// to recompute it since it is used in other places.
	template <typename X>
	Iterator Find(const X& key, size_t hash) const
	{
		if (m_elements.Size() > 0)
		{
			size_t index = hash % m_elements.Size();
			HashElement *he = m_elements[index];
			while (he)
			{
				if (he->m_hash == hash && equals(he->m_key, key))
					return Iterator(this, (Elements::Iterator)m_elements.Begin() + index, he);
				he = he->m_next;
			}
		}
		return End();
	}

	// resize only if it makes the table bigger
	void Resize(size_t newsize)
	{
		if (newsize <= m_elements.Size())
			return;

		Elements newelements;
		newelements.Resize(newsize);
		Elements::Iterator i;

		for (i = newelements.Begin(); i != newelements.End(); ++i)
			*i = 0;

		for (i = m_elements.Begin(); i != m_elements.End(); ++i)
		{
			HashElement *he = *i;
			while (he)
			{
				HashElement *next = he->m_next;
				size_t index = he->m_hash % newsize;
				he->m_next = newelements[index];
				newelements[index] = he;
				he = next;
			}
		}

		m_resizeThreshold = (size_t)(m_fillfactor * newsize);
		m_elements.AttachTo(newelements);
	}

	void PutBackHashElement(HashElement *he)
	{
		m_pool.Return(he);
		--m_numElements;
	}

	HashElement *GetNextHashElement(size_t hash)
	{
		HashElement *he = m_pool.Get();
		he->m_hash = hash;
		++m_numElements;
		return he;
	}

	// This method actually puts an object into the hashtable.
	template<typename X, typename Y>
	I& Put(size_t hash, const X& key, const Y& item)
	{
		// check for resize
		if (m_numElements >= m_resizeThreshold)
			Resize(m_elements.Size() * 2 + 1);

		size_t index = hash % m_elements.Size();
		HashElement *he = GetNextHashElement(hash);

		he->m_key = key;
		he->m_item = item;
		he->m_next = m_elements[index];
		m_elements[index] = he;

		return he->m_item;
	}

	// This method actually puts an object into the hashtable.
	template <typename X>
	I& Put(size_t hash, const X& key)
	{
		// check for resize
		if (m_numElements >= m_resizeThreshold)
			Resize(m_elements.Size() * 2 + 1);

		size_t index = hash % m_elements.Size();
		HashElement *he = GetNextHashElement(hash);

		he->m_key = key;
		he->m_next = m_elements[index];
		m_elements[index] = he;

		return he->m_item;
	}

	friend class ForwardHashMapIterator;
};


/**
 * This class is used to easily create a case insensitive
 * SOAPHashMap container.
 *
 * This class overides the the default hashcode functor (template
 * parameter H) and equals functor (template parameter E) which
 * of the SOAPHashMap class to SOAPHashCodeFunctorNoCase<K> and
 * SOAPEqualsFunctorNoCase<K> respectively.
 *
 * These functors are only implemented for the SOAPString class.
 *
 * @see SOAPHashCodeFunctorNoCase<SOAPString>
 * @see SOAPEqualsFunctorNoCase<SOAPString>
 *
 */
template<typename K, typename I>
class SOAPHashMapNoCase : public SOAPHashMap<K, I,
				SOAPHashCodeFunctorNoCase<K>,
				SOAPEqualsFunctorNoCase<K> >
{
private:
	typedef SOAPHashMap<K, I,
				SOAPHashCodeFunctorNoCase<K>,
				SOAPEqualsFunctorNoCase<K> > super;

public:
	SOAPHashMapNoCase(size_t s = 31, float fillfactor = 0.75)
		: super(s, fillfactor)
	{
	}
};

END_EASYSOAP_NAMESPACE

#endif // __SOAPHASHMAP_H__

