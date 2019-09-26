// ZBSymbol.h: interface for the ZBSymbol class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBSYMBOL_H__2D0F308C_3DD6_402F_9954_202E6053BEB8__INCLUDED_)
#define AFX_ZBSYMBOL_H__2D0F308C_3DD6_402F_9954_202E6053BEB8__INCLUDED_

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

#include "zBaseSym\ZIBasicSymbol.h"
#include "zBaseSym\ZIObjectPath.h"
#include "zBaseSym\ZINavigableSymbol.h"

#include "zBaseLib\PSS_Bitmap.h"

#include "zProperty\ZIProperties.h"
#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"
#include "zBaseSym\ZIBasicSymbolAcceptVisitor.h"
#include "zBaseSym\ZIBasicSymbolVisitor.h"
#include "zBaseLib\ZIToolTip.h"

#include "zModel\ZBExtAppPropertyMgr.h"
#include "zModel\ZBExtFilePropertyMgr.h"
#include "zModel\ZVSymbolAttributes.h"

// JMR-MODIF - Le 20 février 2006 - Ajout de l'en-tête pour la prise en charge des Tokens.
#include "zBaseLib\PSS_Tokenizer.h"

//////////////////////////////////////////////////////////////////////
// Forward declaration
class ZBSymbolEdit;
class ZBPropertyAttributes;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 27 septembre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// Each symbol implement the subject and observer interface
class AFX_EXT_CLASS ZBSymbol : public CODSymbolComponent,
                               public ZIBasicSymbol,
                               public ZIObjectPath,
                               public ZINavigableSymbol,
                               public ZIProperties,
                               public ZBExtAppPropertyMgr,
                               public ZBExtFilePropertyMgr,
                               public ZVSymbolAttributes,
                               public ZIBasicSymbolAcceptVisitor,
                               public ZISubject,
                               public ZIObserver,
                               public ZIToolTip
{
    DECLARE_SERIAL( ZBSymbol )

public:

    ZBSymbol();
    virtual ~ZBSymbol();

    /* Copy constructor. */
    ZBSymbol( const ZBSymbol& src );

    /* Assignment operator. */
    ZBSymbol& operator=( const ZBSymbol& src );

    /* Create a duplicate copy of this object. */
    virtual CODComponent* Dup() const;

    // Return the unique object type ID
    virtual int GetObjectTypeID() const
    {
        return -1;
    }

    //////////////////////////////////////////////////////////////////////
    // Attributes management methods
    virtual bool AcceptDynamicAttributes() const
    {
        return true;
    }

    virtual bool    OnFillDefaultAttributes        ( ZBPropertyAttributes* pAttributes );
    virtual bool    OnChangeAttributes            ( ZBPropertyAttributes* pAttributes );
    virtual CString    GetAttributeString            ( ZBPropertyAttributes* pAttributes ) const;
    virtual void    RefreshAttributeAreaText    ( bool Redraw = false );

    bool GetDisplayTitleText() const;
    void SetDisplayTitleText( bool value );

    ZBPropertyAttributes* CreateEmptyAttributes();
    void DeleteAllAttributes();

    ///////////////////////////////////////////////////////
    // ZIBasicSymbol methods

    virtual CString GetSymbolComment();
    virtual BOOL SetSymbolComment( const CString value );

    virtual CString GetSymbolName();
    virtual BOOL SetSymbolName( const CString value );

    virtual int        GetSymbolReferenceNumber    ();
    virtual CString    GetSymbolReferenceNumberStr    ();
    virtual BOOL    SetSymbolReferenceNumber    ( int value );
    virtual BOOL    SetSymbolReferenceNumberStr    ( const CString value );

    virtual void EditSymbolName();

    virtual bool Match( const CString            What,
                        ZBPropertyAttributes*    pPropAttributes    = NULL, 
                        bool                    CaseSensitive    = false,
                        bool                    PartialSearch    = false );

    // Check if the new name is a valid one
    virtual bool IsNewNameValid( const CString value ) const;

    // Create the symbol itself
    BOOL Create( UINT nID, HINSTANCE hInst, const CString Name = _T( "" ) );

    virtual ZBSymbolEdit* CreateEditText( const CString AreaName,
                                          const CString EditName,
                                          CODComponent* pParent        = NULL );

    virtual ZBSymbolEdit* CreateAndReplaceEditText( const CString EditName, CODComponent* pParent = NULL );

    // Return the Edit Box area
    virtual CODComponent* GetEditBoxArea()
    {
        return ZVSymbolAttributes::GetEditBoxArea();
    }

    // Return the comment Edit
    virtual CODTextComponent* GetCommentTextEdit()
    {
        return ZVSymbolAttributes::GetCommentTextEdit();
    }

    // The comment can be edited
    virtual bool CommentTextEditReadOnly() const
    {
        return false;
    }

    // Return the symbol name Edit
    virtual CODTextComponent* GetSymbolNameTextEdit()
    {
        return ZVSymbolAttributes::GetSymbolNameTextEdit();
    }

    // The symbol name can be edited
    virtual bool SymbolNameTextEditReadOnly() const
    {
        return false;
    }

    virtual CODTextComponent* GetAttributeTextEdit()
    {
        return ZVSymbolAttributes::GetAttributeTextEdit();
    }

    virtual CODLineComponent* GetSplitter1()
    {
        return ZVSymbolAttributes::GetSplitter1();
    }

    virtual CODLineComponent* GetSplitter2()
    {
        return ZVSymbolAttributes::GetSplitter2();
    }

    // Copy the definition only
    virtual void CopySymbolDefinitionFrom( CODSymbolComponent& src );

    virtual CString GetNameOfReference() const;
    virtual void SetNameOfReference( CString value );

    virtual bool IsLocal() const;
    virtual void SetIsLocal( bool value = true );

    // JMR-MODIF - Le 3 septembre 2006 - Ajout de la fonction virtuelle DuplicateStyleOnTwinSymbol.
    virtual BOOL DuplicateStyleOnTwinSymbol()
    {
        return FALSE;
    }

    // JMR-MODIF - Le 22 mars 2006 - Fonction permettant de définir si le symbole est générique.
    virtual BOOL IsGeneric()
    {
        return FALSE;
    }

    // JMR-MODIF - Le 5 avril 2006 - Fonction permettant de définir si le symbole est un processus.
    virtual BOOL IsProcess()
    {
        return FALSE;
    }

    // JMR-MODIF - Le 3 mai 2006 - Fonction permettant de définir si le symbole est une procédure.
    virtual BOOL IsProcedure()
    {
        return FALSE;
    }

    // JMR-MODIF - Le 3 mai 2006 - Fonction permettant de définir si le symbole est un point start.
    virtual BOOL IsStart()
    {
        return FALSE;
    }

    // JMR-MODIF - Le 3 mai 2006 - Fonction permettant de définir si le symbole est un point stop.
    virtual BOOL IsStop()
    {
        return FALSE;
    }

    // JMR-MODIF - Le 3 mai 2006 - Fonction permettant de définir si le symbole est une porte.
    virtual BOOL IsDoor()
    {
        return FALSE;
    }

    // JMR-MODIF - Le 3 mai 2006 - Fonction permettant de définir si le symbole est une page.
    virtual BOOL IsPage()
    {
        return FALSE;
    }

    // JMR-MODIF - Le 3 mai 2006 - Fonction permettant de définir si le symbole est un paquet.
    virtual BOOL IsPackage()
    {
        return FALSE;
    }

    //////////////////////////////////////////////////////////////////////
    // Area state methods
    virtual bool IncludeNameArea() const
    {
        // The default is true to have a name area
        return true;
    }

    virtual bool IncludeDescriptionArea() const
    {
        // Default return false
        return false;
    }

    virtual bool IncludeAttributeArea() const
    {
        // Default return false
        return false;
    }

    virtual void DisplayNameArea( bool value = true )
    {
        ZVSymbolAttributes::DisplayNameArea( value );
    }

    virtual bool IsNameAreaVisible() const
    {
        return ZVSymbolAttributes::IsNameAreaVisible();
    }

    virtual void DisplayDescriptionArea( bool value = true )
    {
        ZVSymbolAttributes::DisplayDescriptionArea( value );
    }

    virtual bool IsDescriptionsAreaVisible() const
    {
        return ZVSymbolAttributes::IsDescriptionsAreaVisible();
    }

    virtual void DisplayAttributeArea( bool value = true )
    {
        ZVSymbolAttributes::DisplayAttributeArea( value );
    }

    virtual bool IsAttributeAreaVisible() const
    {
        return ZVSymbolAttributes::IsAttributeAreaVisible();
    }

    //////////////////////////////////////////////////////////////////////
    // Symbol mouse methods
    virtual bool AcceptMouseInteraction() const
    {
        // Yes, in order to manage the attributes' splitters
        return true;
    }

    virtual bool OnMouseMove( UINT nFlags, CPoint point, CODController& Ctrl )
    {
        return ZVSymbolAttributes::OnMouseMove( nFlags, point, Ctrl );
    }

    virtual bool OnLButtonDown( UINT nFlags, CPoint point, CODController& Ctrl )
    {
        return ZVSymbolAttributes::OnLButtonDown( nFlags, point, Ctrl );
    }

    virtual bool OnLButtonUp( UINT nFlags, CPoint point, CODController& Ctrl )
    {
        return ZVSymbolAttributes::OnLButtonUp( nFlags, point, Ctrl );
    }

    virtual bool OnLButtonDblClk( UINT nFlags, CPoint point, CODController& Ctrl )
    {
        return false;
    }

    virtual bool OnRButtonDown( UINT nFlags, CPoint point, CODController& Ctrl )
    {
        return false;
    }

    virtual bool OnRButtonUp( UINT nFlags, CPoint point, CODController& Ctrl )
    {
        return false;
    }

    // Show the symbol in error
    virtual void ShowInError( bool value = true );

    // Apply the format coming from another object
    virtual void ApplyFormatFromObject( CODSymbolComponent&    Object,
                                        bool                Font    = true,
                                        bool                Fill    = true,
                                        bool                Line    = true );

    // Used to find the local symbol of this reference
    virtual CODComponent* GetLocalSymbol();

    // Used to find the referenced symbol of this master symbol
    virtual CODComponentSet* GetReferenceSymbols();

    virtual bool IsReferenced() const;
    virtual bool IsReferenceValid() const;
    virtual void AssignReferenceSymbol( CODSymbolComponent* pReference );
    virtual void RemoveReferenceSymbol();
    virtual CODSymbolComponent* GetSymbolReference() const;

    virtual bool IsChildModelRef() const
    {
        return false;
    }

    // Retreive the owner symbol model
    virtual CODModel* GetOwnerModel();

    // Retreive the root symbol model
    virtual CODModel* GetRootModel();

    // JMR-MODIF - Le 2 mars 2006 - La fonction GetpModel est changée de protected à public.
    // Nécessaire, car certaine fonction doivent récupérer uniquement le modèle enfant pour travailler.
    CODModel* GetpModel()
    {
        return m_pModel;
    };

    // Set the model modified flag to the specified value
    virtual void SetModifiedFlag( BOOL Value = TRUE );

    /* Called after the object is created and on the desk 
       return true if the object can be created or false if the
       object must be destroyed immediatly */
    virtual bool OnPostCreation( CODModel* pModel = NULL, CODController* pCtrl = NULL )
    {
        if ( !InitializeAttributeAreas() )
        {
            return false;
        }

        // Check the size of components
        AdjustAreaPosition();

        return true;
    }

    /* Called before the object is deleted
       return true if the object can be deleted */
    virtual bool OnPreDelete( CODModel* pModel = NULL, CODController* pCtrl = NULL )
    {
        // The default is to return true
        return true;
    }

    /* Called after the double click occured on the object */
    virtual void OnPostDoubleClick( CODModel* pModel = NULL, CODController* pCtrl = NULL )
    {
        // Does nothing in the base class method
    }

    // Creation of a new child model, base function does nothing
    virtual BOOL CreateEmptyChildModel( CODModel* pParent );

    // Call by the controller when the symbol should be deleted
    virtual void OnDeleteSymbol();

    // Called by the link itself when disconnected
    virtual void OnLinkDisconnect( CODLinkComponent* pLink )
    {
        // Do nothing
    }

    // Called by the link itself when disconnected
    virtual void OnLinkConnect( CODLinkComponent* pLink )
    {
        // Do nothing
    }

    // Return the child model if there is one
    virtual CODModel* GetChildModel();

    // Set a new child model
    virtual void SetChildModel( CODModel* pModel );

    // Return true if the symbol can contain a child model
    virtual bool CanContainChildModel() const 
    {
        return false;
    }

    // Call by the controller when a tooltip is required
    virtual bool OnToolTip( CString& ToolTipText, CPoint point, ToolTipMode ToolTip = NormalToolTip );

    // Drag and drop methods
    virtual bool AcceptDropItem( CObject* pObj, CPoint pt )
    {
        return ( AcceptExtApp()  && ZBExtAppPropertyMgr::AcceptDropItem ( pObj, pt ) ) ||
               ( AcceptExtFile() && ZBExtFilePropertyMgr::AcceptDropItem( pObj, pt ) );
    }

    virtual bool DropItem( CObject* pObj, CPoint pt )
    {
        return ( ( AcceptExtApp()  && ZBExtAppPropertyMgr::AcceptDropItem ( pObj, pt ) ) ? ZBExtAppPropertyMgr::DropItem ( pObj, pt ) : false ) ||
               ( ( AcceptExtFile() && ZBExtFilePropertyMgr::AcceptDropItem( pObj, pt ) ) ? ZBExtFilePropertyMgr::DropItem( pObj, pt ) : false );
    }

    // External file and external application methods
    virtual bool AcceptExtApp() const
    {
        return false;
    }

    virtual bool DoInsertExtApp( bool DisplayDialog = true )
    {
        return ZBExtAppPropertyMgr::DoInsertExtApp( DisplayDialog );
    }

    virtual bool AcceptExtFile() const
    {
        return false;
    }

    virtual bool DoInsertExtFile( bool DisplayDialog = true )
    {
        return ZBExtFilePropertyMgr::DoInsertExtFile( DisplayDialog );
    }

    //////////////////////////////////////////////////////////////////////
    // JMR-MODIF - Le 20 février 2006 - Ajout des fonctions cadres propres aux prestations.
    virtual bool HasPrestations() const
    {
        return false;
    }

    virtual PSS_Tokenizer GetPrestationsList()
    {
        PSS_Tokenizer aToken( _T( "" ) );
        return aToken;
    }

    // ****************************************************************************
    // JMR-MODIF - Le 29 juillet 2007 - Ajout des fonctions concernant les risques.

    CString GetRiskLevel();
    void SetRiskLevel( CString Level );
    // ****************************************************************************

    //////////////////////////////////////////////////////////////////////
    // Unit methods
    virtual bool HasUnit() const
    {
        return false;
    }

    virtual CString GetUnitName() const
    {
        return _T( "" );
    }

    virtual CString GetUnitGUID() const
    {
        return _T( "" );
    }

    virtual void OnMove();

    virtual int GetRightSubMenu() const;
    virtual int GetIconIndex() const;

    virtual void CalculateAbsolutePath()
    {
        // If no path defined
        if ( GetAbsolutePath().IsEmpty() )
        {
            AddMemberToPath( GetSymbolName() );
        }
    }

    // Return the child model pathname just serialized
    CString GetChildModelPathName() const
    {
        return m_ChildModelPathName;
    }

    // Redraw the symbol
    virtual void RedrawSymbol();

    //////////////////////////////////////////////////////////////////////
    // Call-back on symbols
    virtual void OnSymbolNameChanged( CODComponent& Comp, const CString OldName )
    {
    }

    virtual void OnPageNameChanged( ZDProcessGraphPage* pPage, const CString OldName )
    {
    }

    virtual void OnUserEntityChanged( ZBUserEntity* pUserEntity, const CString OldName )
    {
    }

    //////////////////////////////////////////////////////////////////////
    // ZIBasicSymbolAcceptVisitor methods

    /* AcceptVisitor method let the object be visited
       by concreted derived ZIBasicSymbolVisitor classes */
    virtual bool AcceptVisitor( ZIBasicSymbolVisitor& Visitor )
    {
        return Visitor.Visit( *this );
    }

    BOOL RemoveSymbol( const CString SymbolName );
    BOOL RemoveSymbol( CODComponent* pComponent );
    BOOL RemoveSymbol( CODComponent* pMainComponent, CODComponent* pComponent );

    CODComponent* FindSymbol( const CString SymbolName );
    CODComponent* FindSymbol( CODComponent* pMainComponent, const CString SymbolName );
    CODComponent* FindSymbolInChild( CODComponent* pMainComponent, const CString SymbolName );

    ///////////////////////////////////////////////////////
    // ZIProperties methods

    // Return true if the object has properties
    virtual bool HasProperties() const
    {
        return true;
    }

    // Call to retreive properties for the object
    virtual bool FillProperties( ZBPropertySet& PropSet, bool NumericValue = false, bool GroupValue = false );

    // Call to save new changes to object's properties
    virtual bool SaveProperties( ZBPropertySet& PropSet );

    // Called to retreive a property for the object
    virtual bool FillProperty( ZBProperty& Property );

    // Called to save a property for the object
    virtual bool SaveProperty( ZBProperty& Property );

    // Called to check the property value
    virtual bool CheckPropertyValue( ZBProperty& Property, CString& value, ZBPropertySet& Properties );

    // Called to process the extended input for the property value
    virtual bool ProcessExtendedInput( ZBProperty&        Property,
                                       CString&            value,
                                       ZBPropertySet&    Properties,
                                       bool&            Refresh );

    // Called to process the a menu command for the property value
    virtual bool ProcessMenuCommand( int            MenuCommand,
                                     ZBProperty&    Property,
                                     CString&        value,
                                     ZBPropertySet&    Properties,
                                     bool&            Refresh );

    // Called before the property changed
    virtual bool OnPrePropertyChanged( CString NewValue, ZBProperty& Property, ZBPropertySet& Properties );

    // Called after the property changed
    virtual bool OnPostPropertyChanged( ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh );

    // Called when an internal drag&drop of property occured
    virtual bool OnDropInternalPropertyItem( ZBProperty&    SrcProperty,
                                             ZBProperty&    DstProperty,
                                             bool            Top2Down,
                                             ZBPropertySet&    Properties );

    // Call to create the properties
    virtual bool CreateSymbolProperties();

    // Call to know if properties can be edited
    virtual bool IsPropertiesReadOnly() const
    {
        return false;
    }
    
    virtual ZBDynamicProperties* GetDynamicPropertiesManager()
    {
        return m_DynamicPropManager;
    }

    // Unit retreival methods
    CString RetreiveUnitGUID( const CString Name, bool& Error ) const;
    CString RetreiveUnitName( const CString GUID, bool& Error ) const;
    CString RetreiveUnitDescription( const CString GUID, bool& Error ) const;
    float RetreiveUnitCost( const CString GUID, bool& Error ) const;

    // Logical system retreival methods
    CString RetreiveLogicalSystemGUID( const CString Name, bool& Error ) const;
    CString RetreiveLogicalSystemName( const CString GUID, bool& Error ) const;
    CString RetreiveLogicalSystemDescription( const CString GUID, bool& Error ) const;

    /////////////////////////////////////////////////////////////////////////////////////////
    // JMR-MODIF - Le 27 février 2006 - Ajout des méthodes de recherche pour les prestations.
    CString RetreivePrestationName( const CString GUID, bool& Error ) const;

    // JMR-MODIF - Le 22 juillet 2007 - Ajout de la fonction UpdateGraphicFromRisk.
    void UpdateGraphicFromRisk( COLORREF Color, BOOL Italic );

    // Get and Set the current line color
    virtual void SetCurrentLineColor( COLORREF value );
    virtual COLORREF GetCurrentLineColor() const
    {
        return m_CurrentLineColor;
    }

    // Get and Set the current label color
    virtual void SetCurrentLabelColor( COLORREF value );

    virtual COLORREF GetCurrentLabelColor() const
    {
        return m_CurrentLabelLineColor;
    }

    COLORREF    GetInitialLineColor() const;
    void        SetInitialLineColor( COLORREF value );
    int            GetInitialLineWidth() const;
    void        SetInitialLineWidth( int value );
    COLORREF    GetInitialLabelLineColor() const;
    void        SetInitialLabelLineColor( COLORREF value );
    int            GetInitialLabelLineWidth() const;
    void        SetInitialLabelLineWidth( int value );

    ///////////////////////////////////////////////////////
    // ZINavigableSymbol methods
    // All methods to obtain following symbols
    virtual size_t GetFollowingSymbols( CODNodeArray& Nodes );
    virtual size_t GetFollowingSymbols_Right( CODNodeArray& Nodes );
    virtual size_t GetFollowingSymbols_Left( CODNodeArray& Nodes );
    virtual size_t GetFollowingSymbols_Up( CODNodeArray& Nodes );
    virtual size_t GetFollowingSymbols_Down( CODNodeArray& Nodes );

    // All methods to obtain following symbols
    virtual size_t GetEnteringSymbols( CODNodeArray& Nodes );
    virtual size_t GetEnteringSymbols_Right( CODNodeArray& Nodes );
    virtual size_t GetEnteringSymbols_Left( CODNodeArray& Nodes );
    virtual size_t GetEnteringSymbols_Up( CODNodeArray& Nodes );
    virtual size_t GetEnteringSymbols_Down( CODNodeArray& Nodes );

    // All methods to obtain leaving links
    virtual size_t GetEdgesLeaving( CODEdgeArray& Edges );
    virtual size_t GetEdgesLeaving_Right( CODEdgeArray& Edges );
    virtual size_t GetEdgesLeaving_Left( CODEdgeArray& Edges );
    virtual size_t GetEdgesLeaving_Up( CODEdgeArray& Edges );
    virtual size_t GetEdgesLeaving_Down( CODEdgeArray& Edges );

    // All methods to obtain entering links
    virtual size_t GetEdgesEntering( CODEdgeArray& Edges );
    virtual size_t GetEdgesEntering_Right( CODEdgeArray& Edges );
    virtual size_t GetEdgesEntering_Left( CODEdgeArray& Edges );
    virtual size_t GetEdgesEntering_Up( CODEdgeArray& Edges );
    virtual size_t GetEdgesEntering_Down( CODEdgeArray& Edges );

    // ******************************************************************************************************
    // JMR-MODIF - Le 7 février 2006 - Ajout des fonctions permettant de déterminer si l'objet a été copié.
    // ATTENTION : Cet indicateur n'est valable que pour déterminer si une copie de cet objet a été crée au 
    // cours de l'utilisation du logiciel. Ceci est voulu, car ces fonctions sont utilisées pour détruire des
    // données persistantes en mémoire seulement si un ordre de copie a été donné pour cet objet lors de son
    // utilisation. Mais ce n'est pas un indicateur persistant, c'est à dire qu'il n'est pas sauvegardé. Lors
    // de l'ouverture d'un fichier, les objets symboles ne sont pas crées de la même manière, et les données
    // persistantes à supprimer n'existe plus. Pour cette raison, s'il s'agit vraiment de déterminer si l'objet
    // est une copie d'un autre objet, alors cet indicateur devient faussé. Pour déterminer si l'objet est une
    // copie, il faut utiliser la fonction IsLocal(), qui utilise une donnée persistante.
    // SVP NE PAS CHANGER LE FONCTIONNEMENT DE CES FONCTIONS DE MANIERE IRREFLECHIE, CAR ELLES SONT UTILISEES
    // POUR UN BUT PRECIS, QUI EST LE NETTOYAGE DE LA MEMOIRE, ET UNE MODIFICATION INADAPTEE RISQUE DE
    // DESTABILISER LE PROGRAMME.
    void SetIsCopy( BOOL Value = TRUE )
    {
        m_IsCopy = Value;
    }

    BOOL IsCopy()
    {
        return m_IsCopy;
    }
    // ******************************************************************************************************

    /* Serializes the symbol. */
    virtual void Serialize( CArchive& ar );

    // Update mecanism for symbol change
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

protected:

    ///////////////////////////////////////////////////////
    // ZIBasicSymbol methods
    virtual CODLabelComponent* CreateSymbolLabel();

    virtual CODComponent* GetpEditBoxArea()
    {
        return ZVSymbolAttributes::GetpEditBoxArea();
    }

    virtual void SetpEditBoxArea( CODComponent* value )
    {
        ZVSymbolAttributes::SetpEditBoxArea( value );
    }

    virtual CODTextComponent* GetpNameEditText()
    {
        return ZVSymbolAttributes::GetpNameEditText();
    }

    virtual void SetpNameEditText( CODTextComponent* value )
    {
        ZVSymbolAttributes::SetpNameEditText( value );
    }

    virtual CODTextComponent* GetpCommentEditText()
    {
        return ZVSymbolAttributes::GetpCommentEditText();
    }

    virtual void SetpCommentEditText( CODTextComponent* value )
    {
        ZVSymbolAttributes::SetpCommentEditText( value );
    }

    virtual CODLineComponent* GetpSplitter1()
    {
        return ZVSymbolAttributes::GetpSplitter1();
    }

    virtual void SetpSplitter1( CODLineComponent* value )
    {
        ZVSymbolAttributes::SetpSplitter1( value );
    }

    virtual CODLineComponent* GetpSplitter2()
    {
        return ZVSymbolAttributes::GetpSplitter2();
    }

    virtual void SetpSplitter2( CODLineComponent* value )
    {
        ZVSymbolAttributes::SetpSplitter2( value );
    }

    void SetpModel( CODModel* pValue )
    {
        m_pModel = pValue;
    }

    // All methods to obtain leaving and entering links of a specific name
    size_t GetEdgesLeaving_Name( const CString Name, CODEdgeArray& Edges );
    size_t GetEdgesEntering_Name( const CString Name, CODEdgeArray& Edges );
    
protected:

    bool                    m_IsInCreationProcess;
    bool                    m_IsLocal;

    CODSymbolComponent*        m_pReference;

    CString                    m_NameOfReference;

    // Used to display all symbols related to Users, forms, etc.
    CPoint                    m_AllSymbolPosition;

    // The sub model
    CODModel*                m_pModel;

    // The manager for dynamic properties management
    ZBDynamicProperties*    m_DynamicPropManager;

private:

    CString                    m_Name;
    CString                    m_Comment;
    CString                    m_ChildModelPathName;

    COLORREF                m_CurrentLineColor;
    COLORREF                m_CurrentLabelLineColor;
    COLORREF                m_InitialLineColor;
    COLORREF                m_InitialLabelLineColor;

    int                        m_InitialLineWidth;
    int                        m_InitialLabelLineWidth;

    CPoint                    m_ShortCutBitmapPosition;

    // Bitmap resource
    static PSS_Bitmap         m_ShortCutBitmap;

    // JMR-MODIF - Le 7 février 2006 - Ajout d'un flag permettant de déterminer si l'objet crée est une copie.
    BOOL                    m_IsCopy;
};

