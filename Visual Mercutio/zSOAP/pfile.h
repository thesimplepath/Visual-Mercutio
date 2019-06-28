/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module XXXClass.h | Interface of the <c XXXClass> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Gaya
// <nl>Created:         03/2002
// <nl>Description:  XXXClass frame window support
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __PFILE_HDR_
#define __PFILE_HDR_

//change the definition of AFX_EXT... to make it import
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
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// todo FIXME -cCheck -oJean: changed the class member names (updated with m_), see what is the impact on Messenger
class AFX_EXT_CLASS pfile
{
    public:
        enum IEDirectoryMode
        {
            publicFolder,
            privateFolder
        };

        std::string m_Doc;
        unsigned    m_Crc;
        unsigned    m_Len;
        std::string m_FileName;
        int         m_Folder;
        int         m_IsPublic;

        pfile()
        {}

        pfile(int isPublic, int folderID, const std::string& fPath, const std::string& fileName) :
            m_FileName(fileName),
            m_Folder(folderID),
            m_IsPublic(isPublic)
        {
            std::FILE* pFile = std::fopen((fPath + _T("\\") + fileName).c_str(), "rb");

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

        void operator = (const pfile& ref)
        {
            m_Folder   = ref.m_Folder;
            m_FileName = ref.m_FileName;
            m_Doc      = ref.m_Doc;
            m_Len      = ref.m_Len;
            m_Crc      = ref.m_Crc;
        }

        bool save(const std::string& path)
        {
            std::string fileName = path + _T("\\") + m_FileName;
            std::FILE*  pFile    = std::fopen(fileName.c_str(), "wb");

            if (!pFile)
                return false;

            std::fwrite(m_Doc.c_str(), m_Len, 1, pFile);
            std::fclose(pFile);

            return true;
        }

    private:
        std::string pBase64Encoder(const std::string& doc)
        {
            return _T("");
        }
};

#endif