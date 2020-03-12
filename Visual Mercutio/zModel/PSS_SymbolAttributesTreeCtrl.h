/****************************************************************************
 * ==> PSS_SymbolAttributesTreeCtrl ----------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol attributes tree controller               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SymbolAttributesTreeCtrlH
#define PSS_SymbolAttributesTreeCtrlH

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
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_TreeCtrl.h"
#include "zProperty\ZIProperties.h"
#include "zProperty\PSS_PropertyAttributes.h"

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
* Symbol attributes tree controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SymbolAttributesTreeCtrl : public PSS_TreeCtrl,
                                                   public PSS_Subject,
                                                   public PSS_Observer
{
    public:
        /**
        * Constructor
        *@param pPropAttributes - the property attributes
        *@param pPropSet - the property set
        */
        PSS_SymbolAttributesTreeCtrl(PSS_PropertyAttributes* pPropAttributes = NULL, ZBPropertySet* pPropSet = NULL);

        virtual ~PSS_SymbolAttributesTreeCtrl();

        /**
        * Initializes the controller
        */
        virtual void Initialize();

        /**
        * Initializes the controller
        *@param pPropAttributes - the property attributes
        *@param pPropSet - the property set
        */
        virtual void Initialize(PSS_PropertyAttributes* pPropAttributes, ZBPropertySet* pPropSet);

        /**
        * Refreshes the controller
        */
        virtual void Refresh();

        /**
        * Fills the matching checked items
        *@return true on success, otherwise false
        */
        virtual bool FillMatchingCheckedItems();

        /**
        * Called when the controller receives a message
        *@param pSubject - the subject which sent the message
        *@param pMsg - the received message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /**
        * Tree data
        */
        class ITreeData : public CObject
        {
            public:
                /**
                * Data type
                */
                enum IEDataType
                {
                    IE_DT_Category,
                    IE_DT_Item,
                    IE_DT_Unknown
                };

                PSS_PropertyAttributes::IAttribute* m_pPropAttribute;
                IEDataType                          m_Type;

                ITreeData();

                /**
                * Constructor
                *@param category - the property category
                *@param item - the property item
                */
                ITreeData(int category, int item = -1);

                /**
                * Constructor
                *@param pPropAttribute - the property attribuze
                */
                ITreeData(PSS_PropertyAttributes::IAttribute* pPropAttribute);
        
                virtual ~ITreeData();
        };

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SymbolAttributesTreeCtrl)
        virtual BOOL DestroyWindow();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_SymbolAttributesTreeCtrl)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnItemExpanded(LPNMHDR pnmhdr, LRESULT *pLResult);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Gets the no drop image index
        *@return the no drop image index
        */
        virtual inline int GetIndexOfNoDropImage() const;

        /**
        * Gets the drag object
        *@param dragItem - the drag item handle
        *@return the drag object, NULL if not found or on error
        */
        virtual CObject* GetDragObject(HTREEITEM dragItem);

    private:
        typedef sfl::CCArray_T <ITreeData*, ITreeData*> ITreeDataSet;
        typedef sfl::Iterator_T<ITreeData*>             ITreeDataIterator;

        PSS_PropertyAttributes* m_pPropAttributes;
        ZBPropertySet*          m_pPropSet;
        ITreeDataSet            m_DataSet;
        bool                    m_HasBeenInitialized;

        /**
        * Creates the tree
        */
        void CreateTree();

        /**
        * Loads the tree
        */
        void LoadTree();

        /**
        * Destroys the tree
        */
        void DestroyTree();

        /**
        * Empties the dataset
        */
        void EmptyDataSet();

        /**
        * Processes the property
        *@param pProp - the property
        *@return true on success, otherwise false
        */
        bool ProcessProperty(PSS_Property* pProp);

        /**
        * Gets the parent property
        *@param pProp - the property for which the parent should be get
        *@return the parent property, NULL on error
        */
        HTREEITEM GetParentProperty(PSS_Property* pProp);

        /**
        * Checks the property attribute
        *@param pAttribute - the property attribute to check
        */
        void CheckAttribute(PSS_PropertyAttributes::IAttribute* pAttribute);

        /**
        * Adds a property item
        *@param label - the property label
        *@param category - the property category
        *@param item - the property item
        *@param hParentTreeItem - the property parent tree item handle
        *@return the newla added property item handle, NULL on error
        */
        HTREEITEM AddPropertyItem(const CString& label, int category, int item = -1, HTREEITEM hParentTreeItem = NULL);

        /**
        * Finds an element from a dataset
        *@param category - the property category
        *@param item - the property item
        *@return the element, NULL if not found or on error
        */
        ITreeData* FindElementFromDataSet(int category, int item = -1);

        /**
        * Finds an element from a dataset
        *@param pPropAttribute - the property attribute
        *@return the element, NULL if not found or on error
        */
        ITreeData* FindElementFromDataSet(PSS_PropertyAttributes::IAttribute* pPropAttribute);

        /**
        * Adds a data to a dataset
        *@param category - the property category
        *@param item - the property item
        *@return the added data, NULL on error
        */
        ITreeData* AddDataToSet(int category, int item = -1);

        /**
        * Adds a data to a dataset
        *@param pPropAttribute - the property attribute
        *@return the added data, NULL on error
        */
        ITreeData* AddDataToSet(PSS_PropertyAttributes::IAttribute* pPropAttribute);
};

//---------------------------------------------------------------------------
// PSS_SymbolAttributesTreeCtrl
//---------------------------------------------------------------------------
int PSS_SymbolAttributesTreeCtrl::GetIndexOfNoDropImage() const
{
    return 4;
}
//---------------------------------------------------------------------------

#endif
