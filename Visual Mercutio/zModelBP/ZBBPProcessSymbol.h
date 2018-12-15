// ZBBPProcessSymbol.h: interface for the ZBBPProcessSymbol class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBBPPROCESSSYMBOL_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPPROCESSSYMBOL_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

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

#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ZBSymbol.h"

#include "ZBBPSimPropProcess.h"

// JMR-MODIF - Le 26 janvier 2006 - Ajout de l'en-tête ZBBPPrestationsProperties.
#include "ZBBPPrestationsProperties.h"

// JMR-MODIF - Le 6 février 2006 - Ajout de l'en-tête ZBProcDeliveries.
#include "ZBProcDeliveries.h"

// JMR-MODIF - Le 17 février 2006 - Déplacé le header ProcGraphModelMdlBP.h du fichier .cpp vers le fichier .h
#include "ProcGraphModelMdlBP.h"

// JMR-MODIF - Le 19 novembre 2006 - Ajout de l'en-tête ZBLogicalRulesEntity.h
#include "zModel\ZBLogicalRulesEntity.h"

// JMR-MODIF - Le 18 décembre 2006 - Ajout de l'en-tête ZBProcRules.h
#include "ZBProcRules.h"

// JMR-MODIF - Le 18 décembre 2006 - Ajout de l'en-tête ZBBPRulesProp.h
#include "ZBBPRulesProp.h"

// JMR-MODIF - Le 3 juin 2007 - Ajout de l'en-tête ZBProcRisk.h
#include "ZBProcRisk.h"

// JMR-MODIF - Le 3 juin 2007 - Ajout de l'en-tête ZBBPRiskProp.h
#include "ZBBPRiskProp.h"

// JMR-MODIF - Le 8 juillet 2007 - Ajout de l'en-tête ZBMediator.
#include "zMediator\ZBMediator.h"

// JMR-MODIF - Le 8 juillet 2007 - Ajout de l'en-tête ZVRiskTypeContainer.
#include "ZVRiskTypeContainer.h"

// JMR-MODIF - Le 11 juillet 2007 - Ajout de l'en-tête ZVRiskImpactContainer.
#include "ZVRiskImpactContainer.h"

// JMR-MODIF - Le 11 juillet 2007 - Ajout de l'en-tête ZVRiskProbabilityContainer.
#include "ZVRiskProbabilityContainer.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 26 septembre 2005 - Ajout de la décoration unicode _T( ), nettoyage du code inutilisé.

class AFX_EXT_CLASS ZBBPProcessSymbol : public ZBSymbol
{
    DECLARE_SERIAL( ZBBPProcessSymbol )

public:

    ZBBPProcessSymbol( const CString Name = _T( "" ) );
    virtual ~ZBBPProcessSymbol();

    /* Copy constructor. */
    ZBBPProcessSymbol( const ZBBPProcessSymbol& src );

    /* Assignment operator. */
    ZBBPProcessSymbol& operator=( const ZBBPProcessSymbol& src );

    /* Create a duplicate copy of this object. */
    virtual CODComponent* Dup() const;

    // Return the unique object type ID
    virtual int GetObjectTypeID() const
    {
        return 3;
    }

    // Copy the definition only
    virtual void CopySymbolDefinitionFrom( CODSymbolComponent& src );

    // Overloaded to be able to modify the activity name
    // and description
    virtual BOOL SetSymbolName( const CString value );

    // Return true if the symbol can contain a child model
    virtual bool CanContainChildModel() const
    {
        return true;
    }

    // Call when a new symbol is created
    virtual bool CreateSymbolProperties();

    // Call to retreive properties for the object
    virtual bool FillProperties( ZBPropertySet& PropSet, bool NumericValue = false, bool GroupValue = false );

    // Call to save new changes to object's properties
    virtual bool SaveProperties( ZBPropertySet& PropSet );

    // JMR-MODIF - Le 15 février 2006 - Ajout de la fonction SaveProperty.
    bool SaveProperty( ZBProperty& Property );

    // JMR-MODIF - Le 15 février 2006 - Ajout de la fonction OnPostPropertyChanged.
    bool OnPostPropertyChanged( ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh );

    //////////////////////////////////////////////////////////////////////
    // Attributes management methods
    virtual bool OnFillDefaultAttributes( ZBPropertyAttributes* pAttributes );
    virtual bool OnChangeAttributes( ZBPropertyAttributes* pAttributes );
    virtual CString GetAttributeString( ZBPropertyAttributes* pAttributes ) const;

