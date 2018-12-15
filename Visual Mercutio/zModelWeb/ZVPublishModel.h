// ZVPublishModel header file.

#ifndef ZVPublishModel_h
#define ZVPublishModel_h 1

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zWinUtil32\ZCLanguageCombo.h"
#include "zLanguageDef.h"

// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"

//////////////////////////////////////////////////////////////////////
// Forward class declaration

#ifdef _ZMODELWEBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 28 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// ******************************************************************************************************************
// * JMR-MODIF - Le 4 juillet 2005 - Supprimé l'option de publication HTML en chemin relatif ou absolu. Ajouté        *
// * l'option de publication du rapport Conceptor.                                                                    *
// ******************************************************************************************************************

class AFX_EXT_CLASS ZVPublishModel
{
public:

    ZVPublishModel( ZBPropertyAttributes* pAttributes    = NULL,
                    ZBPropertySet* pSet                    = NULL,
                    const CString IniFile                = _T( "" ) );

    virtual ~ZVPublishModel();

    // This function starts the process of choosing directory.
    BOOL Choose();

    const CString GetDirectory();

    bool GetVisualizeResult() const
    {
        return m_VisualizeResult;
    }

    // JMR-MODIF - Le 5 juillet 2005 - Ajout de la fonction GetPublishConceptor.
    bool GetPublishConceptor() const
    {
        return m_PublishConceptor;
    }

    // JMR-MODIF - Le 5 août 2005 - Ajout de la fonction GetPublishConceptorDetails.
    bool GetPublishConceptorDetails() const
    {
        return m_PublishConceptorDetails;
    }

    // JMR-MODIF - Le 5 août 2005 - Ajout de la fonction GetPublishConceptorDeliverables.
    bool GetPublishConceptorDeliverables() const
    {
        return m_PublishConceptorDeliverables;
    }

    // JMR-MODIF - Le 2 mars 2006 - Ajout de la fonction GetPublishProcess.
    bool GetPublishProcess() const
    {
        return m_PublishProcess;
    }

    // JMR-MODIF - Le 14 janvier 2007 - Ajout de la fonction GetPublishRuleBook.
    bool GetPublishRuleBook() const
    {
        return m_PublishRuleBook;
    }

    CString GetHyperLink() const
    {
        return m_HyperLink;
    }

    CString GetImageFilename() const
    {
        return m_ImageFilename;
    }

    Language GetLanguage() const
    {
        return m_Language;
    }

    ZBPropertyAttributes* GetPropAttributes() const
    {
        return m_pPropAttributes;
    }

    // RS-MODIF 12.12.04 remove attributes function
    void RemoveAllAttributes();
    void AddAttribute( _ZBPropertyAttribute* pAttribute );
    _ZBPropertyAttribute* FindAttribute( int CategoryID, int ItemID );

private:

    ZVPublishModel( const ZVPublishModel &right );
    const ZVPublishModel & operator=( const ZVPublishModel &right );

    bool LoadStateFromIniFile();
    bool SaveStateToIniFile();
    
    // RS-MODIF 12.12.04 load and save and delete attributes also
    bool LoadAttributesFromIniFile();
    bool SaveAttributesToIniFile();
    bool DeleteAttributesFromIniFile();

private:

    CString                    m_Directory;
    CString                    m_ImageFilename;
    CString                    m_HyperLink;
    CString                    m_IniFile;

    CStringArray            m_ArrayOfAddress;

    bool                    m_VisualizeResult;
    bool                    m_PublishConceptor;                    // JMR-MODIF - Ajout de m_PublishConceptor.
    bool                    m_PublishConceptorDetails;            // JMR-MODIF - Ajout de m_PublishConceptorDetails.
    bool                    m_PublishConceptorDeliverables;        // JMR-MODIF - Ajout de m_PublishConceptorDeliverables.
    bool                    m_PublishProcess;                    // JMR-MODIF - Ajout de m_PublishProcess.
    bool                    m_PublishRuleBook;                    // JMR-MODIF - Ajout de m_PublishRuleBook.

    Language                m_Language;

    ZBPropertyAttributes*    m_pPropAttributes;

    ZBPropertySet*            m_pPropSet;

    // RS-MODIF 12.12.04 to get the attributes
    _ZBPropertyAttributeSet    m_AttributeSet;
};

inline const CString ZVPublishModel::GetDirectory()
{
    return m_Directory;
}

#endif    // ZVPublishModel_h
