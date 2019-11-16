/****************************************************************************
 * ==> PSS_WorkspaceWizardTemplateItem -------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace wizard template item                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceWizardTemplateItemH
#define PSS_WorkspaceWizardTemplateItemH

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
#ifndef PSS_WorkspaceWizardTemplateItem
    #define PSS_WorkspaceWizardTemplateItem ZBWorkspaceWizardTemplateItem
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
* Workspace wizard template item
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WorkspaceWizardTemplateItem : public CObject
{
    DECLARE_SERIAL(PSS_WorkspaceWizardTemplateItem)

    public:
        /**
        * Constructor
        *@param templateName - template name
        *@param templateDescription - template description
        *@param iconFile - icon file
        *@param iconIndex - icon index
        */
        PSS_WorkspaceWizardTemplateItem(const CString& templateName        = "",
                                        const CString& templateDescription = "",
                                        const CString& iconFile            = "",
                                        int            iconIndex           = -1);

        virtual ~PSS_WorkspaceWizardTemplateItem();

        /**
        * Gets the template name
        *@return the template name
        */
        virtual inline CString GetTemplateName() const;

        /**
        * Sets the template name
        *@param value - the template name
        */
        virtual inline void SetTemplateName(const CString& value);

        /**
        * Gets the template description
        *@return the template description
        */
        virtual inline CString GetTemplateDescription() const;

        /**
        * Sets the template description
        *@param value - the template description
        */
        virtual inline void SetTemplateDescription(const CString& value);

        /**
        * Gets the icon file
        *@return the icon file
        */
        virtual inline CString GetIconFile() const;

        /**
        * Sets the icon file
        *@param value - the icon file
        */
        virtual inline void SetIconFile(const CString& value);

        /**
        * Gets the icon index
        *@return the icon index
        */
        virtual inline int GetIconIndex() const;

        /**
        * Sets the icon index
        *@param value - the icon index
        */
        virtual inline void SetIconIndex(int value);

        /**
        * Gets the icon handle
        *@return the icon handle
        */
        virtual inline HICON GetIcon() const;

        /**
        * Sets the icon handle
        *@param hIcon - the icon handle
        */
        virtual inline void SetIcon(HICON hIcon);

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

    private:
        HICON   m_hIcon;
        CString m_TemplateName;
        CString m_TemplateDescription;
        CString m_IconFile;
        int     m_IconIndex;

        /**
        * Loads the icon file
        */
        void LoadIconFile();
};

//---------------------------------------------------------------------------
// PSS_WorkspaceWizardTemplateItem
//---------------------------------------------------------------------------
CString PSS_WorkspaceWizardTemplateItem::GetTemplateName() const
{
    return m_TemplateName;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceWizardTemplateItem::SetTemplateName(const CString& value)
{
    m_TemplateName = value;
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceWizardTemplateItem::GetTemplateDescription() const
{
    return m_TemplateDescription;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceWizardTemplateItem::SetTemplateDescription(const CString& value)
{
    m_TemplateDescription = value;
}
//---------------------------------------------------------------------------
CString PSS_WorkspaceWizardTemplateItem::GetIconFile() const
{
    return m_IconFile;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceWizardTemplateItem::SetIconFile(const CString& value)
{
    m_IconFile = value;
}
//---------------------------------------------------------------------------
int PSS_WorkspaceWizardTemplateItem::GetIconIndex() const
{
    return m_IconIndex;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceWizardTemplateItem::SetIconIndex(int value)
{
    m_IconIndex = value;
}
//---------------------------------------------------------------------------
HICON PSS_WorkspaceWizardTemplateItem::GetIcon() const
{
    return m_hIcon;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceWizardTemplateItem::SetIcon(HICON hIcon)
{
    m_hIcon = hIcon;
}
//---------------------------------------------------------------------------

#endif
