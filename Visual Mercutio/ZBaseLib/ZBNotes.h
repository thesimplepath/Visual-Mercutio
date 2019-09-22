/****************************************************************************
 * ==> PSS_Notes -----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a notes class                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_NotesH
#define PSS_NotesH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "Mfc.h"

// processsoft
#include "ZUser.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Notes
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZBNotes : public CObject
{
    DECLARE_SERIAL(ZBNotes)

public:
    //## Constructors (generated)
    ZBNotes(const ZBNotes &right);

    //## Constructors (specified)
      //## Operation: ZBNotes%937741717
    ZBNotes(CString Comment = "", CString Username = "");

    //## Destructor (generated)
    virtual ~ZBNotes();

    //## Assignment Operation (generated)
    const ZBNotes & operator=(const ZBNotes &right);


    //## Other Operations (specified)
      //## Operation: Clone%937741718
    ZBNotes* Clone();

    //## Operation: ClearNotes%937741722
    //    Clear the notes
    void ClearNotes();

    //## Operation: ClearComment%937741723
    //    Clear the note's comment
    void ClearComment();

    //## Operation: ClearUsername%937741724
    //    Clear the note's username.
    void ClearUsername();

    //## Operation: GetFormattedNotes%937741725
    //    Return the notes with \r\n char.
    CString GetFormattedNotes(CRect* pRect = NULL);

    //## Operation: operator >>%937741719
    //    Store from the archive to the object Notes.
    AFX_EXT_API friend CArchive& operator >> (CArchive& ar, ZBNotes& Notes);

    //## Operation: operator <<%937741720
    //    Store the object Notes to the archive.
    AFX_EXT_API friend CArchive& operator << (CArchive& ar, ZBNotes& Notes);

    //## Operation: Serialize%937741721
    //    Serialization function required for MFC mecanism.
    virtual void Serialize(CArchive& ar);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Comment%37E4CC9F025F
      //    Contains the comment
    const CString& GetComment() const;
    void SetComment(const CString& value);

    //## Attribute: Username%37E4CC9F0260
    //    Contains the username of the note.
    const CString GetUsername() const;
    void SetUsername(CString value);

private:
    CString m_Username;
    CString m_Comment;
};

inline const CString& ZBNotes::GetComment() const
{
    return m_Comment;
}

inline void ZBNotes::SetComment(const CString& value)
{
    m_Comment = value;
}

inline const CString ZBNotes::GetUsername() const
{
    return m_Username;
}

inline void ZBNotes::SetUsername(CString value)
{
    m_Username = value;
}

#endif
