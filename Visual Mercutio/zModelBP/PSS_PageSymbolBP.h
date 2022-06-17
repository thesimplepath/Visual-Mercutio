/****************************************************************************
 * ==> PSS_PageSymbolBP ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a page symbol for banking process                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PageSymbolBPH
#define PSS_PageSymbolBPH

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

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_PageSymbolBP
    #define PSS_PageSymbolBP ZBBPPageSymbol
#endif

// processsoft
#include "zModel\PSS_Symbol.h"

// class name mapping
#ifndef PSS_ProcessGraphPage
    #define PSS_ProcessGraphPage ZDProcessGraphPage
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_ProcessGraphPage;
class PSS_ProcessGraphModelMdl;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Page symbol for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PageSymbolBP : public PSS_Symbol
{
    DECLARE_SERIAL(PSS_PageSymbolBP)

    public:
        /**
        * Constructor
        *@param name - the symbol name
        */
        PSS_PageSymbolBP(const CString& name = _T(""));

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PageSymbolBP(const PSS_PageSymbolBP& other);

        virtual ~PSS_PageSymbolBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_PageSymbolBP& operator = (const PSS_PageSymbolBP& other);

        /**
        * Adds a reference to this object
        *@return the updated reference count
        */
        virtual inline ULONG STDMETHODCALLTYPE AddRef();

        /**
        * Releases a reference from this object
        *@return the updated reference count
        */
        virtual inline ULONG STDMETHODCALLTYPE Release();

        /**
        * Creates the symbol component
        *@param name - the symbol name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const CString& name = _T(""));

        /**
        * Creates a new child model
        *@param pParent - the parent model in which the new child model will be created
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateEmptyChildModel(CODModel* pParent);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual CODComponent* Dup() const;

        /**
        * Copies the symbol definition from another symbol
        *@param src - the source symbol to copy from
        */
        virtual void CopySymbolDefinitionFrom(const CODSymbolComponent& src);

        /**
        * Checks if this symbol is a page
        *@return TRUE if this symbol is a page, otherwise FALSE
        */
        virtual inline BOOL IsPage() const;

        /**
        * Gets the page
        *@return the page
        */
        virtual inline PSS_ProcessGraphPage* GetPage();

        /**
        * Gets the page model
        *@return the page model
        */
        virtual PSS_ProcessGraphModelMdl* GetPageModel();

        /**
        * Sets the page model
        *@param pModel - the page model
        *@return true on success, otherwise false
        */
        virtual bool SetPageModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Recalculates the twin page reference
        *@param pRootModel - the root model to recalculate from
        */
        virtual void RecalculateTwinPageReference(PSS_ProcessGraphModelMdl* pRootModel);

        /**
        * Gets the twin page reference number
        *@return the twin page reference number
        */
        virtual inline int GetTwinPageReferenceNumber() const;

        /**
        * Sets the twin page reference number
        *@param value - the twin page reference number
        */
        virtual void SetTwinPageReferenceNumber(int refNumber);

        /**
        * Assigns a twin page symbol
        *@param pPage - the twin page symbol to assign
        */
        virtual void AssignTwinPageSymbol(PSS_PageSymbolBP* pPage);

        /**
        * Removes the twin page symbol
        *@param removeTwin - if true, the twin symbol linked with this one will also be removed
        */
        virtual void RemoveTwinPageSymbol(bool removeTwin = true);

        /**
        * Gets the twin page symbol
        *@return the twin page symbol
        */
        virtual inline PSS_PageSymbolBP* GetTwinPageSymbol() const;

        /**
        * Sets the twin page symbol
        *@param pDoor - the twin page symbol
        */
        virtual inline void SetTwinPageSymbol(PSS_PageSymbolBP* pPage);

        /**
        * Duplicates the style of the current symbol on the twin symbol
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DuplicateStyleOnTwinSymbol();

        /**
        * Creates the symbol properties
        *@return true on success, otherwise false
        */
        virtual bool CreateSymbolProperties();

        /**
        * Checks if the symbol contains properties
        *@return true if the symbol contains properties, otherwise false
        */
        virtual inline bool HasProperties() const;

        /**
        * Fills an array with the symbol properties
        *@param[in, out] propSet - property set to fill with the symbol properties, filled set on function ends
        *@param numericValues - if true, only properties containing a numeric values will be filled
        *@param groupValues - if true, values will be grouped
        *@return true on success, otherwise false
        */
        virtual bool FillProperties(PSS_Properties::IPropertySet& propSet, bool numericValues = false, bool groupValues = false);

        /**
        * Saves the changes to object properties
        *@param propSet - property set to fill with the saved properties
        *@return true on success, otherwise false
        */
        virtual bool SaveProperties(PSS_Properties::IPropertySet& PropSet);

        /**
        * Checks if the properties are read-only
        *@return true if the properties are read-only, otherwise false
        */
        virtual inline bool IsPropertiesReadOnly() const;

        /**
        * Checks if the symbol can contain a child model
        *@return true if the symbol can contain a child model, otherwise false
        */
        virtual inline bool CanContainChildModel() const;

        /**
        * Checks if the child model is a reference
        *@return true if the child model is a reference, otherwise false
        */
        virtual inline bool IsChildModelRef() const;

        /**
        * Checks if the symbol name is read-only
        *@return true if the symbol name is read-only, otherwise false
        */
        virtual inline bool SymbolNameTextEditReadOnly() const;

        /**
        * Checks if the symbol comment is read-only
        *@return true if the symbol comment is read-only, otherwise false
        */
        virtual inline bool CommentTextEditReadOnly() const;

        /**
        * Checks if the symbol accepts the dynamic attributes
        *@return true if the symbol accepts the dynamic attributes, otherwise false
        */
        virtual inline bool AcceptDynamicAttributes() const;

        /**
        * Checks if an item may be dropped on this symbol
        *@param pObj - the object to drop
        *@param point - the drop point in pixels
        *@return true if an item may be dropped on this symbol, otherwise false
        */
        virtual bool AcceptDropItem(CObject* pObj, const CPoint& point);

        /**
        * Drops an item on this symbol
        *@param pObj - the object to drop
        *@param point - the drop point in pixels
        *@return true on success, otherwise false
        */
        virtual bool DropItem(CObject* pObj, const CPoint& point);

        /**
        * Checks if a preview is shown
        *@return true if a preview is shown, otherwise false
        */
        virtual inline bool GetShowPreview() const;

        /**
        * Sets if a preview is shown
        *@param value - if true, a preview is shown
        */
        virtual inline void SetShowPreview(bool value);

        /**
        * Gets the right submenu resource index
        *@return the right submenu resource index
        */
        virtual inline int GetRightSubMenu() const;

        /**
        * Gets the icon resource index
        *@return the icon resource index
        */
        virtual inline int GetIconIndex() const;

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Called after the symbol was created and before it's added on the model
        *@param pModel - the model containing the newly created symbol
        *@param pCtrl - the model controller
        *@return true if the symbol can be added on the model, false if the symbol should be destroyed immediatly
        */
        virtual bool OnPostCreation(CODModel* pModel = NULL, CODController* pCtrl = NULL);

        /**
        * Called before the symbol is deleted
        *@param pModel - the model containing the symbol about to be deleted
        *@param pCtrl - the model controller
        *@return true if the symbol can be deleted, otherwise false
        */
        virtual bool OnPreDelete(CODModel* pModel = NULL, CODController* pCtrl = NULL);

        /**
        * Called when the page name changed
        *@param pPage - the page for which the name changed
        *@param oldName - the old component name
        */
        virtual void OnPageNameChanged(PSS_ProcessGraphPage* pPage, const CString& oldName);

        /**
        * Called when the symbol is double clicked
        *@return TRUE if the double click was performed, otherwise FALSE
        */
        virtual BOOL OnDoubleClick();

        /**
        * Called after the double click occured on the symbol
        *@param pModel - the double-clicked model
        *@param pCtrl - the model controller
        */
        virtual void OnPostDoubleClick(CODModel* pModel = NULL, CODController* pCtrl = NULL);

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

        /**
        * Called when the symbol is drawn
        *@param pDc - the device context to draw on
        */
        virtual void OnDraw(CDC* pDC);

        /**
        * Called when a tooltip is required
        *@param[in, out] toolTipText - tooltip text, formatted tooltip text on function ends
        *@param point - hit point
        *@param mode - tooltip mode
        *@return true if tooltip can be shown, otherwise false
        */
        virtual bool OnToolTip(CString&                   toolTipText,
                               const CPoint&              point,
                               PSS_ToolTip::IEToolTipMode mode = PSS_ToolTip::IEToolTipMode::IE_TT_Normal);

    protected:
        PSS_ProcessGraphPage* m_pPage;

        /**
        * Adjusts the element position
        */
        virtual void AdjustElementPosition();

        /**
        * Builds the symbol name
        *@return the built symbol name
        */
        virtual CString BuildSymbolName();

    private:
        PSS_PageSymbolBP* m_pTwinPageSymbol;
        CRect             m_CommentRect;
        CString           m_PageName;
        CString           m_SubModelPathName;
        int               m_TwinPageRefNumber;
        bool              m_ShowPreview;
};

