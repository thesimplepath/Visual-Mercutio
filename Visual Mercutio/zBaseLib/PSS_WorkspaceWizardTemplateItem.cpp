/****************************************************************************
 * ==> PSS_WorkspaceWizardTemplateItem -------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace wizard template item                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceWizardTemplateItem.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_WorkspaceWizardTemplateItem, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_WorkspaceWizardTemplateItem
//---------------------------------------------------------------------------
PSS_WorkspaceWizardTemplateItem::PSS_WorkspaceWizardTemplateItem(const CString& templateName,
                                                                 const CString& templateDescription,
                                                                 const CString& iconFile,
                                                                 int            iconIndex) :
    CObject(),
    m_hIcon(NULL),
    m_TemplateName(templateName),
    m_TemplateDescription(templateDescription),
    m_IconFile(iconFile),
    m_IconIndex(iconIndex)
{
    LoadIconFile();
}
//---------------------------------------------------------------------------
PSS_WorkspaceWizardTemplateItem::~PSS_WorkspaceWizardTemplateItem()
{
    if (m_hIcon)
        ::DestroyIcon(m_hIcon);

    m_hIcon = NULL;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceWizardTemplateItem::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // write the elements
        ar << m_TemplateName;
        ar << m_TemplateDescription;
        ar << m_IconFile;
        ar << m_IconIndex;
    }
    else
    {
        // read the elements
        ar >> m_TemplateName;
        ar >> m_TemplateDescription;
        ar >> m_IconFile;
        ar >> m_IconIndex;

        // load the icon after reading the item
        LoadIconFile();
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceWizardTemplateItem::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceWizardTemplateItem::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_WorkspaceWizardTemplateItem::LoadIconFile()
{
    // load the icon only if a file and an icon index is defined
    if (!m_IconFile.IsEmpty() && m_IconIndex != -1)
        m_hIcon = ::ExtractIcon(::AfxGetInstanceHandle(), m_IconFile, m_IconIndex);
}
//---------------------------------------------------------------------------
