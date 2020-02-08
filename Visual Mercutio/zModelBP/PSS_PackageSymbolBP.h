/****************************************************************************
 * ==> PSS_PackageSymbolBP -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a package symbol for banking process              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PackageSymbolBPH
#define PSS_PackageSymbolBPH

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
#ifndef PSS_PackageSymbolBP
    #define PSS_PackageSymbolBP ZBBPPackageSymbol
#endif

// processsoft
#include "zBaseLib\PSS_Bitmap.h"
#include "zModel\PSS_Symbol.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// Forward declaration
class PSS_ProcessModelDocTmpl;
class PSS_ProcessGraphModelDoc;
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
* Package symbol for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PackageSymbolBP : public PSS_Symbol
{
    DECLARE_SERIAL(PSS_PackageSymbolBP)

    public:
        /**
        * Constructor
        *@param name - the symbol name
        *@param fileName - the package file name
        */
        PSS_PackageSymbolBP(const CString& name = _T(""), const CString& fileName = _T(""));

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PackageSymbolBP(const PSS_PackageSymbolBP& other);

        virtual ~PSS_PackageSymbolBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_PackageSymbolBP& operator = (const PSS_PackageSymbolBP& other);

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
        *@param fileName - the package file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const CString& name = _T(""), const CString& fileName = _T(""));

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
        * Checks if this symbol is a package
        *@return TRUE if this symbol is a package, otherwise FALSE
        */
        virtual inline BOOL IsPackage() const;

        /**
        * Sets the symbol name
        *@param value - the symbol name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetSymbolName(const CString& value);

        /**
        * Gets the package document
        *@return the package document
        */
        virtual inline PSS_ProcessGraphModelDoc* GetPackageDocument();

        /**
        * Loads the package
        *@param pDocTmpl - the document template
        *@param pParent - the parent
        *@return true on success, otherwise false
        */
        virtual bool LoadPackage(PSS_ProcessModelDocTmpl* pDocTmpl, PSS_ProcessGraphModelMdl* pParent = NULL);

        /**
        * Unloads the package
        *@return true on success, otherwise false
        */
        virtual bool UnloadPackage();

        /**
        * Checks if the package is loaded
        *@return true if the package is loaded, otherwise false
        */
        virtual inline bool IsLoaded() const;

        /**
        * Checks if the package is linked to a file name
        *@return true if the package is linked to a file name, otherwise false
        */
        virtual inline bool IsLinkedToFileName() const;

        /**
        * Gets the file name at which this package is linked
        *@return the file name at which this package is linked
        */
        virtual inline CString GetFileNameLinkedTo() const;

        /**
        * Sets the file name at which this package is linked
        *@param value - the file name at which this package is linked
        */
        virtual inline void SetFileNameLinkedTo(const CString& value);

        /**
        * Clears the linked file name
        */
        virtual inline void ClearLinkedToFileName();

        /**
        * Gets the package name
        *@return the package name
        */
        virtual inline const CString GetPackageName();

        /**
        * Sets the package name
        *@param value - the package name
        */
        virtual inline void SetPackageName(const CString& value);

        /**
        * Checks if the symbol can contain a child model
        *@return true if the symbol can contain a child model, otherwise false
        */
        virtual inline bool CanContainChildModel() const;

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
        * Called when the symbol is double clicked
        *@return TRUE if the double click was performed, otherwise FALSE
        */
        virtual BOOL OnDoubleClick();

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
                               PSS_ToolTip::IEToolTipMode mode = PSS_ToolTip::IE_TT_Normal);

    protected:
        /**
        * Adjusts the element position
        */
        virtual void AdjustElementPosition();

    private:
        static PSS_Bitmap         m_LinkedToFileBitmap;
        PSS_ProcessGraphModelDoc* m_pPackageDoc;
        CRect                     m_CommentRect;
        CPoint                    m_LinkedToFileBitmapPosition;
        CString                   m_FileNameLinkedTo;
        bool                      m_ShowPreview;
};

//---------------------------------------------------------------------------
// PSS_PackageSymbolBP
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE PSS_PackageSymbolBP::AddRef()
{
    return CODSymbolComponent::AddRef();
}
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE PSS_PackageSymbolBP::Release()
{
    return CODSymbolComponent::Release();
}
//---------------------------------------------------------------------------
BOOL PSS_PackageSymbolBP::IsPackage() const
{
    return TRUE;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelDoc* PSS_PackageSymbolBP::GetPackageDocument()
{
    return m_pPackageDoc;
}
//---------------------------------------------------------------------------
bool PSS_PackageSymbolBP::IsLoaded() const
{
    return m_pPackageDoc != NULL;
}
//---------------------------------------------------------------------------
bool PSS_PackageSymbolBP::IsLinkedToFileName() const
{
    return !m_FileNameLinkedTo.IsEmpty();
}
//---------------------------------------------------------------------------
CString PSS_PackageSymbolBP::GetFileNameLinkedTo() const
{
    return m_FileNameLinkedTo;
}
//---------------------------------------------------------------------------
void PSS_PackageSymbolBP::SetFileNameLinkedTo(const CString& value)
{
    m_FileNameLinkedTo = value;
}
//---------------------------------------------------------------------------
void PSS_PackageSymbolBP::ClearLinkedToFileName()
{
    m_FileNameLinkedTo.Empty();
}
//---------------------------------------------------------------------------
const CString PSS_PackageSymbolBP::GetPackageName()
{
    return PSS_Symbol::GetSymbolName();
}
//---------------------------------------------------------------------------
void PSS_PackageSymbolBP::SetPackageName(const CString& value)
{
    PSS_Symbol::SetSymbolName(value);
}
//---------------------------------------------------------------------------
bool PSS_PackageSymbolBP::CanContainChildModel() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_PackageSymbolBP::AcceptDynamicAttributes() const
{
    // no dynamic attributes
    return false;
}
//---------------------------------------------------------------------------
bool PSS_PackageSymbolBP::GetShowPreview() const
{
    return m_ShowPreview;
}
//---------------------------------------------------------------------------
void PSS_PackageSymbolBP::SetShowPreview(bool value)
{
    m_ShowPreview = value;
}
//---------------------------------------------------------------------------
int PSS_PackageSymbolBP::GetRightSubMenu() const
{
    return 9;
}
//---------------------------------------------------------------------------
int PSS_PackageSymbolBP::GetIconIndex() const
{
    return (IsLocal() ? 11 : 19);
}
//---------------------------------------------------------------------------

#endif
