/****************************************************************************
 * ==> PSS_ProcessGraphPage ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a process graph page                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessGraphPageH
#define PSS_ProcessGraphPageH

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
#ifndef PSS_ProcessGraphPage
    #define PSS_ProcessGraphPage ZDProcessGraphPage
#endif

// processsoft
#include "PSS_ProcessGraphModelMdl.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

using namespace sfl;

/**
* Process graph page
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessGraphPage : public CObject
{
    DECLARE_SERIAL(PSS_ProcessGraphPage)

    public:
        /**
        * Constructor
        *@param pageName - the page name
        *@param pModel - the parent model, can be NULL
        */
        PSS_ProcessGraphPage(const CString& pageName = _T(""), PSS_ProcessGraphModelMdl* pModel = NULL);

        virtual ~PSS_ProcessGraphPage();

        /**
        * Gets the page name
        *@return the page name
        */
        virtual inline CString GetPageName() const;

        /**
        * Sets the page name
        *@param value - the page name
        */
        virtual inline void SetPageName(const CString& value);

        /**
        * Gets the model
        *@return the model
        */
        virtual inline PSS_ProcessGraphModelMdl* GetModel() const;

        /**
        * Sets the model
        *@param pModel - the model
        */
        virtual inline void SetModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        PSS_ProcessGraphModelMdl* m_pModel;
        CString                   m_ModelName;
        CString                   m_PageName;
};

//---------------------------------------------------------------------------
// PSS_ProcessGraphPage
//---------------------------------------------------------------------------
CString PSS_ProcessGraphPage::GetPageName() const
{
    return m_PageName;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphPage::SetPageName(const CString& value)
{
    m_PageName = value;

    if (m_pModel)
        m_pModel->SetModelName(m_PageName);
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphPage::GetModel() const
{
    return m_pModel;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphPage::SetModel(PSS_ProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;
}
//---------------------------------------------------------------------------

#endif
