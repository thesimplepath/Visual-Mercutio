// ZCProcessModelDocument.h : header file

#if !defined(AFX_ZCPROCESSMODELDOCUMENT_H__7E93C702_5D30_42EF_B694_0B86EF25FE4C__INCLUDED_)
#define AFX_ZCPROCESSMODELDOCUMENT_H__7E93C702_5D30_42EF_B694_0B86EF25FE4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModel\ZCProcessModelTree.h"
#include "zBaseLib\ZIObserver.h"

// JMR-MODIF - Le 14 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZCProcessModelDocument view

class ZCProcessModelDocument : public ZCProcessModelTree, public ZIObserver
{
public:

    DECLARE_DYNCREATE( ZCProcessModelDocument )

    ZCProcessModelDocument();
    virtual ~ZCProcessModelDocument();

    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

// Generated message map functions
protected:

    //{{AFX_MSG(ZCProcessModelDocument)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZCPROCESSMODELDOCUMENT_H__7E93C702_5D30_42EF_B694_0B86EF25FE4C__INCLUDED_)
