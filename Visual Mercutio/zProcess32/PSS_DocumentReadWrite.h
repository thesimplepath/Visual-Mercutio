/****************************************************************************
 * ==> PSS_DocumentReadWrite -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a document reader and writer                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DocumentReadWriteH
#define PSS_DocumentReadWriteH

 // old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_DocumentReadWrite
    #define PSS_DocumentReadWrite ZDDocumentReadWrite
#endif

// processsoft
#include "zBaseLib\PSS_Document.h"

/**
* Document reader and writer
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_DocumentReadWrite : public PSS_Document
{
    DECLARE_SERIAL(PSS_DocumentReadWrite)

    public:
        typedef PSS_Document inherited;

        virtual ~PSS_DocumentReadWrite();

        /**
        * Copies a page
        *@param pTargetDoc - the target document to copy to
        *@param pageIndex - the page index
        *@param sourceDocIndex - the source document index
        *@param destDocIndex - the destination document index
        */
        virtual BOOL CopyPage(PSS_DocumentReadWrite* pTargetDoc,
                              int                    pageIndex,
                              int                    sourceDocIndex = -1,
                              int                    destDocIndex   = -1);

        /**
        * Copies the objects contained in a page
        *@param pTargetDoc - the target document to copy to
        *@param pageIndex - the page index
        *@param sourceDocIndex - the source document index
        *@param destDocIndex - the destination document index
        */
        virtual BOOL CopyPageOnlyObjects(PSS_DocumentReadWrite* pTargetDoc,
                                         int                    pageIndex,
                                         int                    sourceDocIndex = -1,
                                         int                    destDocIndex   = -1);

        /**
        * Copies the formulas contained in a page
        *@param pTargetDoc - the target document to copy to
        *@param pageIndex - the page index
        *@param sourceDocIndex - the source document index
        *@param destDocIndex - the destination document index
        */
        virtual BOOL CopyPageOnlyFormula(PSS_DocumentReadWrite* pTargetDoc,
                                         int                    pageIndex,
                                         int                    sourceDocIndex = -1,
                                         int                    destDocIndex   = -1);

        /**
        * Deletes a page
        *@param pageIndex - the page index
        *@param docIndex - the document index
        */
        virtual BOOL DeletePage(int pageIndex, int docIndex = -1);

        /**
        * Moves the content of a page to another page
        *@param pDocument - the document to move from
        *@param copyFormat - if TRUE, the format will be copied
        *@param sourceDocIndex - the source document index
        *@param destDocIndex - the destination document index
        */
        virtual void MoveContents(PSS_DocumentReadWrite* pDocument,
                                  BOOL                   copyFormat,
                                  int                    sourceDocIndex = -1,
                                  int                    destDocIndex   = -1);

        /**
        * Sets the current style
        *@param name - the style name
        *@param docIndex - the document index
        */
        virtual void SetCurrentStyle(const CString& name, int docIndex = -1);

        /**
        * Checks if the style has been deleted, restore the default style if yes
        *@param hStyle - the style to check
        *@param docIndex - the document index
        */
        virtual void StyleHasBeenDeleted(PSS_Style::Handle hStyle, int docIndex = -1);

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
        //{{AFX_MSG(PSS_DocumentReadWrite)
        afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
        afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
        afx_msg void OnImport();
        afx_msg void OnExport();
        afx_msg void OnFileOptions();
        afx_msg void OnFileProperty();
        afx_msg void OnFileSave();
        afx_msg void OnFileSaveAs();
        afx_msg void OnFormulaScenarioAssociate();
        afx_msg void OnFormulaScenarioCopy();
        afx_msg void OnFormulaScenarioCreation();
        afx_msg void OnFormulaScenarioDelete();
        afx_msg void OnDefineStyle();
        afx_msg void OnChangeStyle();
        afx_msg void OnInsertNewPage();
        afx_msg void OnFormAttach();
        afx_msg void OnPageDelete();
        afx_msg void OnFormManage();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        PSS_DocumentReadWrite();

        /**
        * Builds the template name
        *@param[out] str - the template name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL BuildTemplateName(CString& str);

        /**
        * Saves the document if modified
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveModified();

        /**
        * Called when a new document is created
        *@return TRUE if the document can be created, otherwise FALSE
        */
        virtual BOOL OnNewDocument();

        /**
        * Called when a document is opened
        *@param pPathName - the path name
        *@return TRUE if the document can be opened, otherwise FALSE
        */
        virtual BOOL OnOpenDocument(const char* pPathName);

        /**
        * Called when a document is about to be saved
        *@param pPathName - the path name
        *@return TRUE if the document can be saved, otherwise FALSE
        */
        virtual BOOL OnSaveDocument(const char* pPathName);

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DocumentReadWrite(const PSS_DocumentReadWrite& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_DocumentReadWrite& operator = (const PSS_DocumentReadWrite& other);
};

#endif
