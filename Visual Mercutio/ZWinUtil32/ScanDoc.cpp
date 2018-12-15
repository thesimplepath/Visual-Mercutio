//    Advanced Dedicated Software
//    Dominique AIGROZ
//  Source file: ScanDoc.cpp

#include <StdAfx.h>

// ScanDoc
#include "ScanDoc.h"

#include "ScanWelcome.h"
#include "ScanInfo.h"
#include "ScanContinue.h"
#include "zWeb\ZVFilePreviewDlg.h"

#include "zBaseLib\file.h"
#include "zBaseLib\ZDirectory.h"

#include "zBaseLib\MsgBox.h"



ZIScanDocuments::Document::Document( const CString Filename /*= ""*/, const CString Name /*= ""*/, const CString Description /*= ""*/ )
: m_Filename(Filename), m_Name(Name), m_Description(Description)
{
}
ZIScanDocuments::Document::~Document()
{
}




ZIScanDocuments::ZIScanDocuments()
{
}



ZIScanDocuments::~ZIScanDocuments()
{
    for (size_t Index = 0; Index < GetDocumentCount(); ++Index)
    {
        if (GetDocumentAt( Index ))
            delete GetDocumentAt( Index );
    }
    m_Doc.RemoveAll();
}



BOOL ZIScanDocuments::ChooseDocuments ()
{
      return ProcessChoose();
}


BOOL ZIScanDocuments::ProcessChoose ()
{

    ZIScanWelcome    ScanWelcome;     

    if (ScanWelcome.DoModal() == IDCANCEL)
        return FALSE;
    

    bool    FirstTime = true;
    while (true)
    {
        ZIScanContinueSelect    ScanContinueSelect( FirstTime );     
        
        UINT    RetValue;
        if ( (RetValue=ScanContinueSelect.DoModal()) == IDCANCEL)
            return FALSE;

        if (RetValue == IDOK)
            break;

        // Show the file in preview
        ZVFilePreviewDlg    FilePreviewDlg( (LPCTSTR)ScanContinueSelect.GetFilename(), FALSE );
        FilePreviewDlg.DoModal();
        // Asks if the user wants to include the selected file
        MsgBox        mbox;
        if (mbox.DisplayMsgBox( IDS_CONFIRM_INSERT_SCANDOC, MB_YESNO ) == IDYES)
        {
            ZIScanInformation    ScanInformation( ScanContinueSelect.GetFilename() );
            if (ScanInformation.DoModal() == IDCANCEL)
                return FALSE;
            // And now add the document in the table
            AddDocument( ScanContinueSelect.GetFilename(), ScanInformation.GetName(), ScanInformation.GetDescription() );
            ZFile    FileSelected(ScanContinueSelect.GetFilename());
            // Now change de directory, 
            // and this to avoid the user selecting the same directory
            ZDirectory::ChangeCurrentDirectory( FileSelected.GetFilePath() );
            // Reset the flag for first time
            FirstTime = false;
        }
    }
    return TRUE;
}


void ZIScanDocuments::AddDocument( const CString Filename, const CString Name, const CString Description /*= ""*/ )
{
    Document*    pDoc = new Document( Filename, Name, Description );
    if (pDoc)
        m_Doc.Add( (CObject*)pDoc );
}


ZIScanDocuments::Document*    ZIScanDocuments::GetDocumentAt( size_t Index )
{
    if (Index < (size_t)m_Doc.GetSize())
        return (ZIScanDocuments::Document*)m_Doc.GetAt( Index );
    return NULL;
}
