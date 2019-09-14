/****************************************************************************
 * ==> PSS_EncryptedEvaluationAppInfoFile ----------------------------------*
 ****************************************************************************
 * Description : Provides an encrypted evaluation application info file     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EncryptedEvaluationAppInfoFileH
#define PSS_EncryptedEvaluationAppInfoFileH

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
#include "PSS_EncryptedInfoFile.H"

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
* Encrypted evaluation application info file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EncryptedEvaluationAppInfoFile : public PSS_EncryptedInfoFile
{
    public:
        /**
        * Constructor
        *@param fileName - file name
        */
        PSS_EncryptedEvaluationAppInfoFile(const CString& fileName = "");

        virtual ~PSS_EncryptedEvaluationAppInfoFile();

        /**
        * Initializes the class
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Initialize(const CString& fileName);

        /**
        * Creates an empty file
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateEmpty(const CString& fileName);

        /**
        * Initializes the file first use
        *@param dayCount - day count the application is allowed to be used, -1 for infinite
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitializeFirstUse(int dayCount = -1);

        /**
        * Checks the product key
        *@param productKey - product key
        *@return TRUE if the product key is valid, otherwise FALSE
        */
        virtual BOOL CheckProductKey(const CString& productKey);

        /**
        * Checks the expiration date
        *@return TRUE if expiration date is reached, otherwise FALSE
        */
        virtual BOOL CheckExpiration();

        /**
        * Reads the product key
        *@return the product key
        */
        virtual CString ReadProductKey();

        /**
        * Writes the product key
        *@param value - the product key
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL WriteProductKey(const CString& value);

        /**
        * Reads the installation date
        *@return the installation date
        */
        virtual ZBDate ReadInstallationDate();

        /**
        * Writes the installation date
        *@param value - the installation date
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL WriteInstallationDate(const ZBDate& value);

        /**
        * Reads the last date usage
        *@return the last date usage
        */
        virtual ZBDate ReadLastDateUsage();

        /**
        * Writes the last date usage
        *@param value - the last date usage
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL WriteLastDateUsage(const ZBDate& value);

        /**
        * Reads the valid date
        *@return the valid date
        */
        virtual ZBDate ReadValidDate();

        /**
        * Writes the valid date
        *@param value - the valid date
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL WriteValidDate(ZBDate value);

        /**
        * Reads the day count
        *@return the day count
        */
        virtual int ReadDayCount();

        /**
        * Writes the day count
        *@param value - the day count
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL WriteDayCount(int value);

    private:
        CString m_ProductKey;
        ZBDate  m_InstallationDate;
        ZBDate  m_LastDateUsage;
        ZBDate  m_ValidDate;
        int     m_DayCount;

        /**
        * Reads the file info
        *@return TRUE on success, otherwise FALSE
        */
        BOOL ReadFileInfo();

        /**
        * Writes the file info
        *@return TRUE on success, otherwise FALSE
        */
        BOOL WriteFileInfo();

        /**
        * Gets the product key
        *@return the product key
        */
        inline CString GetProductKey() const;

        /**
        * Sets the product key
        *@param value - the product key
        */
        inline void SetProductKey(const CString& value);

        /**
        * Gets the installation date
        *@return the installation date
        */
        inline ZBDate& GetInstallationDate();

        /**
        * Sets the installation date
        *@param value - the installation date
        */
        inline void SetInstallationDate(const ZBDate& value);

        /**
        * Gets the last date usage
        *@return the last date usage
        */
        inline ZBDate& GetLastDateUsage();

        /**
        * Sets the last date usage
        *@param value - the last date usage
        */
        inline void SetLastDateUsage(const ZBDate& value);

        /**
        * Gets the valid date
        *@return the valid date
        */
        inline ZBDate& GetValidDate();

        /**
        * Sets the valid date
        *@param value - the valid date
        */
        inline void SetValidDate(const ZBDate& value);

        /**
        * Gets the day count
        *@return the day count
        */
        inline int GetTotalDays() const;

        /**
        * Sets the day count
        *@param value - the day count
        */
        inline void SetTotalDays(int value);
};

//---------------------------------------------------------------------------
// PSS_EncryptedEvaluationAppInfoFile
//---------------------------------------------------------------------------
CString PSS_EncryptedEvaluationAppInfoFile::GetProductKey() const
{
    return m_ProductKey;
}
//---------------------------------------------------------------------------
void PSS_EncryptedEvaluationAppInfoFile::SetProductKey(const CString& value)
{
    m_ProductKey = value;
}
//---------------------------------------------------------------------------
ZBDate& PSS_EncryptedEvaluationAppInfoFile::GetInstallationDate()
{
    return m_InstallationDate;
}
//---------------------------------------------------------------------------
void PSS_EncryptedEvaluationAppInfoFile::SetInstallationDate(const ZBDate& value)
{
    m_InstallationDate = value;
}
//---------------------------------------------------------------------------
ZBDate& PSS_EncryptedEvaluationAppInfoFile::GetLastDateUsage()
{
    return m_LastDateUsage;
}
//---------------------------------------------------------------------------
void PSS_EncryptedEvaluationAppInfoFile::SetLastDateUsage(const ZBDate& value)
{
    m_LastDateUsage = value;
}
//---------------------------------------------------------------------------
ZBDate& PSS_EncryptedEvaluationAppInfoFile::GetValidDate()
{
    return m_ValidDate;
}
//---------------------------------------------------------------------------
void PSS_EncryptedEvaluationAppInfoFile::SetValidDate(const ZBDate& value)
{
    m_ValidDate = value;
}
//---------------------------------------------------------------------------
int PSS_EncryptedEvaluationAppInfoFile::GetTotalDays() const
{
    return m_DayCount;
}
//---------------------------------------------------------------------------
void PSS_EncryptedEvaluationAppInfoFile::SetTotalDays(int value)
{
    m_DayCount = value;
}
//---------------------------------------------------------------------------

#endif
