/****************************************************************************
 * ==> PSS_GenericSymbolBP -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic symbol for banking process              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GenericSymbolBPH
#define PSS_GenericSymbolBPH

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
#ifndef PSS_GenericSymbolBP
    #define PSS_GenericSymbolBP ZBBPGenericSymbol
#endif

// processsoft
#include "zModel\PSS_Symbol.h"

// resources
#include "zBaseSym\zBaseSymRes.h"

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
* Generic symbol for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GenericSymbolBP : public PSS_Symbol
{
    DECLARE_SERIAL(PSS_GenericSymbolBP)

    public:
        /**
        * Constructor
        *@param name - the symbol name
        */
        PSS_GenericSymbolBP(const CString& name = _T(""));

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_GenericSymbolBP(const PSS_GenericSymbolBP& other);

        virtual ~PSS_GenericSymbolBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_GenericSymbolBP& operator = (const PSS_GenericSymbolBP& other);

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
        virtual BOOL Create(UINT nID, const CString& name = _T(""));

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual CODComponent* Dup() const;

        /**
        * Checks if the symbol accepts the dynamic attributes
        *@return true if the symbol accepts the dynamic attributes, otherwise false
        */
        virtual inline bool AcceptDynamicAttributes() const;

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
        * Checks if the symbol properties are read only
        *@return true if the symbol properties are read only, otherwise false
        */
        virtual inline bool IsPropertiesReadOnly() const;

        /**
        * Gets the symbol reference number
        *@return the symbol reference number
        */
        virtual inline int GetSymbolReferenceNumber();

        /**
        * Checks if the symbol is a generic symbol
        *@return TRUE if the symbol is a generic symbol, otherwise FALSE
        */
        virtual inline BOOL IsGeneric() const;

        /**
        * Gets the right submenu resource index
        *@return the right submenu resource index
        */
        virtual inline int GetRightSubMenu() const;

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);
};

//---------------------------------------------------------------------------
// PSS_GenericSymbolBP
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE PSS_GenericSymbolBP::AddRef()
{
    return CODSymbolComponent::AddRef();
}
//---------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE PSS_GenericSymbolBP::Release()
{
    return CODSymbolComponent::Release();
}
//---------------------------------------------------------------------------
bool PSS_GenericSymbolBP::AcceptDynamicAttributes() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_GenericSymbolBP::CanContainChildModel() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_GenericSymbolBP::IsChildModelRef() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_GenericSymbolBP::SymbolNameTextEditReadOnly() const
{
    return false;
}
//---------------------------------------------------------------------------
bool PSS_GenericSymbolBP::CommentTextEditReadOnly() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_GenericSymbolBP::IsPropertiesReadOnly() const
{
    return true;
}
//---------------------------------------------------------------------------
int PSS_GenericSymbolBP::GetSymbolReferenceNumber()
{
    return -1;
}
//---------------------------------------------------------------------------
BOOL PSS_GenericSymbolBP::IsGeneric() const
{
    return TRUE;
}
//---------------------------------------------------------------------------
int PSS_GenericSymbolBP::GetRightSubMenu() const
{
    return 10;
}
//---------------------------------------------------------------------------

#endif
