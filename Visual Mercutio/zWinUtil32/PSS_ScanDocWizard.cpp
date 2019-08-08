/****************************************************************************
 * ==> PSS_ScanDocWizard ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a scan documents Wizard                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ScanDocWizard.h"

// processsoft
#include "zBaseLib\file.h"
#include "zBaseLib\ZDirectory.h"
#include "zBaseLib\MsgBox.h"
#include "zWeb\PSS_FilePreviewDlg.h"
#include "PSS_ScanWelcomeDialog.h"
#include "PSS_ScanInformationDialog.h"
#include "PSS_ScanContinueSelectDialog.h"

//---------------------------------------------------------------------------
// PSS_ScanDocWizard::IDocument
//---------------------------------------------------------------------------
PSS_ScanDocWizard::IDocument::IDocument(const CString& fileName, const CString& name, const CString& description) :
    CObject(),
    m_FileName(fileName),
    m_Name(name),
    m_Description(description)
{}
//---------------------------------------------------------------------------
PSS_ScanDocWizard::IDocument::~IDocument()
{}
//---------------------------------------------------------------------------
// PSS_ScanDocWizard
//---------------------------------------------------------------------------
PSS_ScanDocWizard::PSS_ScanDocWizard()
{}
//---------------------------------------------------------------------------
PSS_ScanDocWizard::PSS_ScanDocWizard(const PSS_ScanDocWizard& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ScanDocWizard::~PSS_ScanDocWizard()
{
    const std::size_t docCount = GetDocumentCount();

    for (std::size_t index = 0; index < docCount; ++index)
        if (GetDocumentAt(index))
            delete GetDocumentAt(index);

    m_DocArray.RemoveAll();
}
//---------------------------------------------------------------------------
const PSS_ScanDocWizard& PSS_ScanDocWizard::operator = (const PSS_ScanDocWizard& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_ScanDocWizard::Execute()
{
    return ProcessSelection();
}
//---------------------------------------------------------------------------
PSS_ScanDocWizard::IDocument* PSS_ScanDocWizard::GetDocumentAt(std::size_t index)
{
    if (index < std::size_t(m_DocArray.GetSize()))
        return (IDocument*)m_DocArray.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ScanDocWizard::AddDocument(const CString& fileName, const CString& name, const CString& description)
{
    std::unique_ptr<IDocument> pDoc(new IDocument(fileName, name, description));
    
    if (pDoc.get())
    {
        m_DocArray.Add(pDoc.get());
        pDoc.release();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ScanDocWizard::ProcessSelection()
{
    PSS_ScanWelcomeDialog scanWelcomeDialog;

    if (scanWelcomeDialog.DoModal() == IDCANCEL)
        return FALSE;

    bool firstTime = true;

    while (true)
    {
        PSS_ScanContinueSelectDialog scanContinueSelectDialog(firstTime);
        
        const UINT retValue = scanContinueSelectDialog.DoModal();

        if (retValue == IDCANCEL)
            return FALSE;
        else
        if (retValue == IDOK)
            break;

        // show the file in preview
        PSS_FilePreviewDlg filePreviewDlg(LPCTSTR(scanContinueSelectDialog.GetFileName()), FALSE);
        filePreviewDlg.DoModal();

        MsgBox mBox;

        // ask if the user wants to include the selected file
        if (mBox.DisplayMsgBox(IDS_CONFIRM_INSERT_SCANDOC, MB_YESNO) == IDYES)
        {
            PSS_ScanInformationDialog scanInforDialog(scanContinueSelectDialog.GetFileName());

            if (scanInforDialog.DoModal() == IDCANCEL)
                return FALSE;

            // add the document in the table
            AddDocument(scanContinueSelectDialog.GetFileName(), scanInforDialog.GetName(), scanInforDialog.GetDescription());

            ZFile fileSelected(scanContinueSelectDialog.GetFileName());

            // change de directory to prevent the user to select the same
            ZDirectory::ChangeCurrentDirectory(fileSelected.GetFilePath());

            // reset the flag for first time
            firstTime = false;
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
