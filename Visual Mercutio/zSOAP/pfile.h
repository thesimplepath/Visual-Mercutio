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

#include "zConversion\String16.h"
string convertTo( String16 inStr );
string base64encode( const unsigned char *pcBuffIn, long nLenIn );

#ifdef _ZSOAPEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS pfile
{
public:

    enum m_directoryMode
    {
        publicFolder,
        privateFolder
    };

    pfile()
    {
    }

    void operator = ( const pfile& ref )
    {
        folder    = ref.folder;
        fname    = ref.fname;
        doc        = ref.doc;
        len        = ref.len;
        crc        = ref.crc;
    }

    pfile( int publicis, int folderid, string fpath, string filename )
    {
        ispublic    = publicis;
        folder        = folderid;
        fname        = filename;

        FILE* fo = fopen( ( fpath + _T( "\\" ) + filename ).c_str(), "rb" );

        if ( fo == NULL )
            throw _T( "Wrong file name" );

        //get file length
        fseek( fo, 0, SEEK_END );

        len = ftell( fo );

        fseek( fo, 0, SEEK_SET );        

        //alloc memory
        char* doc = (char*)new char[len + 1];
        
        //read file
        int left    = len;
        int pos        = 0;

        while ( left > 0 )
        {
            int doread = 16384;

            if ( left<16364 )
                doread = left;

            int read = fread( (char*)doc + pos, doread, 1, fo );

            pos        += doread;
            left    -= doread;
        }

        doc[len] = 0;    //just in case

        //encode file
        this->doc = base64encode( (const unsigned char*)doc, len );        

        //FILE* q=fopen("c:\\qqq","wb");fwrite(this->doc.c_str(),this->doc.length(),1,q);fclose(q);printf("W=%d\n",len);

        //calc crc
        crc = 0;

        for ( unsigned int i = 0; i < len; i++ )
            crc += i * doc[i];

        //clean mem
        delete [] doc;

        fclose( fo );
    }

    bool save( string path )
    {
        string fl    = path + _T( "\\" ) + fname;
        FILE* fo    = fopen( fl.c_str(), "wb" );

        fwrite( doc.c_str(), len, 1, fo );
        fclose( fo );

        return true;
    }

    string            doc;
    unsigned int    crc;
    unsigned int    len;
    string            fname;
    int                folder;
    int                ispublic;
    
private:

    string pBase64Encoder( string doc )
    {
        string ret = _T( "" );
        return ret;
    }
};

#endif