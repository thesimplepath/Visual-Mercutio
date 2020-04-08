/****************************************************************************
 * ==> PSS_SoapData_File ---------------------------------------------------*
 ****************************************************************************
 * Description : SOAP data containing files                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SoapData_FilesH
#define PSS_SoapData_FilesH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zConversion\PSS_String16.h"
#include "zConversion\PSS_StringTools.h"
#include "zConversion\PSS_Encoding.h"

#ifdef _ZSOAPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* SOAP data containing files
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SoapData_File
{
    public:
        /**
        * Directory mode
        */
        enum IEDirectoryMode
        {
            IE_DM_PublicFolder,
            IE_DM_PrivateFolder
        };

        std::string m_Doc;
        unsigned    m_Crc;
        unsigned    m_Len;
        std::string m_FileName;
        int         m_Folder;
        int         m_IsPublic;

        /**
        * Constructor
        */
        PSS_SoapData_File() :
            m_Crc(0),
            m_Len(0),
            m_Folder(-1),
            m_IsPublic(-1)
        {}

        /**
        * Constructor
        *@param isPublic - if true, the file is public
        *@param folderID - folder identifier
        *@param fPath - file path
        *@param fileName - file name
        */
        PSS_SoapData_File(int isPublic, int folderID, const std::string& fPath, const std::string& fileName) :
            m_FileName(fileName),
            m_Folder(folderID),
            m_IsPublic(isPublic)
        {
            std::FILE* pFile;
            fopen_s(&pFile, (fPath + _T("\\") + fileName).c_str(), "rb");

            if (!pFile)
                throw _T("Wrong file name");

            // get file length
            std::fseek(pFile, 0, SEEK_END);
            m_Len = std::ftell(pFile);
            std::fseek(pFile, 0, SEEK_SET);

            // alloc memory
            char* pDoc = new char[m_Len + 1];
        
            // read file
            int left = m_Len;
            int pos  = 0;

            while (left > 0)
            {
                int doRead = 16384;

                if (left < 16364)
                    doRead = left;

                const int read = std::fread(pDoc + pos, doRead, 1, pFile);

                pos  += doRead;
                left -= doRead;
            }

            // just in case...
            pDoc[m_Len] = 0;

            // encode file
            m_Doc = PSS_Encoding::Base64Encode(pDoc, m_Len);

            // calculate crc
            m_Crc = 0;

            for (std::size_t i = 0; i < m_Len; ++i)
                m_Crc += i * pDoc[i];

            // clean memory
            delete[] pDoc;

            std::fclose(pFile);
        }

        /**
        * Copy operator
        *@param ref - reference data file to copy from
        */
        void operator = (const PSS_SoapData_File& ref)
        {
            m_Folder   = ref.m_Folder;
            m_FileName = ref.m_FileName;
            m_Doc      = ref.m_Doc;
            m_Len      = ref.m_Len;
            m_Crc      = ref.m_Crc;
        }

        /**
        * Save the file content
        *@param path - file path
        *@return true on success, otherwise false
        */
        bool Save(const std::string& path)
        {
            std::string fileName = path + _T("\\") + m_FileName;
            
            std::FILE* pFile;
            fopen_s(&pFile, fileName.c_str(), "wb");

            if (!pFile)
                return false;

            std::fwrite(m_Doc.c_str(), m_Len, 1, pFile);
            std::fclose(pFile);

            return true;
        }
};

#endif