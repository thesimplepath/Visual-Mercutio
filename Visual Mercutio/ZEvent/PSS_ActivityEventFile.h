/****************************************************************************
 * ==> PSS_ActivityEventFile -----------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity event file                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ActivityEventFileH
#define PSS_ActivityEventFileH

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

// processoft
#include "PSS_ActivityEvent.h"
#include "EventFl.h"

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
* Activity event file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ActivityEventFile : public ZBEventFile
{
    public:
        PSS_ActivityEventFile();

    protected:
        /**
        * Builds a line
        *@param path - path
        *@param fileName - file name
        */
        virtual void BuildLine(const CString& path, const CString& fileName);

        /**
        * Parses a line
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ParseLine();

        /**
        * Allocates a new event
        *@return the newly created event, NULL on error
        */
        virtual inline ZBEvent* AllocateEvent() const;

    private:
        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ActivityEventFile(const PSS_ActivityEventFile& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_ActivityEventFile& operator = (const PSS_ActivityEventFile& other);
};

//---------------------------------------------------------------------------
// PSS_ActivityEventFile
//---------------------------------------------------------------------------
ZBEvent* PSS_ActivityEventFile::AllocateEvent() const
{
    PSS_ActivityEvent* pEvent = new PSS_ActivityEvent;
    return pEvent;
}
//---------------------------------------------------------------------------

#endif
