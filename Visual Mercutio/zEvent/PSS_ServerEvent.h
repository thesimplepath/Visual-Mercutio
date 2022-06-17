/****************************************************************************
 * ==> PSS_ServerEvent -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a server event                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ServerEventH
#define PSS_ServerEventH

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
#include "PSS_Event.h"

#ifdef _ZEVENTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Event server
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ServerEvent : public PSS_Event
{
    public:
        /**
        * Event result
        */
        enum class IEResult
        {
            IE_ER_NF,
            IE_ER_Imported,
            IE_ER_Rejected,
            IE_ER_LogAdded,
            IE_ER_LogProblem
        };

        PSS_ServerEvent();

        /**
        * Constructor
        *@param time - time
        *@param fileName - file name
        *@param eventResultValue - event result value
        */
        PSS_ServerEvent(const COleDateTime& time, const CString& fileName, IEResult eventResultValue);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ServerEvent(const PSS_ServerEvent& other);

        virtual ~PSS_ServerEvent();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ServerEvent& operator = (const PSS_ServerEvent& other);

        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;

        /**
        * Gets the event result
        *@return the event result
        */
        virtual inline IEResult GetEventResult() const;

        /**
        * Gets the event result as a string
        *@return the event result as a string
        */
        virtual CString GetEventResultStr() const;

    protected:
        IEResult m_EventResult;
        CString  m_FileName;
};

//---------------------------------------------------------------------------
// PSS_ServerEvent
//---------------------------------------------------------------------------
CString PSS_ServerEvent::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
PSS_ServerEvent::IEResult PSS_ServerEvent::GetEventResult() const
{
    return m_EventResult;
}
//---------------------------------------------------------------------------

#endif
