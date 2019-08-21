/****************************************************************************
 * ==> PSS_GlobalFieldDocument ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a global field document                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_GlobalFieldDocument.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_GlobalFieldDocument, PSS_BaseDocument, g_DefVersion)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_GlobalFieldDocument, PSS_BaseDocument)
    //{{AFX_MSG_MAP(PSS_GlobalFieldDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_GlobalFieldDocument
//---------------------------------------------------------------------------
PSS_GlobalFieldDocument::PSS_GlobalFieldDocument() :
    PSS_BaseDocument(),
    m_pHistoryValueManager(NULL),
    m_pGlobalFieldManager(NULL)
{}
//---------------------------------------------------------------------------
PSS_GlobalFieldDocument::PSS_GlobalFieldDocument(const PSS_GlobalFieldDocument& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_GlobalFieldDocument::~PSS_GlobalFieldDocument()
{}
//---------------------------------------------------------------------------
const PSS_GlobalFieldDocument& PSS_GlobalFieldDocument::operator = (const PSS_GlobalFieldDocument& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_GlobalFieldDocument::Initialize(const CString&          fileName,
                                         PSS_GlobalFieldManager* pGlobalFieldManager,
                                         ZAHistoryFieldManager*  pHistoryValueManager)
{
    SetPathName(fileName, FALSE);

    // assign the manager pointers
    m_pHistoryValueManager = pHistoryValueManager;
    m_pGlobalFieldManager  = pGlobalFieldManager;
}
//---------------------------------------------------------------------------
void PSS_GlobalFieldDocument::Initialize(PSS_GlobalFieldManager* pGlobalFieldManager,
                                         ZAHistoryFieldManager*  pHistoryValueManager)
{
    // assign the manager pointers
    m_pHistoryValueManager = pHistoryValueManager;
    m_pGlobalFieldManager  = pGlobalFieldManager;
}
//---------------------------------------------------------------------------
BOOL PSS_GlobalFieldDocument::ReadDocument(const CString&          fileName,
                                           PSS_GlobalFieldManager* pGlobalFieldManager,
                                           ZAHistoryFieldManager*  pHistoryValueManager)
{
    if (!pGlobalFieldManager || !pHistoryValueManager)
        return FALSE;

    // assign the manager pointers
    Initialize(pGlobalFieldManager, pHistoryValueManager);

    return ReadDocument(fileName);
}
//---------------------------------------------------------------------------
BOOL PSS_GlobalFieldDocument::ReadDocument(const CString& fileName)
{
    for (int i = 0; i < 5; ++i)
        if (PSS_BaseDocument::ReadDocument(fileName))
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_GlobalFieldDocument::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
        WriteFileStamp(ar, GetDocumentStamp());
    else
        ReadFileStamp(ar, GetDocumentStamp());

    if (m_pGlobalFieldManager && m_pHistoryValueManager)
    {
        m_pGlobalFieldManager->Serialize(ar);
        m_pHistoryValueManager->Serialize(ar);
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GlobalFieldDocument::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GlobalFieldDocument::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
