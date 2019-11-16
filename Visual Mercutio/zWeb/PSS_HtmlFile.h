/****************************************************************************
 * ==> PSS_HtmlFile --------------------------------------------------------*
 ****************************************************************************
 * Description : Html file                                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HtmlFileH
#define PSS_HtmlFileH

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

#ifdef _ZWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Html file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_HtmlFile
{
    public:
        /**
        * Constructor
        *@param fileName - html file name
        */
        PSS_HtmlFile(const CString& fileName = _T(""));

        virtual ~PSS_HtmlFile();

        /**
        * Stream operators for chars
        *@param pValue - value to add
        *@return this
        */
        PSS_HtmlFile& operator << (const char* pValue);

        /**
        * Stream operators for numeric values
        *@param value - value to add
        *@return this
        */
        PSS_HtmlFile& operator << (float  value);
        PSS_HtmlFile& operator << (double value);
        PSS_HtmlFile& operator << (DWORD  value);
        PSS_HtmlFile& operator << (UINT   value);
        PSS_HtmlFile& operator << (WORD   value);
        PSS_HtmlFile& operator << (short  value);
        PSS_HtmlFile& operator << (LONG   value);

        /**
        * Creates the html file
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(const CString& fileName);

        /**
        * Reads one line of the file buffer
        *@param[out] line - read line
        *@param removeNewLineChar - if true, carriage returns will be removed from line
        *@return remaining chars, 0 if file was completety processed, -1 on error
        */
        int ReadLine(CString& line, bool removeNewLineChar = false);

        /**
        * Writes one line in the file buffer
        *@param line - line to write
        *@param addNewLineChar - if true, carriage returns will be added to line end
        *@return TRUE on success, otherwise FALSE
        */
        BOOL WriteLine(const CString& line, bool addNewLineChar = false);

        /**
        * Opens the file for write, creates it if still no exists
        *@return TRUE on success, otherwise FALSE
        */
        BOOL OpenFileCreate();

        /**
        * Opens the file for read
        *@return TRUE on success, otherwise FALSE
        */
        BOOL OpenFileRead();

        /**
        * Closes the file
        *@return TRUE on success, otherwise FALSE
        */
        BOOL CloseFile();

    private:
        CString m_FileName;
        CFile   m_File;
        char*   m_pCurrent;
        char*   m_pNext;
        char    m_FileBuffer[300];

        /**
        * Copy constructor
        *@param other - other file to copy from
        */
        PSS_HtmlFile(const PSS_HtmlFile& other);

        /**
        * Copy operator
        *@param other - other file to copy from
        */
        const PSS_HtmlFile& operator = (const PSS_HtmlFile& other);

        // Read a char buffer from the file.
        // Once the return value is zero, the file has been
        // completely processed.
        // If the return code is -1, an error occured.
        int ReadFileBuffer();
};

#endif
