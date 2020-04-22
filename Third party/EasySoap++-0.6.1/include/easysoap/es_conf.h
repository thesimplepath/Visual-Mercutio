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
 * $Id: es_conf.h,v 1.4 2002/06/26 20:09:26 dcrowley Exp $
 */

#ifndef __ES_CONF_H_
#define __ES_CONF_H_

#include "es_comp.h"

#ifndef EASYSOAP_EXPORT
#define EASYSOAP_EXPORT
#endif

//
// There are a few situations where some compilers
// want the typename keyword before a type declaration.
// Some compilers on the other hand don't like it one
// bit ....
#ifdef HAVE_TEMPLATE_KEYWORD_QUALIFIER
#define MEMBER_TYPE(T) typename T
#else
#define MEMBER_TYPE(T) T
#endif

//
//  Let's set up a macro for compilers that
//  support namespaces...
#ifdef HAVE_NAMESPACES 
#define BEGIN_EASYSOAP_NAMESPACE namespace EasySoap {
#define END_EASYSOAP_NAMESPACE }
#define EASYSOAP_NAMESPACE(x) EasySoap::x
#define USING_EASYSOAP_NAMESPACE using namespace EasySoap;
#else // DONT HAVE_NAMESPACES
#define BEGIN_EASYSOAP_NAMESPACE
#define END_EASYSOAP_NAMESPACE
#define EASYSOAP_NAMESPACE(x) x
#define USING_EASYSOAP_NAMESPACE
#endif

//
// If we're using the dmalloc library...
// we have to include the malloc family defines
// before we include the dmalloc header.
#ifdef DEBUG_DMALLOC
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif // HAVE_STDLIB_H
#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif // HAVE_MALLOC_H
#include <dmalloc.h>
#endif // DEBUG_DMALLOC

#endif // __ES_CONF_H_
