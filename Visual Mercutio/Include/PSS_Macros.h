/****************************************************************************
 * ==> PSS_Macros ----------------------------------------------------------*
 ****************************************************************************
 * Description : Defines the global macros                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MacrosH
#define PSS_MacrosH

// shorten runtime type information calls
#if !defined(ISA)
    #define ISA(pObj, className) pObj->IsKindOf(RUNTIME_CLASS(className))
#endif

#endif