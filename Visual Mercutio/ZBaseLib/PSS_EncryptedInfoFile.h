/****************************************************************************
 * ==> PSS_EncryptedInfoFile  ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a basic encrypted info file                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EncryptedInfoFileH
#define PSS_EncryptedInfoFileH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include <fstream> 
#include <share.h>

// processsoft
#include "PSS_EncryptedLine.h"

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
* Encrypted info file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EncryptedInfoFile
{
    public:
        /**
        * Constructor
        *@param tableEntries- table entry count to reserve
        */
        PSS_EncryptedInfoFile(std::size_t tableEntries = 40);

        /**
        * Constructor
        *@param fileName - file name
        *@param tableEntries- table entry count to reserve
        */
        PSS_EncryptedInfoFile(const CString& fileName, std::size_t tableEntries = 40);

        virtual ~PSS_EncryptedInfoFile();

        /**
        * Creates an empty encrypted file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateEmpty();

        /**
        * Creates an empty encrypted file
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        BOOL CreateEmptyFile(const CString& fileName);

        /**
        * Gets a string value from index
        *@param index - index
        *@return the value, empty string if not found or on error
        *@note If an error occurred, the value returned by the GetErrorStatus() will be TRUE
        */
        CString GetString(std::size_t index);

        /**
        * Sets a string value at index
        *@param value - value
        *@param index - index
        *@return TRUE on success, otherwise FALSE
        */
        BOOL SetString(const CString& value, std::size_t index);

        /**
        * Gets a time value from index
        *@param index - index
        *@return the value, empty time if not found or on error
        *@note If an error occurred, the value returned by the GetErrorStatus() will be TRUE
        */
        CTime GetTime(std::size_t index);

        /**
        * Sets a time value at index
        *@param value - value
        *@param index - index
        *@return TRUE on success, otherwise FALSE
        */
        BOOL SetTime(const CTime& value, std::size_t index);

        /**
        * Gets a date value from index
        *@param index - index
        *@return the value, empty date if not found or on error
        *@note If an error occurred, the value returned by the GetErrorStatus() will be TRUE
        */
        ZBDate GetDate(std::size_t index);

        /**
        * Sets a date value at index
        *@param value - value
        *@param index - index
        *@return TRUE on success, otherwise FALSE
        */
        BOOL SetDate(const ZBDate& value, std::size_t index);

        /**
        * Gets an integer value from index
        *@param index - index
        *@return the value, 0 if not found or on error
        *@note If an error occurred, the value returned by the GetErrorStatus() will be TRUE
        */
        int GetInt(std::size_t index);

        /**
        * Sets an integer value at index
        *@param value - value
        *@param index - index
        *@return TRUE on success, otherwise FALSE
        */
        BOOL SetInt(int value, std::size_t index);

        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline const CString GetFileName() const;

        /**
        * Sets the file name
        *@param value - the file name
        */
        virtual inline void SetFileName(const CString& value);

    protected:
        CArray<PSS_EncryptedLine, PSS_EncryptedLine> m_EntityTable;
        std::fstream                                 m_FileStream;
        CString                                      m_FileName;
        std::size_t                                  m_TableEntries;
        BOOL                                         m_Error;

        /**
        * Sets a valid file date 
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetValidFileDate();

        /**
        * Checks if the file date is valid
        *@return TRUE if the file date is valid, otherwise FALSE
        */
        virtual BOOL IsFileDateValid();

        /**
        * Gets the error status
        *@return the error status
        */
        virtual inline const BOOL GetErrorStatus() const;

        /**
        * Sets the error status
        *@param value - if TRUE, an error happened
        */
        virtual inline void SetErrorStatus(const BOOL value);

        /**
        * Clears the error status
        */
        virtual inline void ClearErrorStatus();

        /**
        * Checks if the security entity table exists
        *@return TRUE if the security entity table exists, otherwise FALSE
        */
        virtual inline BOOL EntityTableExist() const;

        /**
        * Allocates memory for the security entity table
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL AllocateEntityTable();

        /**
        * Reads the security entity table from the file
        */
        virtual void ReadEntityTable();

        /**
        * Writes the security entity table to the file
        */
        virtual void WriteEntityTable();
};

//---------------------------------------------------------------------------
// PSS_EncryptedInfoFile
//---------------------------------------------------------------------------
const CString PSS_EncryptedInfoFile::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_EncryptedInfoFile::SetFileName(const CString& value)
{
    m_FileName = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_EncryptedInfoFile::GetErrorStatus() const
{
    return m_Error;
}
//---------------------------------------------------------------------------
void PSS_EncryptedInfoFile::SetErrorStatus(const BOOL value)
{
    m_Error = value;
}
//---------------------------------------------------------------------------
void PSS_EncryptedInfoFile::ClearErrorStatus()
{
    m_Error = FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_EncryptedInfoFile::EntityTableExist() const
{
    return m_EntityTable.GetSize();
}
//---------------------------------------------------------------------------

#endif
