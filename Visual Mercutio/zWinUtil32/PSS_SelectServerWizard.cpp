/****************************************************************************
 * ==> PSS_SelectServerWizard ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a select a server Wizard                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_SelectServerWizard.h"

// processsoft
#include "zRes32\ZRes.h"
#include "zBaseLib\ZMessage.h"
#include "PSS_SelectServerWelcomeDialog.h"
#include "PSS_SelectServerDialog.h"

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
CString PSS_SelectServerWizard::m_File;
CString PSS_SelectServerWizard::m_CompleteFile;
CString PSS_SelectServerWizard::m_ServerDirectory;
BOOL    PSS_SelectServerWizard::m_Local;
//---------------------------------------------------------------------------
// PSS_SelectServerWizard
//---------------------------------------------------------------------------
PSS_SelectServerWizard::PSS_SelectServerWizard()
{
    m_Local = FALSE;
}
//---------------------------------------------------------------------------
PSS_SelectServerWizard::PSS_SelectServerWizard(const CString& file, BOOL local)
{
    m_File  = file;
    m_Local = local;
}
//---------------------------------------------------------------------------
PSS_SelectServerWizard::PSS_SelectServerWizard(const PSS_SelectServerWizard& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_SelectServerWizard::~PSS_SelectServerWizard()
{}
//---------------------------------------------------------------------------
const PSS_SelectServerWizard& PSS_SelectServerWizard::operator = (const PSS_SelectServerWizard& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_SelectServerWizard::Execute()
{
    return ProcessSelection();
}
//---------------------------------------------------------------------------
CString PSS_SelectServerWizard::Execute(const CString& file, BOOL local)
{
    m_File  = file;
    m_Local = local;

    if (ProcessSelection())
        return m_CompleteFile;

    return _T("");
}
//---------------------------------------------------------------------------
BOOL PSS_SelectServerWizard::ProcessSelection()
{
    if (m_File.IsEmpty())
        return FALSE;

    PSS_SelectServerWelcomeDialog selectServerWelcomeDialog(m_Local);

    if (selectServerWelcomeDialog.DoModal() == IDCANCEL)
        return FALSE;

    PSS_SelectServerDialog selectServerDialog(m_Local);

    if (selectServerDialog.DoModal() == IDCANCEL)
        return FALSE;

    // no directory selected
    if (selectServerDialog.GetDirectory().IsEmpty())
        return FALSE;

    CString     completeFile = selectServerDialog.GetDirectory() + _T("\\") + m_File;
    CFileStatus status;

    if (!CFile::GetStatus(completeFile, status))
    {
        ZIMessage message;
        message.DisplayMessage(IDS_NF_SELECTSERVER, IDS_NF_SELECTSERVER_TITLE);

        return FALSE;
    }

    m_CompleteFile    = completeFile;
    m_ServerDirectory = selectServerDialog.GetDirectory();

    return TRUE;
}
//---------------------------------------------------------------------------
