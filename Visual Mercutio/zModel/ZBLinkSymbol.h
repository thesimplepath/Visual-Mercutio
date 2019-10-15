// ZBLinkSymbol.h: interface for the ZBLinkSymbol class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBLINKSYMBOL_H__E3F0977D_D63F_41AF_8667_2F903330AC3A__INCLUDED_)
#define AFX_ZBLINKSYMBOL_H__E3F0977D_D63F_41AF_8667_2F903330AC3A__INCLUDED_

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
#include "zProperty\ZIProperties.h"
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseSym\ZIBasicSymbolAcceptVisitor.h"
#include "zBaseSym\ZIBasicSymbolVisitor.h"
#include "zBaseLib\PSS_ToolTip.h"

// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"

#include "zModel\ZBExtAppPropertyMgr.h"
#include "zModel\ZBExtFilePropertyMgr.h"
#include "zModel\ZVSymbolAttributes.h"

#include "zBaseLib\PSS_Bitmap.h"

#include "zModel\Maths.h"

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

// JMR-MODIF - Le 28 septembre 2005 - Ajout de la décoration unicode _T( ), suppression du code inutilisé.

class AFX_EXT_CLASS ZBLinkSymbol : public CODLinkComponent,
                                   public ZIBasicSymbol,
                                   public ZIObjectPath,
                                   public ZIProperties,
                                   public ZBExtAppPropertyMgr,
                                   public ZBExtFilePropertyMgr,
                                   public ZVSymbolAttributes,
                                   public ZIBasicSymbolAcceptVisitor,
                                   public PSS_Subject,
                                   public PSS_Observer,
                                   public PSS_ToolTip
{
    DECLARE_SERIAL(ZBLinkSymbol)

public:

    ZBLinkSymbol();
    virtual ~ZBLinkSymbol();

    /* Copy constructor. */
    ZBLinkSymbol(const ZBLinkSymbol& src);

    /* Assignment operator. */
    ZBLinkSymbol& operator=(const ZBLinkSymbol& src);

    /* Create a duplicate copy of this object. */
    virtual CODComponent* Dup() const;

    // Return the unique object type ID
    virtual int GetObjectTypeID() const
    {
        return -1;
    };

    virtual BOOL OnConnectionMove(CODConnection* pConnection);

    virtual void OnMove();

    // Creates the link symbol 
    BOOL Create(int nStyle = -1, int nPointSize = -1, COLORREF crColor = -1, int bTransparent = -1);
    BOOL CreateOrthogonal(int nStyle = -1, int nPointSize = -1, COLORREF crColor = -1, int bTransparent = -1);
    BOOL SetLineProperty(int nStyle, int nPointSize = -1, COLORREF crColor = -1, int bTransparent = -1);

    //////////////////////////////////////////////////////////////////////
    // Attributes management methods
    virtual bool AcceptDynamicAttributes() const
    {
        return true;
    };

    virtual bool OnFillDefaultAttributes(ZBPropertyAttributes* pAttributes);
    virtual bool OnChangeAttributes(ZBPropertyAttributes* pAttributes);
    virtual CString GetAttributeString(ZBPropertyAttributes* pAttributes) const;
    virtual void RefreshAttributeAreaText(bool Redraw = false);

    bool GetDisplayTitleText() const;
    void SetDisplayTitleText(bool value);

    ///////////////////////////////////////////////////////
    // Basic Symbol methods

    // Create the symbol itself
    BOOL Create(UINT nID, HINSTANCE hInst, const CString Name = _T(""));

    ZBSymbolEdit* CreateEditText(const CString AreaName, const CString EditName, CODComponent* pParent = NULL);
    ZBSymbolEdit* CreateAndReplaceEditText(const CString EditName, CODComponent* pParent = NULL);

    virtual CString GetSymbolComment();
    virtual BOOL SetSymbolComment(const CString value);

    virtual CString GetSymbolName();
    virtual BOOL SetSymbolName(const CString value);

    // JMR-MODIF - Le 27 mars 2006 - Ajout de la fonction virtuelle OnSymbolNameChange.
    virtual void OnSymbolNameChange(CString OldName, CString NewName)
    {}

    virtual int GetSymbolReferenceNumber();
    virtual CString GetSymbolReferenceNumberStr();
    virtual BOOL SetSymbolReferenceNumber(int value);
    virtual BOOL SetSymbolReferenceNumberStr(const CString value);

    virtual bool Match(const CString            What,
                       ZBPropertyAttributes*    pPropAttributes = NULL,
                       bool                    CaseSensitive = false,
                       bool                    PartialSearch = false);

    // Unit retreival methods
    CString RetreiveUnitGUID(const CString Name, bool& Error) const;
    CString RetreiveUnitName(const CString GUID, bool& Error) const;
    CString RetreiveUnitDescription(const CString GUID, bool& Error) const;
    float RetreiveUnitCost(const CString GUID, bool& Error) const;

    // Logical system retreival methods
    CString RetreiveLogicalSystemGUID(const CString Name, bool& Error) const;
    CString RetreiveLogicalSystemName(const CString GUID, bool& Error) const;
    CString RetreiveLogicalSystemDescription(const CString GUID, bool& Error) const;

    virtual void EditSymbolName();

    // Check if the new name is a valid one
    virtual bool IsNewNameValid(const CString value) const;

    // Return the Edit Box area
    virtual CODComponent* GetEditBoxArea()
    {
        return ZVSymbolAttributes::GetEditBoxArea();
    };

    // Return the comment Edit
    virtual CODTextComponent* GetCommentTextEdit()
    {
        return ZVSymbolAttributes::GetCommentTextEdit();
    };

    // The comment can be edited
    virtual bool CommentTextEditReadOnly() const
    {
        return false;
    };

    // Return the symbol name Edit
    virtual CODTextComponent* GetSymbolNameTextEdit()
    {
        return ZVSymbolAttributes::GetSymbolNameTextEdit();
    };

    // The symbol name can be edited
    virtual bool SymbolNameTextEditReadOnly() const
    {
        return false;
    };

    virtual CODTextComponent* GetAttributeTextEdit()
    {
        return ZVSymbolAttributes::GetAttributeTextEdit();
    };

    virtual CODLineComponent* GetSplitter1()
    {
        return ZVSymbolAttributes::GetSplitter1();
    };

    virtual CODLineComponent* GetSplitter2()
    {
        return ZVSymbolAttributes::GetSplitter2();
    };

    // Copy the definition only
    virtual void CopySymbolDefinitionFrom(CODSymbolComponent& src);

    virtual CString GetNameOfReference() const;
    virtual void SetNameOfReference(CString value);

    virtual bool IsLocal() const;
    virtual void SetIsLocal(bool value = true);

    // JMR-MODIF - Le 22 mars 2006 - Fonction permettant de définir si le symbole est générique.
    virtual BOOL IsGeneric()
    {
        return FALSE;
    }

    // ****************************************************************************
    // JMR-MODIF - Le 29 juillet 2007 - Ajout des fonctions concernant les risques.

    CString GetRiskLevel();
    void SetRiskLevel(CString Level);
    // ****************************************************************************

    //////////////////////////////////////////////////////////////////////
    // Area state methods
    virtual bool IncludeNameArea() const
    {
        // The default is true to have a name area
        return true;
    };

    virtual bool IncludeDescriptionArea() const
    {
        // Default return false
        return false;
    };

    virtual bool IncludeAttributeArea() const
    {
        // Default return false
        return false;
    };

    virtual void DisplayNameArea(bool value = true)
    {
        ZVSymbolAttributes::DisplayNameArea(value);
    };

    virtual bool IsNameAreaVisible() const
    {
        return ZVSymbolAttributes::IsNameAreaVisible();
    };

    virtual void DisplayDescriptionArea(bool value = true)
    {
        ZVSymbolAttributes::DisplayDescriptionArea(value);
    };

    virtual bool IsDescriptionsAreaVisible() const
    {
        return ZVSymbolAttributes::IsDescriptionsAreaVisible();
    };

    virtual void DisplayAttributeArea(bool value = true)
    {
        ZVSymbolAttributes::DisplayAttributeArea(value);
    };

    virtual bool IsAttributeAreaVisible() const
    {
        return ZVSymbolAttributes::IsAttributeAreaVisible();
    };

    //////////////////////////////////////////////////////////////////////
    // Symbol mouse methods
    virtual bool AcceptMouseInteraction() const
    {
        // Yes, in order to manage the attributes' splitters
        return true;
    };

    virtual bool OnMouseMove(UINT nFlags, CPoint point, CODController& Ctrl)
    {
        return ZVSymbolAttributes::OnMouseMove(nFlags, point, Ctrl);
    };

    virtual bool OnLButtonDown(UINT nFlags, CPoint point, CODController& Ctrl)
    {
        return ZVSymbolAttributes::OnLButtonDown(nFlags, point, Ctrl);
    };

    virtual bool OnLButtonUp(UINT nFlags, CPoint point, CODController& Ctrl)
    {
        return ZVSymbolAttributes::OnLButtonUp(nFlags, point, Ctrl);
    };

    virtual bool OnLButtonDblClk(UINT nFlags, CPoint point, CODController& Ctrl)
    {
        return false;
    };

    virtual bool OnRButtonDown(UINT nFlags, CPoint point, CODController& Ctrl)
    {
        return false;
    };

    virtual bool OnRButtonUp(UINT nFlags, CPoint point, CODController& Ctrl)
    {
        return false;
    };

    // Show the symbol in error
    virtual void ShowInError(bool value = true);

    // Apply the format coming from another object
    virtual void ApplyFormatFromObject(CODSymbolComponent&    Object,
                                       bool                Font = true,
                                       bool                Fill = true,
                                       bool                Line = true);

    // Used to find the local symbol of this reference
    virtual CODComponent* GetLocalSymbol();

    // Used to find the referenced symbol of this master symbol
    virtual CODComponentSet* GetReferenceSymbols();

    virtual bool IsReferenced() const;
    virtual bool IsReferenceValid() const;
    virtual void AssignReferenceSymbol(CODSymbolComponent* pReference);
    virtual void RemoveReferenceSymbol();
    virtual CODSymbolComponent* GetSymbolReference() const;

    // Return true if the symbol can contain a child model
    virtual bool CanContainChildModel() const
    {
        return false;
    };

    virtual bool IsChildModelRef() const
    {
        return false;
    };

    // Return the right sub menu number
    virtual int    GetRightSubMenu() const
    {
        return -1;
    }

    // Return the symbol index image
    virtual int GetIconIndex() const
    {
        return 0;
    }

    // Retreive the owner symbol model
    virtual CODModel* GetOwnerModel();

    // Retreive the root symbol model
    virtual CODModel* GetRootModel();

    // Set the model modified flag to the specified value
    virtual void SetModifiedFlag(BOOL Value = TRUE);

    /* Called after the object is created and on the desk
       return true if the object can be created or false if the
       object must be destroyed immediatly */
    virtual bool OnPostCreation(CODModel* pModel = NULL, CODController* pCtrl = NULL)
    {
        if (!InitializeAttributeAreas())
        {
            return false;
        }

        // Check the size of components
        AdjustAreaPosition();

        return true;
    };

    /* Called before the object is deleted
       return true if the object can be deleted */
    virtual bool OnPreDelete(CODModel* pModel = NULL, CODController* pCtrl = NULL)
    {
        // The default is to return true
        return true;
    };

    /* Called after the double click occured on the object */
    virtual void OnPostDoubleClick(CODModel* pModel = NULL, CODController* pCtrl = NULL)
    {
        // Does nothing in the base class method
    };

    virtual void CalculateAbsolutePath()
    {
        // If no path defined
        if (GetAbsolutePath().IsEmpty())
        {
            AddMemberToPath(GetSymbolName());
        }
    };

    // Redraw the symbol
    virtual void RedrawSymbol();

    // JMR-MODIF - Le 18 janvier 2006 - Ajout de la fonction AdjustLinePath
    void AdjustLinePath();

    // Drag and drop methods
    virtual bool AcceptDropItem(CObject* pObj, CPoint pt)
    {
        return (AcceptExtApp() && ZBExtAppPropertyMgr::AcceptDropItem(pObj, pt)) ||
            (AcceptExtFile() && ZBExtFilePropertyMgr::AcceptDropItem(pObj, pt));
    };

    virtual bool DropItem(CObject* pObj, CPoint pt)
    {
        return ((AcceptExtApp() && ZBExtAppPropertyMgr::AcceptDropItem(pObj, pt)) ? ZBExtAppPropertyMgr::DropItem(pObj, pt) : false) ||
            ((AcceptExtFile() && ZBExtFilePropertyMgr::AcceptDropItem(pObj, pt)) ? ZBExtFilePropertyMgr::DropItem(pObj, pt) : false);
    };

    // External file and external application methods
    virtual bool AcceptExtApp() const
    {
        return false;
    };

    virtual bool DoInsertExtApp(bool DisplayDialog = true)
    {
        return ZBExtAppPropertyMgr::DoInsertExtApp(DisplayDialog);
    };

    virtual bool AcceptExtFile() const
    {
        return false;
    };

    virtual bool DoInsertExtFile(bool DisplayDialog = true)
    {
        return ZBExtFilePropertyMgr::DoInsertExtFile(DisplayDialog);
    };

    //////////////////////////////////////////////////////////////////////
    // Unit methods
    virtual bool HasUnit() const
    {
        return false;
    };

    virtual CString GetUnitName() const
    {
        return _T("");
    };

    virtual CString GetUnitGUID() const
    {
        return _T("");
    };

    ///////////////////////////////////////////////////////
    // Properties methods

    // Return true if the object has properties
    virtual bool HasProperties() const
    {
        return true;
    };

    // Call to retreive properties for the object
    virtual bool FillProperties(ZBPropertySet& PropSet, bool NumericValue = false, bool GroupValue = false);

    // Call to save new changes to object's properties
    virtual bool SaveProperties(ZBPropertySet& PropSet);

    // Called to retreive a property for the object
    virtual bool FillProperty(ZBProperty& Property);

    // Called to save a property for the object
    virtual bool SaveProperty(ZBProperty& Property);

    // Called to check the property value
    virtual bool CheckPropertyValue(ZBProperty& Property, CString& value, ZBPropertySet& Properties);

    // Called to process the extended input for the property value
    virtual bool ProcessExtendedInput(ZBProperty&        Property,
                                      CString&            value,
                                      ZBPropertySet&    Properties,
                                      bool&            Refresh);

    // Called to process the a menu command for the property value
    virtual bool ProcessMenuCommand(int            MenuCommand,
                                    ZBProperty&    Property,
                                    CString&        value,
                                    ZBPropertySet&    Properties,
                                    bool&            Refresh);

    // Called before the property changed
    virtual bool OnPrePropertyChanged(CString NewValue, ZBProperty& Property, ZBPropertySet& Properties);

    // Called after the property changed
    virtual bool OnPostPropertyChanged(ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh);

    // Called when an internal drag&drop of property occured
    virtual bool OnDropInternalPropertyItem(ZBProperty&    SrcProperty,
                                            ZBProperty&    DstProperty,
                                            bool            Top2Down,
                                            ZBPropertySet&    Properties);

    // Call to create the properties
    virtual bool CreateSymbolProperties();

    // Call to know if properties can be edited
    virtual bool IsPropertiesReadOnly() const
    {
        return false;
    };

    virtual ZBDynamicProperties* GetDynamicPropertiesManager()
    {
        return m_DynamicPropManager;
    };

    //////////////////////////////////////////////////////////////////////
    // Call-back on symbols
    virtual void OnSymbolNameChanged(CODComponent& Comp, const CString OldName)
    {};

    virtual void OnPageNameChanged(ZDProcessGraphPage* pPage, const CString OldName)
    {};

    virtual void OnUserEntityChanged(ZBUserEntity* pUserEntity, const CString OldName)
    {};

    //////////////////////////////////////////////////////////////////////
    // ZIBasicSymbolAcceptVisitor methods

    /* AcceptVisitor method let the object be visited
       by concreted derived ZIBasicSymbolVisitor classes */
    virtual bool AcceptVisitor(ZIBasicSymbolVisitor& Visitor)
    {
        return Visitor.Visit(*this);
    };

    /* Serializes the symbol. */
    virtual void Serialize(CArchive& ar);

    // Update mecanism for symbol change
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    // Call by the controller when a tooltip is required
    virtual bool OnToolTip(CString& ToolTipText, CPoint point, PSS_ToolTip::IEToolTipMode ToolTip = PSS_ToolTip::IE_TT_Normal);

    /////////////////////////////////////////////////////////////////////////////
    // Following and Entering link methods

    virtual CODSymbolComponent* GetFollowingSymbol();
    virtual CODSymbolComponent* GetEnteringSymbol();

    // JMR-MODIF - Le 22 juillet 2007 - Ajout de la fonction UpdateGraphicFromRisk.
    void UpdateGraphicFromRisk(COLORREF Color, BOOL Italic);

    // Get and Set the current line color
    virtual void SetCurrentLineColor(COLORREF value);
    virtual COLORREF GetCurrentLineColor() const
    {
        return m_CurrentLineColor;
    };

    // Get and Set the current line width
    virtual void SetCurrentLineWidth(int value);
    virtual int GetCurrentLineWidth() const
    {
        return m_CurrentLineWidth;
    };

    // Get and Set the current line style.
    virtual void SetCurrentLineStyle(int value);
    virtual int GetCurrentLineStyle() const
    {
        return m_CurrentLineStyle;
    };

    // Get and Set the initial line style.
    virtual void SetInitialLineStyle(int value);
    virtual int GetInitialLineStyle() const
    {
        return m_InitialLineStyle;
    };

    // Get and Set the current label color
    virtual void SetCurrentLabelColor(COLORREF value);
    virtual COLORREF GetCurrentLabelColor() const
    {
        return m_CurrentLabelLineColor;
    };

    COLORREF    GetInitialLineColor() const;
    void        SetInitialLineColor(COLORREF value);
    int            GetInitialLineWidth() const;
    void        SetInitialLineWidth(int value);
    COLORREF    GetInitialLabelLineColor() const;
    void        SetInitialLabelLineColor(COLORREF value);
    int            GetInitialLabelLineWidth() const;
    void        SetInitialLabelLineWidth(int value);

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

    void SetIsCopy(BOOL Value = TRUE)
    {
        m_IsCopy = Value;
    }

    BOOL IsCopy()
    {
        return m_IsCopy;
    }
    // ******************************************************************************************************

protected:

    ///////////////////////////////////////////////////////
    // ZIBasicSymbol methods
    virtual CODLabelComponent* CreateSymbolLabel();

    virtual CODComponent* GetpEditBoxArea()
    {
        return ZVSymbolAttributes::GetpEditBoxArea();
    };

    virtual void SetpEditBoxArea(CODComponent* value)
    {
        ZVSymbolAttributes::SetpEditBoxArea(value);
    };

    virtual CODTextComponent* GetpNameEditText()
    {
        return ZVSymbolAttributes::GetpNameEditText();
    };

    virtual void SetpNameEditText(CODTextComponent* value)
    {
        ZVSymbolAttributes::SetpNameEditText(value);
    };

    virtual CODTextComponent* GetpCommentEditText()
    {
        return ZVSymbolAttributes::GetpCommentEditText();
    };

    virtual void SetpCommentEditText(CODTextComponent* value)
    {
        ZVSymbolAttributes::SetpCommentEditText(value);
    };

    virtual CODLineComponent* GetpSplitter1()
    {
        return ZVSymbolAttributes::GetpSplitter1();
    };

    virtual void SetpSplitter1(CODLineComponent* value)
    {
        ZVSymbolAttributes::SetpSplitter1(value);
    };

    virtual CODLineComponent* GetpSplitter2()
    {
        return ZVSymbolAttributes::GetpSplitter2();
    };

    virtual void SetpSplitter2(CODLineComponent* value)
    {
        ZVSymbolAttributes::SetpSplitter2(value);
    };

protected:

    bool                    m_IsInCreationProcess;
    bool                    m_IsLocal;

    CODSymbolComponent*        m_pReference;

    CString                    m_NameOfReference;

    // The manager for dynamic properties management
    ZBDynamicProperties*    m_DynamicPropManager;

private:

    COLORREF                m_CurrentLineColor;
    COLORREF                m_CurrentLabelLineColor;
    COLORREF                m_InitialLineColor;
    COLORREF                m_InitialLabelLineColor;

    int                        m_CurrentLineWidth;
    int                        m_InitialLineWidth;
    int                        m_InitialLabelLineWidth;

    int                        m_CurrentLineStyle;
    int                        m_InitialLineStyle;

    // Used to display all symbols related to
    // Users, forms, etc.
    CPoint                    m_AllSymbolPosition;

    // Used to display the shortcut bitmap for referenced symbol
    CPoint                    m_ShortCutBitmapPosition;

    // Bitmap resource
    static    PSS_Bitmap      m_ShortCutBitmap;

    // JMR-MODIF - Le 7 février 2006 - Ajout d'un flag permettant de déterminer si l'objet crée est une copie.
    BOOL                    m_IsCopy;
};

