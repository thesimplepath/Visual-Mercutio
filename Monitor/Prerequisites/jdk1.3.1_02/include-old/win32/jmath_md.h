/*
 * @(#)jmath_md.h	1.12 00/02/02
 *
 * Copyright 1995-2000 Sun Microsystems, Inc. All Rights Reserved.
 * 
 * This software is the proprietary information of Sun Microsystems, Inc.  
 * Use is subject to license terms.
 * 
 */

/*
 * An awful hack, but the dumb MSC compiler #define's exception to _exception
 * for compatibility with non-ANSI names, and this conflicts with the field
 * named 'exception' in 'struct execenv' of interpreter.h.
 */
#include <math.h>
#undef exception

#define DREM(a,b) drem(a,b)

/* drem and rint are defined in math_md.c */
extern double drem(double dividend, double divisor);
extern double rint(double a);
