// ProcessModelDocTmpl.h: interface for the ZDProcessModelDocTmpl class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROCESSMODELDOCTMPL_H__774B92A7_A6E0_4F8A_BA01_43592BFF4A62__INCLUDED_)
#define AFX_PROCESSMODELDOCTMPL_H__774B92A7_A6E0_4F8A_BA01_43592BFF4A62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "DocTmplEx.h"

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR - MODIF - Le 16 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

class AFX_EXT_CLASS ZDProcessModelDocTmpl : public ZDDocTemplateEx
{
    DECLARE_DYNAMIC( ZDProcessModelDocTmpl )

public:

    ZDProcessModelDocTmpl( UINT                nIDResource,
                           CRuntimeClass*    pDocClass,
                           CRuntimeClass*    pFrameClass,
                           CRuntimeClass*    pViewClass,
                           WORD                nMenuId            = 0,
                           UINT                nMaxMRU            = _AFX_MRU_COUNT );

    virtual ~ZDProcessModelDocTmpl();
};

#endif // !defined(AFX_PROCESSMODELDOCTMPL_H__774B92A7_A6E0_4F8A_BA01_43592BFF4A62__INCLUDED_)
