/****************************************************************************
 * ==> PSS_DocTemplateEx ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an extended document template                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DocTemplateExH
#define PSS_DocTemplateExH

#if _MSC_VER > 1000
    #pragma once
#endif

#ifdef _AFXEXT
// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
#endif

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_MRU_RANGE unsigned(ID_FILE_MRU_LAST - ID_FILE_MRU_FIRST)
//---------------------------------------------------------------------------

/**
* Extended document template
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DocTemplateEx : public CMultiDocTemplate
{
    DECLARE_DYNAMIC(PSS_DocTemplateEx)

    public:
        /**
        * Constructor
        *@param resourceID - resource identifier
        *@param pDocClass - document class
        *@param pFrameClass - frame class
        *@param pViewClass - view class
        *@param menuID - menu identifier
        *@param maxMRU - maximum MRU count
        */
        PSS_DocTemplateEx(UINT           resourceID,
                          CRuntimeClass* pDocClass,
                          CRuntimeClass* pFrameClass,
                          CRuntimeClass* pViewClass,
                          UINT           menuID = 0,
                          UINT           maxMRU = _AFX_MRU_COUNT);

        virtual ~PSS_DocTemplateEx();

        /**
        * Gets the menu identifier
        *@return the menu identifier
        */
        virtual inline UINT GetMenuID() const;

        /**
        * Adds new file name to recent file list
        *@param pPathName - file name and path to add to list
        */
        virtual void AddToRecentFileList(LPCTSTR pPathName);

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
        CRecentFileList* m_pRecentFileList;
        UINT             m_MenuID;

        /**
        * Loads the stanard profile settings
        *@param maxMRU - maximum RMU count
        */
        virtual void LoadStdProfileSettings(UINT maxMRU);

        /**
        * Saves the stanard profile settings
        */
        virtual void SaveStdProfileSettings();

        /**
        * Called when the recent file menu is updated
        *@param pCmdUI - user interface command to process
        */
        virtual void OnUpdateRecentFileMenu(CCmdUI* pCmdUI);

        /**
        * Called when recent file should be opened
        *@param id - menu identifier identifying the recent file to open
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OnOpenRecentFile(UINT id);

        /**
        * Routes and dispatches standard command message types
        *@param nID - message identifier
        *@param nCode - message code
        *@param pExtra - extra custom user data
        *@param pHandlerInfo - handler info
        *@return TRUE on success, otherwise FALSE
        *@note This hack is necessary because the menu ID is a member of the class. MFC message maps
        *      need the IDs to be global
        */
        virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
};

//---------------------------------------------------------------------------
// PSS_DocTemplateEx
//---------------------------------------------------------------------------
UINT PSS_DocTemplateEx::GetMenuID() const
{
    return m_MenuID;
}
//---------------------------------------------------------------------------

#endif
