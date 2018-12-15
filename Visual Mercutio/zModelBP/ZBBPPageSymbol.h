// ZBBPPageSymbol.h: interface for the ZBBPPageSymbol class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBBPPageSymbol_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPPageSymbol_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

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

#include "zModel\ZBSymbol.h"

// Forward declaration
class ZDProcessGraphPage;
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

// JMR-MODIF - Le 4 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBBPPageSymbol : public ZBSymbol
{
    DECLARE_SERIAL( ZBBPPageSymbol )

public:

    ZBBPPageSymbol( const CString Name = _T( "" ) );
    virtual ~ZBBPPageSymbol();

    /* Copy constructor. */
    ZBBPPageSymbol( const ZBBPPageSymbol& src );

    /* Assignment operator. */
    ZBBPPageSymbol& operator=( const ZBBPPageSymbol& src );

    /* Create a duplicate copy of this object. */
    virtual CODComponent* Dup() const;

    // Return the page pointer
    ZDProcessGraphPage* GetPage()
    {
        return m_pPage;
    }

    // Return the model page
    ZDProcessGraphModelMdl* GetModelPage();

    // Set a new model to the page
    bool SetPageModel( ZDProcessGraphModelMdl* pModel );

    // Used to recalculate the twin page reference serialized by its reference number
    void RecalculateTwinPageReference( ZDProcessGraphModelMdl* pRootModel );

    int GetTwinPageReferenceNumber() const
    {
        return m_TwinPageRefNumber;
    }

    void SetTwinPageReferenceNumber( int RefNumber );
    void RemoveTwinPageSymbol( bool RemoveTwin = true );
    void AssignTwinPageSymbol( ZBBPPageSymbol* pPage );

    ZBBPPageSymbol* GetTwinPageSymbol() const
    {
        return m_pTwinPageSymbol;
    }

    void SetTwinPageSymbol( ZBBPPageSymbol* pPage )
    {
        m_pTwinPageSymbol = pPage;
    }

    // JMR-MODIF - Le 3 septembre 2006 - Ajout de la fonction DuplicateStyleOnTwinSymbol.
    BOOL DuplicateStyleOnTwinSymbol();

    //////////////////////////////////////////////////////////////////////
    // Attributes management methods
    virtual bool AcceptDynamicAttributes() const
    {
        // No dynamic attributes
        return false;
    }

    //////////////////////////////////////////////////////////////////////
    // Call-back on symbols
    virtual void OnPageNameChanged( ZDProcessGraphPage* pPage, const CString OldName );

    // Update mecanism for symbol change
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

    ///////////////////////////////////////////////////////
    // Basic Symbol methods

    // Copy the definition only
    virtual void CopySymbolDefinitionFrom( CODSymbolComponent& src );

    // The comment can be edited
    virtual bool CommentTextEditReadOnly() const
    {
        // Cannot be edited
        return false;
    }

    // The symbol name can be edited
    virtual bool SymbolNameTextEditReadOnly() const
    {
        // Cannot be edited
        return true;
    }

    // Return true if the symbol can contain a child model
    virtual bool CanContainChildModel() const
    {
        return true;
    }

    // The child model is a reference
    virtual bool IsChildModelRef() const
    {
        return true;
    }

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

    /* Called before the object is deleted
       return true if the object can be deleted */
    virtual bool OnPreDelete( CODModel* pModel = NULL, CODController* pCtrl = NULL );

    /* Called after the double click occured on the object */
    virtual void OnPostDoubleClick( CODModel* pModel = NULL, CODController* pCtrl = NULL );

    bool GetDisplayPreview() const
    {
        return m_DisplayPreview;
    }

    void SetDisplayPreview( bool value )
    {
        m_DisplayPreview = value;
    }

    ///////////////////////////////////////////////////////
    // Properties methods

    // Return true if the object has properties
    virtual bool HasProperties() const
    {
        return true;
    }

    // Call to retreive properties for the object
    virtual bool FillProperties( ZBPropertySet& PropSet, bool NumericValue = false, bool GroupValue = false );

    // Call to save new changes to object's properties
    virtual bool SaveProperties( ZBPropertySet& PropSet );

    // Call to create the properties
    virtual bool CreateSymbolProperties();

    // Call to know if properties can be edited
    virtual bool IsPropertiesReadOnly() const
    {
        // Properties cannot be edited
        return true;
    }

    virtual void OnDraw(CDC* pDC);

    ULONG STDMETHODCALLTYPE AddRef()
    {
        return CODSymbolComponent::AddRef();
    }

    ULONG STDMETHODCALLTYPE Release()
    {
        return CODSymbolComponent::Release();
    }

    // JMR-MODIF - Le 3 mai 2006 - Fonction permettant de définir si le symbole est une page.
    virtual BOOL IsPage()
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

protected:

    virtual void AdjustElementPosition();
    CString BuildSymbolName();

protected:

    ZDProcessGraphPage*        m_pPage;

private:

    // The model for the canvas. The model holds all information about
    // the canvas, while the viewport actually displays it.
    CRect                    m_CommentRect;

    bool                    m_DisplayPreview;

    CString                    m_PageName;
    CString                    m_SubModelPathName;

    // The twin page name saves the name of the other page
    int                        m_TwinPageRefNumber;

    ZBBPPageSymbol*            m_pTwinPageSymbol;
};

inline int ZBBPPageSymbol::GetRightSubMenu() const
{
    return 7;
}

inline int ZBBPPageSymbol::GetIconIndex() const
{
    return ( IsLocal() ) ? 7 : 15;
}

#endif // !defined(AFX_ZBBPPageSymbol_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)