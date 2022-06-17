/****************************************************************************
 * ==> PSS_SearchEdit ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a search edit                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SearchEditH
#define PSS_SearchEditH

#if _MSC_VER >= 1000
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
#include "zBaseLib\PSS_DragEdit.h"

// forward class declaration
class PSS_SearchEdit;

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
* Search edit button
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SearchEditButton : public CButton
{
    public:
        /**
        * Button type
        */
        enum class IEType
        {
            IE_T_Directory = 0,
            IE_T_File,
            IE_T_Popup,
            IE_T_Extended
        };

        PSS_SearchEditButton();
        virtual ~PSS_SearchEditButton();

        /**
        * Creates the button
        *@param pWnd - parent window
        *@param type - button type
        *@param menu - menu item
        *@param title - title
        *@param initialDir - initial directory
        *@param filters - filters
        *@param filterCount - filter count
        *@param enableMenuItems - if true, the menu items will be enabled
        *@param noNotify - if true, notifications will not be sent
        *@param resize - if true, button will be resized
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(PSS_SearchEdit* pWnd,
                            IEType          type,
                            UINT            menu,
                            const CString&  title,
                            const CString&  initialDir,
                            const CString&  filters,
                            std::size_t     filterCount,
                            bool            enableMenuItems,
                            bool            noNotify,
                            bool            resize);

        /**
        * Creates the button
        *@param pWnd - parent window
        *@param type - button type
        *@param pMenu - menu
        *@param title - title
        *@param initialDir - initial directory
        *@param filters - filters
        *@param filterCount - filter count
        *@param enableMenuItems - if true, the menu items will be enabled
        *@param noNotify - if true, notifications will not be sent
        *@param resize - if true, button will be resized
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(PSS_SearchEdit* pWnd,
                            IEType          type,
                            CMenu*          pMenu,
                            const CString&  title,
                            const CString&  initialDir,
                            const CString&  filters,
                            std::size_t     filterCount,
                            bool            enableMenuItems,
                            bool            noNotify,
                            bool            resize);

        /**
        * Gets the next identifier
        *@param pWnd - parent window
        *@return the next identifier
        */
        virtual UINT GetNextID(CWnd* pWnd) const;

    protected:
        CWnd*           m_pWnd;
        CMenu*          m_pMenu;
        PSS_SearchEdit* m_pEdit;
        IEType          m_Type;
        CFont           m_Font;
        CString         m_Title;
        CString         m_InitialDir;
        CString         m_Filters;
        UINT            m_ID;
        UINT            m_Menu;
        std::size_t     m_FilterCount;
        bool            m_EnableMenuItems;
        bool            m_NoNotify;

        /// Generated message map functions
        //{{AFX_MSG(PSS_SearchEditButton)
        afx_msg void OnClicked();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        bool m_IsProcessingMenuItems;

        /**
        * Creates a button
        *@param pWnd - parent window
        *@param type - button type
        *@param resize - if true, the button will be resized
        */
        BOOL CreateButton(CWnd* pWnd, IEType type, bool resize);
};

/**
* Search edit
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SearchEdit : public PSS_DragEdit
{
    public:
        PSS_SearchEdit();
        virtual ~PSS_SearchEdit();

        /**
        * Creates the edit
        *@param style - edit style
        *@param rect - edit surrounding rect
        *@param pParentWnd - parent window
        *@param id - identifier
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(DWORD style, const RECT& rect, CWnd* pParentWnd, UINT id);

        /**
        * Creates the edit
        *@param pClassName - class name
        *@param pWindowName - window name
        *@param style - edit style
        *@param rect - edit surrounding rect
        *@param pParentWnd - parent window
        *@param id - identifier
        *@param pContext - context
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(LPCTSTR         pClassName,
                            LPCTSTR         pWindowName,
                            DWORD           style,
                            const RECT&     rect,
                            CWnd*           pParentWnd,
                            UINT            id,
                            CCreateContext* pContext = NULL);

        /**
        * Sets the edit search type
        *@param type edit search type
        */
        virtual void SetSearchType(PSS_SearchEditButton::IEType type);

        /**
        * Sets the edit search type
        *@param menu - menu item
        *@param enableMenuItems - if true, the menu items will be enabled
        *@param noNotify - if true, notifications will not be sent
        *@param type edit search type
        */
        virtual void SetSearchType(PSS_SearchEditButton::IEType type,
                                   UINT                         menu,
                                   bool                         enableMenuItems = false,
                                   bool                         noNotify        = false);

        /**
        * Sets the edit search type
        *@param pMenu - menu
        *@param enableMenuItems - if true, the menu items will be enabled
        *@param noNotify - if true, notifications will not be sent
        *@param type edit search type
        */
        virtual void SetSearchType(PSS_SearchEditButton::IEType type,
                                   CMenu*                       pMenu,
                                   bool                         enableMenuItems = false,
                                   bool                         noNotify        = false);

        /**
        * Sets the edit search type
        *@param type edit search type
        *@param title - title
        *@param initialDir - initial directory
        */
        virtual void SetSearchType(PSS_SearchEditButton::IEType type,
                                   const CString&               title,
                                   const CString&               initialDir = _T(""));

        /**
        * Sets the edit search type
        *@param type edit search type
        *@param id - identifier
        *@param initialDir - initial directory
        */
        virtual void SetSearchType(PSS_SearchEditButton::IEType type, UINT id, const CString& initialDir);

        /**
        * Sets the edit search type
        *@param type edit search type
        *@param title - title
        *@param initialDir - initial directory
        *@param filters - filters
        *@param filterCount - filter count
        */
        virtual void SetSearchType(PSS_SearchEditButton::IEType type,
                                   const CString&               title,
                                   const CString&               initialDir,
                                   const CString&               filters,
                                   std::size_t                  filterCount);

        /**
        * Sets the edit search type
        *@param type edit search type
        *@param id - identifier
        *@param initialDir - initial directory
        *@param filters - filters
        *@param filterCount - filter count
        */
        virtual void SetSearchType(PSS_SearchEditButton::IEType type,
                                   UINT                         id,
                                   const CString&               initialDir,
                                   const CString&               filters,
                                   std::size_t                  filterCount);

        /**
        * Called when a menu command is selected
        *@param menuCommand - menu command
        */
        virtual void OnMenuCommand(int menuCommand);

        /**
        * Called when an extended command is selected
        *@param menuCommand - menu command
        */
        virtual void OnExtendedCommand();

        /**
        * Sets if button should be created
        *@param value - if TRUE, button will be created, otherwise FALSE
        */
        void DoCreateButton(BOOL value);

    protected:
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SearchEdit)
        virtual void PreSubclassWindow();
        //}}AFX_VIRTUAL

        //{{AFX_MSG(PSS_SearchEdit)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnEnable(BOOL bEnable);
        afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CMenu*                       m_pMenu;
        CWnd*                        m_pParentWnd;
        PSS_SearchEditButton         m_Button;
        PSS_SearchEditButton::IEType m_Type;
        CString                      m_Title;
        CString                      m_InitialDir;
        CString                      m_Filters;
        std::size_t                  m_FilterCount;
        UINT                         m_Menu;
        BOOL                         m_DoCreateButton;
        bool                         m_BeingResized;
        bool                         m_BeingCreated;
        bool                         m_EnableMenuItems;
        bool                         m_NoNotify;

        /**
        * Creates a button
        *@param resize - if true, the button will be resized
        */
        void CreateButton(bool resize);
};

#endif
