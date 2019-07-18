#include <StdAfx.h>
#include "FldInfoC.h"

// processsoft
#include "zBaseLib\InpVal.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZCFolderInformation, ZIListCtrl)
    //{{AFX_MSG_MAP(ZCFolderInformation)
    ON_NOTIFY_REFLECT_EX(NM_DBLCLK, OnDoubleClick)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

static int _gColText[] = { IDS_COLUMN1_FOLDERINFO, IDS_COLUMN2_FOLDERINFO };
static int _gColSize[] = { 80, 165 };

//## end module%373A82F10021.additionalDeclarations


// Class ZCFolderInformation 












ZCFolderInformation::ZCFolderInformation (ZDFolderStamp* pFolderStamp, BOOL CanModify)
  //## begin ZCFolderInformation::ZCFolderInformation%926579193.hasinit preserve=no
      : m_IsColumnBuilt(FALSE)
  //## end ZCFolderInformation::ZCFolderInformation%926579193.hasinit
  //## begin ZCFolderInformation::ZCFolderInformation%926579193.initialization preserve=yes
      , m_pFolderStamp(pFolderStamp), m_CanModify(CanModify)
  //## end ZCFolderInformation::ZCFolderInformation%926579193.initialization
{
  //## begin ZCFolderInformation::ZCFolderInformation%926579193.body preserve=yes
  //## end ZCFolderInformation::ZCFolderInformation%926579193.body
}


ZCFolderInformation::~ZCFolderInformation()
{
  //## begin ZCFolderInformation::~ZCFolderInformation%.body preserve=yes
  //## end ZCFolderInformation::~ZCFolderInformation%.body
}



//## Other Operations (implementation)
void ZCFolderInformation::Initialize (ZDFolderStamp* pFolderStamp, BOOL RemoveAll, BOOL CanModify)
{
  //## begin ZCFolderInformation::Initialize%926579194.body preserve=yes
    if (RemoveAll)
        DeleteAllItems();
    m_pFolderStamp = pFolderStamp;
    m_CanModify = CanModify;
    EnableSort( TRUE );
    ZCFolderInformation::Refresh();
  //## end ZCFolderInformation::Initialize%926579194.body
}

