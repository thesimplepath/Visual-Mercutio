/****************************************************************************
 * ==> PSS_ScanDocuments ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a scan documents manager                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ScanDocuments.h"

// processsoft
#include "zBaseLib\file.h"
#include "zBaseLib\ZDirectory.h"
#include "zBaseLib\MsgBox.h"
#include "zWeb\PSS_FilePreviewDlg.h"
#include "PSS_ScanWelcomeDialog.h"
#include "PSS_ScanInformationDialog.h"
#include "PSS_ScanContinueSelectDialog.h"

//---------------------------------------------------------------------------
// PSS_ScanDocuments::IDocument
//---------------------------------------------------------------------------
PSS_ScanDocuments::IDocument::IDocument(const CString& fileName, const CString& name, const CString& description) :
    m_FileName(fileName),
    m_Name(name),
    m_Description(description)
{}
//---------------------------------------------------------------------------
PSS_ScanDocuments::IDocument::~IDocument()
{}
//---------------------------------------------------------------------------
// PSS_ScanDocuments
//---------------------------------------------------------------------------
PSS_ScanDocuments::PSS_ScanDocuments()
{}
//---------------------------------------------------------------------------
PSS_ScanDocuments::PSS_ScanDocuments(const PSS_ScanDocuments& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ScanDocuments::~PSS_ScanDocuments()
{
    const std::size_t docCount = GetDocumentCount();

    for (std::size_t index = 0; index < docCount; ++index)
        if (GetDocumentAt(index))
            delete GetDocumentAt(index);

    m_Doc.RemoveAll();
}
//---------------------------------------------------------------------------
const PSS_ScanDocuments& PSS_ScanDocuments::operator = (const PSS_ScanDocuments& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_ScanDocuments::SelectDocuments()
{
    return ProcessSelection();
}
//---------------------------------------------------------------------------
PSS_ScanDocuments::IDocument* PSS_ScanDocuments::GetDocumentAt(std::size_t index)
{
    if (index < std::size_t(m_Doc.GetSize()))
        return (IDocument*)m_Doc.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ScanDocuments::AddDocument(const CString& fileName, const CString& name, const CString& description)
{
    std::unique_ptr<IDocument> pDoc(new IDocument(fileName, name, description));
    
    if (pDoc.get())
    {
        m_Doc.Add((CObject*)pDoc.get());
        pDoc.release();
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ScanDocuments::ProcessSelection()
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
