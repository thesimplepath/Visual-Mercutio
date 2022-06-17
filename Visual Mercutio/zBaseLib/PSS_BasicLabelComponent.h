/****************************************************************************
 * ==> PSS_BasicLabelComponent ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic label editor which implements filtering   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BasicLabelComponentH
#define PSS_BasicLabelComponentH

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
#ifndef PSS_BasicLabelComponent
    #define PSS_BasicLabelComponent ZABaseLabelComponent
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
* Basic label component which allows filtering on input
*@author Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BasicLabelComponent : public CODLabelComponent
{
    DECLARE_SERIAL(PSS_BasicLabelComponent)

    public:
        /**
        * Label editor
        */
        class AFX_EXT_CLASS ILabelEdit : public CODTextCompEdit
        {
        public:
            /**
            * Constructor
            *@param pTextComp - text component owning this editor
            */
            ILabelEdit(PSS_BasicLabelComponent* pTextComp = NULL);

            virtual ~ILabelEdit();

            /**
            * Pre-translates the Windows messages
            *@param pMsg - message
            */
            virtual BOOL PreTranslateMessage(MSG* pMsg);
        };

        PSS_BasicLabelComponent();

        /**
        * Constructor
        *@param ctlPoint - control point
        */
        PSS_BasicLabelComponent(const OD_CONTROL_POINT ctlPoint);

        virtual ~PSS_BasicLabelComponent();

        /**
        * Begin edition
        *@param pContainer - viewport container
        */
        virtual BOOL BeginEdit(sfl::MvcViewport* pContainer);

        /**
        * Gets if empty text is allowed after edition
        *@return true if empty text is allowed, otherwise false
        */
        virtual bool GetAllowEmptyText() const;

        /**
        * Sets if empty text is allowed after edition
        *@param value - if true, empty text is allowed
        */
        virtual void SetAllowEmptyText(bool value);

    private:
        bool m_AllowEmptyText;
};

#endif