    // Call by the controller when a tooltip is required
    virtual bool OnToolTip( CString& ToolTipText, CPoint point, ToolTipMode ToolTip = NormalToolTip );

    // Drag and drop methods
    virtual bool AcceptDropItem( CObject* pObj, CPoint pt );
    virtual bool DropItem( CObject* pObj, CPoint pt );

    /* Creates the symbol component. */
    BOOL Create( const CString Name = _T( "" ) );

    /* Called after the object is created and on the desk 
       return true if the object can be created or false if the
       object must be destroyed immediatly */
    virtual bool OnPostCreation( CODModel* pModel = NULL, CODController* pCtrl = NULL );

    bool GetDisplayPreview() const
    {
        return m_DisplayPreview;
    }

    void SetDisplayPreview( bool value )
    {
        m_DisplayPreview = value;
    }

    //////////////////////////////////////////////////////////////////////
    // Area state methods
    virtual bool IncludeDescriptionArea() const
    {
        // We would like to offer the description area
        return true;
    }

    virtual bool IncludeAttributeArea() const
    {
        // We would like to offer the attribute area
        return true;
    }

    virtual bool CreateWorkflowActivity( bool DefaultProp = true );
    virtual bool SetDefaultPropertyToWorkflowActivity();

    virtual void OnDraw( CDC* pDC );

    ULONG STDMETHODCALLTYPE AddRef()
    {
        return CODSymbolComponent::AddRef();
    }

    ULONG STDMETHODCALLTYPE Release()
    {
        return CODSymbolComponent::Release();
    }

    // JMR-MODIF - Le 5 avril 2006 - Fonction permettant de définir si le symbole est un processus.
    virtual BOOL IsProcess()
    {
        return TRUE;
    }

    // Creation of a new child model
    virtual BOOL CreateEmptyChildModel( CODModel* pParent );

    /* Serializes the symbol. */
    virtual void Serialize( CArchive& ar );

    virtual int GetRightSubMenu() const;
    virtual int GetIconIndex() const;

    virtual BOOL OnDoubleClick();

    //@cmember
    /* Gets the process workload forecast. */
    ZBBPAnnualNumberProperties& GetProcessWorkloadForecast();

    //@cmember
    /* Sets the process workload forecast. */
    void SetProcessWorkloadForecast( const double value );
    void SetProcessWorkloadForecast( ZBBPAnnualNumberProperties& AnnualNumberProp );

    //@cmember
    /* Gets the process cost forecast. */
    ZBBPAnnualNumberProperties& GetProcessCostForecast();

    //@cmember
    /* Sets the process cost forecast. */
    void SetProcessCostForecast( const double value );
    void SetProcessCostForecast( ZBBPAnnualNumberProperties& AnnualNumberProp );

    // JMR-MODIF - Le 14 mars 2006 - Ajout de la fonction GetProcessCost pour la prise en charge des coûts HMO.
    ZBBPAnnualNumberProperties& GetProcessCost();

    // JMR-MODIF - Le 14 mars 2006 - Ajout de la fonction SetProcessCost pour la prise en charge des coûts HMO.
    void SetProcessCost( const double value );
    void SetProcessCost( ZBBPAnnualNumberProperties& AnnualNumberProp );

    // ************************************************************************************************************
    // JMR-MODIF - Le 20 février 2006 - Ajout des fonctions cadres propres aux prestations.
    virtual bool HasPrestations() const
    {
        return true;
    }

    virtual ZBTokenizer GetPrestationsList();

    void OnDelCurrentPrestation( ZBProperty&    Property,
                                 CString&        value,
                                 ZBPropertySet&    Properties,
                                 bool&            Refresh );
    // ************************************************************************************************************

    // ************************************************************************************************************
    // JMR-MODIF - Le 3 juin 2007 - Ajout des fonctions nécessaires à la gestion des risques.

    // Obtient le nombre de risques contenus dans le gestionnaire de risques.
    int GetRiskCount() const
    {
        return m_Risks.GetRiskCount();
    }

    // Obtient le nom du risque, en spécifiant son index.
    CString GetRiskName( size_t Index ) const
    {
        return m_Risks.GetRiskName( Index );
    }

    // Inscrit le nom du risque, en spécifiant son index.
    void SetRiskName( size_t Index, CString Value )
    {
        m_Risks.SetRiskName( Index, Value );
    }

