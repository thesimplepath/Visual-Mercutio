/****************************************************************************
 * ==> PSS_Macros ----------------------------------------------------------*
 ****************************************************************************
 * Description : Defines the global macros                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_MacrosH
#define PSS_MacrosH

// std
#include <string>

// shorten runtime type information calls
#ifndef ISA
    #define ISA(pObj, className) pObj->IsKindOf(RUNTIME_CLASS(className))
#endif

// processsoft assert macro, available in both debug and release
#ifndef PSS_Assert
    // required to convert the __LINE__ number into a string using preprocessor macros
    #define M_S1(x) #x
    #define M_S2(x) M_S1(x)
    #define M_LINENB M_S2(__LINE__)

    #define PSS_Assert(condition)\
    {\
        if (!(condition))\
        {\
            std::string message  = "Assertion FAILED - ";\
                        message += #condition;\
                        message += " - in file - ";\
                        message += __FILE__;\
                        message += " - at line - ";\
                        message += M_LINENB;\
    \
            throw std::exception(message.c_str());\
        }\
    }
#endif

#endif