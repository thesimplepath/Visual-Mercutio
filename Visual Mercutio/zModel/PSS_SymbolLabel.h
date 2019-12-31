/****************************************************************************
 * ==> PSS_SymbolLabel -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a symbol label                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SymbolLabelH
#define PSS_SymbolLabelH

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
#ifndef PSS_SymbolLabel
    #define PSS_SymbolLabel ZBSymbolLabel
#endif

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
* Symbol label
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SymbolLabel : public CODLabelComponent
{
    DECLARE_SERIAL(PSS_SymbolLabel)

    public:
        /**
        * Constructor
        *@param notifyParent - if true, the parent will be notified about changes performed on the label
        */
        PSS_SymbolLabel(bool notifyParent = false);

        /**
        * Constructor
        *@param pOwner - the label owner
        *@param notifyParent - if true, the parent will be notified about changes performed on the label
        */
        PSS_SymbolLabel(CODSymbolComponent* pOwner, bool notifyParent = false);

        /**
        * Constructor
        *@param align - the label alignment inside the parent
        *@param notifyParent - if true, the parent will be notified about changes performed on the label
        */
        PSS_SymbolLabel(const OD_CONTROL_POINT align, bool notifyParent = false);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_SymbolLabel(const PSS_SymbolLabel& other);

        virtual ~PSS_SymbolLabel();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_SymbolLabel& operator = (const PSS_SymbolLabel& other);

        /**
        * Makes a copy of this object
        *@return the duplicated object, NULL on error
        */
        virtual CODComponent* Dup() const;

        /**
        * Gets if the parent should be notified about changes performed on the label
        *@return true if the parent should be notified about changes performed on the label, otherwise false
        */
        virtual inline bool GetNotifyParent() const;

        /**
        * Sets if the parent should be notified about changes performed on the label
        *@param value - if true, the parent should be notified about changes performed on the label
        */
        virtual inline void SetNotifyParent(bool value);

        /**
        * Called when the label moves
        */
        virtual inline void OnMove();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        bool m_NotifyParent;
};

//---------------------------------------------------------------------------
// PSS_SymbolLabel
//---------------------------------------------------------------------------
bool PSS_SymbolLabel::GetNotifyParent() const
{
    return m_NotifyParent;
}
//---------------------------------------------------------------------------
void PSS_SymbolLabel::SetNotifyParent(bool value)
{
    m_NotifyParent = value;
}
//---------------------------------------------------------------------------
void PSS_SymbolLabel::OnMove()
{
    CODLabelComponent::OnMove();

    if (m_NotifyParent)
    {
        CODSymbolComponent* pComp = GetOwner();

        // call the function to finalize the embedded elements positions
        if (pComp)
            pComp->OnMove();
    }
}
//---------------------------------------------------------------------------

#endif
