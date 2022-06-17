/****************************************************************************
 * ==> PSS_BasicTextComponent ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic text editor which implements filtering    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BasicTextComponentH
#define PSS_BasicTextComponentH

#if _MSC_VER >= 1000
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
#ifndef PSS_BasicTextComponent
    #define PSS_BasicTextComponent ZABaseTextComponent
#endif

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Basic text component which allows filtering on input
*@author Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BasicTextComponent : public CODTextComponent
{
    DECLARE_SERIAL(PSS_BasicTextComponent)

    public:
        /**
        * Text editor
        */
        class AFX_EXT_CLASS ITextEdit : public CODTextCompEdit
        {
            public:
                /**
                * Constructor
                *@param pTextComp - text component owning this editor
                */
                ITextEdit(PSS_BasicTextComponent* pTextComp = NULL);

                virtual ~ITextEdit();

                /**
                * Enables or disables the char filtering
                *@param value - if true, the char filtering will be enabled
                */
                virtual void EnableCharFilter(bool value = true);

                /**
                * Pre-translates the Windows messages
                *@param pMsg - message
                */
                virtual BOOL PreTranslateMessage(MSG* pMsg);

            private:
                bool m_FilterChars;
        };

        typedef CODTextComponent inherited;

        PSS_BasicTextComponent();
        virtual ~PSS_BasicTextComponent();

        /**
        * Enables or disables the char filtering
        *@param value - if true, the char filtering will be enabled
        */
        virtual void EnableCharFilter(bool value = true);

        /**
        * Begin edition
        *@param pContainer - viewport container
        */
        virtual BOOL BeginEdit(sfl::MvcViewport* pContainer);

    private:
        bool m_FilterChars;
};

#endif