//---------------------------------------------------------------------------
// PSS_PageSymbolBP
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE PSS_PageSymbolBP::AddRef()
{
    return CODSymbolComponent::AddRef();
}
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE PSS_PageSymbolBP::Release()
{
    return CODSymbolComponent::Release();
}
//---------------------------------------------------------------------------
BOOL PSS_PageSymbolBP::IsPage() const
{
    return TRUE;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphPage* PSS_PageSymbolBP::GetPage()
{
    return m_pPage;
}
//---------------------------------------------------------------------------
int PSS_PageSymbolBP::GetTwinPageReferenceNumber() const
{
    return m_TwinPageRefNumber;
}
//---------------------------------------------------------------------------
PSS_PageSymbolBP* PSS_PageSymbolBP::GetTwinPageSymbol() const
{
    return m_pTwinPageSymbol;
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::SetTwinPageSymbol(PSS_PageSymbolBP* pPage)
{
    m_pTwinPageSymbol = pPage;
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::HasProperties() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::IsPropertiesReadOnly() const
{
    // properties cannot be edited
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::CanContainChildModel() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::IsChildModelRef() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::SymbolNameTextEditReadOnly() const
{
    // cannot be edited
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::CommentTextEditReadOnly() const
{
    // cannot be edited
    return false;
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::AcceptDynamicAttributes() const
{
    // no dynamic attributes
    return false;
}
//---------------------------------------------------------------------------
bool PSS_PageSymbolBP::GetShowPreview() const
{
    return m_ShowPreview;
}
//---------------------------------------------------------------------------
void PSS_PageSymbolBP::SetShowPreview(bool value)
{
    m_ShowPreview = value;
}
//---------------------------------------------------------------------------
int PSS_PageSymbolBP::GetRightSubMenu() const
{
    return 7;
}
//---------------------------------------------------------------------------
int PSS_PageSymbolBP::GetIconIndex() const
{
    return (IsLocal() ? 7 : 15);
}
//---------------------------------------------------------------------------

#endif
