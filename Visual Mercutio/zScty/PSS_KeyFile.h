/****************************************************************************
 * ==> PSS_KeyFile ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file containing keys for licenses               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_KeyFileH
#define PSS_KeyFileH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

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
* Key file entity
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_KeyEntity
{
    public:
        PSS_KeyEntity();
        virtual ~PSS_KeyEntity();

        /**
        * Generates a random key
        *@return randomly generated key
        */
        virtual CString GenerateRandomEntity();

        /**
        * Checks if a key entity is equals to another
        *@param entity - entity to compare with
        *@return true if keys are equals, otherwise false
        */
        virtual bool IsEqual(const PSS_KeyEntity& entity) const;

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

        /**
        * Encrypts the entity
        *@note This function may also be used to decrypt an encrypted entity
        */
        virtual void EncryptEntity();

    private:
        CString m_Entity;
};

//---------------------------------------------------------------------------
// PSS_KeyEntity
//---------------------------------------------------------------------------
const CString PSS_KeyEntity::GetEntity() const
{
    return m_Entity;
}
//---------------------------------------------------------------------------
void PSS_KeyEntity::SetEntity(const CString& entity)
{
    m_Entity = entity;
}
//---------------------------------------------------------------------------

/**
* Key file, provides a file containing keys for licenses
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_KeyFile
{
    public:
        PSS_KeyFile();

        /**
        * Constructor
        *@param fileName - security file name
        */
        PSS_KeyFile(const CString& fileName);

        /**
        * Constructor
        *@param fileName - security file name
        *@param clearFileName - clear file name
        *@param count - count
        */
        PSS_KeyFile(const CString& fileName, const CString& clearFileName, int count);

        virtual ~PSS_KeyFile();

        /**
        * Creates the security file name with the creation date and counters
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GenerateFile();

        /**
        * Checks if the key is a valid key
        *@param key - key to check
        *@return TRUE if key is a valid key, otherwise FALSE
        */
        virtual BOOL IsKeyValid(const CString& key);

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
        * Gets the clear file name
        *@return the clear file name
        */
        virtual inline const CString GetClearFileName() const;

        /**
        * Sets the clear file name
        *@param fileName - the clear file name
        */
        virtual inline void SetClearFileName(const CString& fileName);

    private:
        CStdioFile    m_SecurityFile;
        PSS_KeyEntity m_KeyEntityTable[10000];
        CString       m_FileName;
        CString       m_ClearFileName;
        int           m_Count;

        /**
        * Writes the entity table to disk
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        BOOL WriteEntityTable(const CString& fileName);

        /**
        * Loads the security entities from the file to the table
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        BOOL LoadSecurityTable(const CString& fileName);
};

//---------------------------------------------------------------------------
// PSS_KeyFile
//---------------------------------------------------------------------------
const CString PSS_KeyFile::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
void PSS_KeyFile::SetFileName(const CString& fileName)
{
    m_FileName = fileName;
}
//---------------------------------------------------------------------------
const CString PSS_KeyFile::GetClearFileName() const
{
    return m_ClearFileName;
}
//---------------------------------------------------------------------------
void PSS_KeyFile::SetClearFileName(const CString& fileName)
{
    m_ClearFileName = fileName;
}
//---------------------------------------------------------------------------

#endif
