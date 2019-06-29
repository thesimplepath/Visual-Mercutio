// DocTmplEx.cpp : implementation file

#include "stdafx.h"
#include "DocTmplEx.h"

// mfc
#include <afxadv.h>

// processsoft
#include "zMediator\PSS_Application.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(ZDDocTemplateEx, CMultiDocTemplate)

/////////////////////////////////////////////////////////////////////////////
// ZDDocTemplateEx

ZDDocTemplateEx::ZDDocTemplateEx( UINT                nIDResource,
                                  CRuntimeClass*    pDocClass,
                                  CRuntimeClass*    pFrameClass,
                                  CRuntimeClass*    pViewClass,
                                  UINT                nMenuId,
                                  UINT                nMaxMRU )
    : CMultiDocTemplate( nIDResource, pDocClass, pFrameClass, pViewClass )
{
    m_pRecentFileList    = NULL;
    m_nMenuId            = nMenuId;

    if ( m_nMenuId )
    {
        LoadStdProfileSettings( nMaxMRU );
    }
}

ZDDocTemplateEx::~ZDDocTemplateEx()
{
    CWinApp* pApp = AfxGetApp();

    if ( pApp->m_pCmdInfo == NULL ||
         pApp->m_pCmdInfo->m_nShellCommand != CCommandLineInfo::AppUnregister )
    {
        if ( !afxContextIsDLL )
        {
            SaveStdProfileSettings();
        }
    }

    // Free recent file list
    if ( m_pRecentFileList != NULL )
    {
        delete m_pRecentFileList;
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZDDocTemplateEx implementation

void ZDDocTemplateEx::AddToRecentFileList(LPCTSTR pPathName)
{
    ASSERT_VALID(this);
    ASSERT(pPathName);
    ASSERT(AfxIsValidString(pPathName));

    if (m_pRecentFileList)
        m_pRecentFileList->Add(pPathName);
}
//---------------------------------------------------------------------------
void ZDDocTemplateEx::LoadStdProfileSettings(UINT maxMRU)
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
void ZDDocTemplateEx::SaveStdProfileSettings()
{
    ASSERT_VALID(this);

    if (m_pRecentFileList)
        m_pRecentFileList->WriteList();
}
//---------------------------------------------------------------------------
void ZDDocTemplateEx::OnUpdateRecentFileMenu(CCmdUI* pCmdUI)
{
    ASSERT_VALID(this);

    // updating a submenu?
    if (pCmdUI->m_pSubMenu)
    {
        UINT nEnable = MF_ENABLED;

        // inactivate the submenu when the file list is empty
        if ((!m_pRecentFileList) || (!m_pRecentFileList->GetSize() == 0 ) || (*m_pRecentFileList)[0].IsEmpty())
            nEnable = ( MF_DISABLED | MF_GRAYED );
        
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
BOOL ZDDocTemplateEx::OnOpenRecentFile(UINT id)
{
    ASSERT_VALID(this);
    ASSERT(m_pRecentFileList);

    ASSERT(id >= m_nMenuId);
    ASSERT(id <  m_nMenuId + UINT(m_pRecentFileList->GetSize()));

    const int index = id - m_nMenuId;

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
// This hack is necessary because the menu ID is a member of the class.
// MFC message maps need the IDs to be global.
BOOL ZDDocTemplateEx::OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo )
{
    // Determine the message number and code (packed into nCode)
    UINT    nMsg = 0;
    int        nCod = nCode;

    if ( nCod != CN_UPDATE_COMMAND_UI )
    {
        nMsg = HIWORD( nCod );
        nCod = LOWORD( nCod );
    }

    // For backward compatibility HIWORD(nCode) == 0 is WM_COMMAND
    if ( nMsg == 0 )
    {
        nMsg = WM_COMMAND;
    }

    if ( ( nCod == CN_UPDATE_COMMAND_UI ) && ( nID >= m_nMenuId ) && ( nID <= m_nMenuId + MRU_RANGE ) )
    {
        // Default is ok
        BOOL bResult = TRUE;

        ASSERT( pExtra != NULL );

        CCmdUI* pCmdUI = (CCmdUI*)pExtra;

        // Idle - not set
        ASSERT( !pCmdUI->m_bContinueRouting );

        OnUpdateRecentFileMenu( pCmdUI );

        bResult = !pCmdUI->m_bContinueRouting;

        // Go back to idle
        pCmdUI->m_bContinueRouting = FALSE;

        return bResult;
    }

    if ( ( nMsg == WM_COMMAND ) && ( nCod == CN_COMMAND ) && ( nID >= m_nMenuId ) && ( nID <= m_nMenuId+MRU_RANGE ) )
    {
#ifdef _DEBUG
            if ( afxTraceFlags & traceCmdRouting )
            {
                TRACE2( _T( "SENDING command id 0x%04X to %hs target.\n" ),
                        nID,
                        GetRuntimeClass()->m_lpszClassName );
            }
#endif //_DEBUG

        return OnOpenRecentFile( nID );
    }

    return CMultiDocTemplate::OnCmdMsg( nID, nCode, pExtra, pHandlerInfo );
}

/////////////////////////////////////////////////////////////////////////////
// ZDDocTemplateEx diagnostics

#ifdef _DEBUG
void ZDDocTemplateEx::Dump( CDumpContext& dc ) const
{
    CMultiDocTemplate::Dump( dc );

    if ( m_pRecentFileList != NULL )
    {
        dc << _T( "\nm_strRecentFiles[] = " );

        int nSize = m_pRecentFileList->GetSize();

        for ( int i = 0; i < nSize; i++ )
        {
            if ( (*m_pRecentFileList)[i].GetLength() != 0 )
            {
                dc << _T( "\n\tFile: " ) << (*m_pRecentFileList)[i];
            }
        }
    }

    dc << _T( "\n" );
}

void ZDDocTemplateEx::AssertValid() const
{
    CMultiDocTemplate::AssertValid();
}
#endif //_DEBUG
