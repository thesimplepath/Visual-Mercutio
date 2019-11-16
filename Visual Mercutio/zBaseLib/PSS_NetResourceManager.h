/****************************************************************************
 * ==> PSS_NetResourceManager ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a net resource manager                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_NetResourceManagerH
#define PSS_NetResourceManagerH

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
#include "PSS_NetResource.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Net resource manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_NetResourceManager : public CObject
{
    public:
        PSS_NetResourceManager();
        virtual ~PSS_NetResourceManager();

        /**
        * Adds a net resource
        *@param pNetResource - net resource to add
        *@return true on success, otherwise false
        */
        virtual bool AddNetResource(LPNETRESOURCE pNetResource);

        /**
        * Adds a net resource
        *@param pNetResource - net resource to add
        *@return true on success, otherwise false
        */
        virtual bool AddNetResource(PSS_NetResource* pNetResource);

        /**
        * Removes a net resource
        *@param pNetResource - net resource to remove
        *@return true on success, otherwise false
        */
        virtual bool RemoveNetResource(PSS_NetResource* pNetResource);

        /**
        * Removes a net resource at index
        *@param index - index
        *@return true on success, otherwise false
        */
        virtual bool RemoveNetResourceAt(std::size_t index);

        /**
        * Removes all the net resources
        *@param deleteFromMemory - if true, the net resources will also be deleted from memory
        *@return true on success, otherwise false
        */
        virtual bool RemoveAllNetResources(bool deleteFromMemory = true);

        /**
        * Gets a net resource at index
        *@param index - index
        *@return the net resource, NULL if not found or on error
        */
        virtual PSS_NetResource* GetNetResourceAt(std::size_t index);

        /**
        * Gets the net resource count
        *@return the net resource count
        */
        virtual inline std::size_t GetNetResourceCount() const;

    private:
        CObArray m_NetResourceArray;
};

//---------------------------------------------------------------------------
// PSS_NetResourceManager
//---------------------------------------------------------------------------
std::size_t PSS_NetResourceManager::GetNetResourceCount() const
{
    return m_NetResourceArray.GetSize();
}
//---------------------------------------------------------------------------

#endif
