/****************************************************************************
 * ==> PSS_BasePropSheet ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic property sheet                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BasePropSheetH
#define PSS_BasePropSheetH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "Mfc.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Basic property sheet
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BasePropSheet : public CPropertySheet
{
    DECLARE_DYNAMIC(PSS_BasePropSheet)

    public:
        /**
        * Constructor
        *@param defaultTab - default tab index
        */
        PSS_BasePropSheet(int defaultTab = 0);

        /**
        * Constructor
        *@param captionID - caption identifier
        *@param defaultTab - default tab index
        */
        PSS_BasePropSheet(UINT captionID, int defaultTab = 0);

        /**
        * Constructor
        *@param pCaption - caption name
        *@param defaultTab - default tab index
        */
        PSS_BasePropSheet(LPCTSTR pCaption, int defaultTab = 0);

        virtual ~PSS_BasePropSheet();

        /**
        * Gets the current page
        *@return the current page
        */
        virtual int GetCurPage() const;

        /**
        * Gets the page array
        *@return the page array
        */
        virtual inline CObArray& GetPageArray();

        /**
        * Finds the property page
        *@param pPage - property page to search
        *@return property page index
        */
        virtual int FindPropertyPage(CPropertyPage* pPage);

        /**
        * Deletes the property page
        *@param pPage - property page to delete
        *@return true on success, otherwise false
        */
        virtual bool DeletePropertyPage(CPropertyPage* pPage);

        /**
        * Deletes the property page at index
        *@param index - property page index to delete
        *@return true on success, otherwise false
        */
        virtual bool DeletePropertyPageAt(std::size_t index);

        /**
        * Deletes all the property pages
        */
        virtual void DeleteAllPropertyPages();

    protected:
        CObArray m_PageArray;

        /// Generated message map functions
        //{{AFX_MSG(ZIBasePropSheet)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_BasePropSheet(const PSS_BasePropSheet& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_BasePropSheet& operator = (const PSS_BasePropSheet& other);
};

//---------------------------------------------------------------------------
// PSS_BasePropSheet
//---------------------------------------------------------------------------
CObArray& PSS_BasePropSheet::GetPageArray()
{
    return m_PageArray;
}
//---------------------------------------------------------------------------

#endif
