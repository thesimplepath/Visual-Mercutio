/****************************************************************************
 * ==> PSS_Security --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the security basic features                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SecurityH
#define PSS_SecurityH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// std
#include <fstream>

// Windows
#ifdef _WIN32
    #include <winver.h>
#else
    #include <ver.h>
#endif
#include <SHELLAPI.H>
#include <direct.h>
#include <dos.h>

#ifdef _ZSCTYEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Security entity
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SecurityEntity
{
    public:
        PSS_SecurityEntity();

        /**
        * Constructor
        *@param entity - the entity content
        */
        PSS_SecurityEntity(const CString& entity);

        virtual ~PSS_SecurityEntity();

        /**
        * Generates a random key
        *@return randomly generated key
        */
        virtual CString GenerateRandomEntity();

        /**
        * Decrypts the counter and return it
        *@return decrypted counter
        */
        virtual int GetCounter();

        /**
        * Generates a counter
        *@return generated counter
        */
        virtual CString GenerateCounter(int counter);

        /**
        * Decrypts the date and return it
        *@return decrypted date
        */
        virtual CTime GetDate();

        /**
        * Generates a date
        *@return generated date
        */
        virtual CString GenerateDate(const CTime& date);

        /**
        * Gets the entity version
        *@return the entity version
        */
        virtual int GetVersion();

        /**
        * Generates the entity version
        *@param version - the entity version to generate
        *@return the generated entity version
        */
        virtual CString GenerateVersion(int version);

        /**
        * Encrypts the entity
        *@note This function may also be used to decrypt an encrypted entity
        */
        virtual void EncryptEntity();

        /**
        * Gets the entity content
        *@return the entity content
        */
        virtual inline const CString GetEntity() const;

        /**
        * Sets the entity content
        *@param entity - the entity content
        */
        virtual inline void SetEntity(const CString& entity);

    private:
        CString m_Entity;
};

//---------------------------------------------------------------------------
// PSS_SecurityEntity
//---------------------------------------------------------------------------
inline const CString PSS_SecurityEntity::GetEntity() const
{
    return m_Entity;
}
//---------------------------------------------------------------------------
inline void PSS_SecurityEntity::SetEntity(const CString& entity)
{
    m_Entity = entity;
}
//---------------------------------------------------------------------------

/**
* Security, provide methods for security checking
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Security
{
    public:
        PSS_Security();

        /**
        * Constructor
        *@param fileName - security file name
        *@param appRegistryKey - application registry key
        *@param appPID - application identifier
        */
        PSS_Security(const CString& fileName, const CString& appRegistryKey = "", const CString& appPID = "");

        virtual ~PSS_Security();

        /**
        * Gets the current security version
        *@return current security version
        */
        virtual int GetCurrentVersion() const;

        /**
        * Sets the last use date
        *@param date - last use date
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetLastUseDate(const CTime& date);

        /**
        * Sets the last use counter
        *@param counter - last use counter
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetLastUseCounter(int counter);

        /**
        * Gets the difference between the initial counter and the last counter
        *@return the difference between the initial counter and the last counter
        */
        virtual int GetCounterSpan();

        /**
        * Gets the time span since installation
        *@return the time span since installation
        */
        virtual CTimeSpan GetTimeSpan();

        /**
        * Increments the use counter
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL IncrementCounter();

        /**
        * Gets the license file version
        *@return the license file version
        */
        virtual int GetVersion();

        /**
        * Changes the version number
        *@param version - new version number
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetVersion(int version);

        /**
        * Gets the security file name
        *@return the security file name
        */
        virtual inline const CString GetFileName() const;

        /**
        * Sets the security file name
        *@param fileName - the security file name
        */
        virtual inline void SetFileName(const CString& fileName);

        /**
        * Shows a warning box
        */
        virtual void ShowWarning();

        /**
        * Shows a stop window
        */
        virtual void ShowStopWnd();

    protected:
        CString m_FileName;
        CString m_Key;
        CString m_PID;

        /**
        * Creates the security file name with the creation date and counters
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create();

        /**
        * Gets if error happened
        *@return TRUE if error happened, otherwise FALSE
        */
        virtual inline const BOOL GetError() const;

        /**
        * Sets error happened
        *@param value - if TRUE, error happened
        */
        virtual inline void SetError(BOOL value);

    private:
        PSS_SecurityEntity m_SecurityEntityTable[20];
        CStdioFile         m_SecurityFile;
        BOOL               m_Error;

        /**
        * Writes the entity table to disk
        *@return TRUE on success, otherwise FALSE
        */
        BOOL WriteEntityTable();

        /**
        * Loads the security entities from the file to the table
        *@return TRUE on success, otherwise FALSE
        */
        BOOL LoadSecurityTable();

        /**
        * Gets the security file name
        *@return the security file name
        */
        CString GetSecurityFileName() const;
};

//---------------------------------------------------------------------------
// PSS_Security
//---------------------------------------------------------------------------
const CString PSS_Security::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_Security::SetFileName(const CString& fileName)
{
    m_FileName = fileName;
}
//---------------------------------------------------------------------------
const BOOL PSS_Security::GetError() const
{
    return m_Error;
}
//---------------------------------------------------------------------------
void PSS_Security::SetError(BOOL value)
{
    m_Error = value;
}
//---------------------------------------------------------------------------

#endif
