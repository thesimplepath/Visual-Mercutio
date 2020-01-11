/****************************************************************************
 * ==> PSS_SymbolListCtrl --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol list controller                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SymbolListCtrlH
#define PSS_SymbolListCtrlH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_ListCtrl.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Symbol list controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SymbolListCtrl : public PSS_ListCtrl
{
    DECLARE_DYNAMIC(PSS_SymbolListCtrl)

    public:
        PSS_SymbolListCtrl();
        virtual ~PSS_SymbolListCtrl();

        /**
        * Initializes the controller
        *@param pSet - the component set
        *@param resID - the resource identifier
        *@return the component count
        */
        virtual int Initialize(CODComponentSet* pSet, UINT resID);

        /**
        * Refreshes the controller
        *@return the component count
        */
        virtual int Refresh();

        /**
        * Gets the selected symbol
        *@return the selected symbol, NULL if no selection or on error
        */
        virtual CODSymbolComponent* GetSelectedSymbol();

    protected:
        /// Generated message map
        //{{AFX_MSG(PSS_SymbolListCtrl)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CODComponentSet* m_pSet;
        BOOL             m_ColumnsBuilt;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SymbolListCtrl(const PSS_SymbolListCtrl& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_SymbolListCtrl& operator = (const PSS_SymbolListCtrl& other);

        /**
        * Builds columns
        *@param resID - the resource identifier
        */
        void BuildColumns(UINT resID);

        /**
        * Gets the symbol item index
        *@param pComponent - the symbol component for which the item index should be found
        *@return the symbol item index, -1 if not found or on error
        */
        int GetItemIndex(CODSymbolComponent* pComponent);
};

#endif
