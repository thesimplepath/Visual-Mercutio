/****************************************************************************
 * ==> PSS_LanguageCombo ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a combo box allowing to select a language         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LanguageComboH
#define PSS_LanguageComboH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zLanguageDef.h"

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
* Combo box allowing to select a language
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_LanguageCombo : public CCJFlatComboBox
{
    public:
        /**
        * Constructor
        *@param initialLanguage - initial language to select, may be unknown
        */
        PSS_LanguageCombo(ELanguage initialLanguage = E_LN_Unknown);

        virtual ~PSS_LanguageCombo();

        /**
        * Initializes the combo box
        */
        virtual int Initialize();

        /**
        * Initializes the combo box with a default language
        *@param initialLanguage - initial language to select
        */
        virtual inline int Initialize(ELanguage initialLanguage);

        /**
        * Gets the language
        *@return the language
        */
        virtual inline ELanguage GetLanguage() const;

        /**
        * Selects the language
        *@param newLanguage - new language to select
        */
        virtual inline void SelectLanguage(ELanguage newLanguage);

    protected:
        /// message map
        //{{AFX_MSG(PSS_LanguageCombo)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        ELanguage m_Language;

        /**
        * Copy constructor
        *@param other - other combo box to copy from
        */
        PSS_LanguageCombo(const PSS_LanguageCombo& other);

        /**
        * Copy operator
        *@param other - other combo box to copy from
        */
        const PSS_LanguageCombo& operator = (const PSS_LanguageCombo& other);
};

//---------------------------------------------------------------------------
// PSS_LanguageCombo
//---------------------------------------------------------------------------
int PSS_LanguageCombo::Initialize(ELanguage initialLanguage)
{
    m_Language = initialLanguage;
    return Initialize();
}
//---------------------------------------------------------------------------
ELanguage PSS_LanguageCombo::GetLanguage() const
{
    return static_cast<ELanguage>(GetCurSel());
}
//---------------------------------------------------------------------------
void PSS_LanguageCombo::SelectLanguage(ELanguage newLanguage)
{
    SetCurSel(newLanguage);
}
//---------------------------------------------------------------------------

#endif