    // Obtient la description du risque, en spécifiant son index.
    CString GetRiskDesc( size_t Index ) const
    {
        return m_Risks.GetRiskDesc( Index );
    }

    // Inscrit la description du risque, en spécifiant son index.
    void SetRiskDesc( size_t Index, CString Value )
    {
        m_Risks.SetRiskDesc( Index, Value );
    }

    // Obtient le type du risque, en spécifiant son index.
    CString GetRiskType( size_t Index ) const
    {
        int        Count        = ZBMediator::Instance()->GetMainApp()->GetRiskTypeContainer()->GetElementCount();
        CString    s_RiskType    = m_Risks.GetRiskType( Index );

        for ( int i = 0; i < Count; i++ )
        {
            if ( s_RiskType == ZBMediator::Instance()->GetMainApp()->GetRiskTypeContainer()->GetElementAt( i ) )
            {
                return m_Risks.GetRiskType( Index );
            }
        }

        return _T( "" );
    }

    // Inscrit le type du risque, en spécifiant son index.
    void SetRiskType( size_t Index, CString Value )
    {
        m_Risks.SetRiskType( Index, Value );
    }

    // Obtient l'impact du risque, en spécifiant son index.
    int GetRiskImpact( size_t Index ) const
    {
        return m_Risks.GetRiskImpact( Index );
    }

    // Inscrit l'impact du risque, en spécifiant son index.
    void SetRiskImpact( size_t Index, int Value )
    {
        m_Risks.SetRiskImpact( Index, Value );
    }

    // Obtient la probabilité du risque, en spécifiant son index.
    int GetRiskProbability( size_t Index ) const
    {
        return m_Risks.GetRiskProbability( Index );
    }

    // Inscrit la probabilité du risque, en spécifiant son index.
    void SetRiskProbability( size_t Index, int Value )
    {
        m_Risks.SetRiskProbability( Index, Value );
    }

    // Obtient la sévérité du risque, en spécifiant son index.
    int GetRiskSeverity( size_t Index ) const
    {
        return m_Risks.GetRiskSeverity( Index );
    }

    // Inscrit la sévérité du risque, en spécifiant son index.
    void SetRiskSeverity( size_t Index, int Value )
    {
        m_Risks.SetRiskSeverity( Index, Value );
    }

    // Obtient l'estimation unitaire du risque, en spécifiant son index.
    float GetRiskUE( size_t Index ) const
    {
        return m_Risks.GetRiskUE( Index );
    }

    // Inscrit l'estimation unitaire du risque, en spécifiant son index.
    void SetRiskUE( size_t Index, float Value )
    {
        m_Risks.SetRiskUE( Index, Value );
    }

    // Obtient la perte operationnelle annuelle du risque, en spécifiant son index.
    float GetRiskPOA( size_t Index ) const
    {
        return m_Risks.GetRiskPOA( Index );
    }

    // Inscrit la perte operationnelle annuelle du risque, en spécifiant son index.
    void SetRiskPOA( size_t Index, float Value )
    {
        m_Risks.SetRiskPOA( Index, Value );
    }

    // Obtient l'action du risque, en spécifiant son index.
    bool GetRiskAction( size_t Index ) const
    {
        return m_Risks.GetRiskAction( Index );
    }

    // Inscrit l'action du risque, en spécifiant son index.
    void SetRiskAction( size_t Index, bool Value )
    {
        m_Risks.SetRiskAction( Index, Value );
    }
    // ************************************************************************************************************

    // ************************************************************************************************************
    // JMR-MODIF - Le 6 février 2006 - Ajout des fonctions nécessaires à la gestion des livraisons.

    void OnDeliverableNameChange( CString OldName, CString NewName );

    ZBProcDeliveries& GetDeliveries()
    {
        return m_Deliveries;
    }

    int GetDeliveriesCount() const
    {
        return m_Deliveries.GetDeliveriesCount();
    }

    ZBBPDeliveriesProperties* GetDeliveryProperty( size_t Index ) const
    {
        return m_Deliveries.GetProperty( Index );
    }

    CString GetDeliveryName( size_t Index ) const
    {
        return m_Deliveries.GetDeliveryName( Index );
    }

    void SetDeliveryName( size_t Index, CString Value )
    {
        m_Deliveries.SetDeliveryName( Index, Value );
    }

