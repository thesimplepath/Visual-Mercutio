/****************************************************************************
 * ==> PSS_StateObject -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a state object                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_StateObjectH
#define PSS_StateObjectH

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
#ifndef PSS_StateObject
    #define PSS_StateObject ZBStateObject
#endif

// processsoft
#include "PSS_AutomationCollections.h"
#include "PSS_StateLink.h"

// class name mapping
#ifndef PSS_LinkSymbol
    #define PSS_LinkSymbol ZBLinkSymbol
#endif

// forward class declaration
class ZDProcessGraphModelMdl;
class ZBSymbol;
class PSS_LinkSymbol;
class PSS_StateLink;

#ifdef _ZWKFEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* State object
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StateObject : public CObject
{
    DECLARE_SERIAL(PSS_StateObject)

    public:
        /**
        * Constructor
        *@param pSymbol - symbol
        *@param pLinkSymbol - link symbol
        *@param direction - link direction
        *@param pModel - model
        */
        PSS_StateObject(ZBSymbol*                      pSymbol = NULL,
                        PSS_LinkSymbol*                pLinkSymbol = NULL,
                        PSS_StateLink::IELinkDirection direction = PSS_StateLink::IE_LD_EnteringUp,
                        ZDProcessGraphModelMdl*        pModel = NULL);

        /**
        * Constructor
        *@param pSymbol - symbol
        *@param pStateLink- state link
        *@param pModel - model
        */
        PSS_StateObject(ZBSymbol*               pSymbol,
                        PSS_StateLink*          pStateLink,
                        ZDProcessGraphModelMdl* pModel = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_StateObject(const PSS_StateObject& other);

        virtual ~PSS_StateObject();

        /**
        * Assignment operator
        *@param other - other object to copy from
        */
        PSS_StateObject& operator = (const PSS_StateObject& src);

        /**
        * Clones the object
        *@return cloned object
        */
        virtual PSS_StateObject* Clone() const;

        /**
        * Assigns a model
        *@param pModel - model to assign
        */
        virtual void AssignModel(ZDProcessGraphModelMdl* pModel);

        /**
        * Gets the symbol
        *@return symbol
        */
        virtual inline ZBSymbol* GetSymbol() const;

        /**
        * Sets the symbol
        *@param pSymbol - symbol to set
        */
        virtual inline void SetSymbol(ZBSymbol* pSymbol);

        /**
        * Checks if object is equals to another one
        *@param pOther - other object to compare with
        *@return true if the objects are equals, otherwise false
        */
        virtual bool IsEqual(PSS_StateObject* pOther);

        /**
        * Checks if a link exists in the state object
        *@param linkSymbol - link symbol to search for
        *@return true if the link exists in the state object, otherwose false
        */
        virtual bool Exist(PSS_LinkSymbol& linkSymbol);

        /**
        * Gets the number of existing edges found in the state object
        *@param pEdges - edges to search for
        *@return the number of existing edges found in the state object
        *@note All edges must exist in the state object, otherwise false is returned
        */
        virtual std::size_t EdgesExist(CODEdgeArray& edges);

        /**
        * Gets the link set
        *@return the link set
        */
        virtual inline       PSS_StateLinksSet& GetLinkSet();
        virtual inline const PSS_StateLinksSet& GetLinkSetConst() const;

        /**
        * Gets the state link count
        *@return the state link count
        */
        virtual inline std::size_t GetStateLinkCount() const;

        /**
        * Gets the state link at
        *@param index - index to get at
        *@return the state link at index, NULL if not found or on error
        */
        virtual inline PSS_StateLink* GetStateLinkAt(std::size_t index) const;

        /**
        * Adds a link
        *@param pLinkSymbol - link symbol
        *@param direction - link direction
        */
        virtual void AddLink(PSS_LinkSymbol* pLinkSymbol, PSS_StateLink::IELinkDirection direction);

        /**
        * Removes a link
        *@param pLinkSymbol - link symbol to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveLink(PSS_LinkSymbol* pLinkSymbol);
 
        /**
        * Removes a link by reference
        *@param refNb - link reference number to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveLink(int refNb);

        /**
        * Removes all the links
        */
        virtual void RemoveAllLinks();

        /**
        * Merges a state object with another
        *@param pOther - other state object to link with
        *@return true on success, otherwise false
        */
        virtual bool Merge(PSS_StateObject* pRight);

        /**
        * Merges a state object with others objects in a set
        *@param others - other state objects to link with
        *@return true on success, otherwise false
        */
        virtual bool Merge(PSS_StateObjectSet& others);

        /**
        * Serializes the state object content
        *@param ar - archive in which the content will be serialized
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the state link validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the state link content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    private:
        ZBSymbol*               m_pSymbol;
        PSS_StateLinksSet       m_Set;
        ZDProcessGraphModelMdl* m_pModel;

        /**
        * Assigns the model to the state links
        */
        void AssignModelToStateLinks();

        /**
        * Adds a state link
        *@param pStateLink - state link to add
        *@return newly added state link index, -1 on error
        */
        int AddStateLink(PSS_StateLink* pStateLink);
};

//---------------------------------------------------------------------------
// PSS_StateObject
//---------------------------------------------------------------------------
ZBSymbol* PSS_StateObject::GetSymbol() const
{
    return m_pSymbol;
}
//---------------------------------------------------------------------------
void PSS_StateObject::SetSymbol(ZBSymbol* value)
{
    m_pSymbol = value;
}
//---------------------------------------------------------------------------
PSS_StateLinksSet& PSS_StateObject::GetLinkSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------
const PSS_StateLinksSet& PSS_StateObject::GetLinkSetConst() const
{
    return m_Set;
}
//---------------------------------------------------------------------------
std::size_t PSS_StateObject::GetStateLinkCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------
PSS_StateLink* PSS_StateObject::GetStateLinkAt(std::size_t index) const
{
    return (index < GetStateLinkCount() ? m_Set.GetAt(index) : NULL);
}
//---------------------------------------------------------------------------

#endif
