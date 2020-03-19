/****************************************************************************
 * ==> PSS_PropertyDescription ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a property description                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PropertyDescriptionH
#define PSS_PropertyDescriptionH

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
#include "zBaseLib\PSS_Observer.h"

// old class name mapping
#ifndef PSS_Property
    #define PSS_Property ZBProperty
#endif

// forward class declaration
class PSS_Property;
class PSS_ObserverMsg;

#ifdef _ZPTYMGREXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Property description
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PropertyDescription : public CStatic,
                                              public PSS_Observer
{
    public:
        PSS_PropertyDescription();
        virtual ~PSS_PropertyDescription();

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_PropertyDescription)
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_PropertyDescription)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        COLORREF m_Background;
        COLORREF m_Text;
        CFont    m_Font;
        CFont    m_FontBold;
        CString  m_Title;
        CString  m_Description;

        /**
        * Empties the control data
        */
        void EmptyControlData();

        /**
        * Updates the control data
        *@param pProp - the property to use to update the control data
        */
        void UpdateControlData(PSS_Property* pProp);
};

#endif