    CString GetDeliveryDeliverables( size_t Index ) const
    {
        return m_Deliveries.GetDeliveryDeliverables( Index );
    }

    void SetDeliveryDeliverables( size_t Index, CString Value )
    {
        m_Deliveries.SetDeliveryDeliverables( Index, Value );
    }

    bool AddDeliveryDeliverable( size_t Index, CString Value )
    {
        return m_Deliveries.AddDeliveryDeliverable( Index, Value );
    }

    bool RemoveDeliveryDeliverable( size_t Index, CString Value )
    {
        return m_Deliveries.RemoveDeliveryDeliverable( Index, Value );
    }

    bool RemoveAllDeliveryDeliverable( size_t Index )
    {
        return m_Deliveries.RemoveAllDeliveryDeliverable( Index );
    }

    float GetDeliveryQuantity( size_t Index ) const
    {
        return m_Deliveries.GetDeliveryQuantity( Index );
    }

    void SetDeliveryQuantity( size_t Index, const float value )
    {
        m_Deliveries.SetDeliveryQuantity( Index, value );
    }

    float GetDeliveryPercentage( size_t Index ) const
    {
        return m_Deliveries.GetDeliveryPercentage( Index );
    }

    void SetDeliveryPercentage( size_t Index, const float value )
    {
        m_Deliveries.SetDeliveryPercentage( Index, value );
    }

    CString GetDeliveryMain( size_t Index ) const
    {
        return m_Deliveries.GetDeliveryMain( Index );
    }

    void SetDeliveryMain( size_t Index, CString Value )
    {
        m_Deliveries.SetDeliveryMain( Index, Value );
    }
    // ************************************************************************************************************

    bool ProcessExtendedInput( ZBProperty&        Property,
                               CString&            value,
                               ZBPropertySet&    Properties,
                               bool&            Refresh );

    bool ProcessMenuCommand( int            MenuCommand,
                             ZBProperty&    Property,
                             CString&        value,
                             ZBPropertySet&    Properties,
                             bool&            Refresh );

    // JMR-MODIF - Le 18 décembre 2006 - Ajout de la fonction OnDropInternalPropertyItem.
    virtual bool OnDropInternalPropertyItem( ZBProperty&    SrcProperty,
                                             ZBProperty&    DstProperty,
                                             bool            Top2Down,
                                             ZBPropertySet&    Properties );

    // JMR-MODIF - Le 26 avril 2007 - Ajout de la fonction ContainsRule.
    BOOL ContainsRule( CString RuleName );

    // JMR-MODIF - Le 9 octobre 2007 - Ajout de la fonction CheckRulesSync.
    void CheckRulesSync( CStringArray& RulesList );

protected:

    virtual void AdjustElementPosition();

private:

    // ************************************************************************************************************
    // JMR-MODIF - Le 10 juin 2007 - Ajout des fonctions nécesaires à la gestion des risques.

    void OnAddNewRisk( ZBProperty&        Property,
                       CString&            value,
                       ZBPropertySet&    Properties,
                       bool&            Refresh );

    void OnDelCurrentRisk( ZBProperty&        Property,
                           CString&            value,
                           ZBPropertySet&    Properties,
                           bool&            Refresh );

    int AddNewRisk()
    {
        return m_Risks.AddNewRisk();
    }

    bool DeleteRisk( size_t Index )
    {
        return m_Risks.DeleteRisk( Index );
    }
    // ************************************************************************************************************

    // ************************************************************************************************************
    // JMR-MODIF - Le 10 février 2006 - Ajout des fonctions nécessaires à la gestion des livraisons.

    void OnAddNewDelivery( ZBProperty&        Property,
                           CString&            value,
                           ZBPropertySet&    Properties,
                           bool&            Refresh );

    void OnDelCurrentDelivery( ZBProperty&        Property,
                               CString&            value,
                               ZBPropertySet&    Properties,
                               bool&            Refresh );

    int AddNewDelivery()
    {
        return m_Deliveries.AddNewDelivery();
    }

    bool DeleteDelivery( size_t Index )
    {
        return m_Deliveries.DeleteDelivery( Index );
    }

    CString GetPossibleListOfMainDeliverables( ZBPropertySet& PropSet, int nCatID );
    CString GetAvailableDeliverables( ZBPropertySet& PropSet );
    CString CheckMainDeliverable( int Index );
    CString CheckDeliverables( int Index );

