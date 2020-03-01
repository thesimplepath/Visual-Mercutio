/****************************************************************************
 * ==> PSS_RiskTypeContainer -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a risk type container                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RiskTypeContainerH
#define PSS_RiskTypeContainerH

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
* Risk type container
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RiskTypeContainer : public CObject
{
    public:
        PSS_RiskTypeContainer();
        virtual ~PSS_RiskTypeContainer();

        /**
        * Loads the risk type from a file
        *@param fileName - the risk type file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL LoadFile(const CString& fileName);

        /**
        * Gets the file name
        *@return the file name
        */
        virtual CString GetFileName() const;

        /**
        * Gets the element array
        *@return the element array
        */
        virtual CStringArray* GetElementsArray();

        /**
        * Gets the element at index
        *@param index - the index
        *@return the element at index, NULL if not found or on error
        */
        virtual CString GetElementAt(std::size_t index) const;

        /**
        * Removes all the elements
        */
        virtual void RemoveAllElements();

        /**
        * Gets the element count
        *@return the element count
        */
        virtual inline std::size_t GetElementCount() const;

    private:
        CString      m_FileName;
        CStringArray m_Set;
};

//---------------------------------------------------------------------------
// PSS_RiskTypeContainer
//---------------------------------------------------------------------------
std::size_t PSS_RiskTypeContainer::GetElementCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------

#endif
