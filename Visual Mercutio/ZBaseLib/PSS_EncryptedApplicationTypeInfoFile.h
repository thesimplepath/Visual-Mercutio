/****************************************************************************
 * ==> PSS_EncryptedApplicationTypeInfoFile --------------------------------*
 ****************************************************************************
 * Description : Provides an encrypted application type info file           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EncryptedApplicationTypeInfoFileH
#define PSS_EncryptedApplicationTypeInfoFileH

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
* Encrypted application type info file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EncryptedApplicationTypeInfoFile : public PSS_EncryptedInfoFile
{
    public:
        /**
        * Application type info
        */
        enum IEType
        {
            IE_IT_Unknown,
            IE_IT_HomeEdition,
            IE_IT_NetworkEdition,
            IE_ITEntrepriseEdition
        };

        /**
        * Constructor
        *@param fileName - file name
        */
        PSS_EncryptedApplicationTypeInfoFile(const CString& fileName = "");

        virtual ~PSS_EncryptedApplicationTypeInfoFile();

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
        virtual BOOL CreateEmpty(const CString& filename);

        /**
        * Checks the product key
        *@param productKey - product key
        *@return TRUE if the product key is valid, otherwise FALSE
        */
        virtual BOOL CheckProductKey(const CString& productKey);

        /**
        * Reads the application type
        *@return the application type
        */
        virtual IEType ReadApplicationType();

        /**
        * Writes the application type
        *@param value - the application type
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL WriteApplicationType(IEType value);

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

    private:
        IEType  m_ApplicationType;
        CString m_ProductKey;

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
        * Gets the application type
        *@return the application type
        */
        inline IEType GetApplicationType() const;

        /**
        * Sets the application type
        *@param value - the application type
        */
        inline void SetApplicationType(IEType value);

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
};

//---------------------------------------------------------------------------
// PSS_EncryptedApplicationTypeInfoFile
//---------------------------------------------------------------------------
PSS_EncryptedApplicationTypeInfoFile::IEType PSS_EncryptedApplicationTypeInfoFile::GetApplicationType() const
{
    return m_ApplicationType;
}
//---------------------------------------------------------------------------
void PSS_EncryptedApplicationTypeInfoFile::SetApplicationType(IEType value)
{
    m_ApplicationType = value;
}
//---------------------------------------------------------------------------
CString PSS_EncryptedApplicationTypeInfoFile::GetProductKey() const
{
    return m_ProductKey;
}
//---------------------------------------------------------------------------
void PSS_EncryptedApplicationTypeInfoFile::SetProductKey(const CString& value)
{
    m_ProductKey = value;
}
//---------------------------------------------------------------------------

#endif
