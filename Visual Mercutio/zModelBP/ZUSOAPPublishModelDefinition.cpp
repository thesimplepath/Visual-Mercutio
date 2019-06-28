// ZUSOAPPublishModelDefinition.cpp: implementation of the ZUSOAPPublishModelDefinition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUSOAPPublishModelDefinition.h"

#include "ProcGraphModelMdlBP.h"

#include "zModel\ProcGraphModelDoc.h"

#include "ZBPublishMessengerModelInformation.h"
#include "zSOAP\pPublishSettings.h"

#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"

#include "ZBBPDoorSymbol.h"
#include "ZBBPPageSymbol.h"
#include "ZBBPProcedureSymbol.h"
#include "ZBBPProcessSymbol.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"
#include "ZBDeliverableLinkSymbol.h"

#include "zProperty\ZBDynamicPropertiesManager.h"
#include "ZBInputAttributes.h"
#include "ZBDistributionAttributes.h"

#include "zModel\ZUODSymbolManipulator.h"

// Include files for log
#include "zBaseLib\ZILog.h"
#include "zModel\ZBGenericSymbolErrorLine.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des d�corations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// JMR-MODIF - Le 21 juin 2006 - Ajout de la variable pInfo dans le constructeur.
ZUSOAPPublishModelDefinition::ZUSOAPPublishModelDefinition( ZBPublishMessengerModelInformation*    pInfo,
                                                            ZDProcessGraphModelMdl*                pModel /*= NULL*/,
                                                            void*                                pClass /*= NULL*/ )
    : m_pInfo                ( pInfo ),
      ZUProcessNavigation    ( pModel, pClass ),
      m_pDoc                ( NULL ),
      m_CounterRow            ( 0 )
{
    // JMR-MODIF - Le 21 juin 2006 - Ajout de l'alias dans la publication.
    m_pm.addAlias( m_pInfo->m_MessengerAlias );
}

ZUSOAPPublishModelDefinition::~ZUSOAPPublishModelDefinition()
{
}

