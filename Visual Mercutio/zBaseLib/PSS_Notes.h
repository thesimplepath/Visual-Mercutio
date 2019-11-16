/****************************************************************************
 * ==> PSS_Notes -----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the notes                                         *
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
#include "PSS_User.h"

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
class AFX_EXT_CLASS PSS_Notes : public CObject
{
    DECLARE_SERIAL(PSS_Notes)

    public:
        /**
        * Constructor
        *@param comment - comment
        *@param userName - user name
        */
        PSS_Notes(const CString& comment = "", const CString& userName = "");

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Notes(const PSS_Notes& other);

        virtual ~PSS_Notes();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Notes& operator = (const PSS_Notes& other);

        /**
        * Stores from the archive to the notes
        *@param ar - archive
        *@param notes - notes
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_Notes& notes);

        /**
        * Stores the file to the archive
        *@param ar - archive
        *@param notes - notes
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, const PSS_Notes& Notes);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_Notes* Clone() const;

        /**
        * Clears the notes
        */
        virtual void ClearNotes();

        /**
        * Clears the notes user name
        */
        virtual void ClearUserName();

        /**
        * Clears the notes comments
        */
        virtual void ClearComment();

        /**
        * Gets the formatted notes (i.e with \r\n char)
        *@param pRect - rectangle in which the notes should fit
        *@return the formatted notes
        */
        virtual CString GetFormattedNotes(CRect* pRect = NULL);

        /**
        * Gets the notes user name
        *@return the notes user name
        */
        virtual inline const CString GetUserName() const;

        /**
        * Sets the notes user name
        *@param value - the notes user name
        */
        virtual inline void SetUserName(const CString& value);

        /**
        * Gets the notes comment
        *@return the notes comment
        */
        virtual inline const CString& GetComment() const;

        /**
        * Sets the notes comment
        *@param value - the notes comment
        */
        virtual inline void SetComment(const CString& value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CString m_UserName;
        CString m_Comment;
};

//---------------------------------------------------------------------------
// PSS_Notes
//---------------------------------------------------------------------------
const CString PSS_Notes::GetUserName() const
{
    return m_UserName;
}
//---------------------------------------------------------------------------
void PSS_Notes::SetUserName(const CString& value)
{
    m_UserName = value;
}
//---------------------------------------------------------------------------
const CString& PSS_Notes::GetComment() const
{
    return m_Comment;
}
//---------------------------------------------------------------------------
void PSS_Notes::SetComment(const CString& value)
{
    m_Comment = value;
}
//---------------------------------------------------------------------------

#endif
