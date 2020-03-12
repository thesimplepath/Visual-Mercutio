/****************************************************************************
 * ==> PSS_SymbolAttributes ------------------------------------------------*
 ****************************************************************************
 * Description : Provides the symbol attributes                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SymbolAttributesH
#define PSS_SymbolAttributesH

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
#include "zBaseSym\PSS_BasicSymbol.h"
#include "zProperty\PSS_PropertyAttributes.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Symbol attributes
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SymbolAttributes
{
    public:
        /**
        * Constructor
        *@param pSymbol - the symbol which will contain the attributes
        */
        PSS_SymbolAttributes(PSS_BasicSymbol* pSymbol = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SymbolAttributes(const PSS_SymbolAttributes& other);

        virtual ~PSS_SymbolAttributes();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_SymbolAttributes& operator = (const PSS_SymbolAttributes& other);

        /**
        * Sets the symbol
        *@param pSymbol - the symbol
        */
        virtual inline void SetSymbol(PSS_BasicSymbol* pSymbol);

        /**
        * Gets the attributes
        *@return the attributes
        */
        virtual inline PSS_PropertyAttributes& GetAttributes();

        /**
        * Initializes the attribute areas
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitializeAttributeAreas();

        /**
        * Adjusts the area position
        *@param pComp - the splitter component for which position should be adjusted
        *@param y - the y position in pixels
        */
        virtual void AdjustAreaPosition(CODLineComponent* pComp = NULL, int y = -1);

        /**
        * Adjusts the element position
        */
        virtual void AdjustElementPosition();

        /**
        * Sets if the dynamic area should be used
        *@param value - if true, the dynamic area should be used
        */
        virtual inline void SetUseDynamicArea(bool value = true);

        /**
        * Check if the dynamic area should be used
        *@return true if the dynamic area should be used, otherwise false
        */
        virtual inline bool UseDynamicArea() const;

        /**
        * Shows or hides the name area
        *@param value - if true, the name area is shown
        */
        virtual inline void ShowNameArea(bool value = true);

        /**
        * Checks if the name area is visible
        *@return true if the name area is visible, otherwise false
        */
        virtual inline bool IsNameAreaVisible() const;

        /**
        * Shows or hides the description area
        *@param value - if true, the description area is shown
        */
        virtual inline void ShowDescriptionArea(bool value = true);

        /**
        * Checks if the description area is visible
        *@return true if the description area is visible, otherwise false
        */
        virtual inline bool IsDescriptionsAreaVisible() const;

        /**
        * Shows or hides the attribute area
        *@param value - if true, the attribute area is shown
        */
        virtual inline void ShowAttributeArea(bool value = true);

        /**
        * Checks if the attribute area is visible
        *@return true if the attribute area is visible, otherwise false
        */
        virtual inline bool IsAttributeAreaVisible() const;

        /**
        * Gets the edit box area
        *@return the edit box area
        */
        virtual CODComponent* GetEditBoxArea();

        /**
        * Gets the symbol name text edit area
        *@return the symbol name text edit area
        */
        virtual CODTextComponent* GetSymbolNameTextEdit();

        /**
        * Gets the symbol comment text edit area
        *@return the symbol comment text edit area
        */
        virtual CODTextComponent* GetCommentTextEdit();

        /**
        * Gets the attribute text edit area
        *@return the attribute text edit area
        */
        virtual CODTextComponent* GetAttributeTextEdit();

        /**
        * Gets the first splitter
        *@return the first splitter
        */
        virtual CODLineComponent* GetSplitter1();

        /**
        * Gets the second splitter
        *@return the second splitter
        */
        virtual CODLineComponent* GetSplitter2();

        /**
        * Gets the edit box area component
        *@return the edit box area component
        */
        virtual inline CODComponent* GetEditBoxAreaComponent();

        /**
        * Sets the edit box area component
        *@param pComponent - the edit box area component
        */
        virtual inline void SetEditBoxAreaComponent(CODComponent* pComponent);

        /**
        * Gets the name edit box area component
        *@return the name box area component
        */
        virtual inline CODTextComponent* GetNameEditTextComponent();

        /**
        * Sets the name edit box area component
        *@param pTextComp - the name edit box area component
        */
        virtual inline void SetNameEditTextComponent(CODTextComponent* pTextComp);

        /**
        * Gets the comment edit box area component
        *@return the comment edit box area component
        */
        virtual inline CODTextComponent* GetCommentEditTextComponent();

        /**
        * Sets the comment edit box area component
        *@param pTextComp - the comment edit box area component
        */
        virtual inline void SetCommentEditTextComponent(CODTextComponent* pTextComp);

        /**
        * Gets the first splitter component
        *@return the first splitter component
        */
        virtual inline CODLineComponent* GetSplitter1Component();

        /**
        * Sets the first splitter component
        *@param pSplitter - the first splitter component
        */
        virtual inline void SetSplitter1Component(CODLineComponent* pSplitter);

        /**
        * Gets the second splitter component
        *@return the second splitter component
        */
        virtual inline CODLineComponent* GetSplitter2Component();

        /**
        * Sets the second splitter component
        *@param pSplitter - the second splitter component
        */
        virtual inline void SetSplitter2Component(CODLineComponent* pSplitter);

        /**
        * Called when the mouse moves above an area
        *@param flags - the shift keys state flags
        *@param point - the mouse position in pixels
        *@param ctrl - the hovered controller
        */
        virtual bool OnMouseMove(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called when the left mouse button is down
        *@param flags - the shift keys state flags
        *@param point - the mouse position in pixels
        *@param ctrl - the controller below the mouse cursor
        */
        virtual bool OnLButtonDown(UINT flags, const CPoint& point, CODController& ctrl);

        /**
        * Called when the left mouse button is up
        *@param flags - the shift keys state flags
        *@param point - the mouse position in pixels
        *@param ctrl - the controller below the mouse cursor
        */
        virtual bool OnLButtonUp(UINT flags, const CPoint& point, CODController& ctrl);

    protected:
        PSS_BasicSymbol*       m_pSymbol;
        CODComponent*          m_pEditBoxArea;
        CODTextComponent*      m_pNameEditText;
        CODTextComponent*      m_pCommentEditText;
        CODTextComponent*      m_pAttributeEditText;
        CODLineComponent*      m_pSplitterComponent1;
        CODLineComponent*      m_pSplitterComponent2;
        PSS_PropertyAttributes m_Attributes;
        bool                   m_UseDynamicArea;
        bool                   m_ShowNameArea;
        bool                   m_ShowDescriptionArea;
        bool                   m_ShowAttributeArea;
        bool                   m_ReinitializeAreaAtCreation;
        bool                   m_RelativeCoordinates;

        /**
        * Moves the component to a position
        *@param comp - the component to move
        *@param pos - the position to move to
        */
        virtual void MoveTo(CODComponent& comp, const CPoint& pos);

        /**
        * Moves and resizes the component to a position
        *@param comp - the component to move
        *@param posRect - the rect surrounding the component position to move and resize
        */
        virtual void MoveTo(CODComponent& comp, const CRect& posRect);

        /**
        * Scales a component
        *@param comp - the component to scale
        *@param bounds - the component bounds to scale to
        *@param controlPoint - the control point
        */
        virtual void Scale(CODComponent& comp, const CSize& bounds, const OD_CONTROL_POINT controlPoint);
};

//---------------------------------------------------------------------------
// PSS_SymbolAttributes
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::SetSymbol(PSS_BasicSymbol* pSymbol)
{
    m_pSymbol = pSymbol;
}
//---------------------------------------------------------------------------
PSS_PropertyAttributes& PSS_SymbolAttributes::GetAttributes()
{
    return m_Attributes;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::SetUseDynamicArea(bool value)
{
    m_UseDynamicArea = value;
}
//---------------------------------------------------------------------------
bool PSS_SymbolAttributes::UseDynamicArea() const
{
    return m_UseDynamicArea;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::ShowNameArea(bool value)
{
    m_ShowNameArea = value;
}
//---------------------------------------------------------------------------
bool PSS_SymbolAttributes::IsNameAreaVisible() const
{
    return m_ShowNameArea;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::ShowDescriptionArea(bool value)
{
    m_ShowDescriptionArea = value;
}
//---------------------------------------------------------------------------
bool PSS_SymbolAttributes::IsDescriptionsAreaVisible() const
{
    return m_ShowDescriptionArea;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::ShowAttributeArea(bool value)
{
    m_ShowAttributeArea = value;
}
//---------------------------------------------------------------------------
bool PSS_SymbolAttributes::IsAttributeAreaVisible() const
{
    return m_ShowAttributeArea;
}
//---------------------------------------------------------------------------
CODComponent* PSS_SymbolAttributes::GetEditBoxAreaComponent()
{
    return m_pEditBoxArea;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::SetEditBoxAreaComponent(CODComponent* pComponent)
{
    m_pEditBoxArea = pComponent;
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_SymbolAttributes::GetNameEditTextComponent()
{
    return m_pNameEditText;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::SetNameEditTextComponent(CODTextComponent* pTextComp)
{
    m_pNameEditText = pTextComp;
}
//---------------------------------------------------------------------------
CODTextComponent* PSS_SymbolAttributes::GetCommentEditTextComponent()
{
    return m_pCommentEditText;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::SetCommentEditTextComponent(CODTextComponent* pTextComp)
{
    m_pCommentEditText = pTextComp;
}
//---------------------------------------------------------------------------
CODLineComponent* PSS_SymbolAttributes::GetSplitter1Component()
{
    return m_pSplitterComponent1;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::SetSplitter1Component(CODLineComponent* pSplitter)
{
    m_pSplitterComponent1 = pSplitter;
}
//---------------------------------------------------------------------------
CODLineComponent* PSS_SymbolAttributes::GetSplitter2Component()
{
    return m_pSplitterComponent2;
}
//---------------------------------------------------------------------------
void PSS_SymbolAttributes::SetSplitter2Component(CODLineComponent* pSplitter)
{
    m_pSplitterComponent2 = pSplitter;
}
//---------------------------------------------------------------------------

#endif
