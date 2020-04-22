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
 * $Id: es_borl.h,v 1.1 2002/03/14 22:33:19 dcrowley Exp $
 */

#ifndef __ES_BORL_H_
#define __ES_BORL_H_

#define HAVE_ERRNO_H
#define HAVE_MATH_H
#define HAVE_MALLOC_H
#define HAVE_STDLIB_H
#define HAVE_FLOAT_H
#define HAVE_WCHART

#define snprintf _snprintf
#define vsnprintf _vsnprintf
#define isnan _isnan
#define finite _finite

#ifdef EASYSOAP_STATIC
#define EASYSOAP_EXPORT
#else // not EASYSOAP_STATIC
#ifdef EASYSOAP_DLL
#define EASYSOAP_EXPORT __declspec( dllexport )
#else // not EASYSOAP_DLL
#define EASYSOAP_EXPORT __declspec (dllimport )
#endif // EASYSOAP_EXPORTS
#endif // EASYSOAP_STATIC

#define MEMBER_TYPE(T) T

#endif // __ES_BORL_H_
