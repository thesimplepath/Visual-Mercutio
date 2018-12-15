// ZBWorkspaceWizardTemplateItem.cpp: implementation of the ZBWorkspaceWizardTemplateItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBWorkspaceWizardTemplateItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(ZBWorkspaceWizardTemplateItem, CObject, def_Version)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBWorkspaceWizardTemplateItem::ZBWorkspaceWizardTemplateItem(CString TemplateName /*= ""*/,
                                                             CString TemplateDescription /*= ""*/,
                                                             CString IconFile /*= ""*/,
                                                             int IconIndex /*= -1*/)
:     m_TemplateName(TemplateName),
    m_TemplateDescription(TemplateDescription),
    m_IconFile(IconFile),
    m_IconIndex(IconIndex),
    m_Icon(NULL)
{
    LoadIconFile();
}

ZBWorkspaceWizardTemplateItem::~ZBWorkspaceWizardTemplateItem()
{
    if (m_Icon)
        ::DestroyIcon( m_Icon );
    m_Icon = NULL;
}


void ZBWorkspaceWizardTemplateItem::LoadIconFile()
{
    // Load the icon if a file and an icon index is defined
    if (!m_IconFile.IsEmpty() && m_IconIndex != -1)
    {
        m_Icon = ::ExtractIcon( ::AfxGetInstanceHandle(), m_IconFile, m_IconIndex );
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceWizardTemplateItem serialization

void ZBWorkspaceWizardTemplateItem::Serialize (CArchive& ar)
{
    if (ar.IsStoring())
    {    // Write the elements
        ar << m_TemplateName;
        ar << m_TemplateDescription;
        ar << m_IconFile;
        ar << m_IconIndex;
    }
    else
    {    // Read the elements
        ar >> m_TemplateName;
        ar >> m_TemplateDescription;
        ar >> m_IconFile;
        ar >> m_IconIndex;
        // Load Icon after reading item
        LoadIconFile();
    }
}


/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceWizardTemplateItem diagnostics

#ifdef _DEBUG
void ZBWorkspaceWizardTemplateItem::AssertValid() const
{
    CObject::AssertValid();
}

void ZBWorkspaceWizardTemplateItem::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG
