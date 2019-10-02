/****************************************************************************
 * ==> PSS_WorkspaceFileEntity ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace file entity                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceFileEntity.h"

// processsoft
#include "PSS_WorkspaceGroupEntity.h"
#include "PSS_WorkspaceFilePropertiesDlg.h"
#include "ZUFileLauncher.h"
#include "PSS_FileDialog.h"
#include "PSS_MsgBox.h"

// resources
#include "zBaseLibRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_WorkspaceFileEntity, PSS_WorkspaceEntity, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_WorkspaceFileEntity
//---------------------------------------------------------------------------
PSS_WorkspaceFileEntity::PSS_WorkspaceFileEntity(const CString& name, PSS_WorkspaceEntity* pParent) :
    PSS_WorkspaceEntity(name, pParent)
{
    m_File.SetCompleteFileName(name);
    SetEntityName(m_File.GetFileTitle() + m_File.GetFileExt());
}
//---------------------------------------------------------------------------
PSS_WorkspaceFileEntity::~PSS_WorkspaceFileEntity()
{}
//---------------------------------------------------------------------------
bool PSS_WorkspaceFileEntity::HasFileName() const
{
    return !const_cast<PSS_File&>(m_File).GetCompleteFileName().IsEmpty();
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceFileEntity::GetFileName() const
{
    return const_cast<PSS_File&>(m_File).GetCompleteFileName();
}
//---------------------------------------------------------------------------
void PSS_WorkspaceFileEntity::SetFileName(const CString& value)
{
    m_File.SetCompleteFileName(value);
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceFileEntity::GetFileTitle() const
{
    return const_cast<PSS_File&>(m_File).GetFileName();
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceFileEntity::GetFilePath() const
{
    return const_cast<PSS_File&>(m_File).GetFilePath();
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceFileEntity::GetFileExt() const
{
    return const_cast<PSS_File&>(m_File).GetFileExt();
}
//---------------------------------------------------------------------------
HICON PSS_WorkspaceFileEntity::GetFileNameIcon() const
{
    const int iconIndex = const_cast<PSS_File&>(m_File).GetIconIndex();

    if (iconIndex < 0)
        return NULL;

    return ::ExtractIcon(::AfxGetInstanceHandle(), GetFileName(), iconIndex);
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceFileEntity::OpenFile()
{
    if (!m_File.Exist())
    {
        PSS_MsgBox mBox;

        if (mBox.Show(IDS_WKS_FILENAME_DEXIST, MB_YESNO) == IDYES)
        {
            CString title;
            VERIFY(title.LoadString(IDS_WORKSPACE_FILESELECT_T));

            // set the "*.*" files filter
            CString filters;
            VERIFY(filters.LoadString(AFX_IDS_ALLFILTER));

            filters += char('\0');
            filters +=   _T("*.*");
            filters += char('\0');

            PSS_FileDialog fileDialog(title, filters, 1);

            if (fileDialog.DoModal() == IDOK)
                // assigns the new file name
                m_File.SetCompleteFileName(fileDialog.GetFileName());
            else
                return false;
        }
        else
            return false;
    }

    // launch the file
    ZUFileLauncher fl;

    return fl.Launch(m_File.GetCompleteFileName());
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceFileEntity::PropertiesVisible()
{
    PSS_WorkspaceFilePropertiesDlg dlg(dynamic_cast<PSS_WorkspaceGroupEntity*>(GetParent()), GetEntityName(), GetFileName());

    if (dlg.DoModal() == IDOK)
    {
        SetEntityName(dlg.GetFileTitle());
        SetFileName(dlg.GetFileName());
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceFileEntity::AssertValid() const
    {
        PSS_WorkspaceEntity::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceFileEntity::Dump(CDumpContext& dc) const
    {
        PSS_WorkspaceEntity::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_WorkspaceFileEntity::Serialize(CArchive& ar)
{
    PSS_WorkspaceEntity::Serialize(ar);

    if (ar.IsStoring())
        // write the elements
        ar << m_File;
    else
        // read the elements
        ar >> m_File;
}
//---------------------------------------------------------------------------
