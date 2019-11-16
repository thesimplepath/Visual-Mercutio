/****************************************************************************
 * ==> PSS_EventFile -------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an event file                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EventFileH
#define PSS_EventFileH

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
* Event file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EventFile
{
    public:
        PSS_EventFile();
        virtual ~PSS_EventFile();

        /**
        * Imports an activity from a file
        *@param fileName - file name
        *@return the imported activity, NULL on error
        */
        virtual PSS_Event* ImportActivityFromFile(const CString& fileName);

        /**
        * Exports an activity to a file
        *@param fileName - file name
        *@param pActivity - activity to export
        *@return TRUE on success, otherrwise FALSE
        */
        virtual BOOL ExportActivityToFile(const CString& fileName, PSS_Event* pActivity);

    protected:
        PSS_Event* m_pEvent;
        CString    m_FileBuffer;
        char*      m_pCurrent;
        char*      m_pNext;
        int        m_BufferSize;
        bool       m_LocalEvent;

        /**
        * Builds a line
        *@param path - path
        *@param fileName - file name
        */
        virtual void BuildLine(const CString& path, const CString& fileName) = 0;

        /**
        * Parses a line
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ParseLine() = 0;

        /**
        * Allocates a new event
        *@return the newly created event, NULL on error
        */
        virtual PSS_Event* AllocateEvent() const = 0;

    private:
        CString m_FileName;
        CFile   m_File;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_EventFile(const PSS_EventFile& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_EventFile& operator = (const PSS_EventFile& other);

        /**
        * Opens a file, creates it if still not exists
        *@return TRUE on success, otherwise FALSE
        */
        BOOL OpenFileCreate();

        /**
        * Opens a file for read
        *@return TRUE on success, otherwise FALSE
        */
        BOOL OpenFileRead();

        /**
        * Closes a file
        *@return TRUE on success, otherwise FALSE
        */
        BOOL CloseFile();

        /**
        * Reads the file buffer
        *@return read byte count
        */
        int ReadFileBuffer();

        /**
        * Writes a line in the file
        */
        inline void WriteLine();

        /**
        * Imports a line from the file
        *@return TRUE on success, otherwise FALSE
        */
        BOOL ImportLine();

        /**
        * Exports a line to the file
        */
        void ExportLine();
};

//---------------------------------------------------------------------------
// PSS_EventFile
//---------------------------------------------------------------------------
void PSS_EventFile::WriteLine()
{
    m_File.Write(m_FileBuffer, m_FileBuffer.GetLength());
}
//---------------------------------------------------------------------------

#endif
