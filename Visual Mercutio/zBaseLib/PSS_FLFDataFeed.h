/****************************************************************************
 * ==> PSS_FLFDataFeed -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a class used to import additional information     *
 *               coming from FLF file                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FLFDataFeedH
#define PSS_FLFDataFeedH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "PSS_Export.h"

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
* Class used to import additional information coming from FLF file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FLFDataFeed : public PSS_Export
{
    public:
        PSS_FLFDataFeed();
        virtual ~PSS_FLFDataFeed();

        /**
        * Processes the line and updates the document
        *@param line - line
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ProcessLine(const CString& line);

        /**
        * Imports additional information
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ImportAdditionalInfo();

        /**
        * Imports the file to the document
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PreImport();

        /**
        * Gets the process name
        *@return the process name
        */
        virtual inline const CString& GetProcessName() const;

        /**
        * Gets the form name
        *@return the form name
        */
        virtual inline const CString& GetFormName() const;

        /**
        * Gets the folder name
        *@return the folder name
        */
        virtual inline const CString& GetFolderName() const;

        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline const CString& GetFileName() const;

        /**
        * Gets the process exchange file name
        *@return the process exchange file name
        */
        virtual inline const CString& GetProcessExchangeFileName() const;

        /**
        * Gets if the source file should be kept or not
        *@return TRUE if the source file should be kept, otherwise FALSE
        */
        virtual inline const BOOL& GetKeepOnlyFLF() const;

    private:
        CString m_ProcessName;
        CString m_FormName;
        CString m_FolderName;
        CString m_FileName;
        CString m_ProcessExchangeFileName;
        BOOL    m_KeepOnlyFLF;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FLFDataFeed(const PSS_FLFDataFeed& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FLFDataFeed& operator = (const PSS_FLFDataFeed& other);
};

//---------------------------------------------------------------------------
// PSS_FLFDataFeed
//---------------------------------------------------------------------------
const CString& PSS_FLFDataFeed::GetProcessName() const
{
    return m_ProcessName;
}
//---------------------------------------------------------------------------
const CString& PSS_FLFDataFeed::GetFormName() const
{
    return m_FormName;
}
//---------------------------------------------------------------------------
const CString& PSS_FLFDataFeed::GetFolderName() const
{
    return m_FolderName;
}
//---------------------------------------------------------------------------
const CString& PSS_FLFDataFeed::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
const CString& PSS_FLFDataFeed::GetProcessExchangeFileName() const
{
    return m_ProcessExchangeFileName;
}
//---------------------------------------------------------------------------
const BOOL& PSS_FLFDataFeed::GetKeepOnlyFLF() const
{
    return m_KeepOnlyFLF;
}
//---------------------------------------------------------------------------

#endif
