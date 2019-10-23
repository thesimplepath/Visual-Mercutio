/****************************************************************************
 * ==> PSS_FolderInfoCtrl --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a folder info control                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FolderInfoCtrlH
#define PSS_FolderInfoCtrlH

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
#include "zBaseLib\PSS_FolderStamp.h"
#include "zBaseLib\PSS_ListCtrl.h"

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
* Folder info control
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FolderInfoCtrl : public PSS_ListCtrl
{
    public:
        /**
        * Constructor
        *@param pFolderStamp - folder stamp, can be NULL
        *@param canModify - if TRUE, folder can be modified
        */
        PSS_FolderInfoCtrl(PSS_FolderStamp* pFolderStamp = NULL, BOOL canModify = FALSE);

        virtual ~PSS_FolderInfoCtrl();

        /**
        * Initializes the control with the folder information
        *@param pFolderStamp - folder stamp, can be NULL
        *@param removeAll - if TRUE, all previous folder content will be removed
        *@param canModify - if TRUE, folder can be modified
        */
        virtual void Initialize(PSS_FolderStamp* pFolderStamp, BOOL removeAll = TRUE, BOOL canModify = FALSE);

        /**
        * Refreshes the control
        */
        virtual void Refresh ();

        //{{AFX_MSG(PSS_FolderInfoCtrl)
        afx_msg BOOL OnDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_FolderStamp* m_pFolderStamp;
        CString          m_FolderNameTitle;
        CString          m_FolderDescriptionTitle;
        CString          m_CreationUserTitle;
        CString          m_CreationDateTitle;
        CString          m_PublishVersionTitle;
        CString          m_TypeTitle;
        CString          m_TemplateNameTitle;
        CString          m_TemplateFilenameTitle;
        BOOL             m_IsColumnBuilt;
        BOOL             m_CanModify;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FolderInfoCtrl(const PSS_FolderInfoCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FolderInfoCtrl & operator = (const PSS_FolderInfoCtrl& other);
};

#endif
