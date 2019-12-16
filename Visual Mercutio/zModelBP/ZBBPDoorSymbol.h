// ZBBPDoorSymbol.h: interface for the ZBBPDoorSymbol class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBBPDoorSymbol_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPDoorSymbol_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

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

#include "zModel\PSS_Symbol.h"

// class name mapping
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_ProcessGraphModelMdl;

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 6 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZBBPDoorSymbol : public PSS_Symbol
{
    DECLARE_SERIAL(ZBBPDoorSymbol)

public:

    ZBBPDoorSymbol(const CString Name = _T(""));
    virtual ~ZBBPDoorSymbol();

    /* Copy constructor. */
    ZBBPDoorSymbol(const ZBBPDoorSymbol& src);

    /* Assignment operator. */
    ZBBPDoorSymbol& operator=(const ZBBPDoorSymbol& src);

    /* Create a duplicate copy of this object. */
    virtual CODComponent* Dup() const;

    // Copy the definition only
    virtual void CopySymbolDefinitionFrom(CODSymbolComponent& src);

    // Return the model door
    PSS_ProcessGraphModelMdl* GetModelDoor();

    // Set a new model to the door
    bool SetDoorModel(PSS_ProcessGraphModelMdl* pModel);

    // Recalculate the door reference for a given twin door name
    void RecalculateTwinDoorReference(PSS_ProcessGraphModelMdl* pRootModel);

    int GetTwinDoorReferenceNumber() const
    {
        return m_TwinDoorRefNumber;
    }

    void SetTwinDoorReferenceNumber(int RefNumber);
    void RemoveTwinDoorSymbol(bool RemoveTwin = true);
    void AssignTwinDoorSymbol(ZBBPDoorSymbol* pDoor);

    ZBBPDoorSymbol* GetTwinDoorSymbol() const
    {
        return m_pTwinDoorSymbol;
    }

    void SetTwinDoorSymbol(ZBBPDoorSymbol* pDoor)
    {
        m_pTwinDoorSymbol = pDoor;
    }

    // JMR-MODIF - Le 3 septembre 2006 - Ajout de la fonction DuplicateStyleOnTwinSymbol.
    BOOL DuplicateStyleOnTwinSymbol();

    //////////////////////////////////////////////////////////////////////
    // Call-back on symbols
    virtual void OnSymbolNameChanged(CODComponent& Comp, const CString OldName);

    // Update mecanism for symbol change
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    ///////////////////////////////////////////////////////
    // Basic Symbol methods

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

    //////////////////////////////////////////////////////////////////////
    // Attributes management methods
    virtual bool AcceptDynamicAttributes() const
    {
        // No dynamic attributes
        return false;
    }

    /**
    * Called when a tooltip is required
    *@param[in, out] toolTipText - tooltip text, formatted tooltip text on function ends
    *@param point - hit point
    *@param mode - tooltip mode
    *@return true if tooltip can be shown, otherwise false
    */
    virtual bool OnToolTip(CString& toolTipText, const CPoint& point, PSS_ToolTip::IEToolTipMode mode = PSS_ToolTip::IE_TT_Normal);

    // Drag and drop methods
    virtual bool AcceptDropItem(CObject* pObj, const CPoint& pt);
    virtual bool DropItem(CObject* pObj, const CPoint& pt);

    /* Creates the symbol component. */
    BOOL Create(const CString Name = _T(""));

    /* Called after the object is created and on the desk
       return true if the object can be created or false if the
       object must be destroyed immediatly */
    virtual bool OnPostCreation(CODModel* pModel = NULL, CODController* pCtrl = NULL);

    /* Called before the object is deleted
       return true if the object can be deleted */
    virtual bool OnPreDelete(CODModel* pModel = NULL, CODController* pCtrl = NULL);

    /* Called after the double click occured on the object */
    virtual void OnPostDoubleClick(CODModel* pModel = NULL, CODController* pCtrl = NULL);

    bool GetDisplayPreview() const
    {
        return m_DisplayPreview;
    };
    void SetDisplayPreview(bool value)
    {
        m_DisplayPreview = value;
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

    // JMR-MODIF - Le 3 mai 2006 - Fonction permettant de définir si le symbole est une porte.
    virtual BOOL IsDoor()
    {
        return TRUE;
    }

    /* Serializes the symbol. */
    virtual void Serialize(CArchive& ar);

    virtual int GetRightSubMenu() const;
    virtual int GetIconIndex() const;

    virtual BOOL OnDoubleClick();

protected:

    virtual void AdjustElementPosition();
    CString BuildSymbolName();

private:

    // The model for the canvas. The model holds all information about 
    // the canvas, while the viewport actually displays it.
    CRect                    m_CommentRect;
    bool                    m_DisplayPreview;
    CString                    m_SubModelPathName;
    // The twin door name saves the name of the other door
    int                        m_TwinDoorRefNumber;
    ZBBPDoorSymbol*            m_pTwinDoorSymbol;
};

inline int ZBBPDoorSymbol::GetRightSubMenu() const
{
    return 6;
}

inline int ZBBPDoorSymbol::GetIconIndex() const
{
    return (IsLocal()) ? 8 : 16;
}

#endif
