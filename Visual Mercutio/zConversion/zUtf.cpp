/////////////////////////////////////////////////////////////////////////////
//@doc zUtf
//@module zUtf.cpp | Implementation of the <c zUtf> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Gaya
// <nl>Created: 03/2002
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "zUtf.h"

// JMR-MODIF - Le 10 janvier 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/* Conversion UTF8/UTF16 - Unicode 3 standard compliant *********************/
char bytesFromUTF8[256] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

typedef unsigned short    UTF16;
typedef unsigned char    UTF8;
typedef unsigned long    UCS4;
typedef unsigned short    UCS2;

UCS4 offsetsFromUTF8[6] =
{
    0x00000000UL,
    0x00003080UL,
    0x000E2080UL,
    0x03C82080UL,
    0xFA082080UL,
    0x82082080UL
};

UTF8 firstByteMark[7] =
{
    0x00,
    0x00,
    0xC0,
    0xE0,
    0xF0,
    0xF8,
    0xFC
};

const UCS4    kReplacementCharacter    = 0x0000FFFDUL;
const UCS4    kMaximumUCS2            = 0x0000FFFFUL;
const UCS4    kMaximumUTF16            = 0x0010FFFFUL;
const UCS4    kMaximumUCS4            = 0x7FFFFFFFUL;

const int    halfShift                = 10;
const UCS4    halfBase                = 0x0010000UL;
const UCS4    halfMask                = 0x3FFUL;
const UCS4    kSurrogateHighStart        = 0xD800UL;
const UCS4    kSurrogateHighEnd        = 0xDBFFUL;
const UCS4    kSurrogateLowStart        = 0xDC00UL;
const UCS4    kSurrogateLowEnd        = 0xDFFFUL;

typedef enum
{
    ok,                 /* conversion successful */
    sourceExhausted,    /* partial character in source, but hit end */
    targetExhausted        /* insuff. room in target for conversion */
} ConversionResult;

ConversionResult ConvertUTF16toUTF8 ( UTF16** sourceStart,
                                      const UTF16* sourceEnd,
                                      UTF8** targetStart,
                                      const UTF8* targetEnd )
{
    ConversionResult    result = ok;
    register UTF16*        source = *sourceStart;
    register UTF8*        target = *targetStart;

    while ( source < sourceEnd )
    {
        register UCS4            ch;
        register unsigned short    bytesToWrite    = 0;
        register const UCS4        byteMask        = 0xBF;
        register const UCS4        byteMark        = 0x80; 

        ch = *source++;

        if ( ch >= kSurrogateHighStart && ch <= kSurrogateHighEnd && source < sourceEnd )
        {
            register UCS4 ch2 = *source;

            if ( ch2 >= kSurrogateLowStart && ch2 <= kSurrogateLowEnd )
            {
                ch = ( ( ch - kSurrogateHighStart ) << halfShift ) + ( ch2 - kSurrogateLowStart ) + halfBase;
                ++source;
            }
        }

        if ( ch < 0x80 )
        {
            bytesToWrite = 1;
        }
        else if ( ch < 0x800 )
        {
            bytesToWrite = 2;
        }
        else if ( ch < 0x10000 )
        {
            bytesToWrite = 3;
        }
        else if ( ch < 0x200000 )
        {
            bytesToWrite = 4;
        }
        else if ( ch < 0x4000000 )
        {
            bytesToWrite = 5;
        }
        else if ( ch <= kMaximumUCS4 )
        {
            bytesToWrite = 6;
        }
        else
        {
            bytesToWrite = 2;
            ch = kReplacementCharacter;
        }

        // I wish there were a smart way to avoid this conditional
        target += bytesToWrite;

        if ( target > targetEnd )
        {
            target -= bytesToWrite;
            result = targetExhausted;
            break;
        }

        switch ( bytesToWrite )
        {
            // note: code falls through cases!
            case 6:
            {
                *--target = (UTF8)( ( ch | byteMark ) & byteMask );
                ch >>= 6;
            }

            case 5:
            {
                *--target = (UTF8)( ( ch | byteMark ) & byteMask );
                ch >>= 6;
            }

            case 4:
            {
                *--target = (UTF8)( ( ch | byteMark ) & byteMask );
                ch >>= 6;
            }

            case 3:
            {
                *--target = (UTF8)( ( ch | byteMark ) & byteMask );
                ch >>= 6;
            }

            case 2:
            {
                *--target = (UTF8)( ( ch | byteMark ) & byteMask );
                ch >>= 6;
            }

            case 1:
            {
                *--target =  (UTF8)ch | firstByteMark[bytesToWrite];
            }
        }

        target += bytesToWrite;
    }

    *sourceStart = source;
    *targetStart = target;

    return result;
}

