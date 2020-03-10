/****************************************************************************
 * ==> PSS_InputAttributesList ---------------------------------------------*
 ****************************************************************************
 * Description : Provides an input attributes list                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InputAttributesListH
#define PSS_InputAttributesListH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_ListCtrl.h"

// class name mapping
#ifndef PSS_InputAttribute
    #define PSS_InputAttribute ZBInputAttribute
#endif
#ifndef PSS_InputAttributeManager
    #define PSS_InputAttributeManager ZBInputAttributeManager
#endif
#ifndef PSS_DynamicPropertiesManager
    #define PSS_DynamicPropertiesManager ZBDynamicPropertiesManager
#endif
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declaration
class PSS_InputAttribute;
class PSS_InputAttributeManager;
class PSS_DynamicPropertiesManager;
class PSS_ProcessGraphModelDoc;

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
* Input attributes list
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InputAttributesList : public PSS_ListCtrl,
                                              public PSS_Subject,
                                              public PSS_Observer
{
    DECLARE_DYNAMIC(PSS_InputAttributesList)

    public:
        PSS_InputAttributesList();
        virtual ~PSS_InputAttributesList();

        /**
        * Initializes the list
        *@param pInputManager - the input manager
        *@param pPropManager - the properties manager
        *@param showAll - if true, all the attributes should be shown
        *@param symbolRef - the symbol reference
        *@return the attribute count
        */
        virtual int Initialize(PSS_InputAttributeManager*    pInputManager,
                               PSS_DynamicPropertiesManager* pPropManager,
                               bool                          showAll   =  false,
                               int                           symbolRef = -1);

        /**
        * Gets the selected input attribute
        *@return the selected input attribute, NULL if no selection or on error
        */
        virtual PSS_InputAttribute* GetSelectedInputAttribute();

        /**
        * Shows all the attributes
        *@param value - if true, all the attributes will be shown
        *@param refresh - if true, the attributes will be refreshed immediately
        */
        virtual inline void ShowAll(bool value = true, bool refresh = true);

        /**
        * Sets the symbol reference
        *@param value - the symbol reference
        *@param refresh - if true, the attributes will be refreshed immediately
        */
        virtual inline void SetSymbolRef(int value, bool refresh = true);

        /**
        * Refreshes the attributes
        *@return the attribute count
        */
        virtual int Refresh();

        /**
        * Deletes all the attributes
        */
        virtual void Empty();

        /**
        * Called when the frame is updated
        *@param pSubject - subject
        *@param pMSg - message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_InputAttributesList)
        //}}AFX_VIRTUAL

        /// Generated message map
        //{{AFX_MSG(PSS_InputAttributesList)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_InputAttributeManager*    m_pInputManager;
        PSS_DynamicPropertiesManager* m_pPropManager;
        PSS_ProcessGraphModelDoc*     m_pDoc;
        CODComponent*                 m_pComp;
        int                           m_SymbolRef;
        BOOL                          m_ColumnsBuilt;
        bool                          m_ShowAll;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_InputAttributesList(const PSS_InputAttributesList& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_InputAttributesList& operator = (const PSS_InputAttributesList& other);

        /**
        * Builds the columns
        */
        void BuildColumns();

        /**
        * Called when the document was activated
        *@param pDoc - the activated document
        */
        void DocumentActivated(PSS_ProcessGraphModelDoc* pDoc);
};

//---------------------------------------------------------------------------
// PSS_InputAttributesList
//---------------------------------------------------------------------------
void PSS_InputAttributesList::ShowAll(bool value, bool refresh)
{
    m_ShowAll = value;

    if (refresh)
        Refresh();
}
//---------------------------------------------------------------------------
void PSS_InputAttributesList::SetSymbolRef(int value, bool refresh)
{
    m_SymbolRef = value;

    if (refresh)
        Refresh();
}
//---------------------------------------------------------------------------

#endif
