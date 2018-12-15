/****************************************************************************
 * ==> zMacros --.....------------------------------------------------------*
 ****************************************************************************
 * Description : Defines the global macros                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef zMacrosH
#define zMacrosH

// shorten runtime type information calls
#if !defined(ISA)
    #define ISA(pObj, className) pObj->IsKindOf(RUNTIME_CLASS(className))
#endif

#endif