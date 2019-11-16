/****************************************************************************
 * ==> PSS_DocTemplateEx ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an extended document template                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DocTemplateEx.h"

 // mfc
#include <afxadv.h>

// processsoft
#include "zMediator\PSS_Application.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_DocTemplateEx, CMultiDocTemplate)
//---------------------------------------------------------------------------
// PSS_DocTemplateEx
//---------------------------------------------------------------------------
PSS_DocTemplateEx::PSS_DocTemplateEx(UINT           resourceID,
                                     CRuntimeClass* pDocClass,
                                     CRuntimeClass* pFrameClass,
                                     CRuntimeClass* pViewClass,
                                     UINT           menuID,
                                     UINT           maxMRU) :
    CMultiDocTemplate(resourceID, pDocClass, pFrameClass, pViewClass),
    m_pRecentFileList(NULL),
    m_MenuID(menuID)
{
    if (m_MenuID)
        LoadStdProfileSettings(maxMRU);
}
//---------------------------------------------------------------------------
PSS_DocTemplateEx::~PSS_DocTemplateEx()
{
    CWinApp* pApp = AfxGetApp();

    if (!pApp->m_pCmdInfo || pApp->m_pCmdInfo->m_nShellCommand != CCommandLineInfo::AppUnregister)
        if (!afxContextIsDLL)
            SaveStdProfileSettings();

    // free recent file list
    if (m_pRecentFileList)
        delete m_pRecentFileList;
}
//---------------------------------------------------------------------------
void PSS_DocTemplateEx::AddToRecentFileList(LPCTSTR pPathName)
{
    ASSERT_VALID(this);
    ASSERT(pPathName);
    ASSERT(AfxIsValidString(pPathName));

    if (m_pRecentFileList)
        m_pRecentFileList->Add(pPathName);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_DocTemplateEx::AssertValid() const
    {
        CMultiDocTemplate::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_DocTemplateEx::Dump(CDumpContext& dc) const
    {
        CMultiDocTemplate::Dump(dc);

        if (m_pRecentFileList)
        {
            dc << _T("\nm_strRecentFiles[] = ");

            int size = m_pRecentFileList->GetSize();

            for (int i = 0; i < size; ++i)
                if ((*m_pRecentFileList)[i].GetLength())
                    dc << _T("\n\tFile: ") << (*m_pRecentFileList)[i];
        }

        dc << _T("\n");
    }
#endif
//---------------------------------------------------------------------------
void PSS_DocTemplateEx::LoadStdProfileSettings(UINT maxMRU)
{
    ASSERT_VALID(this);
    ASSERT(!m_pRecentFileList);

    CString fileEntry = _T("File%d");
    CString fileSection;

    GetDocString(fileSection, CDocTemplate::docName);

    // create file MRU since nMaxMRU not zero
    if (maxMRU)
    {
        m_pRecentFileList = new CRecentFileList(0, fileSection, fileEntry, maxMRU);
        m_pRecentFileList->ReadList();
    }
}
//---------------------------------------------------------------------------
void PSS_DocTemplateEx::SaveStdProfileSettings()
{
    ASSERT_VALID(this);

    if (m_pRecentFileList)
        m_pRecentFileList->WriteList();
}
//---------------------------------------------------------------------------
void PSS_DocTemplateEx::OnUpdateRecentFileMenu(CCmdUI* pCmdUI)
{
    ASSERT_VALID(this);

    // updating a submenu?
    if (pCmdUI->m_pSubMenu)
    {
        UINT nEnable = MF_ENABLED;

        // inactivate the submenu when the file list is empty
        if ((!m_pRecentFileList) || (!m_pRecentFileList->GetSize() == 0) || (*m_pRecentFileList)[0].IsEmpty())
            nEnable = (MF_DISABLED | MF_GRAYED);

        pCmdUI->m_pMenu->EnableMenuItem(pCmdUI->m_nIndex, MF_BYPOSITION | nEnable);
        return;
    }

    // no files to reopen?
    if (!m_pRecentFileList)
        pCmdUI->Enable(FALSE);
    else
        m_pRecentFileList->UpdateMenu(pCmdUI);
}
//---------------------------------------------------------------------------
BOOL PSS_DocTemplateEx::OnOpenRecentFile(UINT id)
{
    ASSERT_VALID(this);
    ASSERT(m_pRecentFileList);

    ASSERT(id >= m_MenuID);
    ASSERT(id <  m_MenuID + UINT(m_pRecentFileList->GetSize()));

    const int index = id - m_MenuID;

    ASSERT((*m_pRecentFileList)[index].GetLength());

    TRACE2(_T("MRU: open file (%d) '%s'.\n"), index + 1, LPCTSTR((*m_pRecentFileList)[index]));

    // get opened document and its related file name
    LPCTSTR    pFile = (*m_pRecentFileList)[index];
    CDocument* pDoc  = OpenDocumentFile(pFile);

    // update the reopen files list
    if (!pDoc)
        m_pRecentFileList->Remove(index);
    else
        PSS_Application::Instance()->GetMainForm()->OnAfterOpenDocument(pDoc, pFile);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocTemplateEx::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    // determine the message number and code (packed in nCode param)
    UINT msg  = 0;
    int  code = nCode;

    if (code != CN_UPDATE_COMMAND_UI)
    {
        msg  = HIWORD(code);
        code = LOWORD(code);
    }

    // for backward compatibility HIWORD(nCode) == 0 is WM_COMMAND
    if (!msg)
        msg = WM_COMMAND;

    if ((code == CN_UPDATE_COMMAND_UI) && (nID >= m_MenuID) && (nID <= m_MenuID + M_MRU_RANGE))
    {
        ASSERT(pExtra);

        CCmdUI* pCmdUI = (CCmdUI*)pExtra;

        // idle - not set
        ASSERT(!pCmdUI->m_bContinueRouting);

        OnUpdateRecentFileMenu(pCmdUI);

        const BOOL result = !pCmdUI->m_bContinueRouting;

        // go back to idle
        pCmdUI->m_bContinueRouting = FALSE;

        return result;
    }

    if ((msg == WM_COMMAND) && (code == CN_COMMAND) && (nID >= m_MenuID) && (nID <= m_MenuID + M_MRU_RANGE))
    {
        #ifdef _DEBUG
            if (afxTraceFlags & traceCmdRouting)
                TRACE2(_T("SENDING command id 0x%04X to %hs target.\n"),
                       nID,
                       GetRuntimeClass()->m_lpszClassName);
        #endif

        return OnOpenRecentFile(nID);
    }

    return CMultiDocTemplate::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
//---------------------------------------------------------------------------
