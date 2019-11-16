/****************************************************************************
 * ==> PSS_Notes -----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the notes                                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Notes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_Notes, CObject, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_Notes
//---------------------------------------------------------------------------
PSS_Notes::PSS_Notes(const CString& comment, const CString& userName) :
    CObject(),
    m_UserName(userName),
    m_Comment(comment)
{}
//---------------------------------------------------------------------------
PSS_Notes::PSS_Notes(const PSS_Notes& other) :
    CObject()
{
    *this = other;
}
//---------------------------------------------------------------------------
PSS_Notes::~PSS_Notes()
{}
//---------------------------------------------------------------------------
const PSS_Notes& PSS_Notes::operator = (const PSS_Notes& other)
{
    m_UserName = other.m_UserName;
    m_Comment  = other.m_Comment;

    return *this;
}
//---------------------------------------------------------------------------
CArchive& operator >> (CArchive& ar, PSS_Notes& notes)
{
    ar >> notes.m_UserName;
    ar >> notes.m_Comment;

    return ar;
}
//---------------------------------------------------------------------------
CArchive& operator << (CArchive& ar, const PSS_Notes& notes)
{
    ar << notes.m_UserName;
    ar << notes.m_Comment;

    return ar;
}
//---------------------------------------------------------------------------
PSS_Notes* PSS_Notes::Clone() const
{
    return new PSS_Notes(*this);
}
//---------------------------------------------------------------------------
void PSS_Notes::ClearNotes()
{
    ClearUserName();
    ClearComment();
}
//---------------------------------------------------------------------------
void PSS_Notes::ClearUserName()
{
    m_UserName.Empty();
}
//---------------------------------------------------------------------------
void PSS_Notes::ClearComment()
{
    m_Comment.Empty();
}
//---------------------------------------------------------------------------
CString PSS_Notes::GetFormattedNotes(CRect* pRect)
{
    return m_UserName + "\r\n" + m_Comment;
}
//---------------------------------------------------------------------------
void PSS_Notes::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
        // write the elements
        ar << *this;
    else
        ar >> *this;
}
//---------------------------------------------------------------------------
