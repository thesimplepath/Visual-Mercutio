/****************************************************************************
 * ==> PSS_FileBuffer ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a file buffer                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FileBufferH
#define PSS_FileBufferH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_FileBuffer
    #define PSS_FileBuffer ZBFileBuffer
#endif

// mfc
#include "mfc.h"

// processsoft
#include "PSS_File.h"

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
* File buffer
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FileBuffer : public CObject
{
    DECLARE_SERIAL(PSS_FileBuffer)

    public:
        typedef CObject inherited;

        /**
        * Constructor
        *@param fileName - file name to open
        */
        PSS_FileBuffer(const CString& fileName = _T(""));

        /**
        * Constructor
        *@param file - file to open
        */
        PSS_FileBuffer(PSS_File& file);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FileBuffer(const PSS_FileBuffer& other);

        virtual ~PSS_FileBuffer();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FileBuffer& operator = (const PSS_FileBuffer& other);

        /**
        * Stores from the archive to the object stamp
        *@param ar - archive
        *@param fileBuffer - file buffer
        *@return archive, to allow operator to be chained with other items, e.g a >> b >> c
        */
        AFX_EXT_API friend CArchive& operator >> (CArchive& ar, PSS_FileBuffer& fileBuffer);

        /**
        * Stores the object stamp to the archive
        *@param ar - archive
        *@param file - file
        *@return archive, to allow operator to be chained with other items, e.g a << b << c
        */
        AFX_EXT_API friend CArchive& operator << (CArchive& ar, PSS_FileBuffer fileBuffer);

        /**
        * Creates the buffer from a file
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateBufferFromFile(const CString& fileName);

        /**
        * Creates the buffer from a file
        *@param file - file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateBufferFromFile(PSS_File& file);

        /**
        * Creates the buffer from a file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CreateBufferFromFile();

        /**
        * Creates a file based on the file buffer
        *@param fileName - file name
        *@return the newly created file name on success, otherwise an empty string
        */
        virtual CString CreateFileFromBuffer(const CString& fileName);

        /**
        * Creates a file based on the file buffer
        *@param file - file
        *@return the newly created file name on success, otherwise an empty string
        */
        virtual CString CreateFileFromBuffer(PSS_File& file);

        /**
        * Creates a file based on the file buffer
        *@return the newly created file name on success, otherwise an empty string
        */
        virtual CString CreateFileFromBuffer();

        /**
        * Creates a temporary file based on the file buffer
        *@return the temporary file name on success, otherwise an empty string
        */
        virtual CString CreateTemporaryFileFromBuffer();

        /**
        * Closes the buffer
        */
        virtual void Close();

        /**
        * Clones the buffer
        *@return cloned buffer, NULL on error
        */
        virtual PSS_FileBuffer* Clone();

        /**
        * Serializes file buffer
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Gets the file buffer
        *@return the file buffer
        */
        virtual inline void* GetFileBuffer();

        /**
        * Gets the buffer size
        *@return the buffer size
        */
        virtual inline const std::size_t& GetBufferSize() const;

    private:
        PSS_File    m_File;
        void*       m_pBuffer;
        std::size_t m_Size;
};

//---------------------------------------------------------------------------
// PSS_FileBuffer
//---------------------------------------------------------------------------
void* PSS_FileBuffer::GetFileBuffer()
{
    return m_pBuffer;
}
//---------------------------------------------------------------------------
const std::size_t& PSS_FileBuffer::GetBufferSize() const
{
    return m_Size;
}
//---------------------------------------------------------------------------

#endif