inline CString ZBSymbol::GetNameOfReference() const
{
    return m_NameOfReference;
}

inline void ZBSymbol::SetNameOfReference( CString value )
{
    m_NameOfReference = value;
}

inline CODModel* ZBSymbol::GetChildModel()
{
    return m_pModel;
}

inline void ZBSymbol::SetChildModel( CODModel* pModel )
{
    m_pModel = pModel;
}

inline bool ZBSymbol::IsLocal() const
{
    return m_IsLocal;
}

inline int ZBSymbol::GetRightSubMenu() const
{
    return -1;
}

inline int ZBSymbol::GetIconIndex() const
{
    return -1;
}

inline bool ZBSymbol::IsReferenced() const
{
    return !m_NameOfReference.IsEmpty();
}

inline bool ZBSymbol::IsReferenceValid() const
{
    return ( !m_NameOfReference.IsEmpty() && m_pReference != NULL );
}

inline CODSymbolComponent* ZBSymbol::GetSymbolReference() const
{
    return m_pReference;
}

inline CODComponent* ZBSymbol::FindSymbol( const CString SymbolName )
{
    return ZBSymbol::FindSymbol( this, SymbolName );
}

inline BOOL ZBSymbol::RemoveSymbol( CODComponent* pComponent )
{
    return RemoveSymbol( this, pComponent );
}

inline COLORREF ZBSymbol::GetInitialLineColor() const
{
    return m_InitialLineColor;
}

inline int ZBSymbol::GetInitialLineWidth() const
{
    return m_InitialLineWidth;
}

inline COLORREF ZBSymbol::GetInitialLabelLineColor() const
{
    return m_InitialLabelLineColor;
}

inline int ZBSymbol::GetInitialLabelLineWidth() const
{
    return m_InitialLabelLineWidth;
}

// Call by the controller when a tooltip is required
inline bool ZBSymbol::OnToolTip( CString& ToolTipText, CPoint point, ToolTipMode ToolTip /*= NormalToolTip*/ )
{
    return false;
}

#endif // !defined(AFX_ZBSYMBOL_H__2D0F308C_3DD6_402F_9954_202E6053BEB8__INCLUDED_)