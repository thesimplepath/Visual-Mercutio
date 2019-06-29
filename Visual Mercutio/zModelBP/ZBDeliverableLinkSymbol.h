// **********************************************************************************************************
// *                                       Classe ZBDeliverableLinkSymbol                                    *
// **********************************************************************************************************
// * Cette classe représente un livrable. Elle hélrite de la classe ZBLinkSymbol, qui contient tous les        *
// * outils nécessaires à la jonction entre deux symboles, et ajoute à cette classe l'interface complète    *
// * pour la gestion des livrables.                                                                            *
// **********************************************************************************************************

#if !defined(AFX_ZBDeliverableLinkSymbol_H__E3F0977D_D63F_41AF_8667_2F903330AC3A__INCLUDED_)
#define AFX_ZBDeliverableLinkSymbol_H__E3F0977D_D63F_41AF_8667_2F903330AC3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zMediator\PSS_Application.h"
#include "zModel\ZDProcessGraphPage.h"
#include "zModel\ZBLogicalRulesEntity.h"
#include "zModel\ZBLinkSymbol.h"
#include "ProcGraphModelMdlBP.h"
#include "ZBProcRules.h"
#include "ZBBPRulesProp.h"
#include "ZBProcRisk.h"
#include "ZBBPRiskProp.h"
#include "ZVRiskTypeContainer.h"
#include "ZVRiskImpactContainer.h"
#include "ZVRiskProbabilityContainer.h"
#include "ZBBPAnnualNumberProp.h"
#include "ZBBPSimPropDeliverable.h"
#include "ZBBPCostPropDeliverable2.h"
#include "ZBBPUnitProp2.h"

