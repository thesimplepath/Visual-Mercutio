/****************************************************************************
 * ==> PSS_WorkspaceWizardTemplateManager ----------------------------------*
 ****************************************************************************
 * Description : Provides a workspace wizard template manager               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceWizardTemplateManager.h"

 // processsoft
#include "PSS_WorkspaceWizardTemplateItem.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_WorkspaceWizardTemplateManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_WorkspaceWizardTemplateManager
//---------------------------------------------------------------------------
PSS_WorkspaceWizardTemplateManager::PSS_WorkspaceWizardTemplateManager() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_WorkspaceWizardTemplateManager::~PSS_WorkspaceWizardTemplateManager()
{
    const INT_PTR count = m_Set.GetCount();

    for (INT_PTR i = 0; i < count; ++i)
        if (m_Set.GetAt(i))
            delete m_Set.GetAt(i);

    m_Set.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_WorkspaceWizardTemplateManager::Serialize(CArchive& ar)
{
    m_Set.Serialize(ar);

    if (ar.IsStoring())
    {
        // write the elements
    }
    else
    {
        // read the elements
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceWizardTemplateManager::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceWizardTemplateManager::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
