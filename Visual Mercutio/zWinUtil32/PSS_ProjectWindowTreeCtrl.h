/****************************************************************************
 * ==> PSS_ProjectWindowTreeCtrl -------------------------------------------*
 ****************************************************************************
 * Description : Provides a project window tree control                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProjectWindowTreeCtrlH
#define PSS_ProjectWindowTreeCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZITreeCtl.h"
#include "PSS_ProjectTree.h"

// class name mapping
#ifndef PSS_Document
    #define PSS_Document ZDDocument
#endif

// forward class declaration
class PSS_Document;
class PSS_DocumentData;

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Project window tree control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProjectWindowTreeCtrl : public ZITreeCtrl
{
    public:
        /**
        * Constructor
        *@param pDoc - document
        *@param visibleOnly - visible only
        */
        PSS_ProjectWindowTreeCtrl(PSS_Document* pDoc = NULL, BOOL visibleOnly = TRUE);

        virtual ~PSS_ProjectWindowTreeCtrl();

        /**
        * Initializes the window tree
        *@param pDoc - document
        *@param visibleOnly - visible only
        */
        virtual void Initialize();
        virtual void Initialize(PSS_Document* pDoc, BOOL visibleOnly = TRUE);

        /**
        * Empties the window tree
        */
        virtual void Empty();

        /**
        * Refreshes the window tree
        */
        virtual void Refresh();

        /**
        * Gets the selected document
        *@return the selected document, NULL if no selection or on error
        */
        virtual PSS_DocumentData* GetSelectedDocument();

        /**
        * Gets the selected document title
        *@return the selected document title, empty string if no selection or on error
        */
        virtual CString GetSelectedDocumentTitle();

        //{{AFX_MSG(PSS_ProjectWindowTreeCtrl)
        afx_msg LONG OnFileListChanged(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_Document*   m_pDoc;
        PSS_ProjectTree m_ProjectTree;
        BOOL            m_VisibleOnly;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProjectWindowTreeCtrl(const PSS_ProjectWindowTreeCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ProjectWindowTreeCtrl & operator = (const PSS_ProjectWindowTreeCtrl& other);
};

#endif
