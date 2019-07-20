/****************************************************************************
 * ==> PSS_BasePropSheet ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic property sheet                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_BasePropSheet.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_BasePropSheet, CPropertySheet)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_BasePropSheet, CPropertySheet)
    //{{AFX_MSG_MAP(PSS_BasePropSheet)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_BasePropSheet
//---------------------------------------------------------------------------
PSS_BasePropSheet::PSS_BasePropSheet(int defaultTab) :
    CPropertySheet("", NULL, defaultTab)
{}
//---------------------------------------------------------------------------
PSS_BasePropSheet::PSS_BasePropSheet(UINT captionID, int defaultTab) :
    CPropertySheet(captionID, NULL, defaultTab)
{}
//---------------------------------------------------------------------------
PSS_BasePropSheet::PSS_BasePropSheet(LPCTSTR pCaption, int defaultTab) :
    CPropertySheet(pCaption, NULL, defaultTab)
{}
//---------------------------------------------------------------------------
PSS_BasePropSheet::PSS_BasePropSheet(const PSS_BasePropSheet& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_BasePropSheet::~PSS_BasePropSheet()
{
    DeleteAllPropertyPages();
}
//---------------------------------------------------------------------------
const PSS_BasePropSheet& PSS_BasePropSheet::operator = (const PSS_BasePropSheet& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_BasePropSheet::GetCurPage () const
{
    #ifndef _WIN32
        return m_CurPage;
    #else
        return GetActiveIndex();
    #endif
}
//---------------------------------------------------------------------------
int PSS_BasePropSheet::FindPropertyPage(CPropertyPage* pPage)
{
    const int pageCount = m_PageArray.GetSize();

    for (int i = 0; i < pageCount; ++i)
        if (pPage == m_PageArray[i])
            return i;

    return -1;
}
//---------------------------------------------------------------------------
bool PSS_BasePropSheet::DeletePropertyPage(CPropertyPage* pPage)
{
    const int index = FindPropertyPage(pPage);

    if (index != -1)
        return DeletePropertyPageAt(index);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_BasePropSheet::DeletePropertyPageAt(std::size_t index)
{
    if (index < std::size_t(m_PageArray.GetSize()))
    {
        delete m_PageArray[index];
        m_PageArray.RemoveAt(index);
        RemovePage(index);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_BasePropSheet::DeleteAllPropertyPages()
{
    const int pageCount = m_PageArray.GetSize();

    // delete the pages allocated on the fly by the ZINewForm class
    for (int i = 0; i < pageCount; ++i)
    {
        delete m_PageArray[i];
        RemovePage(0);
    }

    m_PageArray.RemoveAll();
}
//---------------------------------------------------------------------------