/* ================================================================ */

ConversionResult ConvertUTF8toUTF16 ( UTF8** sourceStart,
                                      UTF8* sourceEnd,
                                      UTF16** targetStart,
                                      const UTF16* targetEnd )
{
    ConversionResult    result    = ok;
    register UTF8*        source    = *sourceStart;
    register UTF16*        target    = *targetStart;

    while ( source < sourceEnd )
    {
        register UCS4            ch                    = 0;
        register unsigned short    extraBytesToWrite    = bytesFromUTF8[*source];

        if ( source + extraBytesToWrite > sourceEnd )
        {
            result = sourceExhausted;
            break;
        }

        switch( extraBytesToWrite )
        {    /* note: code falls through cases! */
            case 5:
            {
                ch += *source++;
                ch <<= 6;
            }

            case 4:
            {
                ch += *source++;
                ch <<= 6;
            }

            case 3:
            {
                ch += *source++;
                ch <<= 6;
            }

            case 2:
            {
                ch += *source++;
                ch <<= 6;
            }

            case 1:
            {
                ch += *source++;
                ch <<= 6;
            }

            case 0:
            {
                ch += *source++;
            }
        }

        ch -= offsetsFromUTF8[extraBytesToWrite];

        if ( target >= targetEnd )
        {
            result = targetExhausted; break;
        }

        if ( ch <= kMaximumUCS2 )
        {
            *target++ = (UTF16)ch;
        }
        else if ( ch > kMaximumUTF16 )
        {
            *target++ = kReplacementCharacter;
        }
        else
        {
            if ( target + 1 >= targetEnd )
            {
                result = targetExhausted;
                break;
            }

            ch            -= halfBase;
            *target++     = (UTF16)( ( ch >> halfShift ) + kSurrogateHighStart );
            *target++     = (UTF16)( ( ch & halfMask ) + kSurrogateLowStart );
        }
    }

    *sourceStart = source;
    *targetStart = target;

    return result;
}

std::string zUtf::UTF16toUTF8( const String16& src )
{
    int len            = wcslen( src ) + 1;
    char* trg        = new char[len * 2 + 2];
    char* output    = trg;

    if ( ConvertUTF16toUTF8 ( (UTF16**)&src,
                              (const UTF16*)( src + len ),
                              (UTF8**)&trg,
                              (const UTF8*)( trg + len * 2 ) ) != ok )
    {
        delete [] output;
        return _T( "" );
    }

    std::string ret = output;
    delete [] output;

    return ret;
}

String16 zUtf::UTF8toUTF16( const std::string& src )
{
    int            len        = src.length() + 1;
    wchar_t*    trg        = new wchar_t[len * 2 + 2];
    wchar_t*    output    = trg;
    const char*    srcptr    = src.c_str();

    if ( ConvertUTF8toUTF16( (UTF8**)&( srcptr ),
                             (UTF8*)( srcptr + len ),
                             (UTF16**) &( trg ),
                             (const UTF16*) ( trg + len * 2) ) != ok )
    {
        delete [] output;
        return _T( "" );
    }

    String16 ret( output );
    delete [] output;

    return ret;
}