// JMR-MODIF - Le 29 mai 2006 - Cette fonction permet d'obtenir l'ID du processus parent d'un symbole.
int ZUSOAPPublishModelDefinition::GetParentSymbolReference( ZBSymbol*                pSymbol,
                                                            int                        ParentID        /*= 0*/,
                                                            ZDProcessGraphModelMdl*    pParentModel    /*= NULL*/ )
{
    // Pas de mod�le parent, on part depuis la racine.
    if ( pParentModel == NULL )
    {
        pParentModel = dynamic_cast<ZDProcessGraphModelMdl*>( pSymbol->GetOwnerModel() )->GetRoot();
    }

    if ( pParentModel != NULL )
    {
        // Obtient l'ensemble des pages contenues dans le contr�leur de mod�les.
        ZBProcessGraphPageSet* pSet = pParentModel->GetPageSet();

        if ( pSet != NULL )
        {
            ZBProcessGraphPageIterator i( pSet );

            // On passe en revue toutes les pages enfants contenues dans le contr�leur de mod�les.
            for ( ZDProcessGraphPage* pPage = i.GetFirst(); pPage != NULL; pPage = i.GetNext() )
            {
                // Obtient le contr�leur de mod�le de la page courante.
                ZDProcessGraphModelMdlBP* m_CurModel = dynamic_cast<ZDProcessGraphModelMdlBP*>( pPage->GetpModel() );

                if ( m_CurModel != NULL )
                {
                    // Obtient l'ensemble des symboles contenus dans le contr�leur de mod�les.
                    CODComponentSet* pCompSet = m_CurModel->GetComponents();

                    if ( pCompSet != NULL )
                    {
                        // On passe en revue toutes les symboles contenus dans le contr�leur de mod�les.
                        for ( int j = 0; j < pCompSet->GetSize(); ++j )
                        {
                            CODComponent* pComponent = pCompSet->GetAt( j );

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un processus.
                            if ( pComponent && ISA( pComponent, ZBBPProcessSymbol ) )
                            {
                                // Convertit le symbole.
                                ZBBPProcessSymbol* m_Process = dynamic_cast<ZBBPProcessSymbol*>( pComponent );

                                // Obtient le contr�leur de mod�le du processus.
                                ZDProcessGraphModelMdlBP* m_ChildModel =
                                    dynamic_cast<ZDProcessGraphModelMdlBP*>( m_Process->GetpModel() );

                                // Recherche dans les symboles enfants si un symbole correspond au symbole envoy�.
                                int Result = GetParentSymbolReference( pSymbol,
                                                                       m_Process->GetSymbolReferenceNumber(),
                                                                       m_ChildModel );

                                // Retourne le r�sultat s'il a �t� trouv�.
                                if ( Result != 0 )
                                {
                                    return Result;
                                }
                            }

                            // Contr�le que le composant soit valide, et identifie s'il s'agit d'un symbole.
                            if ( pComponent && ISA( pComponent, ZBSymbol ) )
                            {
                                // Convertit le symbole.
                                ZBSymbol* m_Symbol = dynamic_cast<ZBSymbol*>( pComponent );

                                // Si le symbole trouv� est identique au symbole envoy�, retourne l'ID du parent.
                                if ( m_Symbol->GetSymbolReferenceNumber() == pSymbol->GetSymbolReferenceNumber() )
                                {
                                    return ParentID;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}

bool ZUSOAPPublishModelDefinition::OnStart()
{
    // Start by casting the document class pointer
    ZBPublishMessengerModelInformation* pInfo    = static_cast<ZBPublishMessengerModelInformation*>( m_pClass );
    m_pDoc                                        = pInfo->m_pDoc;
    m_MessengerAddress                            = pInfo->m_MessengerAddress;

    // Sets the correct address
    pPublishSettings::m_Url = (const char*)m_MessengerAddress;

    // Reset the counter for rows
    m_CounterRow = 0;

    if ( !m_pDoc )
    {
        return false;
    }

    m_pm.setModel( pmodel(PSS_String16( m_pModel->GetModelName() ),    // Model name
                          PSS_String16( m_pDoc->GetGUID() ),            // Model ref GUID
                          PSS_String16( pInfo->m_BeginDate ),            // JMR-MODIF - Date de validit� de d�but
                          PSS_String16( pInfo->m_EndDate ) ) );        // JMR-MODIF - Date de validit� de fin.

    // Nothing more to do
    return true;
}

bool ZUSOAPPublishModelDefinition::OnFinish()
{
    // Publish the input attributes
    if ( m_pDoc->GetModel() && ISA( m_pDoc->GetModel(), ZDProcessGraphModelMdlBP ) )
    {
        ZBInputAttributeManager* pInputAttrManager =
            dynamic_cast<ZDProcessGraphModelMdlBP*>( m_pDoc->GetModel() )->GetInputAttributes();

        if ( pInputAttrManager )
        {
            ZBInputAttributeIterator i( &pInputAttrManager->GetInputAttributeSet() );

            for ( ZBInputAttribute* pInputAttrib = i.GetFirst(); pInputAttrib; pInputAttrib = i.GetNext() )
            {
                short left    = pInputAttrib->GetCategoryID() & 0x0000FFFF;
                short right    = pInputAttrib->GetItemID() & 0x0000FFFF;
                int Key        = ( left << 16 ) | right;

                // Comment these lines since we have a problem
                // during the publication. It publishs two times the same
                // dynamic attribute and create a problem in Messenger for 
                // input attributes due to a select in the database, which gives
                // a result set containing two records.
                // 4 september 2002

                // Retreive the right property
                // ZBProperty* pProp = (m_pDoc->HasDynamicPropertiesManager()) ? m_pDoc->GetDynamicPropertiesManager()->GetPropertyItem( pInputAttrib->GetCategoryID(), pInputAttrib->GetItemID() ) : NULL;
                // and publish its definition
                // PublishAttribDef( pInputAttrib->GetSymbolRef(), pProp );

                if ( m_pLog && m_pLog->IsInDebugMode() )
                {
                    CString message;

                    message.Format( IDS_AL_PUBLISHINPUTATTRIBUTE,
                                    pInputAttrib->GetSymbolRef(),
                                    Key,
                                    (const char*)pInputAttrib->GetDefaultValue() );

                    ZBGenericSymbolErrorLine e( message );
                    m_pLog->AddLine( e );
                }

                m_pm.addInput( pinput(pInputAttrib->GetSymbolRef(),                // Object ID (proc or deliv) or -1 for global
                                      Key,                                            // Attrib def ID
                                      PSS_String16( pInputAttrib->GetDefaultValue() ),    // Default value
                                      pInputAttrib->GetFlag(),                        // Flag
                                     -1 ) );                                        // -1 (Reserved for future use)
            }
        }
    }

    // And publish the distribution attributes
    if ( m_pDoc->GetModel() &&
         ISA( m_pDoc->GetModel(), ZDProcessGraphModelMdlBP ) &&
         dynamic_cast<ZDProcessGraphModelMdlBP*>( m_pDoc->GetModel() )->HasDistributionAttributes() )
    {
        ZBDistributionAttributeManager* pDistribManager =
            dynamic_cast<ZDProcessGraphModelMdlBP*>( m_pDoc->GetModel() )->GetDistributionAttributes();

        if ( pDistribManager )
        {
            // Run through all distribution attribute
            ZBDistributionAttributeIterator i( &pDistribManager->GetDistributionAttributeSet() );

            for ( ZBDistributionAttribute* pAttrib = i.GetFirst(); pAttrib; pAttrib = i.GetNext() )
            {
                // Run through all roles
                ZBDistributionRulesForRoleIterator j( &pAttrib->GetDistributionRulesForRoleSet() );

                for ( ZBDistributionRulesForRole* pRole = j.GetFirst(); pRole; pRole = j.GetNext() )
                {
                    // Run through all rules
                    ZBDistributionRuleIterator k( &pRole->GetDistributionRuleSet() );

                    for ( ZBDistributionRule* pDistribRule = k.GetFirst(); pDistribRule; pDistribRule = k.GetNext() )
                    {
                        short left    = pAttrib->GetCategoryID() & 0x0000FFFF;
                        short right    = pAttrib->GetItemID() & 0x0000FFFF;
                        int Key        = ( left << 16 ) | right;

                        if ( m_pLog && m_pLog->IsInDebugMode() )
                        {
                            CString message;

                            message.Format( IDS_AL_PUBLISHDISTRIBATTRIBUTE,
                                            (const char*)pRole->GetRoleGUID(),
                                            Key,
                                            pDistribRule->GetOperator(),
                                            (const char*)pDistribRule->GetValue() );

                            ZBGenericSymbolErrorLine e( message );
                            m_pLog->AddLine( e );
                        }

                        // Change for Gaya 4 september 2002
                        // m_pm.addDistrib( pdistrib( String16( pAttrib->GetUserGroupGUID() ),

                        m_pm.addDistrib( pdistrib(PSS_String16( pRole->GetRoleGUID() ),            // WkgCls ID
                                                  Key,                                            // Attrib Def ID
                                                  pDistribRule->GetOperator(),                    // Operator ID
                                                  PSS_String16( pDistribRule->GetValue() ) ) );    // Data

                        if ( m_pLog && m_pLog->IsInDebugMode() )
                        {
                            CString message;

                            message.Format( IDS_AL_PUBLISHDISTRIBATTRIBUTEMAP,
                                            pAttrib->GetSymbolRef(),
                                            Key,
                                            (const char*)pDistribRule->GetValue(),
                                            pDistribRule->GetLogicalOperator() );

                            ZBGenericSymbolErrorLine e( message );
                            m_pLog->AddLine( e );
                        }

                        m_pm.addDistribmap( pdistribmap( pAttrib->GetSymbolRef(),                    // Object ID
                                                         Key,                                        // Attrib Def ID
                                                         PSS_String16( pDistribRule->GetValue() ),        // Data
                                                         pDistribRule->GetLogicalOperator() ) );    // Logical operator (0=AND 1=OR)
                    }
                }
            }
        }
    }
 
    // Send it to the soap server
    return m_pm.send();
}

bool ZUSOAPPublishModelDefinition::OnDoorSymbol( ZBBPDoorSymbol* pSymbol )
{
    return true;
}

bool ZUSOAPPublishModelDefinition::OnPageSymbol( ZBBPPageSymbol* pSymbol )
{
    return true;
}

bool ZUSOAPPublishModelDefinition::OnProcedureSymbol( ZBBPProcedureSymbol* pSymbol )
{
    // JMR-MODIF - Le 30 mai 2006 - Ajout du param�tre procidprocessus. (Param�tre 5)
    m_pm.addProc( pproc(pSymbol->GetSymbolReferenceNumber(),        // Object ID (Unique between proc/deliv)
                        PSS_String16( pSymbol->GetUnitGUID() ),        // Workgroup ClsID
                        2,                                         // 2 = procedure symbol
                        pSymbol->GetUnitDoubleValidationType(),    // Double Sign
                        GetParentSymbolReference( pSymbol ) ) );    // Processus parent

    ZBPropertySet PropSet;

    // Retrieve the property set from object
    pSymbol->FillProperties( PropSet, true, true );

    // Add the attributes to the pPublishAttribDef class
    PublishAttribDef( pSymbol->GetSymbolReferenceNumber(), PropSet );

    // Remove all properties
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    PropSet.RemoveAll();

    return true;
}

bool ZUSOAPPublishModelDefinition::OnProcessSymbol( ZBBPProcessSymbol* pSymbol )
{
    // ***********************************************************************************************************
    // JMR-MODIF - Le 28 mars 2006 - Ajout de la publication des processus vers Messenger.

    m_pm.addProc( pproc( pSymbol->GetSymbolReferenceNumber(),    // Object ID (Unique between proc/deliv)
                         _T( "" ),                                // Aucun GUID publi� pour les proc�dures.
                         4,                                     // 4 = process symbol
                         0,                                        // Double Sign
                         0 ) );                                    // Processus parent

    ZBPropertySet PropSet;

    // Retrieve the property set from object
    pSymbol->FillProperties( PropSet, true, true );

    // Add the attributes to the pPublishAttribDef class
    PublishAttribDef( pSymbol->GetSymbolReferenceNumber(), PropSet );

    // Remove all properties
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    PropSet.RemoveAll();
    // ***********************************************************************************************************

    return true;
}

bool ZUSOAPPublishModelDefinition::OnStartSymbol( ZBBPStartSymbol* pSymbol )
{
    // JMR-MODIF - Le 30 mai 2006 - Ajout du param�tre procidprocessus. (Param�tre 5)
    m_pm.addProc( pproc(pSymbol->GetSymbolReferenceNumber(),        // Object ID (unique between proc/deliv)
                        PSS_String16( pSymbol->GetUnitGUID() ),        // Workgroup ClsID
                        0,                                         // 0 = start symbol
                        0,                                            // Double Sign
                        GetParentSymbolReference( pSymbol ) ) );    // Processus parent

    ZBPropertySet PropSet;

    // Retrieve the property set from object
    pSymbol->FillProperties( PropSet, true, true );

    // Add the attributes to the pPublishAttribDef class
    PublishAttribDef( pSymbol->GetSymbolReferenceNumber(), PropSet );

    // Remove all properties
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    PropSet.RemoveAll();

    return true;
}

bool ZUSOAPPublishModelDefinition::OnStopSymbol( ZBBPStopSymbol* pSymbol )
{
    // JMR-MODIF - Le 30 mai 2006 - Ajout du param�tre procidprocessus. (Param�tre 5)
    m_pm.addProc( pproc(pSymbol->GetSymbolReferenceNumber(),        // Object ID (unique between proc/deliv)
                        PSS_String16( pSymbol->GetUnitGUID() ),        // Workgroup ClsID
                        1,                                         // 1 = stop symbol
                        0,                                            // Double Sign
                        GetParentSymbolReference( pSymbol ) ) );    // Processus parent

    ZBPropertySet PropSet;

    // Retrieve the property set from object
    pSymbol->FillProperties( PropSet, true, true );

    // Add the attributes to the pPublishAttribDef class
    PublishAttribDef( pSymbol->GetSymbolReferenceNumber(), PropSet );

    // Remove all properties
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    PropSet.RemoveAll();

    return true;
}

bool ZUSOAPPublishModelDefinition::OnDeliverableLinkSymbol( ZBDeliverableLinkSymbol* pSymbol )
{
    CODSymbolComponent* pSrc = pSymbol->GetEnteringSymbol();
    CODSymbolComponent* pDst = pSymbol->GetFollowingSymbol();

    // If not connected correctly, skip it
    if ( !pSrc || !ISA( pSrc, ZBSymbol ) || !pDst || !ISA( pDst, ZBSymbol ) )
    {
        return true;
    }

    // Now check if the source or the destination symbol is
    // a door or a page.

    // When a source symbol is a door or a page
    if ( ISA( pSrc, ZBBPDoorSymbol ) || ISA( pSrc, ZBBPPageSymbol ) )
    {
        // If the deliverable is a reference, skip it
        if ( !pSymbol->IsLocal() )
        {
            return true;
        }

        // Now replace the source symbol by the symbol after the page or the door
        if ( ISA( pSrc, ZBBPDoorSymbol ) )
        {
            ZBBPDoorSymbol* pTwinDoor = dynamic_cast<ZBBPDoorSymbol*>( pSrc )->GetTwinDoorSymbol();

            if ( !pTwinDoor )
            {
                return true;
            }

            CODNodeArray FollowingNodes;
            pTwinDoor->GetEnteringSymbols_Up( FollowingNodes );

            size_t FollowingSymbolCount =
                ZUODSymbolManipulator::KeepOnlySymbolsISA( FollowingNodes, RUNTIME_CLASS( ZBSymbol ) );

            if ( FollowingSymbolCount == 0 )
            {
                return true;
            }

            ASSERT( FollowingNodes.GetSize() > 0 );
            IODNode* pINode = FollowingNodes.GetAt( 0 );
            pSrc = static_cast<CODSymbolComponent*>( pINode );
        }
        else
        {
            ZBBPPageSymbol* pTwinPage = dynamic_cast<ZBBPPageSymbol*>( pSrc )->GetTwinPageSymbol();

            if ( !pTwinPage )
            {
                return true;
            }

            CODNodeArray FollowingNodes;
            pTwinPage->GetEnteringSymbols_Up( FollowingNodes );

            size_t FollowingSymbolCount =
                ZUODSymbolManipulator::KeepOnlySymbolsISA( FollowingNodes, RUNTIME_CLASS( ZBSymbol ) );

            if ( FollowingSymbolCount == 0 )
            {
                return true;
            }

            ASSERT( FollowingNodes.GetSize() > 0 );
            IODNode* pINode = FollowingNodes.GetAt( 0 );
            pSrc = static_cast<CODSymbolComponent*>(pINode);
        }
    }

    // When a destination symbol is a door or a page
    if ( ISA( pDst, ZBBPDoorSymbol ) || ISA( pDst, ZBBPPageSymbol ) )
    {
        // If the deliverable is a reference, skip it
        if ( !pSymbol->IsLocal() )
        {
            return true;
        }

        // Now replace the destination symbol by the symbol after the page or the door
        if ( ISA( pDst, ZBBPDoorSymbol ) )
        {
            ZBBPDoorSymbol* pTwinDoor = dynamic_cast<ZBBPDoorSymbol*>( pDst )->GetTwinDoorSymbol();

            if ( !pTwinDoor )
            {
                return true;
            }

            CODNodeArray FollowingNodes;
            pTwinDoor->GetFollowingSymbols_Down( FollowingNodes );

            size_t FollowingSymbolCount =
                ZUODSymbolManipulator::KeepOnlySymbolsISA( FollowingNodes, RUNTIME_CLASS( ZBSymbol ) );

            if ( FollowingSymbolCount == 0 )
            {
                return true;
            }

            ASSERT( FollowingNodes.GetSize() > 0 );
            IODNode* pINode = FollowingNodes.GetAt( 0 );
            pDst = static_cast<CODSymbolComponent*>( pINode );
        }
        else
        {
            ZBBPPageSymbol* pTwinPage = dynamic_cast<ZBBPPageSymbol*>( pDst )->GetTwinPageSymbol();

            if ( !pTwinPage )
            {
                return true;
            }

            CODNodeArray FollowingNodes;
            pTwinPage->GetFollowingSymbols_Down( FollowingNodes );

            size_t FollowingSymbolCount =
                ZUODSymbolManipulator::KeepOnlySymbolsISA( FollowingNodes, RUNTIME_CLASS( ZBSymbol ) );

            if ( FollowingSymbolCount == 0 )
            {
                return true;
            }

            ASSERT( FollowingNodes.GetSize() > 0 );
            IODNode* pINode = FollowingNodes.GetAt( 0 );
            pDst = static_cast<CODSymbolComponent*>( pINode );
        }
    }

    // To know if it is lateral deliverable
    // From the source, check if the deliverable is defined
    bool Lateral            = false;
    int  LateralDirection    = 0;

    // Retreiving right edges
    CODEdgeArray LeavingRightEdges;
    size_t LeavingRightLinkCount = dynamic_cast<ZBSymbol*>( pSrc )->GetEdgesLeaving_Right( LeavingRightEdges );

    if ( LeavingRightLinkCount > 0 )
    {
        for ( size_t nEdgeIdx = 0; nEdgeIdx < LeavingRightLinkCount; ++nEdgeIdx )
        {
            IODEdge* pIEdge = LeavingRightEdges.GetAt( nEdgeIdx );

            // Check if a ZBLinkSymbol
            if ( !static_cast<CODLinkComponent*>( pIEdge ) ||
                 !ISA( static_cast<CODLinkComponent*>( pIEdge ), ZBDeliverableLinkSymbol ) )
            {
                continue;
            }

            ZBDeliverableLinkSymbol* pLink = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

            if ( !pLink )
            {
                continue;
            }

            if ( pLink->GetSymbolName() == pSymbol->GetSymbolName() )
            {
                Lateral                = true;
                LateralDirection    = 1;    // right
                break;
            }
        }
    }

    // Retreiving left edges
    CODEdgeArray LeavingLeftEdges;
    size_t LeavingLeftLinkCount = dynamic_cast<ZBSymbol*>( pSrc )->GetEdgesLeaving_Left( LeavingLeftEdges );

    if ( LeavingLeftLinkCount > 0 && Lateral == false )
    {
        for ( size_t nEdgeIdx = 0; nEdgeIdx < LeavingLeftLinkCount; ++nEdgeIdx )
        {
            IODEdge* pIEdge = LeavingLeftEdges.GetAt( nEdgeIdx );

            // Check if a ZBLinkSymbol
            if ( !static_cast<CODLinkComponent*>( pIEdge ) ||
                 !ISA(static_cast<CODLinkComponent*>( pIEdge ), ZBDeliverableLinkSymbol ) )
            {
                continue;
            }

            ZBDeliverableLinkSymbol* pLink = static_cast<ZBDeliverableLinkSymbol*>( pIEdge );

            if ( !pLink )
            {
                continue;
            }

            if ( pLink->GetSymbolName() == pSymbol->GetSymbolName() )
            {
                Lateral                = true;
                LateralDirection    = 3;    // left
                break;
            }
        }
    }

    m_pm.addDeliv( pdeliv( pSymbol->GetSymbolReferenceNumber(),                            // Object ID (unique between proc/deliv)
                           dynamic_cast<ZBSymbol*>(pSrc)->GetSymbolReferenceNumber(),    // Src proc
                           dynamic_cast<ZBSymbol*>(pDst)->GetSymbolReferenceNumber(),    // Trg proc
                           PSS_String16(pSymbol->GetSymbolName()),                            // Deliv name
                           (Lateral == true) ? 1 : 0,                                    // Lateral direction : 0 = normal, 1 = lateral starts here
                           LateralDirection,                                            // 0 : top, 1 : right, 2 : bottom, 3 : left
                           pSymbol->GetUnitDoubleValidationType()));                    // Double Sign

    ZBPropertySet PropSet;

    // Retrieve the property set from object
    pSymbol->FillProperties( PropSet, true, true );

    // Add the attributes to the pPublishAttribDef class
    PublishAttribDef( pSymbol->GetSymbolReferenceNumber(), PropSet );

    // Remove all properties
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    PropSet.RemoveAll();

    return true;
}

void ZUSOAPPublishModelDefinition::PublishAttribDef( int Ref, ZBPropertySet& PropSet )
{
    // Remove all properties
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        PublishAttribDef( Ref, pProp );
    }
}

void ZUSOAPPublishModelDefinition::PublishAttribDef( int Ref, ZBProperty* pProp )
{
    if ( pProp )
    {
        short left    = pProp->GetCategoryID() & 0x0000FFFF;
        short right    = pProp->GetItemID() & 0x0000FFFF;
        int Key        = ( left << 16 ) | right;

        CString s;

        switch ( pProp->GetPTValueType() )
        {
            case ZBProperty::PT_DOUBLE:
            {
                s.Format( _T( "%g" ), pProp->GetValueDouble() );
                break;
            }

            case ZBProperty::PT_FLOAT:
            {
                s.Format( _T( "%f" ), pProp->GetValueFloat() );
                break;
            }

            case ZBProperty::PT_DATE:
            {
                s = pProp->GetValueDate().GetStandardFormatedDate();
                break;
            }

            case ZBProperty::PT_TIMESPAN:
            {
                s = pProp->GetValueTimeSpan().GetStandardFormatedTimeSpan();
                break;
            }

            case ZBProperty::PT_DURATION:
            {
                s.Format( _T( "%f" ), (double)pProp->GetValueDuration() );
                break;
            }

            case ZBProperty::PT_UNKNOWN:
            case ZBProperty::PT_STRING:
            default:
            {
                s = pProp->GetValueString();
                break;
            }
        }
        
        if ( m_pLog && m_pLog->IsInDebugMode() )
        {
            CString message;
            message.Format( IDS_AL_PUBLISHSYMBOLATTRIBUTE,
                            Ref,
                            Key,
                            (const char*)s,
                            ( pProp->IsDynamic() ) ? 0 : 1 );

            ZBGenericSymbolErrorLine e( message );
            m_pLog->AddLine( e );
        }

        m_pm.addAttr( ppdattr( Ref,                                    // Object ref ID (either a proc or deliv)
                               m_CounterRow++,                        // Row number
                               Key,                                    // Ref on attribute definition table
                               PSS_String16( s ),                        // Value
                               ( pProp->IsDynamic() ) ? 0 : 1 ) );
    }
}
