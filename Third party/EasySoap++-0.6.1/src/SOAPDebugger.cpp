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
 * $Id: SOAPDebugger.cpp,v 1.11 2001/11/21 06:00:47 dcrowley Exp $
 */


#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap/SOAPDebugger.h>

USING_EASYSOAP_NAMESPACE

FILE *SOAPDebugger::m_file = 0;
int SOAPDebugger::m_messageLevel = 1;

void
SOAPDebugger::SetMessageLevel(int level)
{
	m_messageLevel = level;
}

void
SOAPDebugger::Write(int level, const char *bytes, size_t len)
{
	if (level <= m_messageLevel && m_file)
	{
		fwrite(bytes, 1, len, m_file);
		fflush(m_file);
	}
}

void
SOAPDebugger::Print(int level, const char *str, ...)
{
	if (level <= m_messageLevel && m_file)
	{
		va_list ap;
		va_start(ap, str);
		vfprintf(m_file, str, ap);
		va_end(ap);
		fflush(m_file);
	}
}

void
SOAPDebugger::Close()
{
	if (m_file)
	{
		fwrite("\r\n", 1, 2, m_file);
		fclose(m_file);
		m_file = 0;
	}
}

bool
SOAPDebugger::SetFile(const char *name)
{
	Close();
	m_file = fopen(name, "wb");
	return (m_file != 0);
}