// Forward declaration
class ZBBPDoorSymbol;
class ZBBPPageSymbol;
class ZBBPProcedureSymbol;
class ZBBPProcessSymbol;
class ZDProcessGraphModelMdl;

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 10 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBDeliverableLinkSymbol : public ZBLinkSymbol
{
    DECLARE_SERIAL( ZBDeliverableLinkSymbol )

public:

    ZBDeliverableLinkSymbol();
    virtual ~ZBDeliverableLinkSymbol();

    /* Copy constructor. */
    ZBDeliverableLinkSymbol( const ZBDeliverableLinkSymbol& src );

    /* Assignment operator. */
    ZBDeliverableLinkSymbol& operator=( const ZBDeliverableLinkSymbol& src );

    /* Create a duplicate copy of this object. */
    virtual CODComponent* Dup() const;

    // Copy the definition only
    virtual void CopySymbolDefinitionFrom( CODSymbolComponent& src );

    // Creates the link symbol 
    BOOL Create( int nStyle = -1, int nPointSize = -1, COLORREF crColor = -1, int bTransparent = -1 );
    BOOL CreateOrthogonal( int nStyle = -1, int nPointSize = -1, COLORREF crColor = -1, int bTransparent = -1 );

    // External file and external application methods
    virtual bool AcceptExtApp() const;

    // Let do the base class implementation
    //virtual bool DoInsertExtApp();
    // External file and external application methods
    virtual bool AcceptExtFile() const;

    // Let do the base class implementation
    //virtual bool DoInsertExtFile();

    // JMR-MODIF - Le 19 novembre 2006 - Surcharge de la fonction AcceptDropItem.
    virtual bool AcceptDropItem( CObject* pObj, CPoint pt );

    // JMR-MODIF - Le 19 novembre 2006 - Surcharge de la fonction DropItem.
    virtual bool DropItem( CObject* pObj, CPoint pt );

    // **********************
    // * Properties methods *
    // **********************

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

    // JMR-MODIF - Le 28 novembre 2006 - Ajout de la fonction ProcessMenuCommand.
    bool ProcessMenuCommand( int                MenuCommand,
                             ZBProperty&        Property,
                             CString&            value,
                             ZBPropertySet&        Properties,
                             bool&                Refresh );

    // Called before the property changed
    virtual bool OnPrePropertyChanged( CString NewValue, ZBProperty& Property, ZBPropertySet& Properties );

    // Called after the property changed
    virtual bool OnPostPropertyChanged( ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh );

    // Called when an internal drag&drop of property occured
    virtual bool OnDropInternalPropertyItem( ZBProperty&    SrcProperty,
                                             ZBProperty&    DstProperty,
                                             bool            Top2Down,
                                             ZBPropertySet&    Properties );

    virtual bool CreateSymbolProperties();

    // *********************************
    // * Attributes management methods *
    // *********************************

    virtual bool IncludeDescriptionArea() const
    {
        // Default return false
        return true;
    }

    virtual bool IncludeAttributeArea() const
    {
        // Default return false
        return true;
    }

    /* Serializes the symbol. */
    virtual void Serialize( CArchive& ar );

    /* Called after the object is created and on the desk 
       return true if the object can be created or false if the
       object must be destroyed immediatly */
    virtual bool OnPostCreation( CODModel* pModel = NULL, CODController* pCtrl = NULL );

    /* Called before the object is deleted
       return true if the object can be deleted */
    virtual bool OnPreDelete( CODModel* pModel = NULL, CODController* pCtrl = NULL );

    // Call by the controller when a tooltip is required
    virtual bool OnToolTip( CString& ToolTipText, CPoint point, ToolTipMode ToolTip = NormalToolTip );

    virtual BOOL OnDoubleClick()
    {
        return TRUE;
    }

    virtual int GetRightSubMenu() const;
    virtual int GetIconIndex() const;

    // *************
    // * Callbacks *
    // *************

    /* Called by the framework when a connection is created. */
    virtual void OnConnect( CODConnection* pConnection );

    //@cmember
    /* Called by the framework before a connection is destroyed. */
    virtual void OnDisconnect( CODConnection* pConnection );

    //@cmember
    /* Called by the framework when a connection moves. */
    virtual BOOL OnConnectionMove( CODConnection* pConnection );

    //@cmember
    /* Called by the framework when the dependent on the given connection is removed. */
    virtual BOOL OnRemoveDependent( CODConnection* pConnection );

    //@cmember
    /* Moves a port attached to the symbol. */
    virtual BOOL MovePort( CODPortComponent* pPort, const int nOffsetX, const int nOffsetY );

    // *******************************
    // * Direct properties functions *
    // *******************************

    // Rule list methods
    CString GetRuleList() const;

    void SetRuleList( const CString Value );

    void RemoveAllRules()
    {
        SetRuleList( _T( "" ) );
    }

    bool RuleExist( const CString Value );

    void AddRule( const CString Value );
    void RemoveRule( const CString Value );

    CString GetRuleAt( size_t Index );

    size_t GetRuleCount() const;

    // Item text list methods
    CString GetTextItemList() const;

    void SetTextItemList( const CString Value );

    void RemoveAllTextItems()
    {
        SetTextItemList( _T( "" ) );
    }

    bool TextItemExist( const CString Value );

    void AddTextItem( const CString Value );
    void RemoveTextItem( const CString Value );

    CString GetTextItemAt( size_t Index );

    size_t GetTextItemCount() const;

    //@cmember
    /* Gets the processing time. */
    double GetProcessingTime() const
    {
        return m_CostDeliverableProperties.GetProcessingTime();
    }

    //@cmember
    /* Sets the processing time. */
    void SetProcessingTime( const double value )
    {
        m_CostDeliverableProperties.SetProcessingTime( value );
    }

    /* Not in beta 2, the maximum percentage is not used anymore
    //@cmember
    // Gets the input workload percent.
    float GetInWorkloadPercent() const
    {
        return m_CostDeliverableProperties.GetInWorkloadPercent();
    }
    */

    // Keep this function for compatibility reason with Beta 1
    //@cmember
    // Sets the input workload percent.
    void SetInWorkloadPercent( const float value )
    {
        m_CostDeliverableProperties.SetInWorkloadPercent( value );
    }

    //@cmember
    /* Gets the output workload percent. */
    float GetOutWorkloadPercent() const
    {
        return m_CostDeliverableProperties.GetOutWorkloadPercent();
    }

    //@cmember
    /* Sets the output workload percent. */
    void SetOutWorkloadPercent( const float value )
    {
        m_CostDeliverableProperties.SetOutWorkloadPercent( value );
    }

    //@cmember
    /* Gets the unitary cost. */
    float GetUnitaryCost() const
    {
        return m_CostDeliverableProperties.GetUnitaryCost();
    }

    //@cmember
    /* Sets the unitary cost. */
    void SetUnitaryCost( const float value )
    {
        m_CostDeliverableProperties.SetUnitaryCost( value );
    }

    //@cmember
    /* Gets and Sets the stock duration. */
    double GetCaseDuration() const
    {
        return m_CostDeliverableProperties.GetCaseDuration();
    }

    void SetCaseDuration( const double value )
    {
        m_CostDeliverableProperties.SetCaseDuration( value );
    }

    //@cmember
    /* Gets and Sets the stock duration maximum. */
    double GetCaseDurationMax() const
    {
        return m_CostDeliverableProperties.GetCaseDurationMax();
    }

    void SetCaseDurationMax( const double value )
    {
        m_CostDeliverableProperties.SetCaseDurationMax( value );
    }

    //@cmember
    /* Gets the target duration. */
    double GetTargetDuration() const
    {
        return m_CostDeliverableProperties.GetTargetDuration();
    }

    //@cmember
    /* Sets the target duration. */
    void SetTargetDuration( const double value )
    {
        m_CostDeliverableProperties.SetTargetDuration( value );
    }

    //@cmember
    /* Gets the greenline duration. */
    double GetGreenLineDuration() const
    {
        return m_CostDeliverableProperties.GetGreenLineDuration();
    }

    //@cmember
    /* Sets the greenline duration. */
    void SetGreenLineDuration( const double value )
    {
        m_CostDeliverableProperties.SetGreenLineDuration( value );
    }

    //@cmember
    /* Gets the deliverable cost. */
    ZBBPAnnualNumberProperties& GetCost();

    //@cmember
    /* Sets the deliverable cost. */
    void SetCost( const double value );
    void SetCost( ZBBPAnnualNumberProperties& AnnualNumberProp );

    //@cmember
    /* Gets the deliverable workload forecast. */
    ZBBPAnnualNumberProperties& GetWorkloadForecast();

    //@cmember
    /* Sets the deliverable workload forecast. */
    void SetWorkloadForecast( const double value );
    void SetWorkloadForecast( ZBBPAnnualNumberProperties& AnnualNumberProp );

    //@cmember
    /* Gets the reference object to the quantity. */
    ZBBPAnnualNumberProperties& GetQuantity()
    {
        return m_Quantity;
    }

    //@cmember
    /* Sets a new quantity. */
    void SetQuantity( ZBBPAnnualNumberProperties& AnnualNumberProp )
    {
        GetQuantity() = AnnualNumberProp;
    }

    //@cmember
    /* Sets a new quantity using the original equalizer. */
    void SetQuantityUsingOriginalEqualizer( ZBBPAnnualNumberProperties& AnnualNumberProp )
    {
        m_Quantity.SetAndCalculateQuantitiesBasedOnYear( AnnualNumberProp.GetNumberYear() );
    }

    //@cmember
    /* Gets the quantity year. */
    double GetQuantityYear() const;
    void SetQuantityYear( const double value );

    //@cmember
    /* Get and Set the january quantity. */
    double GetQuantityJanuary() const;
    void SetQuantityJanuary( const double value );

    //@cmember
    /* Get and Set the february quantity. */
    double GetQuantityFebruary() const;
    void SetQuantityFebruary( const double value );

    //@cmember
    /* Get and Set the march quantity. */
    double GetQuantityMarch() const;
    void SetQuantityMarch( const double value );

    //@cmember
    /* Get and Set the april quantity. */
    double GetQuantityApril() const;
    void SetQuantityApril( const double value );

    //@cmember
    /* Get and Set the may quantity. */
    double GetQuantityMay() const;
    void SetQuantityMay( const double value );

    //@cmember
    /* Get and Set the june quantity. */
    double GetQuantityJune() const;
    void SetQuantityJune( const double value );

    //@cmember
    /* Get and Set the july quantity. */
    double GetQuantityJuly() const;
    void SetQuantityJuly( const double value );

    //@cmember
    /* Get and Set the august quantity. */
    double GetQuantityAugust() const;
    void SetQuantityAugust( const double value );

    //@cmember
    /* Get and Set the september quantity. */
    double GetQuantitySeptember() const;
    void SetQuantitySeptember( const double value );

    //@cmember
    /* Get and Set the october quantity. */
    double GetQuantityOctober() const;
    void SetQuantityOctober( const double value );

    //@cmember
    /* Get and Set the november quantity. */
    double GetQuantityNovember() const;
    void SetQuantityNovember( const double value );

    //@cmember
    /* Get and Set the december quantity. */
    double GetQuantityDecember() const;
    void SetQuantityDecember( const double value );

    //@cmember
    /* flag to lock the year quantity. */
    bool GetLockQuantityYear() const;
    void SetLockQuantityYear( const bool value );

    //@cmember
    /* flag to lock the january quantity. */
    bool GetLockQuantityJanuary() const;
    void SetLockQuantityJanuary( const bool value );

    //@cmember
    /* flag to lock the february quantity. */
    bool GetLockQuantityFebruary() const;
    void SetLockQuantityFebruary( const bool value );

    //@cmember
    /* flag to lock the march quantity. */
    bool GetLockQuantityMarch() const;
    void SetLockQuantityMarch( const bool value );

    //@cmember
    /* flag to lock the april quantity. */
    bool GetLockQuantityApril() const;
    void SetLockQuantityApril( const bool value );

    //@cmember
    /* flag to lock the may quantity. */
    bool GetLockQuantityMay() const;
    void SetLockQuantityMay( const bool value );

    //@cmember
    /* flag to lock the june quantity. */
    bool GetLockQuantityJune() const;
    void SetLockQuantityJune( const bool value );

    //@cmember
    /* flag to lock the july quantity. */
    bool GetLockQuantityJuly() const;
    void SetLockQuantityJuly( const bool value );

    //@cmember
    /* flag to lock the august quantity. */
    bool GetLockQuantityAugust() const;
    void SetLockQuantityAugust( const bool value );

    //@cmember
    /* flag to lock the september quantity. */
    bool GetLockQuantitySeptember() const;
    void SetLockQuantitySeptember( const bool value );

    //@cmember
    /* flag to lock the october quantity. */
    bool GetLockQuantityOctober() const;
    void SetLockQuantityOctober( const bool value );

    //@cmember
    /* flag to lock the november quantity. */
    bool GetLockQuantityNovember() const;
    void SetLockQuantityNovember( const bool value );

    //@cmember
    /* flag to lock the december quantity. */
    bool GetLockQuantityDecember() const;
    void SetLockQuantityDecember( const bool value );

    //@cmember
    /* flag to show or not month details. */
    bool GetForceEqualizer() const;
    void SetForceEqualizer( bool value );

    // Returns the combination name of the procedure attached to 
    // this deliverable
    CString GetCombinationName() const;

    // Returns the combination max percentage of the procedure attached to 
    // this deliverable, -1 if error
    float GetCombinationMaxPercentage() const;

    // Returns true if the deliverable is a master of a procedure combination attached to 
    // this deliverable, false if not
    bool IsMasterOfCombination() const;

    // Change les attributs du trait afin de permettre une information visuelle du pourcentage.
    void SetVisualInfo( int iPercent );

    // ****************
    // * Unit methods *
    // ****************

    virtual bool HasUnit() const
    {
        return false;
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

    int GetUnitDoubleValidationType() const
    {
        return m_UnitProp.GetUnitDoubleValidationType();
    }

    void SetUnitDoubleValidationType( const int value )
    {
        m_UnitProp.SetUnitDoubleValidationType( value );
    }

    void GetUnitDoubleValidationTypeStringArray( CStringArray& sar ) const
    {
        m_UnitProp.GetUnitDoubleValidationTypeStringArray( sar );
    }

    int ConvertUnitDoubleValidationString2Type( const CString Type ) const
    {
        return m_UnitProp.ConvertUnitDoubleValidationString2Type( Type );
    }

    CString GetUnitDoubleValidationTypeString( const int Value ) const
    {
        return m_UnitProp.GetUnitDoubleValidationTypeString( Value );
    }

    // Returns the source procedure attached to this deliverable
    ZBBPProcedureSymbol* GetSourceProcedure() const;

    // Returns the destination procedure attached to this deliverable
    ZBBPProcedureSymbol* GetTargetProcedure() const;

    // Returns the coming from process of this deliverable
    ZDProcessGraphModelMdl* GetComingFromModel() const;
    ZBBPProcessSymbol* GetComingFromProcess() const;

    // Returns the going to process attached of this deliverable
    ZDProcessGraphModelMdl* GetGoingToModel() const;
    ZBBPProcessSymbol* GetGoingToProcess() const;

    // Return true if the deliverable is an initial deliverable
    bool IsInitial() const;

    // Return true if the deliverable is a final deliverable
    bool IsFinal() const;

    // Return true if the deliverable is a an interprocess deliverable
    bool IsInterProcess() const;

    // **********
    // * Labels *
    // **********

    //@cmember
    /* Creates a new label and adds it to the symbol. */
    virtual CODLabelComponent* CreateLabel( const LPCTSTR            lpszText,
                                            const OD_CONTROL_POINT    ctlPoint,
                                            CDC*                    pDC            = NULL );

    // JMR-MODIF - Le 26 avril 2007 - Ajout de la fonction ContainsRule.
    BOOL ContainsRule( CString RuleName );

    // JMR-MODIF - Le 9 octobre 2007 - Ajout de la fonction CheckRulesSync.
    void CheckRulesSync( CStringArray& RulesList );

    // **********
    // * Events *
    // **********

    // JMR-MODIF - Le 27 mars 2006 - Ajout de la fonction virtuelle OnSymbolNameChange.
    virtual void OnSymbolNameChange( CString OldName, CString NewName );

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

    // todo FIXME -cFeature -oJean: such functions are repeated 1000x in the code, please make a common function!
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

    // JMR-MODIF - Le 27 mars 2006 - Ajout de la fonction virtuelle NotifyNameChange.
    void NotifyNameChange( const CString                OldName,
                           const CString                NewName,
                           ZDProcessGraphModelMdlBP*    m_RootModel = NULL );

    bool CreateSymbolName();
    bool DoDoorProcedureConnection( ZBBPDoorSymbol* pSrc, ZBBPProcedureSymbol* pDst, CODModel* pModel );
    bool DoProcedureDoorConnection( ZBBPProcedureSymbol* pSrc, ZBBPDoorSymbol* pDst, CODModel* pModel );
    bool DoPageProcedureConnection( ZBBPPageSymbol* pSrc, ZBBPProcedureSymbol* pDst, CODModel* pModel );
    bool DoProcedurePageConnection( ZBBPProcedureSymbol* pSrc, ZBBPPageSymbol* pDst, CODModel* pModel );
    bool DoProcessProcessConnection( ZBBPProcessSymbol* pSrc, ZBBPProcessSymbol* pDst, CODModel* pModel );

    void CheckDeliverableStatus();

    void SavePropertiesToQuantity( ZBPropertySet& Properties );
    void SetNewNumberAndEqualize( ZBProperty& Property, ZBPropertySet& Properties );
    void SaveEqualizerToProperties( ZBPropertySet& Properties );

    // JMR-MODIF - Le 7 juin 2006 - Ajout de la fonction surchargée AdjustPoints.
    void AdjustPoints();

    // JMR-MODIF - Le 25 décembre 2006 - Ajout de la fonction GetRuleNameByGUID.
    CString GetRuleNameByGUID( ZBLogicalRulesEntity* p_Rule, CString RuleGUID );

private:

    ZBBPAnnualNumberProperties        m_Quantity;
    ZBBPSimPropertiesDeliverable    m_SimProperties;
    ZBBPCostPropertiesDeliverable2    m_CostDeliverableProperties;
    ZBBPUnitProperties2                m_UnitProp;

    CStringArray                    m_UnitDoubleValidationTypeArray;

    // JMR-MODIF - Le 22 novembre 2006 - Ajout de la variable m_Rules
    ZBProcRules                        m_Rules;

    // JMR-MODIF - Le 3 juin 2007 - Ajout de la variable m_Risks
    ZBProcRisk                        m_Risks;
};

inline double ZBDeliverableLinkSymbol::GetQuantityYear() const
{
    return m_Quantity.GetNumberYear();
}

inline void ZBDeliverableLinkSymbol::SetQuantityYear( const double value )
{
    m_Quantity.SetNumberYear( value );
}

inline double ZBDeliverableLinkSymbol::GetQuantityJanuary() const
{
    return m_Quantity.GetNumberJanuary();
}

inline void ZBDeliverableLinkSymbol::SetQuantityJanuary( const double value )
{
    m_Quantity.SetNumberJanuary( value );
}

inline double ZBDeliverableLinkSymbol::GetQuantityFebruary() const
{
    return m_Quantity.GetNumberFebruary();
}

inline void ZBDeliverableLinkSymbol::SetQuantityFebruary( const double value )
{
    m_Quantity.SetNumberFebruary( value );
}

inline double ZBDeliverableLinkSymbol::GetQuantityMarch() const
{
    return m_Quantity.GetNumberMarch();
}

inline void ZBDeliverableLinkSymbol::SetQuantityMarch( const double value )
{
    m_Quantity.SetNumberMarch( value );
}

inline double ZBDeliverableLinkSymbol::GetQuantityApril() const
{
    return m_Quantity.GetNumberApril();
}

inline void ZBDeliverableLinkSymbol::SetQuantityApril( const double value )
{
    m_Quantity.SetNumberApril( value );
}

inline double ZBDeliverableLinkSymbol::GetQuantityMay() const
{
    return m_Quantity.GetNumberMay();
}

inline void ZBDeliverableLinkSymbol::SetQuantityMay( const double value )
{
    m_Quantity.SetNumberMay( value );
}

inline double ZBDeliverableLinkSymbol::GetQuantityJune() const
{
    return m_Quantity.GetNumberJune();
}

inline void ZBDeliverableLinkSymbol::SetQuantityJune( const double value )
{
    m_Quantity.SetNumberJune( value );
}

inline double ZBDeliverableLinkSymbol::GetQuantityJuly() const
{
    return m_Quantity.GetNumberJuly();
}

inline void ZBDeliverableLinkSymbol::SetQuantityJuly( const double value )
{
    m_Quantity.SetNumberJuly( value );
}

inline double ZBDeliverableLinkSymbol::GetQuantityAugust() const
{
    return m_Quantity.GetNumberAugust();
}

inline void ZBDeliverableLinkSymbol::SetQuantityAugust( const double value )
{
    m_Quantity.SetNumberAugust( value );
}

inline double ZBDeliverableLinkSymbol::GetQuantitySeptember() const
{
    return m_Quantity.GetNumberSeptember();
}

inline void ZBDeliverableLinkSymbol::SetQuantitySeptember( const double value )
{
    m_Quantity.SetNumberSeptember( value );
}

inline double ZBDeliverableLinkSymbol::GetQuantityOctober() const
{
    return m_Quantity.GetNumberOctober();
}

inline void ZBDeliverableLinkSymbol::SetQuantityOctober( const double value )
{
    m_Quantity.SetNumberOctober( value );
}

inline double ZBDeliverableLinkSymbol::GetQuantityNovember() const
{
    return m_Quantity.GetNumberNovember();
}

inline void ZBDeliverableLinkSymbol::SetQuantityNovember( const double value )
{
    m_Quantity.SetNumberNovember( value );
}

inline double ZBDeliverableLinkSymbol::GetQuantityDecember() const
{
    return m_Quantity.GetNumberDecember();
}

inline void ZBDeliverableLinkSymbol::SetQuantityDecember( const double value )
{
    m_Quantity.SetNumberDecember( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantityYear() const
{
    return m_Quantity.GetLockNumberYear();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantityYear( const bool value )
{
    m_Quantity.SetLockNumberYear( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantityJanuary() const
{
    return m_Quantity.GetLockNumberJanuary();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantityJanuary( const bool value )
{
    m_Quantity.SetLockNumberJanuary( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantityFebruary() const
{
    return m_Quantity.GetLockNumberFebruary();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantityFebruary( const bool value )
{
    m_Quantity.SetLockNumberFebruary( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantityMarch() const
{
    return m_Quantity.GetLockNumberMarch();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantityMarch( const bool value )
{
    m_Quantity.SetLockNumberMarch( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantityApril() const
{
    return m_Quantity.GetLockNumberApril();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantityApril( const bool value )
{
    m_Quantity.SetLockNumberApril( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantityMay() const
{
    return m_Quantity.GetLockNumberMay();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantityMay( const bool value )
{
    m_Quantity.SetLockNumberMay( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantityJune() const
{
    return m_Quantity.GetLockNumberJune();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantityJune( const bool value )
{
    m_Quantity.SetLockNumberJune( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantityJuly() const
{
    return m_Quantity.GetLockNumberJuly();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantityJuly( const bool value )
{
    m_Quantity.SetLockNumberJuly( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantityAugust() const
{
    return m_Quantity.GetLockNumberAugust();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantityAugust( const bool value )
{
    m_Quantity.SetLockNumberAugust( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantitySeptember() const
{
    return m_Quantity.GetLockNumberSeptember();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantitySeptember( const bool value )
{
    m_Quantity.SetLockNumberSeptember( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantityOctober() const
{
    return m_Quantity.GetLockNumberOctober();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantityOctober( const bool value )
{
    m_Quantity.SetLockNumberOctober( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantityNovember() const
{
    return m_Quantity.GetLockNumberNovember();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantityNovember( const bool value )
{
    m_Quantity.SetLockNumberNovember( value );
}

inline bool ZBDeliverableLinkSymbol::GetLockQuantityDecember() const
{
    return m_Quantity.GetLockNumberDecember();
}

inline void ZBDeliverableLinkSymbol::SetLockQuantityDecember( const bool value )
{
    m_Quantity.SetLockNumberDecember( value );
}

inline bool ZBDeliverableLinkSymbol::GetForceEqualizer() const
{
    return m_Quantity.GetForceEqualizer();
}

inline void ZBDeliverableLinkSymbol::SetForceEqualizer( bool value )
{
    m_Quantity.SetForceEqualizer( value );
}

inline ZBBPAnnualNumberProperties& ZBDeliverableLinkSymbol::GetCost()
{
    return m_SimProperties.GetCost();
}

inline void ZBDeliverableLinkSymbol::SetCost( const double value )
{
    m_SimProperties.SetCost( value );
}

inline void ZBDeliverableLinkSymbol::SetCost( ZBBPAnnualNumberProperties& AnnualNumberProp )
{
    m_SimProperties.GetCost() = AnnualNumberProp;
}

inline ZBBPAnnualNumberProperties& ZBDeliverableLinkSymbol::GetWorkloadForecast()
{
    return m_SimProperties.GetWorkloadForecast();
}

inline void ZBDeliverableLinkSymbol::SetWorkloadForecast( const double value )
{
    m_SimProperties.SetWorkloadForecast( value );
}

inline void ZBDeliverableLinkSymbol::SetWorkloadForecast( ZBBPAnnualNumberProperties& AnnualNumberProp )
{
    m_SimProperties.GetWorkloadForecast() = AnnualNumberProp;
}

inline int ZBDeliverableLinkSymbol::GetRightSubMenu() const
{
    return 3;
}

inline int ZBDeliverableLinkSymbol::GetIconIndex() const
{
    return ( IsLocal() ) ? 6 : 14;
}

#endif // !defined(AFX_ZBDeliverableLinkSymbol_H__E3F0977D_D63F_41AF_8667_2F903330AC3A__INCLUDED_)