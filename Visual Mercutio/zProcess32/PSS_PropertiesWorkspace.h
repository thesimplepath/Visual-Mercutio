/****************************************************************************
 * ==> PSS_PropertiesWorkspace ---------------------------------------------*
 ****************************************************************************
 * Description : Provides the properties workspace                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertiesWorkspaceH
#define PSS_PropertiesWorkspaceH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_SpanWnd.h"
#include "zModelBP\PSS_InputAttributesView.h"
#include "zModelBP\PSS_DistributionAttributesView.h"

 /**
 * Properties workspace
 *@author Dominique Aigroz, Jean-Milost Reymond
 */
class PSS_PropertiesWorkspace : public SECControlBar,
                                public PSS_Subject,
                                public PSS_Observer
{
    DECLARE_DYNAMIC(PSS_PropertiesWorkspace)

    public:
        PSS_PropertiesWorkspace();
        virtual ~PSS_PropertiesWorkspace();

        /**
        * Initializes the workspace
        */
        virtual void Initialize();

        /**
        * Releases the workspace
        */
        virtual void Release();

        /**
        * Gets the property view
        *@return the property view
        */
        virtual inline PSS_PropertiesView* GetPropertyView();

        /**
        * Gets the input attribute view
        *@return the input attribute view
        */
        virtual inline PSS_InputAttributesView* GetInputAttributeView();

        /**
        * Gets the distribution attribute view
        *@return the distribution attribute view
        */
        virtual inline PSS_DistributionAttributesView* GetDistributionAttributeView();

        /**
        * Gets the pan view
        *@return the pan view
        */
        virtual inline PSS_SpanWnd* GetPanView();

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PropertiesWorkspace)
        //}}AFX_VIRTUAL
        virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
        virtual void OnExtendContextMenu(CMenu* pMenu);

        /// Generated message map functions
        //{{AFX_MSG(PSS_PropertiesWorkspace)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnListGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg LRESULT OnInitializeModelDocument(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        SEC3DTabWnd                    m_WndTab;
        PSS_SpanWnd                    m_PanView;
        PSS_PropertiesView             m_PropertyView;
        PSS_InputAttributesView        m_InputAttributeView;
        PSS_DistributionAttributesView m_DistributionAttributeView;
};

//---------------------------------------------------------------------------
// PSS_PropertiesWorkspace
//---------------------------------------------------------------------------
PSS_PropertiesView* PSS_PropertiesWorkspace::GetPropertyView()
{
    return &m_PropertyView;
}
//---------------------------------------------------------------------------
PSS_InputAttributesView* PSS_PropertiesWorkspace::GetInputAttributeView()
{
    return &m_InputAttributeView;
}
//---------------------------------------------------------------------------
PSS_DistributionAttributesView* PSS_PropertiesWorkspace::GetDistributionAttributeView()
{
    return &m_DistributionAttributeView;
}
//---------------------------------------------------------------------------
PSS_SpanWnd* PSS_PropertiesWorkspace::GetPanView()
{
    return &m_PanView;
}
//---------------------------------------------------------------------------

#endif
