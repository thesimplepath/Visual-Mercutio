// SelProcW.cpp: implementation of the ZISelectProcessWizard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SelProcW.h"
#include "SelProcS.h"
#include "SelProcC.h"

// File
#include "zBaseLib\File.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZISelectProcessWizard::ZISelectProcessWizard(ZProcess& Process)
: m_Process(Process)

{

}

ZISelectProcessWizard::~ZISelectProcessWizard()
{

}



BOOL ZISelectProcessWizard::PlayWizard()
{

    ZISelectProcessWizardStart    SelectProcessWizardStart( m_Process.GetName() );

    if (SelectProcessWizardStart.DoModal() == IDCANCEL)
        return FALSE;

    ZISelectProcessWizardChoose    SelectProcessWizardChoose( m_Process );

    if (SelectProcessWizardChoose.DoModal() == IDCANCEL)
        return FALSE;
    // Assign the activity name selected
    m_BaseActivityName = SelectProcessWizardChoose.GetBaseActivityName();

    return TRUE;
}



