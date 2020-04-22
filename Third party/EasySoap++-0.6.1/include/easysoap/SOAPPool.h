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
 * $Id: SOAPPool.h,v 1.4 2002/05/29 17:59:43 dcrowley Exp $
 */


#ifndef __SOAPPOOL_H__
#define __SOAPPOOL_H__

#include <easysoap\SOAPStack.h>

BEGIN_EASYSOAP_NAMESPACE

/**
*
*/
template<typename T>
class SOAPPool
{
private:
	SOAPStack<T*>	m_stack;
	int				m_out;

	//
	// Hide default stuff which doesnt make sense
	SOAPPool(const SOAPPool&);
	const SOAPPool& operator=(const SOAPPool&);

public:

	SOAPPool() : m_out(0) {}

	~SOAPPool()
	{
		Empty();
	}

	void Empty()
	{
		while(!m_stack.IsEmpty())
		{
			delete m_stack.Top();
			m_stack.Pop();
		}
	}

	T* Get()
	{
		if (m_stack.IsEmpty())
		{
			T *ret = new T();
			if (!ret)
				throw SOAPMemoryException();
			++m_out;
			return ret;
		}

		T* ret = m_stack.Top();
		m_stack.Pop();
		++m_out;
		return ret;
	}

	T* Get(const T& t)
	{
		if (m_stack.IsEmpty())
		{
			T *ret = new T(t);
			if (!ret)
				throw SOAPMemoryException();
			++m_out;
			return ret;
		}

		T* ret = m_stack.Top();
		m_stack.Pop();
		*ret = t;
		++m_out;
		return ret;
	}

	void Return(T*& ptr)
	{
		if (m_out == 0)
			throw SOAPException("Object leak, object being returned to pool when none were outstanding...");
		--m_out;
		m_stack.Push(ptr);
		ptr = 0;
	}
};

END_EASYSOAP_NAMESPACE

#endif // __SOAPPOOL_H__

