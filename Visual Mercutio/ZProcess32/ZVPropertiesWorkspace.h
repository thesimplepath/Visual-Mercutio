// ZVPropertiesWorkspace.h: interface for the ZVPropertiesWorkspace class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVPropertiesWorkspace_H__8CD08B10_53ED_438C_82AD_1E04FE3C6282__INCLUDED_)
#define AFX_ZVPropertiesWorkspace_H__8CD08B10_53ED_438C_82AD_1E04FE3C6282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\ZVSpanWnd.h"
#include "zModelBP\ZVInputAttributes.h"
#include "zModelBP\ZVDistributionAttributes.h"

// JMR-MODIF - Le 3 juilet 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class ZVPropertiesWorkspace : public SECControlBar,
                              public PSS_Subject,
                              public PSS_Observer
{
    DECLARE_DYNAMIC(ZVPropertiesWorkspace)

public:

    ZVPropertiesWorkspace();
    virtual ~ZVPropertiesWorkspace();

    void Initialize();

    // JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release.
    void Release();

    ZVProperties*                GetPropertyView();
    ZVInputAttributes*            GetInputAttributeView();
    ZVDistributionAttributes*    GetDistributionAttributeView();
    ZVSpanWnd*                    GetPanView();

    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

public:

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVPropertiesWorkspace)
public:
    //}}AFX_VIRTUAL
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
    virtual void OnExtendContextMenu(CMenu* pMenu);

    // Generated message map functions
protected:

    //{{AFX_MSG(ZVPropertiesWorkspace)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnListGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg LRESULT OnInitializeModelDocument(WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    ZVProperties                m_PropertyView;
    ZVInputAttributes            m_InputAttributeView;
    ZVDistributionAttributes    m_DistributionAttributeView;
    ZVSpanWnd                    m_PanView;
    SEC3DTabWnd                    m_wndTab;
};

inline ZVProperties* ZVPropertiesWorkspace::GetPropertyView()
{
    return &m_PropertyView;
}

inline ZVInputAttributes* ZVPropertiesWorkspace::GetInputAttributeView()
{
    return &m_InputAttributeView;
}

inline ZVDistributionAttributes* ZVPropertiesWorkspace::GetDistributionAttributeView()
{
    return &m_DistributionAttributeView;
}

inline ZVSpanWnd* ZVPropertiesWorkspace::GetPanView()
{
    return &m_PanView;
}

#endif
