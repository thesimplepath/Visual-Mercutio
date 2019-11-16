/****************************************************************************
 * ==> PSS_ProcessModelDocTmpl ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a process model document template                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessModelDocTmpl.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ProcessModelDocTmpl, PSS_DocTemplateEx)
//---------------------------------------------------------------------------
// PSS_ProcessModelDocTmpl
//---------------------------------------------------------------------------
PSS_ProcessModelDocTmpl::PSS_ProcessModelDocTmpl(UINT           resourceID,
                                                 CRuntimeClass* pDocClass,
                                                 CRuntimeClass* pFrameClass,
                                                 CRuntimeClass* pViewClass,
                                                 WORD           menuID,
                                                 UINT           maxMRU) :
    PSS_DocTemplateEx(resourceID, pDocClass, pFrameClass, pViewClass, menuID, maxMRU)
{}
//---------------------------------------------------------------------------
PSS_ProcessModelDocTmpl::~PSS_ProcessModelDocTmpl()
{}
//---------------------------------------------------------------------------
