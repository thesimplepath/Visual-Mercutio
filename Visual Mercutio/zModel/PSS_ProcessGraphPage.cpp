/****************************************************************************
 * ==> PSS_ProcessGraphPage ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a process graph page                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessGraphPage.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_ProcessGraphPage, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ProcessGraphPage
//---------------------------------------------------------------------------
PSS_ProcessGraphPage::PSS_ProcessGraphPage(const CString& pageName, PSS_ProcessGraphModelMdl* pModel) :
    CObject(),
    m_pModel(pModel),
    m_PageName(pageName)
{}
//---------------------------------------------------------------------------
PSS_ProcessGraphPage::~PSS_ProcessGraphPage()
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphPage::Serialize(CArchive& ar)
{
    CObject::Serialize(ar);

    if (ar.IsStoring())
    {
        m_ModelName.Empty();

        if (m_pModel)
            m_ModelName = m_pModel->GetAbsolutePath();

        ar << m_PageName;
        ar << m_ModelName;
    }
    else
    {
        ar >> m_PageName;
        ar >> m_ModelName;
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessGraphPage::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessGraphPage::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
