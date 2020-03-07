/****************************************************************************
 * ==> PSS_RiskImpactContainer ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a risk impact container                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RiskImpactContainerH
#define PSS_RiskImpactContainerH

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
* Risk impact container
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RiskImpactContainer : public CObject
{
    public:
        PSS_RiskImpactContainer();
        virtual ~PSS_RiskImpactContainer();

        /**
        * Loads the file
        *@param fileName - the file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadFile(const CString& fileName);

        /**
        * Gets the file name
        *@return the file name
        */
        virtual CString GetFileName();

        /**
        * Gets the element array
        *@return the element array
        */
        virtual CStringArray* GetElementsArray();

        /**
        * Gets the element at index
        *@param index - the index
        *@return the element at index
        */
        virtual CString GetElementAt(std::size_t index) const;

        /**
        * Gets the element count
        *@return the element count
        */
        virtual inline std::size_t GetElementCount() const;

        /**
        * Removes all the elements
        */
        virtual void RemoveAllElements();

    private:
        CString      m_FileName;
        CStringArray m_Set;
};

//---------------------------------------------------------------------------
// PSS_RiskImpactContainer
//---------------------------------------------------------------------------
std::size_t PSS_RiskImpactContainer::GetElementCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------

#endif