void ZCFolderInformation::Refresh ()
{
  //## begin ZCFolderInformation::Refresh%926579197.body preserve=yes
    if (!m_IsColumnBuilt)
    {
        BuildColumns(2, _gColSize, _gColText);
        m_IsColumnBuilt = TRUE;

        m_FolderNameTitle.LoadString( IDS_FOLDERNAME_TITLE );
        m_FolderDescriptionTitle.LoadString( IDS_FOLDERNAME_DESCRIPTION );
        m_CreationUserTitle.LoadString( IDS_FOLDERNAME_CREATIONUSER );
        m_CreationDateTitle.LoadString( IDS_FOLDERNAME_CREATIONDATE );
        m_PublishVersionTitle.LoadString( IDS_FOLDERNAME_PUBLISHVERSION );
        m_TypeTitle.LoadString( IDS_FOLDERNAME_TYPE );
        m_TemplateNameTitle.LoadString( IDS_FOLDERNAME_TEMPLATENAME );
        m_TemplateFilenameTitle.LoadString( IDS_TEMPLATENAME_FILENAME );

    }
    DeleteAllItems();
    CString    Title;
    char    buffer[20];
    int        Index = 0;
    // Add the Folder Name
    InsertItem( Index, m_FolderNameTitle );
    SetItem( Index++, 1, LVIF_TEXT,
             m_pFolderStamp->GetFolderName(),
             0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the Folder Description
    InsertItem( Index, m_FolderDescriptionTitle );
    SetItem( Index++, 1, LVIF_TEXT,
             m_pFolderStamp->GetFolderDescription(),
             0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the Creation Username
    InsertItem( Index, m_CreationUserTitle );
    SetItem( Index++, 1, LVIF_TEXT,
             m_pFolderStamp->GetCreationUserName(),
             0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the Creation Date
    InsertItem( Index, m_CreationDateTitle );
    SetItem( Index++, 1, LVIF_TEXT,
             m_pFolderStamp->GetCreationDate().Format( "%A, %B %d, %Y" ),
             0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the Publish Version
    InsertItem( Index, m_PublishVersionTitle );
    sprintf( buffer, "%ld", m_pFolderStamp->GetPublishVersion() );
    SetItem( Index++, 1, LVIF_TEXT,
             buffer,
             0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the document type
    InsertItem( Index, m_TypeTitle );
    if (m_pFolderStamp->GetFileType() == DocumentType)
        Title.LoadString( IDS_DOCUMENT );
    else
        Title.LoadString( IDS_TEMPLATE );
    SetItem( Index++, 1, LVIF_TEXT,
             Title,
             0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the template name
    InsertItem( Index, m_TemplateNameTitle );
    SetItem( Index++, 1, LVIF_TEXT,
             m_pFolderStamp->GetTitle(),
             0, LVIF_TEXT, LVIF_TEXT, 0 );
    // Add the template filename
    InsertItem( Index, m_TemplateFilenameTitle );
    SetItem( Index++, 1, LVIF_TEXT,
             m_pFolderStamp->GetTemplate(),
             0, LVIF_TEXT, LVIF_TEXT, 0 );
  //## end ZCFolderInformation::Refresh%926579197.body
}

// Additional Declarations
  //## begin ZCFolderInformation%373A81F402E4.declarations preserve=yes
  //## end ZCFolderInformation%373A81F402E4.declarations

//## begin module%373A82F10021.epilog preserve=yes
BOOL ZCFolderInformation::OnDoubleClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // Retreive the selected item
    POSITION pos = GetFirstSelectedItemPosition();
    if (pos == NULL)
        return TRUE;
    int Item = GetNextSelectedItem(pos);
    CString    Label = GetItemText( Item, 0 );

    CString    Value;
    if (Label == m_FolderNameTitle)
        Value = m_pFolderStamp->GetFolderName();
    else
    if (Label == m_FolderDescriptionTitle)
        Value = m_pFolderStamp->GetFolderDescription();
    else
    if (Label == m_CreationUserTitle)
        Value = m_pFolderStamp->GetCreationUserName();
    else
    if (Label == m_CreationDateTitle)
        return TRUE;
    else
    if (Label == m_PublishVersionTitle)
        return TRUE;
    else
    if (Label == m_TypeTitle)
        return TRUE;
    else
    if (Label == m_TemplateNameTitle)
        Value = m_pFolderStamp->GetTitle();
    else
    if (Label == m_TemplateFilenameTitle)
        return TRUE;
    else
        return TRUE;
    // Asks to Edit the value
    CString    Title;
    ZIInputValue    InputValue( Title, Value );

    if (InputValue.DoModal() == IDOK)
    {
        // Change back the value
        if (Label == m_FolderNameTitle)
            m_pFolderStamp->SetFolderName( InputValue.GetValue() );
        else
        if (Label == m_FolderDescriptionTitle)
            m_pFolderStamp->SetFolderDescription( InputValue.GetValue() );
        else
        if (Label == m_CreationUserTitle)
            m_pFolderStamp->SetCreationUserName( InputValue.GetValue() );
        else
        if (Label == m_CreationDateTitle)
            return TRUE;
        else
        if (Label == m_PublishVersionTitle)
            return TRUE;
        else
        if (Label == m_TypeTitle)
            return TRUE;
        else
        if (Label == m_TemplateNameTitle)
            m_pFolderStamp->SetTitle( InputValue.GetValue() );
        else
        if (Label == m_TemplateFilenameTitle)
            return TRUE;
        else
            return TRUE;
        // And finally, refresh the control
        Refresh();
    }
    *pResult = 0;

    return TRUE;    // Keep routing
}
//## end module%373A82F10021.epilog
