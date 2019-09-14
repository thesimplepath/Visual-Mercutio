/****************************************************************************
 * ==> PSS_EncryptedLine  --------------------------------------------------*
 ****************************************************************************
 * Description : Provides an encrypted text line                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EncryptedLineH
#define PSS_EncryptedLineH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "ZBDate.h"

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
* Encrypted text line
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_EncryptedLine : public CObject
{
    DECLARE_DYNCREATE(PSS_EncryptedLine);

    public:
        PSS_EncryptedLine();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_EncryptedLine(const PSS_EncryptedLine& other);

        virtual ~PSS_EncryptedLine();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        virtual const PSS_EncryptedLine& operator = (const PSS_EncryptedLine& other);

        /**
        * Generates a random line
        *@return the generated random line
        */
        virtual CString GenerateRandomLine();

        /**
        * Generates a line from a string value
        *@param value - value
        *@return the generated line
        */
        virtual CString GenerateLine(const CString& value);

        /**
        * Generates a line from a date value
        *@param value - value
        *@return the generated line
        */
        virtual CString GenerateLine(const ZBDate& date);

        /**
        * Generates a line from a time value
        *@param value - value
        *@return the generated line
        */
        virtual CString GenerateLine(const CTime& time);

        /**
        * Generates a line from an integer value
        *@param value - value
        *@return the generated line
        */
        virtual CString GenerateLine(int value);

        /**
        * Decrypts the string value and gets it
        *@return the decrypted value
        */
        virtual CString GetString();

        /**
        * Decrypts the date value and gets it
        *@return the decrypted value
        */
        virtual ZBDate GetDate();

        /**
        * Decrypts the time value and gets it
        *@return the decrypted value
        */
        virtual CTime GetTime();

        /**
        * Decrypts the integer value and gets it
        *@return the decrypted value
        */
        virtual int GetInt();

        /**
        * Gets the entity
        *@return the entity
        */
        virtual inline const CString GetEntity() const;

        /**
        * Sets the entity
        *@param value - the entity
        */
        virtual inline void SetEntity(const CString& value);

    private:
        CString m_Entity;

        /**
        * Encrypts an entity
        *@param line - line containing the entity to encrypt
        */
        void EncryptEntity(const CString& line);

        /**
        * Generates a random line
        *@param size - line size
        *@return the generated random line
        */
        CString GenerateRandomLine(int size);
};

//---------------------------------------------------------------------------
// PSS_EncryptedLine 
//---------------------------------------------------------------------------
const CString PSS_EncryptedLine::GetEntity() const
{
    return m_Entity;
}
//---------------------------------------------------------------------------
inline void PSS_EncryptedLine::SetEntity(const CString& value)
{
    m_Entity = value;
}
//---------------------------------------------------------------------------

#endif
