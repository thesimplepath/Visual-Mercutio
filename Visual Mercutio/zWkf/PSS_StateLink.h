/****************************************************************************
 * ==> PSS_StateLink -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a state link for a state machine                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_StateLinkH
#define PSS_StateLinkH

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
#ifndef PSS_StateLink
    #define PSS_StateLink ZBStateLink
#endif

// mfc
#include "StdAfx.h"

// processsoft
#include "zModel\PSS_LinkSymbol.h"
#include "PSS_AutomationCollections.h"

// class name mapping
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_ProcessGraphModelMdl;

#ifdef _ZWKFEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Provides a state link for a state machine
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_StateLink : public CObject
{
    DECLARE_SERIAL(PSS_StateLink)

    public:
        /**
        * Link directions
        */
        enum IELinkDirection
        {
            IE_LD_EnteringUp,
            IE_LD_EnteringLeft,
            IE_LD_EnteringRight,
            IE_LD_EnteringDown,
            IE_LD_LeavingUp,
            IE_LD_LeavingLeft,
            IE_LD_LeavingRight,
            IE_LD_LeavingDown,
            IE_LD_UnknownDirection
        };

        /**
        * Constructor
        *@param pLinkSymbol - link symbol
        *@param direction - link direction
        *@param pModel - model
        */
        PSS_StateLink(PSS_LinkSymbol*           pLinkSymbol = NULL,
                      IELinkDirection           direction   = IE_LD_EnteringUp,
                      PSS_ProcessGraphModelMdl* pModel      = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_StateLink(const PSS_StateLink& other);

        virtual ~PSS_StateLink();

        /**
        * Assignment operator
        *@param other - other object to copy from
        *@retrurn itself
        */
        PSS_StateLink& operator = (const PSS_StateLink& src);

        /**
        * Clones the state link
        *@return cloned state link
        */
        virtual PSS_StateLink* Clone() const;

        /**
        * Assigns a model
        *@param pModel - model to assign
        */
        virtual inline void AssignModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Gets the link symbol
        *@return the link symbol
        */
        virtual inline PSS_LinkSymbol* GetLinkSymbol() const;

        /**
        * Sets the link symbol
        *@param value - link symbol to set
        */
        virtual inline void SetLinkSymbol(PSS_LinkSymbol* value);

        /**
        * Gets the link direction
        *@return the link direction
        */
        virtual inline IELinkDirection GetDirection() const;

        /**
        * Sets the link direction
        *@param value - link direction to set
        */
        virtual inline void SetDirection(IELinkDirection value);

        /**
        * Checks if instance is equals to another
        *@param other - other instance to compare with
        *@return true if instances are equals, otherwise false
        */
        virtual bool IsEqual(const PSS_StateLink& other) const;

        /**
        * Checks if an internal link symbol instance is equals to another
        *@param other - other instance to compare with
        *@return true if instances are equals, otherwise false
        */
        virtual bool IsEqual(const PSS_LinkSymbol& other) const;

        /**
        * Serializes the state link content
        *@param ar - archive in which the content will be serialized
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the state link validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the state link content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    private:
        PSS_ProcessGraphModelMdl* m_pModel;
        PSS_LinkSymbol*           m_pLinkSymbol;
        IELinkDirection           m_Direction;
};

//---------------------------------------------------------------------------
// PSS_StateLink
//---------------------------------------------------------------------------
void PSS_StateLink::AssignModel(PSS_ProcessGraphModelMdl* pModel)
{
    m_pModel = pModel;
}
//---------------------------------------------------------------------------
PSS_LinkSymbol* PSS_StateLink::GetLinkSymbol() const
{
    return m_pLinkSymbol;
}
//---------------------------------------------------------------------------
void PSS_StateLink::SetLinkSymbol(PSS_LinkSymbol* value)
{
    m_pLinkSymbol = value;
}
//---------------------------------------------------------------------------
PSS_StateLink::IELinkDirection PSS_StateLink::GetDirection() const
{
    return m_Direction;
}
//---------------------------------------------------------------------------
void PSS_StateLink::SetDirection(IELinkDirection value)
{
    m_Direction = value;
}
//---------------------------------------------------------------------------

#endif
