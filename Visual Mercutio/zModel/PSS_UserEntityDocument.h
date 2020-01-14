/****************************************************************************
 * ==> PSS_UserEntityDocument ----------------------------------------------*
 ****************************************************************************
 * Description : Provides an user entity document                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_UserEntityDocumentH
#define PSS_UserEntityDocumentH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_BaseDocument.h"
#include "PSS_UserGroupEntity.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* User entity document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_UserEntityDocument : public PSS_BaseDocument
{
    DECLARE_DYNCREATE(PSS_UserEntityDocument)

    public:
        typedef PSS_BaseDocument inherited;

        PSS_UserEntityDocument();
        virtual ~PSS_UserEntityDocument();

        /**
        * Gets the user group environment
        *@return the user group environment
        */
        virtual inline PSS_UserGroupEntity& GetUserGroupEnvironment();

        /**
        * Checks if the document is loaded
        *@return true if the document is loaded, otherwise false
        */
        virtual inline bool IsLoaded() const;

        /**
        * Sets the document as loaded
        *@param value - if true, the document is loaded
        */
        virtual inline void SetLoaded(bool value = true);

        /**
        * Checks if the document is modified
        *@return true if the document is modified, otherwise false
        */
        virtual inline BOOL IsModified();

        /**
        * Sets the document as modified
        *@param value - if true, the document is modified
        */
        virtual inline void SetModifiedFlag(BOOL value = TRUE);

        /**
        * Checks if the document content is matching with the beta 1 version
        *@return true if the document content is matching with the beta 1 version, otherwise false
        */
        virtual inline bool IsBeta1Format() const;

        /**
        * Checks if the file is an archive
        *@return TRUE if the file is an archive, otherwise FALSE
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Reads the document from a file
        *@param fileName - the file name
        *@return true on success, otherwise false
        */
        virtual bool ReadFromFile(const CString& fileName);

        /**
        * Saves the document to a file
        *@param fileName - the file name
        *@return true on success, otherwise false
        */
        virtual bool SaveToFile(const CString& fileName);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_UserEntityDocument)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Called when a new document is created
        */
        virtual BOOL OnNewDocument();

    private:
        PSS_UserGroupEntity m_UserGroupEnvironment;
        CString             m_GUID;
        bool                m_IsLoaded;
        bool                m_Beta1Format;
};

//---------------------------------------------------------------------------
// PSS_UserEntityDocument
//---------------------------------------------------------------------------
PSS_UserGroupEntity& PSS_UserEntityDocument::GetUserGroupEnvironment()
{
    return m_UserGroupEnvironment;
}
//---------------------------------------------------------------------------
bool PSS_UserEntityDocument::IsLoaded() const
{
    return m_IsLoaded;
}
//---------------------------------------------------------------------------
void PSS_UserEntityDocument::SetLoaded(bool value)
{
    m_IsLoaded = value;
}
//---------------------------------------------------------------------------
BOOL PSS_UserEntityDocument::IsModified()
{
    return (CDocument::IsModified() || m_UserGroupEnvironment.IsModified());
}
//---------------------------------------------------------------------------
void PSS_UserEntityDocument::SetModifiedFlag(BOOL value)
{
    CDocument::SetModifiedFlag(value);
    m_UserGroupEnvironment.SetModifiedFlag(value);
}
//---------------------------------------------------------------------------
bool PSS_UserEntityDocument::IsBeta1Format() const
{
    return m_Beta1Format;
}
//---------------------------------------------------------------------------

#endif
