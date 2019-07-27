/****************************************************************************
 * ==> PSS_GenericPropPage -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic property page                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GenericPropPageH
#define PSS_GenericPropPageH

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
* Generic property page
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GenericPropPage : public CPropertyPage
{
    public:
        /**
        * Constructor
        *@param templateID - template identifier
        *@param pObj - object
        */
        PSS_GenericPropPage(UINT templateID, CObject* pObj);

        virtual ~PSS_GenericPropPage();

        /**
        * Gets the object
        *@return the object
        */
        virtual inline CObject& GetObject() const;

        /**
        * Checks if the property page was initialized
        *@return TRUE if the property page was initialized, otherwise FALSE
        */
        virtual inline BOOL Initialized() const;

        /**
        * Sets the property page initialized
        */
        virtual inline void SetInitialized();

        /**
        * Checks if page is Ok
        *@return TRUE if page is Ok, otherwise false
        */
        virtual inline BOOL IsOk() const;

        /**
        * Saves the values to object
        */
        virtual void SaveValuesToObject () = 0;

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_GenericPropPage)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CObject* m_pObj;
        BOOL     m_Initialized;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_GenericPropPage(const PSS_GenericPropPage& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_GenericPropPage & operator = (const PSS_GenericPropPage& other);
};

//---------------------------------------------------------------------------
// PSS_GenericPropPage
//---------------------------------------------------------------------------
CObject& PSS_GenericPropPage::GetObject() const
{
    return *m_pObj;
}
//---------------------------------------------------------------------------
BOOL PSS_GenericPropPage::Initialized() const
{
    return m_Initialized;
}
//---------------------------------------------------------------------------
void PSS_GenericPropPage::SetInitialized()
{
    m_Initialized = TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_GenericPropPage::IsOk() const
{
    return TRUE;
}
//---------------------------------------------------------------------------

#endif
