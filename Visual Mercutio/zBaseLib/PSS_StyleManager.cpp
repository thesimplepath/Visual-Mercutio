/****************************************************************************
 * ==> PSS_StyleManager ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a style manager                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_StyleManager.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_StyleManager, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_StyleManager
//---------------------------------------------------------------------------
PSS_StyleManager::PSS_StyleManager() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_StyleManager::PSS_StyleManager(const PSS_StyleManager& other) :
    CObject()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_StyleManager::~PSS_StyleManager()
{
    const int count = m_StyleArray.GetSize();

    // delete valid styles
    for (int i = 0; i < count; ++i)
        if (m_StyleArray[i])
            delete m_StyleArray[i];

    m_StyleArray.RemoveAll();
}
//---------------------------------------------------------------------------
const PSS_StyleManager& PSS_StyleManager::operator = (const PSS_StyleManager& other)
{
    const int count = other.m_StyleArray.GetSize();

    if (count > 0)
    {
        m_StyleArray.SetSize(count);

        for (int i = 0; i < count; ++i)
            if (other.m_StyleArray[i])
                m_StyleArray.InsertAt(i, static_cast<PSS_Style*>(other.m_StyleArray[i])->Clone());
    }

    return *this;
}
//---------------------------------------------------------------------------
PSS_Style::Handle PSS_StyleManager::AddStyle(PSS_Style* pStyle)
{
    const int count = m_StyleArray.GetSize();

    // scan the array to know if empty place to store the new style
    for (register int i = 0; i < count; ++i)
        // check if an empty place
        if (!m_StyleArray[i])
        {
            m_StyleArray.SetAt(i, pStyle);
            pStyle->SetStyleHandle(i);
            return i;
        }

    pStyle->SetStyleHandle(m_StyleArray.Add(pStyle));
    return pStyle->GetStyleHandle();
}
//---------------------------------------------------------------------------
BOOL PSS_StyleManager::RemoveStyle(PSS_Style::Handle hStyle)
{
    const int count = m_StyleArray.GetSize();

    for (int i = 0; i < count; ++i)
        if (m_StyleArray[i] && ((PSS_Style*)(m_StyleArray[i]))->GetStyleHandle() == hStyle)
        {
            // free memory at location
            delete m_StyleArray[i];

            // set the element to NULL in the array, do not remove
            m_StyleArray.SetAt(i, NULL);

            return TRUE;
        }

    return FALSE;
}
//---------------------------------------------------------------------------
PSS_Style::Handle PSS_StyleManager::SearchStyle(const CString& name)
{
    const int count = m_StyleArray.GetSize();

    // check valid styles only and check the name
    for (int i = 0; i < count; ++i)
        if (m_StyleArray[i] && static_cast<PSS_Style*>(m_StyleArray[i])->GetStyleName() == name)
            return static_cast<PSS_Style*>(m_StyleArray[i])->GetStyleHandle();

    return g_NoStyleDefined;
}
//---------------------------------------------------------------------------
void PSS_StyleManager::Serialize(CArchive& ar)
{
    m_StyleArray.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_StyleManager::AssertValid() const
    {
        CObject::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_StyleManager::Dump(CDumpContext& dc) const
    {
        CObject::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
