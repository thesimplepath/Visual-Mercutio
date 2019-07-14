// ZDModelStateMachineDocument.cpp : implementation file
//

#include "stdafx.h"
#include "ZDModelStateMachineDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDModelStateMachineDocument

IMPLEMENT_DYNCREATE(ZDModelStateMachineDocument, CDocument)

ZDModelStateMachineDocument::ZDModelStateMachineDocument(PSS_StateMachineCollection* pModelStateMachine) :
    CDocument(),
    m_pStateMachineCollection(pModelStateMachine),
    m_IsLoaded(false)
{}

BOOL ZDModelStateMachineDocument::OnNewDocument()
{
    ASSERT(FALSE);
    return FALSE;
/*
    if (!CDocument::OnNewDocument())
        return FALSE;
    return TRUE;
*/
}

ZDModelStateMachineDocument::~ZDModelStateMachineDocument()
{}


bool ZDModelStateMachineDocument::ReadFromFile(const CString& fileName, PSS_StateMachineCollection* pModelStateMachine)
{
    // Check if necessary to assign a model state machine pointer
    if (pModelStateMachine)
        m_pStateMachineCollection = pModelStateMachine;
    // Check if a model state machine pointer is valid
    if (!m_pStateMachineCollection)
        return false;

    bool           retValue = false;
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
    loadArchive.m_pDocument = this;
    loadArchive.m_bForceFlat = FALSE;
    TRY
    {
        Serialize( loadArchive );
        retValue = TRUE;
    }
    CATCH( CArchiveException, e )
    {
        retValue = FALSE;
    }
    END_CATCH

    loadArchive.Close();
    file.Close();
    // If everything is ok, set the pathname.
    if (retValue)
        SetPathName(fileName, FALSE );
    // Set IsLoaded member
    m_IsLoaded = (retValue) ? true : false;
    return retValue;
}


bool ZDModelStateMachineDocument::SaveToFile(const CString& fileName, PSS_StateMachineCollection* pModelStateMachine)
{
    // Check if necessary to assign a model state machine pointer
    if (pModelStateMachine)
        m_pStateMachineCollection = pModelStateMachine;
    // Check if a model state machine pointer is valid
    if (!m_pStateMachineCollection)
        return false;

    bool            RetValue = false;
    CFile            file;
    CFileException    fe;
    if (!file.Open(fileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite, &fe))
        return FALSE;
    CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);
    saveArchive.m_pDocument = this;
    saveArchive.m_bForceFlat = FALSE;
    TRY
    {
        Serialize( saveArchive );
        RetValue = TRUE;
    }
    CATCH( CArchiveException, e )
    {
        RetValue = FALSE;
    }
    END_CATCH

    saveArchive.Close();
    file.Close();
    // After a save, clear the modified flag
    SetModifiedFlag(FALSE);
    return RetValue;
}



BEGIN_MESSAGE_MAP(ZDModelStateMachineDocument, CDocument)
    //{{AFX_MSG_MAP(ZDModelStateMachineDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZDModelStateMachineDocument diagnostics

#ifdef _DEBUG
void ZDModelStateMachineDocument::AssertValid() const
{
    CDocument::AssertValid();
}

void ZDModelStateMachineDocument::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDModelStateMachineDocument serialization

void ZDModelStateMachineDocument::Serialize(CArchive& ar)
{
    ASSERT( m_pStateMachineCollection );
    // Serialize the environement
    m_pStateMachineCollection->Serialize(ar);

    // If some other information to serialize do it below
/*
    if (ar.IsStoring())
    {
        // TODO: add storing code here
    }
    else
    {
        // TODO: add loading code here
    }
*/
}

/////////////////////////////////////////////////////////////////////////////
// ZDModelStateMachineDocument commands


