/*
 * @(#)tree.h	1.41 00/02/02
 *
 * Copyright 1994-2000 Sun Microsystems, Inc. All Rights Reserved.
 * 
 * This software is the proprietary information of Sun Microsystems, Inc.  
 * Use is subject to license terms.
 * 
 */

/*
 * Definitions having to do with the program tree
 */

#ifndef _JAVASOFT_TREE_H_
#define _JAVASOFT_TREE_H_

#include "oobj.h"	/* for the definition of unicode */
#include "typecodes.h"

extern ClassClass **binclasses;
extern int nbinclasses, sizebinclasses;

/* User specifiable attributes */
#define ACC_PUBLIC            0x0001    /* visible to everyone */
#define ACC_PRIVATE           0x0002	/* visible only to the defining class */
#define ACC_PROTECTED         0x0004    /* visible to subclasses */
#define ACC_STATIC            0x0008    /* instance variable is static */
#define ACC_FINAL             0x0010    /* no further subclassing, overriding */
#define ACC_SYNCHRONIZED      0x0020    /* wrap method call in monitor lock */
#define ACC_SUPER             0x0020    /* funky handling of invokespecial */
#define ACC_VOLATILE          0x0040    /* can cache in registers */
#define ACC_TRANSIENT         0x0080    /* not persistant */
#define ACC_NATIVE            0x0100    /* implemented in C */
#define ACC_INTERFACE         0x0200    /* class is an interface */
#define ACC_ABSTRACT	      0x0400	/* no definition provided */
#define ACC_STRICT            0x0800    /* strict floating point */

#define ACC_WRITTEN_FLAGS     0x0FFF    /* flags actually put in .class file */

/* Other attributes */
#define ACC_VALKNOWN          0x2000    /* constant with known value */
#define ACC_MACHINE_COMPILED  0x4000    /* compiled to machine code */
#define ACC_MIRANDA_METHOD    0x8000    /* auto-generated abstract methods */

#define IsPrivate(access) (((access) & ACC_PRIVATE) != 0)
#define IsPublic(access)  (((access) & ACC_PUBLIC) != 0)
#define IsProtected(access)  (((access) & ACC_PROTECTED) != 0)

#ifdef TRIMMED
# undef DEBUG
# undef STATS
# define NOLOG
#endif


#endif /* !_JAVASOFT_TREE_H_ */
