/****************************************************************************
 * ==> PSS_StopSymbolBP ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a stop symbol for banking process                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_StopSymbolBPH
#define PSS_StopSymbolBPH

#if _MSC_VER > 1000
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
#include "zMediator\PSS_Application.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LogicalRulesEntity.h"
#include "ZBBPUnitProp2.h"
#include "ZBProcRules.h"
#include "PSS_RulesPropertiesBP.h"
#include "ZBProcRisk.h"
#include "PSS_RiskPropertiesBP.h"
#include "ZVRiskTypeContainer.h"
#include "ZVRiskImpactContainer.h"
#include "ZVRiskProbabilityContainer.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZBBPStopSymbol : public PSS_Symbol
{
    DECLARE_SERIAL( ZBBPStopSymbol )

public:

    ZBBPStopSymbol( const CString Name = _T( "" ) );
    virtual ~ZBBPStopSymbol();

    /* Copy constructor. */
    ZBBPStopSymbol( const ZBBPStopSymbol& src );

    /* Assignment operator. */
    ZBBPStopSymbol& operator=( const ZBBPStopSymbol& src );

    /* Create a duplicate copy of this object. */
    virtual CODComponent* Dup() const;

    // Copy the definition only
    virtual void CopySymbolDefinitionFrom(const CODSymbolComponent& src);

    // Return the unique object type ID
    virtual int GetObjectTypeID() const
    {
        return 1;
    }

    /* Creates the symbol component. */
    BOOL Create( const CString Name = _T( "" ) );

    virtual BOOL OnDoubleClick();

    virtual int GetRightSubMenu() const;
    virtual int GetIconIndex() const;

    // Drag and drop methods
    virtual bool AcceptDropItem( CObject* pObj, const CPoint& pt );
    virtual bool DropItem( CObject* pObj, const CPoint& pt );

    // Call when a new symbol is created
    virtual bool CreateSymbolProperties();

    // Call to retreive properties for the object
    virtual bool FillProperties( ZBPropertySet& PropSet, bool NumericValue = false, bool GroupValue = false );

    // Call to save new changes to object's properties
    virtual bool SaveProperties( ZBPropertySet& PropSet );

    // Called to save a property for the object
    virtual bool SaveProperty( ZBProperty& Property );

    // Called to check the property value
    virtual bool CheckPropertyValue( ZBProperty& Property, CString& value, ZBPropertySet& Properties );

    // Called to process the extended input for the property value
    virtual bool ProcessExtendedInput( ZBProperty&        Property,
                                       CString&            value,
                                       ZBPropertySet&    Properties,
                                       bool&            Refresh );

    // JMR-MODIF - Le 18 décembre 2006 - Ajout de la fonction ProcessMenuCommand.
    bool ProcessMenuCommand( int                MenuCommand,
                             ZBProperty&        Property,
                             CString&            value,
                             ZBPropertySet&        Properties,
                             bool&                Refresh );

    // Called after the property changed
    virtual bool OnPostPropertyChanged( ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh );

    // JMR-MODIF - Le 18 décembre 2006 - Ajout de la fonction OnDropInternalPropertyItem.
    virtual bool OnDropInternalPropertyItem( ZBProperty&    SrcProperty,
                                             ZBProperty&    DstProperty,
                                             bool            Top2Down,
                                             ZBPropertySet&    Properties );

    //////////////////////////////////////////////////////////////////////
    // Attributes management methods
    virtual bool OnFillDefaultAttributes( ZBPropertyAttributes* pAttributes );
    virtual bool OnChangeAttributes( ZBPropertyAttributes* pAttributes );
    virtual CString GetAttributeString( ZBPropertyAttributes* pAttributes ) const;

    //////////////////////////////////////////////////////////////////////
    // Call-back on symbols

    /**
    * Called when a tooltip is required
    *@param[in, out] toolTipText - tooltip text, formatted tooltip text on function ends
    *@param point - hit point
    *@param mode - tooltip mode
    *@return true if tooltip can be shown, otherwise false
    */
    virtual bool OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode = PSS_ToolTip::IE_TT_Normal);

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

    /* Serializes the symbol. */
    virtual void Serialize( CArchive& ar );

    //////////////////////////////////////////////////////////////////////
    // Unit methods
    virtual bool HasUnit() const
    {
        return true;
    }

    virtual CString GetUnitName() const
    {
        return m_UnitProp.GetUnitName();
    }

    void SetUnitName( const CString value )
    {
        m_UnitProp.SetUnitName( value );
    }

    float GetUnitCost() const
    {
        return m_UnitProp.GetUnitCost();
    }

    void SetUnitCost( const float value )
    {
        m_UnitProp.SetUnitCost( value );
    }

    virtual CString GetUnitGUID() const
    {
        return m_UnitProp.GetUnitGUID();
    }

    void SetUnitGUID( const CString value )
    {
        m_UnitProp.SetUnitGUID( value );
    }

    /////////////////////////////////////////////////////////////////////
    // Méthodes pour déterminer le type.

    // JMR-MODIF - Le 3 mai 2006 - Fonction permettant de définir si le symbole est un point stop.
    virtual BOOL IsStop()
    {
        return TRUE;
    }

    // JMR-MODIF - Le 26 avril 2007 - Ajout de la fonction ContainsRule.
    BOOL ContainsRule( CString RuleName ) const;

    // JMR-MODIF - Le 9 octobre 2007 - Ajout de la fonction CheckRulesSync.
    void CheckRulesSync( CStringArray& RulesList );

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
    CString GetRiskType(std::size_t index) const
    {
        int     count    = PSS_Application::Instance()->GetMainForm()->GetRiskTypeContainer()->GetElementCount();
        CString riskType = m_Risks.GetRiskType(index);

        for (int i = 0; i < count; ++i)
            if (riskType == PSS_Application::Instance()->GetMainForm()->GetRiskTypeContainer()->GetElementAt(i))
                return m_Risks.GetRiskType(index);

        return _T("");
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

protected:

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

private:

    // JMR-MODIF - Le 25 décembre 2006 - Ajout de la fonction GetRuleNameByGUID.
    CString GetRuleNameByGUID(PSS_LogicalRulesEntity* p_Rule, CString RuleGUID );

private:

    ZBBPUnitProperties2 m_UnitProp;

    // JMR-MODIF - Le 18 décembre 2006 - Ajout de la variable m_Rules
    ZBProcRules            m_Rules;

    // JMR-MODIF - Le 3 juin 2007 - Ajout de la variable m_Risks
    ZBProcRisk            m_Risks;
};

inline int ZBBPStopSymbol::GetRightSubMenu() const
{
    return 5;
}

inline int ZBBPStopSymbol::GetIconIndex() const
{
    return ( IsLocal() ) ? 9 : 17;
}

#endif // !defined(AFX_ZBBPStopSymbol_H__78F947C3_2DC6_4808_A357_392EF1C0512F__INCLUDED_)