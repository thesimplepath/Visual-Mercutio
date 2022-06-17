/****************************************************************************
 * ==> PSS_DoorSymbolBP ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a door symbol for banking process                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DoorSymbolBPH
#define PSS_DoorSymbolBPH

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
#ifndef PSS_DoorSymbolBP
    #define PSS_DoorSymbolBP ZBBPDoorSymbol
#endif

// processsoft
#include "zModel\PSS_Symbol.h"

// class name mapping
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
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
* Door symbol for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DoorSymbolBP : public PSS_Symbol
{
    DECLARE_SERIAL(PSS_DoorSymbolBP)

    public:
        /**
        * Constructor
        *@param name - the symbol name
        */
        PSS_DoorSymbolBP(const CString& name = _T(""));

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_DoorSymbolBP(const PSS_DoorSymbolBP& src);

        virtual ~PSS_DoorSymbolBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_DoorSymbolBP& operator = (const PSS_DoorSymbolBP& other);

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
        * Checks if this symbol is a door
        *@return TRUE if this symbol is a door, otherwise FALSE
        */
        virtual inline BOOL IsDoor() const;

        /**
        * Gets the door model
        *@return the door model
        */
        PSS_ProcessGraphModelMdl* GetDoorModel();

        /**
        * Sets the door model
        *@param pModel - the door model
        *@return true on success, otherwise false
        */
        virtual bool SetDoorModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Recalculates the twin door reference
        *@param pRootModel - the root model to recalculate from
        */
        virtual void RecalculateTwinDoorReference(PSS_ProcessGraphModelMdl* pRootModel);

        /**
        * Gets the twin door reference number
        *@return the twin door reference number
        */
        virtual inline int GetTwinDoorReferenceNumber() const;

        /**
        * Sets the twin door reference number
        *@param value - the twin door reference number
        */
        virtual void SetTwinDoorReferenceNumber(int value);

        /**
        * Assigns a twin door symbol
        *@param pDoor - the twin door symbol to assign
        */
        virtual void AssignTwinDoorSymbol(PSS_DoorSymbolBP* pDoor);

        /**
        * Removes the twin door symbol
        *@param removeTwin - if true, the twin symbol linked with this one will also be removed
        */
        virtual void RemoveTwinDoorSymbol(bool removeTwin = true);

        /**
        * Gets the twin door symbol
        *@return the twin door symbol
        */
        virtual inline PSS_DoorSymbolBP* GetTwinDoorSymbol() const;

        /**
        * Sets the twin door symbol
        *@param pDoor - the twin door symbol
        */
        virtual inline void SetTwinDoorSymbol(PSS_DoorSymbolBP* pDoor);

        /**
        * Duplicates the style of the current symbol on the twin symbol
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DuplicateStyleOnTwinSymbol();

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
        * Called when the symbol name changed
        *@param[in, out] comp - the component for which the name changed
        *@param oldName - the old component name
        */
        virtual void OnSymbolNameChanged(CODComponent& comp, const CString& oldName);

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
        PSS_DoorSymbolBP* m_pTwinDoorSymbol;
        CRect             m_CommentRect;
        CString           m_SubModelPathName;
        int               m_TwinDoorRefNumber;
        bool              m_ShowPreview;
};

//---------------------------------------------------------------------------
// PSS_DoorSymbolBP
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE PSS_DoorSymbolBP::AddRef()
{
    return CODSymbolComponent::AddRef();
}
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE PSS_DoorSymbolBP::Release()
{
    return CODSymbolComponent::Release();
}
//---------------------------------------------------------------------------
BOOL PSS_DoorSymbolBP::IsDoor() const
{
    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_DoorSymbolBP::GetTwinDoorReferenceNumber() const
{
    return m_TwinDoorRefNumber;
}
//---------------------------------------------------------------------------
PSS_DoorSymbolBP* PSS_DoorSymbolBP::GetTwinDoorSymbol() const
{
    return m_pTwinDoorSymbol;
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::SetTwinDoorSymbol(PSS_DoorSymbolBP* pDoor)
{
    m_pTwinDoorSymbol = pDoor;
}
//---------------------------------------------------------------------------
bool PSS_DoorSymbolBP::CanContainChildModel() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DoorSymbolBP::IsChildModelRef() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DoorSymbolBP::SymbolNameTextEditReadOnly() const
{
    // cannot be edited
    return true;
}
//---------------------------------------------------------------------------
bool PSS_DoorSymbolBP::CommentTextEditReadOnly() const
{
    // cannot be edited
    return false;
}
//---------------------------------------------------------------------------
bool PSS_DoorSymbolBP::AcceptDynamicAttributes() const
{
    // no dynamic attributes
    return false;
}
//---------------------------------------------------------------------------
bool PSS_DoorSymbolBP::GetShowPreview() const
{
    return m_ShowPreview;
}
//---------------------------------------------------------------------------
void PSS_DoorSymbolBP::SetShowPreview(bool value)
{
    m_ShowPreview = value;
}
//---------------------------------------------------------------------------
int PSS_DoorSymbolBP::GetRightSubMenu() const
{
    return 6;
}
//---------------------------------------------------------------------------
int PSS_DoorSymbolBP::GetIconIndex() const
{
    return (IsLocal() ? 8 : 16);
}
//---------------------------------------------------------------------------

#endif
