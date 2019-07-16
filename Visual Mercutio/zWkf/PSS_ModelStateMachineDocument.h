/****************************************************************************
 * ==> PSS_ModelStateMachineDocument ---------------------------------------*
 ****************************************************************************
 * Description : Provides a state machine document                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModelStateMachineDocumentH
#define PSS_ModelStateMachineDocumentH

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
#include "PSS_StateMachineCollection.h"

#ifdef _ZWKFEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* State machine document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ModelStateMachineDocument : public CDocument
{
    DECLARE_DYNCREATE(PSS_ModelStateMachineDocument)

    public:
        /**
        * Constructor
        *@param pModelStateMachine - model state machine owning the document
        */
        PSS_ModelStateMachineDocument(PSS_StateMachineCollection* pModelStateMachine = NULL);

        virtual ~PSS_ModelStateMachineDocument();

        /**
        * Reads a document content from a file
        *@param fileName - file name
        *@param pModelStateMachine - model state machine collection, can be NULL
        *@return true on success, otherwise false
        */
        virtual bool ReadFromFile(const CString& fileName, PSS_StateMachineCollection* pModelStateMachine = NULL);

        /**
        * Saves a document content to a file
        *@param fileName - file name
        *@param pModelStateMachine - model state machine collection, can be NULL
        *@return true on success, otherwise false
        */
        virtual bool SaveToFile(const CString& fileName, PSS_StateMachineCollection* pModelStateMachine = NULL);

        /**
        * Checks if document was loaded
        *@return true if document was loaded, otherwise false
        */
        virtual inline bool IsLoaded() const;

        /**
        * Sets the document as loaded
        *@param value - if true, document will be set as loaded
        */
        virtual inline void SetLoaded(bool value = true);

        /**
        * Serializes the document content
        *@param ar - archive in which the content will be serialized
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the state link validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the state link content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        /**
        * Called when a new document is created
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OnNewDocument();

        /// Generated message map functions
        //{{AFX_MSG(ZDModelStateMachineDocument)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_StateMachineCollection* m_pStateMachineCollection;
        bool                        m_IsLoaded;
};

//---------------------------------------------------------------------------
// PSS_ModelStateMachineDocument
//---------------------------------------------------------------------------
bool PSS_ModelStateMachineDocument::IsLoaded() const
{
    return m_IsLoaded;
}
//---------------------------------------------------------------------------
void PSS_ModelStateMachineDocument::SetLoaded(bool value)
{
    m_IsLoaded = value;
}
//---------------------------------------------------------------------------

#endif
