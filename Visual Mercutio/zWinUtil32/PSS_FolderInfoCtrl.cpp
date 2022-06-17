/****************************************************************************
 * ==> PSS_FolderInfoCtrl --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a folder info control                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_FolderInfoCtrl.h"

// processsoft
#include "zBaseLib\PSS_InputValue.h"

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

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
static int g_ColText[] =
{
    IDS_COLUMN1_FOLDERINFO,
    IDS_COLUMN2_FOLDERINFO
};

static int g_ColSize[] =
{
    80,
    165
};
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FolderInfoCtrl, PSS_ListCtrl)
    //{{AFX_MSG_MAP(PSS_FolderInfoCtrl)
    ON_NOTIFY_REFLECT_EX(NM_DBLCLK, OnDoubleClick)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FolderInfoCtrl
//---------------------------------------------------------------------------
PSS_FolderInfoCtrl::PSS_FolderInfoCtrl(PSS_FolderStamp* pFolderStamp, BOOL canModify) :
    PSS_ListCtrl(),
    m_pFolderStamp(pFolderStamp),
    m_IsColumnBuilt(FALSE),
    m_CanModify(canModify)
{}
//---------------------------------------------------------------------------
PSS_FolderInfoCtrl::PSS_FolderInfoCtrl(const PSS_FolderInfoCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_FolderInfoCtrl::~PSS_FolderInfoCtrl()
{}
//---------------------------------------------------------------------------
const PSS_FolderInfoCtrl& PSS_FolderInfoCtrl::operator = (const PSS_FolderInfoCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_FolderInfoCtrl::Initialize(PSS_FolderStamp* pFolderStamp, BOOL removeAll, BOOL canModify)
{
    if (removeAll)
        DeleteAllItems();

    m_pFolderStamp = pFolderStamp;
    m_CanModify    = canModify;
    EnableSort(TRUE);
    Refresh();
}
//---------------------------------------------------------------------------
void PSS_FolderInfoCtrl::Refresh()
{
    if (!m_IsColumnBuilt)
    {
        BuildColumns(2, g_ColSize, g_ColText);
        m_IsColumnBuilt = TRUE;

        m_FolderNameTitle.LoadString(IDS_FOLDERNAME_TITLE);
        m_FolderDescriptionTitle.LoadString(IDS_FOLDERNAME_DESCRIPTION);
        m_CreationUserTitle.LoadString(IDS_FOLDERNAME_CREATIONUSER);
        m_CreationDateTitle.LoadString(IDS_FOLDERNAME_CREATIONDATE);
        m_PublishVersionTitle.LoadString(IDS_FOLDERNAME_PUBLISHVERSION);
        m_TypeTitle.LoadString(IDS_FOLDERNAME_TYPE);
        m_TemplateNameTitle.LoadString(IDS_FOLDERNAME_TEMPLATENAME);
        m_TemplateFileNameTitle.LoadString(IDS_TEMPLATENAME_FILENAME);
    }

    DeleteAllItems();

    CString title;
    char    buffer[20];
    int     index = 0;

    // add the folder name
    InsertItem(index, m_FolderNameTitle);
    SetItem(index, 1, LVIF_TEXT, m_pFolderStamp->GetFolderName(), 0, LVIF_TEXT, LVIF_TEXT, 0);
    ++index;

    // add the folder description
    InsertItem(index, m_FolderDescriptionTitle);
    SetItem(index, 1, LVIF_TEXT, m_pFolderStamp->GetFolderDescription(), 0, LVIF_TEXT, LVIF_TEXT, 0);
    ++index;

    // add the creation user name
    InsertItem(index, m_CreationUserTitle);
    SetItem(index, 1, LVIF_TEXT, m_pFolderStamp->GetCreationUserName(), 0, LVIF_TEXT, LVIF_TEXT, 0);
    ++index;

    // add the creation date
    InsertItem(index, m_CreationDateTitle);
    SetItem(index, 1, LVIF_TEXT, m_pFolderStamp->GetCreationDate().Format( "%A, %B %d, %Y" ), 0, LVIF_TEXT, LVIF_TEXT, 0);
    ++index;

    // add the publish version
    InsertItem(index, m_PublishVersionTitle);
    ::sprintf_s(buffer, 20, "%ld", m_pFolderStamp->GetPublishVersion());
    SetItem(index, 1, LVIF_TEXT, buffer, 0, LVIF_TEXT, LVIF_TEXT, 0);
    ++index;

    // add the document type
    InsertItem(index, m_TypeTitle);
    if (m_pFolderStamp->GetFileType() == PSS_Stamp::IEFileTypeDefinition::IE_FD_DocumentType)
        title.LoadString(IDS_DOCUMENT);
    else
        title.LoadString(IDS_TEMPLATE);
    SetItem(index, 1, LVIF_TEXT, title, 0, LVIF_TEXT, LVIF_TEXT, 0);
    ++index;

    // add the template name
    InsertItem(index, m_TemplateNameTitle);
    SetItem(index, 1, LVIF_TEXT, m_pFolderStamp->GetTitle(), 0, LVIF_TEXT, LVIF_TEXT, 0);
    ++index;

    // add the template file name
    InsertItem(index, m_TemplateFileNameTitle);
    SetItem(index, 1, LVIF_TEXT, m_pFolderStamp->GetTemplate(), 0, LVIF_TEXT, LVIF_TEXT, 0);
}
//---------------------------------------------------------------------------
BOOL PSS_FolderInfoCtrl::OnDoubleClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    POSITION pPos = GetFirstSelectedItemPosition();

    if (!pPos)
        return TRUE;

    // get the selected item
    const int item  = GetNextSelectedItem(pPos);
    CString   label = GetItemText(item, 0);
    CString   value;

    if (label == m_FolderNameTitle)
        value = m_pFolderStamp->GetFolderName();
    else
    if (label == m_FolderDescriptionTitle)
        value = m_pFolderStamp->GetFolderDescription();
    else
    if (label == m_CreationUserTitle)
        value = m_pFolderStamp->GetCreationUserName();
    else
    if (label == m_CreationDateTitle)
        return TRUE;
    else
    if (label == m_PublishVersionTitle)
        return TRUE;
    else
    if (label == m_TypeTitle)
        return TRUE;
    else
    if (label == m_TemplateNameTitle)
        value = m_pFolderStamp->GetTitle();
    else
    if (label == m_TemplateFileNameTitle)
        return TRUE;
    else
        return TRUE;

    CString title;

    // ask to edit the value
    PSS_InputValue inputValue(title, value);

    if (inputValue.DoModal() == IDOK)
    {
        // change back the value
        if (label == m_FolderNameTitle)
            m_pFolderStamp->SetFolderName(inputValue.GetValue());
        else
        if (label == m_FolderDescriptionTitle)
            m_pFolderStamp->SetFolderDescription(inputValue.GetValue());
        else
        if (label == m_CreationUserTitle)
            m_pFolderStamp->SetCreationUserName(inputValue.GetValue());
        else
        if (label == m_CreationDateTitle)
            return TRUE;
        else
        if (label == m_PublishVersionTitle)
            return TRUE;
        else
        if (label == m_TypeTitle)
            return TRUE;
        else
        if (label == m_TemplateNameTitle)
            m_pFolderStamp->SetTitle(inputValue.GetValue());
        else
        if (label == m_TemplateFileNameTitle)
            return TRUE;
        else
            return TRUE;

        // refresh the control
        Refresh();
    }

    *pResult = 0;

    // keep routing
    return TRUE;
}
//---------------------------------------------------------------------------
