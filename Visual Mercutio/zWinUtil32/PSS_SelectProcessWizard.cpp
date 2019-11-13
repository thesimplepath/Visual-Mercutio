/****************************************************************************
 * ==> PSS_SelectProcessWizard ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a select process Wizard                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SelectProcessWizard.h"

// processsoft
#include "zBaseLib\PSS_File.h"
#include "PSS_SelectProcessWizardStartDialog.h"
#include "PSS_SelectProcessWizardDialog.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_SelectProcessWizard
//---------------------------------------------------------------------------
PSS_SelectProcessWizard::PSS_SelectProcessWizard(PSS_Process& process) :
    m_Process(process)
{}
//---------------------------------------------------------------------------
PSS_SelectProcessWizard::~PSS_SelectProcessWizard()
{}
//---------------------------------------------------------------------------
BOOL PSS_SelectProcessWizard::Execute()
{
    PSS_SelectProcessWizardStartDialog selectProcessWizardStartDialog(m_Process.GetName());

    if (selectProcessWizardStartDialog.DoModal() == IDCANCEL)
        return FALSE;

    PSS_SelectProcessWizardDialog selectProcessWizardDialog(m_Process);

    if (selectProcessWizardDialog.DoModal() == IDCANCEL)
        return FALSE;

    // assign the activity name selected
    m_BaseActivityName = selectProcessWizardDialog.GetBaseActivityName();

    return TRUE;
}
//---------------------------------------------------------------------------
