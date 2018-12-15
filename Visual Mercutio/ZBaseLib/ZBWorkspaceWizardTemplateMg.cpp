// ZBWorkspaceWizardTemplateMg.cpp: implementation of the ZBWorkspaceWizardTemplateMg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBWorkspaceWizardTemplateMg.h"
#include "ZBWorkspaceWizardTemplateItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL( ZBWorkspaceWizardTemplateMg, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBWorkspaceWizardTemplateMg::ZBWorkspaceWizardTemplateMg()
{
}

ZBWorkspaceWizardTemplateMg::~ZBWorkspaceWizardTemplateMg()
{
    // JMR-MODIF - Le 23 août 2005 - Désalloue les objets contenus dans m_Set.
    for ( INT_PTR i = 0; i < m_Set.GetCount(); i++ )
    {
        if ( m_Set.GetAt( i ) != NULL )
        {
            delete m_Set.GetAt( i );
        }
    }

    m_Set.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceWizardTemplateMg diagnostics

#ifdef _DEBUG
void ZBWorkspaceWizardTemplateMg::AssertValid() const
{
    CObject::AssertValid();
}

void ZBWorkspaceWizardTemplateMg::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceWizardTemplateMg serialization

void ZBWorkspaceWizardTemplateMg::Serialize ( CArchive& ar )
{
    m_Set.Serialize( ar );

    if ( ar.IsStoring() )
    {    // Write the elements
    }
    else
    {    // Read the elements
    }
}
