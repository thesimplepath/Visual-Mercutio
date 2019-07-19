/****************************************************************************
 * ==> PSS_PublishModel ----------------------------------------------------*
 ****************************************************************************
 * Description : Publishes a model                                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishModelH
#define PSS_PublishModelH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zProperty\ZBPropertyAttributes.h"
#include "zLanguageDef.h"

#ifdef _ZMODELWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Publishes a model
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PublishModel
{
    public:
        /**
        * Constructor
        *@param pAttrributes - model attributes to publish
        *@param pSet - model properties to publish
        *@param iniFile - initialization file name
        */
        PSS_PublishModel(ZBPropertyAttributes* pAttributes = NULL,
                         ZBPropertySet*        pSet        = NULL,
                         const CString&        iniFile     = _T(""));

        virtual ~PSS_PublishModel();

        /**
        * Starts the dir selection process
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SelectDir();

        /**
        * Gets the publication directory
        *@return the publication directory
        */
        virtual inline CString GetDir() const;

        /**
        * Gets if result should be visualized
        *@return true if result should be visualized, otherwise false
        */
        virtual inline bool GetVisualizeResult() const;

        /**
        * Gets if Conceptor should be published
        *@return true if Conceptor should be published, otherwise false
        */
        virtual inline bool GetPublishConceptor() const;

        /**
        * Gets if Conceptor details should be published
        *@return true if Conceptor details should be published, otherwise false
        */
        virtual inline bool GetPublishConceptorDetails() const;

        /**
        * Gets if Conceptor deliverabled should be published
        *@return true if Conceptor deliverables should be published, otherwise false
        */
        virtual inline bool GetPublishConceptorDeliverables() const;

        /**
        * Gets if process should be published
        *@return true if process should be published, otherwise false
        */
        virtual inline bool GetPublishProcess() const;

        /**
        * Gets if rules book should be published
        *@return true if rules book should be published, otherwise false
        */
        virtual inline bool GetPublishRuleBook() const;

        /**
        * Gets the publication hyperlink
        *@return the publication hyperlink
        */
        virtual inline CString GetHyperLink() const;

        /**
        * Gets the image file name
        *@return the image file name
        */
        virtual inline CString GetImageFilename() const;

        /**
        * Gets the publication language
        *@return the publication language
        */
        virtual inline ELanguage GetLanguage() const;

        /**
        * Gets the property attributes
        *@return the property attributes
        */
        virtual inline ZBPropertyAttributes* GetPropAttributes() const;

        /**
        * Adds an attribute
        *@param pAttribute - attribute to add
        */
        virtual void AddAttribute(_ZBPropertyAttribute* pAttribute);

        /**
        * Finds an attribute
        *@param categoryID - category identifier at which the attribute belongs
        *@param itemID - item identifier at which the attribute belongs
        *@return attribute, NULL if not found or on error
        */
        virtual _ZBPropertyAttribute* FindAttribute(int categoryID, int itemID);

        /**
        * Removes all attributes
        */
        virtual void RemoveAllAttributes();

    private:
        ZBPropertyAttributes*   m_pPropAttributes;
        ZBPropertySet*          m_pPropSet;
        _ZBPropertyAttributeSet m_AttributeSet;
        ELanguage               m_Language;
        CStringArray            m_ArrayOfAddress;
        CString                 m_Directory;
        CString                 m_ImageFilename;
        CString                 m_HyperLink;
        CString                 m_IniFile;
        bool                    m_VisualizeResult;
        bool                    m_PublishConceptor;
        bool                    m_PublishConceptorDetails;
        bool                    m_PublishConceptorDeliverables;
        bool                    m_PublishProcess;
        bool                    m_PublishRuleBook;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_PublishModel(const PSS_PublishModel& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return itself
        */
        const PSS_PublishModel& operator = (const PSS_PublishModel& other);

        /**
        * Loads state from ini file
        *@return true on success, otherwise false
        */
        bool LoadStateFromIniFile();

        /**
        * Saves state to ini file
        *@return true on success, otherwise false
        */
        bool SaveStateToIniFile();

        /**
        * Loads attributes from ini file
        *@return true on success, otherwise false
        */
        bool LoadAttributesFromIniFile();

        /**
        * Saves attributes to ini file
        *@return true on success, otherwise false
        */
        bool SaveAttributesToIniFile();

        /**
        * Deletes all attriutes from ini file
        *@return true on success, otherwise false
        */
        bool DeleteAttributesFromIniFile();
};

//---------------------------------------------------------------------------
// PSS_PublishModel
//---------------------------------------------------------------------------
CString PSS_PublishModel::GetDir() const
{
    return m_Directory;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::GetVisualizeResult() const
{
    return m_VisualizeResult;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::GetPublishConceptor() const
{
    return m_PublishConceptor;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::GetPublishConceptorDetails() const
{
    return m_PublishConceptorDetails;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::GetPublishConceptorDeliverables() const
{
    return m_PublishConceptorDeliverables;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::GetPublishProcess() const
{
    return m_PublishProcess;
}
//---------------------------------------------------------------------------
bool PSS_PublishModel::GetPublishRuleBook() const
{
    return m_PublishRuleBook;
}
//---------------------------------------------------------------------------
CString PSS_PublishModel::GetHyperLink() const
{
    return m_HyperLink;
}
//---------------------------------------------------------------------------
CString PSS_PublishModel::GetImageFilename() const
{
    return m_ImageFilename;
}
//---------------------------------------------------------------------------
ELanguage PSS_PublishModel::GetLanguage() const
{
    return m_Language;
}
//---------------------------------------------------------------------------
ZBPropertyAttributes* PSS_PublishModel::GetPropAttributes() const
{
    return m_pPropAttributes;
}
//---------------------------------------------------------------------------

#endif
