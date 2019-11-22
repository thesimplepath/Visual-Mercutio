// ZVSymbolAttributes.h: interface for the ZVSymbolAttributes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ZVSYMBOLATTRIBUTES_H__)
#define _ZVSYMBOLATTRIBUTES_H__

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

#include "zBaseSym\PSS_BasicSymbol.h"

// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 3 octobre 2005 - Ajout des décorations unicode _T( ), suppression du code inutile. (En commentaires)

class AFX_EXT_CLASS ZVSymbolAttributes
{
public:

    ZVSymbolAttributes(PSS_BasicSymbol* pSymbol = NULL )
    {
        m_pEditBoxArea                    = NULL;
        m_pNameEditText                    = NULL;
        m_pCommentEditText                = NULL;
        m_pAttributeEditText            = NULL;
        m_pSplitterComponent1            = NULL;
        m_pSplitterComponent2            = NULL;

        m_pSymbol                        = pSymbol;

        m_UseDynamicArea                = true;
        m_DisplayNameArea                = true;

        m_DisplayDescriptionArea        = false;
        m_DisplayAttributeArea            = false;
        m_RelativeCoordinates            = false;
        m_ReinitializeAreaAtCreation    = false;
    };

    virtual ~ZVSymbolAttributes()
    {
        // JMR-MODIF - Le 21 septembre 2005 - Nettoyage des memory leaks, ajout du code de nettoyage de l'objet.
        if ( m_pSymbol != NULL )
        {
            dynamic_cast<CODComponent*>( m_pSymbol )->RemoveAllChildren();
        }
    };

    void SetSymbol(PSS_BasicSymbol* pSymbol )
    {
        m_pSymbol = pSymbol;
    };

    /* Copy constructor. */
    ZVSymbolAttributes( const ZVSymbolAttributes& src )
    {
        *this = src;
    };

    /* Assignment operator. */
    ZVSymbolAttributes& operator=( const ZVSymbolAttributes& src );

    // Return the pointer to attributes
    ZBPropertyAttributes& GetAttributes()
    {
        return m_Attributes;
    };

    BOOL InitializeAttributeAreas();

    void AdjustAreaPosition( CODLineComponent* pComp = NULL, int y = -1 );
    void AdjustElementPosition();

    virtual void SetUseDynamicArea( bool value = true )
    {
        m_UseDynamicArea = value;
    };

    virtual bool UseDynamicArea() const
    {
        return m_UseDynamicArea;
    };

    virtual void DisplayNameArea( bool value = true )
    {
        m_DisplayNameArea = value;
    };

    virtual bool IsNameAreaVisible() const
    {
        return m_DisplayNameArea;
    };

    virtual void DisplayDescriptionArea( bool value = true )
    {
        m_DisplayDescriptionArea = value;
    };

    virtual bool IsDescriptionsAreaVisible() const
    {
        return m_DisplayDescriptionArea;
    };

    virtual void DisplayAttributeArea( bool value = true )
    {
        m_DisplayAttributeArea = value;
    };

    virtual bool IsAttributeAreaVisible() const
    {
        return m_DisplayAttributeArea;
    };

    // Return the Edit Box area
    CODComponent* GetEditBoxArea();

    // Return the comment Edit
    CODTextComponent* GetCommentTextEdit();

    // Return the symbol name Edit
    CODTextComponent* GetSymbolNameTextEdit();
    
    CODTextComponent* GetAttributeTextEdit();
    CODLineComponent* GetSplitter1();
    CODLineComponent* GetSplitter2();

    CODComponent* GetEditBoxAreaComponent()
    {
        return m_pEditBoxArea;
    };

    void SetEditBoxAreaComponent( CODComponent* value )
    {
        m_pEditBoxArea = value;
    };

    CODTextComponent* GetNameEditTextComponent()
    {
        return m_pNameEditText;
    };

    void SetNameEditTextComponent( CODTextComponent* value )
    {
        m_pNameEditText = value;
    };

    CODTextComponent* GetCommentEditTextComponent()
    {
        return m_pCommentEditText;
    };

    void SetCommentEditTextComponent( CODTextComponent* value )
    {
        m_pCommentEditText = value;
    };

    CODLineComponent* GetSplitter1Component()
    {
        return m_pSplitterComponent1;
    };

    void SetSplitter1Component( CODLineComponent* value )
    {
        m_pSplitterComponent1 = value;
    };

    CODLineComponent* GetSplitter2Component()
    {
        return m_pSplitterComponent2;
    };

    void SetSplitter2Component( CODLineComponent* value )
    {
        m_pSplitterComponent2 = value;
    };

    //////////////////////////////////////////////////////////////////////
    // Symbol mouse methods
    bool OnMouseMove    ( UINT nFlags, CPoint point, CODController& Ctrl );
    bool OnLButtonDown    ( UINT nFlags, CPoint point, CODController& Ctrl );
    bool OnLButtonUp    ( UINT nFlags, CPoint point, CODController& Ctrl );

protected:

    void MoveTo( CODComponent& Comp, CRect& rcPosition );
    void MoveTo( CODComponent& Comp, CPoint point );
    void Scale ( CODComponent& Comp, const CSize& szBounds, const OD_CONTROL_POINT nControlPoint );

protected:

    CODComponent*            m_pEditBoxArea;
    CODTextComponent*        m_pNameEditText;
    CODTextComponent*        m_pCommentEditText;
    CODTextComponent*        m_pAttributeEditText;
    CODLineComponent*        m_pSplitterComponent1;
    CODLineComponent*        m_pSplitterComponent2;

    bool                    m_UseDynamicArea;
    bool                    m_DisplayNameArea;
    bool                    m_DisplayDescriptionArea;
    bool                    m_DisplayAttributeArea;

    // Due to a bug, it is necessary to reinitialize
    // the area for symbol but not for deliverables
    bool                    m_ReinitializeAreaAtCreation;

    bool                    m_RelativeCoordinates;

    // Contains all the dynamic attributes
    ZBPropertyAttributes    m_Attributes;

    //@cmember
    /* Pointer to symbol. */
    PSS_BasicSymbol*            m_pSymbol;
};

#endif // !defined(_ZVSYMBOLATTRIBUTES_H__)