    void UpdateValuesForThisDeliveryProperty( size_t Index );

    int GetDeliverablesInChildPages( CString& DeliverablesList );

    float FindQuantity( const CString Main, ZDProcessGraphModelMdlBP* m_RootModel = NULL );

    float CalculateDeliveryPercentage( float Quantity )
    {
        float m_SumOfDeliveries = CalculateSumOfDeliveries();

        if ( m_SumOfDeliveries == 0.0f )
        {
            return 0.0f;
        }

        return ( Quantity / m_SumOfDeliveries );
    }

    float CalculateSumOfDeliveries()
    {
        float m_SumOfDeliveries = 0.0f;

        for ( int i = 0; i < GetDeliveriesCount(); i++ )
        {
            m_SumOfDeliveries += GetDeliveryQuantity( i );
        }

        return m_SumOfDeliveries;
    }
    // ************************************************************************************************************

    // JMR-MODIF - Le 25 décembre 2006 - Ajout de la fonction GetRuleNameByGUID.
    CString GetRuleNameByGUID( ZBLogicalRulesEntity* p_Rule, CString RuleGUID );

private:

    CRect                        m_CommentRect;

    // JMR-MODIF - Le 16 février 2006 - Ajout de la variable m_IsUserModified.
    bool                        m_IsUserModified;
    bool                        m_DisplayPreview;

    // JMR-MODIF - Le 26 janvier 2006 - Ajout de la variable pour la gestion des propriétés des prestations
    ZBBPPrestationsProperties    m_PrestProperties;
    ZBBPSimPropertiesProcess    m_SimProperties;

    // JMR-MODIF - Le 6 février 2006 - Ajout de la variable m_Deliveries, pour la gestion des livraisons.
    ZBProcDeliveries            m_Deliveries;

    // JMR-MODIF - Le 18 décembre 2006 - Ajout de la variable m_Rules
    ZBProcRules                    m_Rules;

    // JMR-MODIF - Le 3 juin 2007 - Ajout de la variable m_Risks
    ZBProcRisk                    m_Risks;
};

inline ZBBPAnnualNumberProperties& ZBBPProcessSymbol::GetProcessWorkloadForecast()
{
    return m_SimProperties.GetProcessWorkloadForecast();
}

inline void ZBBPProcessSymbol::SetProcessWorkloadForecast( const double value )
{
    m_SimProperties.SetProcessWorkloadForecast( value );
}

inline void ZBBPProcessSymbol::SetProcessWorkloadForecast( ZBBPAnnualNumberProperties& AnnualNumberProp )
{
    m_SimProperties.GetProcessWorkloadForecast() = AnnualNumberProp;
}

inline ZBBPAnnualNumberProperties& ZBBPProcessSymbol::GetProcessCostForecast()
{
    return m_SimProperties.GetProcessCostForecast();
}

inline void ZBBPProcessSymbol::SetProcessCostForecast( const double value )
{
    m_SimProperties.SetProcessCostForecast( value );
}

inline void ZBBPProcessSymbol::SetProcessCostForecast( ZBBPAnnualNumberProperties& AnnualNumberProp )
{
    m_SimProperties.GetProcessCostForecast() = AnnualNumberProp;
}

// JMR-MODIF - Le 14 mars 2006 - Ajout de la fonction GetProcessCost pour la prise en charge des coûts HMO.
inline ZBBPAnnualNumberProperties& ZBBPProcessSymbol::GetProcessCost()
{
    return m_SimProperties.GetProcessCost();
}

// JMR-MODIF - Le 14 mars 2006 - Ajout de la fonction SetProcessCost pour la prise en charge des coûts HMO.
inline void ZBBPProcessSymbol::SetProcessCost( const double value )
{
    m_SimProperties.SetProcessCost( value );
}

// JMR-MODIF - Le 14 mars 2006 - Ajout de la fonction SetProcessCost pour la prise en charge des coûts HMO.
inline void ZBBPProcessSymbol::SetProcessCost( ZBBPAnnualNumberProperties& AnnualNumberProp )
{
    m_SimProperties.GetProcessCost() = AnnualNumberProp;
}

inline int ZBBPProcessSymbol::GetRightSubMenu() const
{
    return 1;
}

inline int ZBBPProcessSymbol::GetIconIndex() const
{
    return ( IsLocal() ) ? 5 : 13;
}

#endif // !defined(AFX_ZBBPPROCESSSYMBOL_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)