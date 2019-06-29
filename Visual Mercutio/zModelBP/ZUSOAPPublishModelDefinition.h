/////////////////////////////////////////////////////////////////////////////
//@doc ZUSOAPPublishModelDefinition
//@module ZUSOAPPublishModelDefinition.h | Interface of the <c ZUSOAPPublishModelDefinition> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:         07/2001
// <nl>Description:  ZUSOAPPublishModelDefinition navigates through the process and
//                     publish the symbol attributes to the SOAP Server
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZUSOAPPublishModelDefinition_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)
#define AFX_ZUSOAPPublishModelDefinition_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// JMR-MODIF - Le 21 juin 2006 - Ajout de l'en-tête ZBPublishMessengerModelInformation.h
#include "ZBPublishMessengerModelInformation.h"

#include "ZUProcessNavigation.h"

#include "zSOAP\PSS_SoapPublisher_Model.h"
#include "zProperty\ZIProperties.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration
class ZDProcessGraphModelDoc;
class ZBPublishMessengerModelInformation;

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 23 mai 2006 - Ajout des décortions unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZUSOAPPublishModelDefinition

class AFX_EXT_CLASS ZUSOAPPublishModelDefinition : public ZUProcessNavigation
{
public:

    // JMR-MODIF - Le 21 juin 2006 - Ajout de la variable pInfo dans le constructeur.
    ZUSOAPPublishModelDefinition( ZBPublishMessengerModelInformation*    pInfo,
                                  ZDProcessGraphModelMdl*                pModel    = NULL,
                                  void*                                    pClass    = NULL );

    virtual ~ZUSOAPPublishModelDefinition();

    // Call-back methods
    virtual bool OnStart                    ();
    virtual bool OnFinish                    ();
    virtual bool OnDoorSymbol                ( ZBBPDoorSymbol*            pSymbol );
    virtual bool OnPageSymbol                ( ZBBPPageSymbol*            pSymbol );
    virtual bool OnProcedureSymbol            ( ZBBPProcedureSymbol*        pSymbol );
    virtual bool OnProcessSymbol            ( ZBBPProcessSymbol*        pSymbol );
    virtual bool OnStartSymbol                ( ZBBPStartSymbol*            pSymbol );
    virtual bool OnStopSymbol                ( ZBBPStopSymbol*            pSymbol );
    virtual bool OnDeliverableLinkSymbol    ( ZBDeliverableLinkSymbol*    pSymbol );

private:

    // JMR-MODIF - Le 29 mai 2006 - Ajout de la fonction GetParentSymbolReference.
    int GetParentSymbolReference            ( ZBSymbol*                    pSymbol,
                                              int                        ParentID        = 0,
                                              ZDProcessGraphModelMdl*    pParentModel    = NULL );

    void PublishAttribDef                    ( int Ref, ZBPropertySet& PropSet );
    void PublishAttribDef                    ( int Ref, ZBProperty* pProp );

private:
    ZBPublishMessengerModelInformation* m_pInfo;
    PSS_SoapPublisher_Model             m_PubMdl;
    ZDProcessGraphModelDoc*             m_pDoc;
    CString                             m_MessengerAddress;
    int                                 m_CounterRow;
};

#endif // !defined(AFX_ZUSOAPPublishModelDefinition_H__1B1E078D_B371_4C96_8A00_A81D926A19E6__INCLUDED_)