/****************************************************************************
 * ==> PSS_TextFile --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic text file                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TextFileH
#define PSS_TextFileH

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
* Generic text file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TextFile
{
    public:
        /**
        * Constructor
        *@param fileName - file name
        */
        PSS_TextFile(const CString& fileName = _T(""));

        virtual ~PSS_TextFile();

        /**
        * Reading information operators
        *@param[out] value - read value
        *@return itself, to allow operator to be chained with other items, e.g a >> b >> c
        */
        PSS_TextFile& operator >> (CString& value);

        /**
        * Writing information operators
        *@param pValue - value to write
        *@return itself, to allow operator to be chained with other items, e.g a << b << c
        */
        PSS_TextFile& operator << (const char* pValue);

        /**
        * Writing information operators
        *@param value - value to write
        *@return itself, to allow operator to be chained with other items, e.g a << b << c
        */
        PSS_TextFile& operator << (float  value);
        PSS_TextFile& operator << (double value);
        PSS_TextFile& operator << (DWORD  value);
        PSS_TextFile& operator << (UINT   value);
        PSS_TextFile& operator << (WORD   value);
        PSS_TextFile& operator << (short  value);
        PSS_TextFile& operator << (LONG   value);

        /**
        * Opens the text file in read mode
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OpenRead(const CString& fileName);

        /**
        * Opens the text file in write mode
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OpenWrite(const CString& fileName);

        /**
        * Opens the file in read mode
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OpenFileRead();

        /**
        * Opens the file in write mode with creation
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OpenFileWrite();

        /**
        * Reads a line from an opened file
        *@param[out] line - read line
        *@param removeNewLineChar - if true, the new line chars will be removed
        *@return 1 on success, 0 if the file has been completely processed, -1 on error
        */
        virtual int ReadLine(CString& line, bool removeNewLineChar = false);

        /**
        * Writes a line to an opened file
        *@param line - read line
        *@param addNewLineChar - if true, the new line chars will be added
        *@return 1 on success, 0 if the file has been completely processed, -1 on error
        */
        virtual BOOL WriteLine(const CString& Line, bool addNewLineChar = false);

        /**
        * Closes the file
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CloseFile();

    private:
        CString m_FileName;
        CFile   m_File;
        char*   m_pCurrent;
        char*   m_pNext;
        char    m_FileBuffer[300];

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_TextFile(const PSS_TextFile& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_TextFile& operator = (const PSS_TextFile& other);

        /**
        * Read a char buffer from the file
        *@return 1 on success, 0 if file was processed entirely, -1 on error
        */
        int ReadFileBuffer();
};

#endif
