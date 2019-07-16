/****************************************************************************
 * ==> PSS_ModelStateMachineDocument ---------------------------------------*
 ****************************************************************************
 * Description : Provides a state machine document                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_ModelStateMachineDocument.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_ModelStateMachineDocument, CDocument)
//---------------------------------------------------------------------------
// MEssage map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ModelStateMachineDocument, CDocument)
    //{{AFX_MSG_MAP(ZDModelStateMachineDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ModelStateMachineDocument
//---------------------------------------------------------------------------
PSS_ModelStateMachineDocument::PSS_ModelStateMachineDocument(PSS_StateMachineCollection* pModelStateMachine) :
    CDocument(),
    m_pStateMachineCollection(pModelStateMachine),
    m_IsLoaded(false)
{}
//---------------------------------------------------------------------------
PSS_ModelStateMachineDocument::~PSS_ModelStateMachineDocument()
{}
//---------------------------------------------------------------------------
bool PSS_ModelStateMachineDocument::ReadFromFile(const CString& fileName, PSS_StateMachineCollection* pModelStateMachine)
{
    // check if necessary to assign a model state machine
    if (pModelStateMachine)
        m_pStateMachineCollection = pModelStateMachine;

    // check if a model state machine is valid
    if (!m_pStateMachineCollection)
        return false;

    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
    loadArchive.m_pDocument  = this;
    loadArchive.m_bForceFlat = FALSE;

    bool retValue = false;

    TRY
    {
        Serialize(loadArchive);
        retValue = true;
    }
    CATCH(CArchiveException, e)
    {
        retValue = false;
    }
    END_CATCH

    loadArchive.Close();
    file.Close();

    // if everything is ok, set the path name
    if (retValue)
        SetPathName(fileName, FALSE);

    m_IsLoaded = retValue;

    return retValue;
}
//---------------------------------------------------------------------------
bool PSS_ModelStateMachineDocument::SaveToFile(const CString& fileName, PSS_StateMachineCollection* pModelStateMachine)
{
    // check if necessary to assign a model state machine pointer
    if (pModelStateMachine)
        m_pStateMachineCollection = pModelStateMachine;

    // check if a model state machine pointer is valid
    if (!m_pStateMachineCollection)
        return false;

    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite, &fe))
        return FALSE;

    CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);
    saveArchive.m_pDocument  = this;
    saveArchive.m_bForceFlat = FALSE;

    bool retValue = false;

    TRY
    {
        Serialize(saveArchive);
        retValue = true;
    }
    CATCH(CArchiveException, e)
    {
        retValue = false;
    }
    END_CATCH

    saveArchive.Close();
    file.Close();

    // after a save, clear the modified flag
    SetModifiedFlag(FALSE);

    return retValue;
}
//---------------------------------------------------------------------------
void PSS_ModelStateMachineDocument::Serialize(CArchive& ar)
{
    ASSERT(m_pStateMachineCollection);

    // serialize the environement
    m_pStateMachineCollection->Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
void PSS_ModelStateMachineDocument::AssertValid() const
{
    CObject::AssertValid();
}
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
void PSS_ModelStateMachineDocument::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif
//---------------------------------------------------------------------------
BOOL PSS_ModelStateMachineDocument::OnNewDocument()
{
    ASSERT(FALSE);
    return FALSE;
}
//---------------------------------------------------------------------------