// Call by the controller when a tooltip is required
inline bool ZBLinkSymbol::OnToolTip(CString& ToolTipText, CPoint point, PSS_ToolTip::IEToolTipMode ToolTip)
{
    return false;
}

inline CString ZBLinkSymbol::GetNameOfReference() const
{
    return m_NameOfReference;
}

inline void ZBLinkSymbol::SetNameOfReference(CString value)
{
    m_NameOfReference = value;
}

inline bool ZBLinkSymbol::IsLocal() const
{
    return m_IsLocal;
}

inline bool ZBLinkSymbol::IsReferenced() const
{
    return !m_NameOfReference.IsEmpty();
}

inline bool ZBLinkSymbol::IsReferenceValid() const
{
    return (!m_NameOfReference.IsEmpty() && m_pReference != NULL);
}

inline CODSymbolComponent* ZBLinkSymbol::GetSymbolReference() const
{
    return m_pReference;
}

inline COLORREF ZBLinkSymbol::GetInitialLineColor() const
{
    return m_InitialLineColor;
}

inline int ZBLinkSymbol::GetInitialLineWidth() const
{
    return m_InitialLineWidth;
}

inline COLORREF ZBLinkSymbol::GetInitialLabelLineColor() const
{
    return m_InitialLabelLineColor;
}

inline int ZBLinkSymbol::GetInitialLabelLineWidth() const
{
    return m_InitialLabelLineWidth;
}

#endif
