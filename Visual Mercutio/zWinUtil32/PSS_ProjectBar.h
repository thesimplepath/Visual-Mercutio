/****************************************************************************
 * ==> PSS_ProjectBar ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a project bar                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProjectBarH
#define PSS_ProjectBarH

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
#include "PSS_ProjectWindowTreeCtrl.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

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
* Project bar
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProjectBar : public CCJControlBar
{
public:
    /**
    * Constructor
    *@param visibleOnly - visible only
    */
    PSS_ProjectBar(BOOL visibleOnly = TRUE);

    virtual ~PSS_ProjectBar();

    /**
    * Initializes the project bar
    *@param visibleOnly - visible only
    */
    virtual void Initialize(BOOL visibleOnly);

protected:
    /// Generated message map functions
    //{{AFX_MSG(PSS_ProjectBar)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg LRESULT OnDocumentHasBeenSelected(WPARAM wParam, LPARAM lParam);
    afx_msg void OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    PSS_ProjectWindowTreeCtrl m_ProjectWindowCtrl;
    BOOL                      m_VisibleOnly;
};

#endif
