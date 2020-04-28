/****************************************************************************
 * ==> PSS_Encoding --------------------------------------------------------*
 ****************************************************************************
 * Description : String encoding and decoding functions helper              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_Encoding.h"

// std
#include <stdio.h>
#include <stdlib.h>

 //---------------------------------------------------------------------------
 // Global defines
 //---------------------------------------------------------------------------
#define M_Base64PutChar(value) {pBuffer[offset] = value; ++offset;}

#define M_MD5_HASH_LENGTH 16

// constants for MD5Transform routine
#define M_S11 7
#define M_S12 12
#define M_S13 17
#define M_S14 22
#define M_S21 5
#define M_S22 9
#define M_S23 14
#define M_S24 20
#define M_S31 4
#define M_S32 11
#define M_S33 16
#define M_S34 23
#define M_S41 6
#define M_S42 10
#define M_S43 15
#define M_S44 21

// F, G, H and I are basic MD5 functions
#define M_F(x, y, z) (((x) &  (y) ) | ((~x) & ( z)))
#define M_G(x, y, z) (((x) &  (z) ) | (( y) & (~z)))
#define M_H(x, y, z) ( (x) ^  (y)   ^  ( z))
#define M_I(x, y, z) ( (y) ^ ((x)   |  (~z)))

// ROTATE_LEFT rotates x left n bits
#define M_ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4. Rotation is separate from addition to prevent recomputation
#define M_FF(a, b, c, d, x, s, ac)\
{\
    (a) += M_F((b), (c), (d)) + (x) + unsigned(ac);\
    (a)  = M_ROTATE_LEFT((a), (s));\
    (a) += (b);\
}

#define M_GG(a, b, c, d, x, s, ac)\
{\
    (a) += M_G((b), (c), (d)) + (x) + unsigned(ac);\
    (a)  = M_ROTATE_LEFT((a), (s));\
    (a) += (b);\
}

#define M_HH(a, b, c, d, x, s, ac)\
{\
    (a) += M_H((b), (c), (d)) + (x) + unsigned(ac);\
    (a)  = M_ROTATE_LEFT((a), (s));\
    (a) += (b);\
}

#define M_II(a, b, c, d, x, s, ac)\
{\
    (a) += M_I((b), (c), (d)) + (x) + unsigned(ac);\
    (a)  = M_ROTATE_LEFT((a), (s));\
    (a) += (b); \
}
//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
unsigned char        g_Alphabet[64 + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static unsigned char g_Padding[64]      =
{
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
//---------------------------------------------------------------------------
// PSS_Encoding
//---------------------------------------------------------------------------
 std::string PSS_Encoding::Base64Decode(const char* pStr, std::size_t len)
{
    static char alphabet[256];
    static char decoder[256];

    unsigned    bits      = 0;
    std::size_t charCount = 0;
    std::size_t errors    = 0;
    std::size_t pos       = 0;
    std::size_t offset    = 0;
    char*       pBuffer   = NULL;

    try
    {
        // decoded string length is shorter than the encoded one, so its length may be used to allocate
        // the output memory buffer
        pBuffer = new char[len + 1];

        // fill alphabet
        for (int i = sizeof(g_Alphabet) - 1; i >= 0; --i)
        {
            alphabet[g_Alphabet[i]] = 1;
            decoder[g_Alphabet[i]] = i;
        }

        unsigned c = 0;

        while (1)
        {
            // stop decoding if the position is higher or equals to input string length
            if (pos >= len)
                break;

            c = pStr[pos];
            ++pos;

            // found encoded string end marks?
            if (c == '=')
                break;

            // out of bounds?
            if (c > 255 || !alphabet[c])
                continue;

            // decode the string, 3 bytes by 3 bytes. Input chunks are merged into an int, for which each byte
            // contains a decrypted char. When the 3 next input chunks were merged, they are written into the
            // output buffer, selecting the right byte by shifting the merged int, and by masking the other bytes
            bits += decoder[c];
            ++charCount;

            if (charCount == 4)
            {
                M_Base64PutChar((bits >> 16) & 0xff);
                M_Base64PutChar((bits >> 8) & 0xff);
                M_Base64PutChar(bits & 0xff);

                bits = 0;
                charCount = 0;
            }
            else
                bits <<= 6;
        }

        // check if remaining chunks to decode, decode them if yes
        if (c > len)
        {
            if (charCount)
                ++errors;
        }
        else
            switch (charCount)
            {
                case 1:
                    ++errors;
                    break;

                case 2:
                    M_Base64PutChar(bits >> 10);
                    break;

                case 3:
                    M_Base64PutChar((bits >> 16) & 0xff);
                    M_Base64PutChar((bits >> 8) & 0xff);
                    break;
            }

        if (errors)
            TRACE("Base 64 decoding error\n");

        // convert the decoded buffer to string
        pBuffer[offset] = 0;
        const std::string result = pBuffer;
        delete[] pBuffer;

        return result;
    }
    catch (...)
    {
        if (pBuffer)
            delete[] pBuffer;

        throw;
    }
}
//---------------------------------------------------------------------------
std::string PSS_Encoding::Base64Encode(const char* pStr, std::size_t len)
{
    unsigned    c         = 0;
    unsigned    bits      = 0;
    std::size_t charCount = 0;
    std::size_t cols      = 0;
    std::size_t pos       = 0;
    std::size_t offset    = 0;
    std::size_t bufSize   = 0;
    char*       pBuffer = NULL;

    try
    {
        // calculate the buffer length to assign
        while (1)
        {
            if (pos >= len)
                break;

            ++pos;
            ++charCount;

            if (charCount == 3)
            {
                bufSize += 4;
                cols    += 4;

                if (cols == 72)
                {
                    ++bufSize;
                    cols = 0;
                }

                charCount = 0;
            }
        }

        // consider the end marks
        bufSize += 6;

        // allocate memory for encoded string
        pBuffer = new char[bufSize + 1];

        charCount = 0;
        cols      = 0;
        pos       = 0;

        while (1)
        {
            if (pos >= len)
                break;

            c = pStr[pos];
            ++pos;

            if (c > 255)
                TRACE("Base 64 encoding encountered char > 255\n");

            // encode the string. Encoded chars are 6 bit long, so the encoded string will be bigger than the
            // source one, because one extra char will be inserted every 3 chars. The encoded string contain
            // 4 chars of 6 bit = 24 bit for each chunk, which represent 3 chars of 8 bit = 24 bit in the source
            // string
            bits += c;
            ++charCount;

            if (charCount == 3)
            {
                M_Base64PutChar(g_Alphabet[(bits >> 18) & 0x3f]);
                M_Base64PutChar(g_Alphabet[(bits >> 12) & 0x3f]);
                M_Base64PutChar(g_Alphabet[(bits >> 6)  & 0x3f]);
                M_Base64PutChar(g_Alphabet[ bits        & 0x3f]);

                cols += 4;

                if (cols == 72)
                {
                    M_Base64PutChar('\n');
                    cols = 0;
                }

                bits      = 0;
                charCount = 0;
            }
            else
                bits <<= 8;
        }

        // check if remaining chunk to encode, encode it if yes, and add end line marks
        if (charCount)
        {
            bits <<= 16 - (8 * charCount);

            M_Base64PutChar(g_Alphabet[(bits >> 18) & 0x3f]);
            M_Base64PutChar(g_Alphabet[(bits >> 12) & 0x3f]);

            if (charCount == 1)
            {
                M_Base64PutChar('=');
                M_Base64PutChar('=');
            }
            else
            {
                M_Base64PutChar(g_Alphabet[(bits >> 6) & 0x3f]);
                M_Base64PutChar('=');
            }

            if (cols)
                M_Base64PutChar('\n');
        }

        M_Base64PutChar('\0');

        // convert the encoded buffer to string
        const std::string result = pBuffer;
        delete[] pBuffer;

        return result;
    }
    catch (...)
    {
        if (pBuffer)
            delete[] pBuffer;

        throw;
    }
}
//---------------------------------------------------------------------------
std::string PSS_Encoding::MD5Encode(const std::string& data, std::size_t len)
{
    if (len < 1 || len > (2 * M_MD5_HASH_LENGTH))
    {
        TRACE0("MD5Encode - out of boundaries...\n");
        return data;
    }

    IMD5Context md;
    char        sum[M_MD5_HASH_LENGTH];

    // initialize the MD5 context
    MD5Init(&md);
    MD5Update((IMD5Context*)&md, (char*)data.c_str(), data.length());
    MD5Final(sum, &md);

    static const char hex[] = "0123456789abcdef";
    char              buffer[2 * M_MD5_HASH_LENGTH + 1];

    // hash the string
    for (int i = 0; i < M_MD5_HASH_LENGTH; ++i)
    {
        buffer[2 * i]     = hex[(sum[i] >> 4) & 0xf];
        buffer[2 * i + 1] = hex[ sum[i]       & 0xf];
    }

    // convert output buffer to string
    buffer[len] = 0;
    const std::string result = buffer;

    return result;
}
//---------------------------------------------------------------------------
void PSS_Encoding::MD5Init(IMD5Context* pContext)
{
    ASSERT(pContext);

    pContext->m_Count[0] = pContext->m_Count[1] = 0;

    // load magic initialization constants
    pContext->m_State[0] = 0x67452301;
    pContext->m_State[1] = 0xefcdab89;
    pContext->m_State[2] = 0x98badcfe;
    pContext->m_State[3] = 0x10325476;
}
//---------------------------------------------------------------------------
void PSS_Encoding::MD5Update(IMD5Context* pContext, char* pStr, std::size_t len)
{
    ASSERT(pContext);

    unsigned i, index, partLen;

    // compute number of bytes mod 64
    index = unsigned((pContext->m_Count[0] >> 3) & 0x3F);

    // update number of bits
    if ((pContext->m_Count[0] += (len << 3)) < (len << 3))
        ++pContext->m_Count[1];

    pContext->m_Count[1] += (len >> 29);

    partLen = 64 - index;

    // transform as many time as possible
    if (len >= partLen)
    {
        MD5MemCpy((char*)&pContext->m_Buffer[index], (char*)pStr, partLen);
        MD5Transform(pContext->m_State, pContext->m_Buffer);

        for (i = partLen; i + 63 < len; i += 64)
            MD5Transform(pContext->m_State, &pStr[i]);

        index = 0;
    }
    else
        i = 0;

    // buffer remaining input
    MD5MemCpy((char*)&pContext->m_Buffer[index], (char*)&pStr[i], len - i);
}
//---------------------------------------------------------------------------
void PSS_Encoding::MD5Final(char digest[16], IMD5Context* pContext)
{
    char     bits[8];
    unsigned index, padLen;

    // save number of bits 
    MD5Encode(bits, pContext->m_Count, 8);

    // pad out to 56 mod 64
    index  = unsigned((pContext->m_Count[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    MD5Update(pContext, (char*)g_Padding, padLen);

    // append length (before padding)
    MD5Update(pContext, bits, 8);

    // store state in digest 
    MD5Encode(digest, pContext->m_State, 16);

    // clear sensitive information
    MD5MemSet((char*)pContext, 0, sizeof(*pContext));
}
//---------------------------------------------------------------------------
void PSS_Encoding::MD5Transform(unsigned state[4], char block[64])
{
    unsigned a = state[0], b = state[1], c = state[2], d = state[3], x[16];

    MD5Decode(x, block, 64);

    // round 1
    M_FF(a, b, c, d, x[0],  M_S11, 0xd76aa478); // 1
    M_FF(d, a, b, c, x[1],  M_S12, 0xe8c7b756); // 2
    M_FF(c, d, a, b, x[2],  M_S13, 0x242070db); // 3
    M_FF(b, c, d, a, x[3],  M_S14, 0xc1bdceee); // 4
    M_FF(a, b, c, d, x[4],  M_S11, 0xf57c0faf); // 5
    M_FF(d, a, b, c, x[5],  M_S12, 0x4787c62a); // 6
    M_FF(c, d, a, b, x[6],  M_S13, 0xa8304613); // 7
    M_FF(b, c, d, a, x[7],  M_S14, 0xfd469501); // 8
    M_FF(a, b, c, d, x[8],  M_S11, 0x698098d8); // 9
    M_FF(d, a, b, c, x[9],  M_S12, 0x8b44f7af); // 10
    M_FF(c, d, a, b, x[10], M_S13, 0xffff5bb1); // 11
    M_FF(b, c, d, a, x[11], M_S14, 0x895cd7be); // 12
    M_FF(a, b, c, d, x[12], M_S11, 0x6b901122); // 13
    M_FF(d, a, b, c, x[13], M_S12, 0xfd987193); // 14
    M_FF(c, d, a, b, x[14], M_S13, 0xa679438e); // 15
    M_FF(b, c, d, a, x[15], M_S14, 0x49b40821); // 16

    // round 2
    M_GG(a, b, c, d, x[1],  M_S21, 0xf61e2562); // 17
    M_GG(d, a, b, c, x[6],  M_S22, 0xc040b340); // 18
    M_GG(c, d, a, b, x[11], M_S23, 0x265e5a51); // 19
    M_GG(b, c, d, a, x[0],  M_S24, 0xe9b6c7aa); // 20
    M_GG(a, b, c, d, x[5],  M_S21, 0xd62f105d); // 21
    M_GG(d, a, b, c, x[10], M_S22, 0x2441453);  // 22
    M_GG(c, d, a, b, x[15], M_S23, 0xd8a1e681); // 23
    M_GG(b, c, d, a, x[4],  M_S24, 0xe7d3fbc8); // 24
    M_GG(a, b, c, d, x[9],  M_S21, 0x21e1cde6); // 25
    M_GG(d, a, b, c, x[14], M_S22, 0xc33707d6); // 26
    M_GG(c, d, a, b, x[3],  M_S23, 0xf4d50d87); // 27
    M_GG(b, c, d, a, x[8],  M_S24, 0x455a14ed); // 28
    M_GG(a, b, c, d, x[13], M_S21, 0xa9e3e905); // 29
    M_GG(d, a, b, c, x[2],  M_S22, 0xfcefa3f8); // 30
    M_GG(c, d, a, b, x[7],  M_S23, 0x676f02d9); // 31
    M_GG(b, c, d, a, x[12], M_S24, 0x8d2a4c8a); // 32

    // round 3
    M_HH(a, b, c, d, x[5],  M_S31, 0xfffa3942); // 33
    M_HH(d, a, b, c, x[8],  M_S32, 0x8771f681); // 34
    M_HH(c, d, a, b, x[11], M_S33, 0x6d9d6122); // 35
    M_HH(b, c, d, a, x[14], M_S34, 0xfde5380c); // 36
    M_HH(a, b, c, d, x[1],  M_S31, 0xa4beea44); // 37
    M_HH(d, a, b, c, x[4],  M_S32, 0x4bdecfa9); // 38
    M_HH(c, d, a, b, x[7],  M_S33, 0xf6bb4b60); // 39
    M_HH(b, c, d, a, x[10], M_S34, 0xbebfbc70); // 40
    M_HH(a, b, c, d, x[13], M_S31, 0x289b7ec6); // 41
    M_HH(d, a, b, c, x[0],  M_S32, 0xeaa127fa); // 42
    M_HH(c, d, a, b, x[3],  M_S33, 0xd4ef3085); // 43
    M_HH(b, c, d, a, x[6],  M_S34, 0x4881d05);  // 44
    M_HH(a, b, c, d, x[9],  M_S31, 0xd9d4d039); // 45
    M_HH(d, a, b, c, x[12], M_S32, 0xe6db99e5); // 46
    M_HH(c, d, a, b, x[15], M_S33, 0x1fa27cf8); // 47
    M_HH(b, c, d, a, x[2],  M_S34, 0xc4ac5665); // 48

    // round 4
    M_II(a, b, c, d, x[0],  M_S41, 0xf4292244); // 49
    M_II(d, a, b, c, x[7],  M_S42, 0x432aff97); // 50
    M_II(c, d, a, b, x[14], M_S43, 0xab9423a7); // 51
    M_II(b, c, d, a, x[5],  M_S44, 0xfc93a039); // 52
    M_II(a, b, c, d, x[12], M_S41, 0x655b59c3); // 53
    M_II(d, a, b, c, x[3],  M_S42, 0x8f0ccc92); // 54
    M_II(c, d, a, b, x[10], M_S43, 0xffeff47d); // 55
    M_II(b, c, d, a, x[1],  M_S44, 0x85845dd1); // 56
    M_II(a, b, c, d, x[8],  M_S41, 0x6fa87e4f); // 57
    M_II(d, a, b, c, x[15], M_S42, 0xfe2ce6e0); // 58
    M_II(c, d, a, b, x[6],  M_S43, 0xa3014314); // 59
    M_II(b, c, d, a, x[13], M_S44, 0x4e0811a1); // 60
    M_II(a, b, c, d, x[4],  M_S41, 0xf7537e82); // 61
    M_II(d, a, b, c, x[11], M_S42, 0xbd3af235); // 62
    M_II(c, d, a, b, x[2],  M_S43, 0x2ad7d2bb); // 63
    M_II(b, c, d, a, x[9],  M_S44, 0xeb86d391); // 64

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;

    // clear sensitive information
    MD5MemSet((char*)x, 0, sizeof(x));
}
//---------------------------------------------------------------------------
void PSS_Encoding::MD5Encode(char* pOutput, unsigned* pInput, std::size_t len)
{
    ASSERT(pInput);
    ASSERT(pOutput);

    for (std::size_t i = 0, j = 0; j < len; ++i, j += 4)
    {
        pOutput[j]     = unsigned( pInput[i]        & 0xff);
        pOutput[j + 1] = unsigned((pInput[i] >> 8)  & 0xff);
        pOutput[j + 2] = unsigned((pInput[i] >> 16) & 0xff);
        pOutput[j + 3] = unsigned((pInput[i] >> 24) & 0xff);
    }
}
//---------------------------------------------------------------------------
void PSS_Encoding::MD5Decode(unsigned* pOutput, char* pInput, std::size_t len)
{
    ASSERT(pInput);
    ASSERT(pOutput);

    for (std::size_t i = 0, j = 0; j < len; ++i, j += 4)
    {
        pOutput[i] = (unsigned(pInput[j])            |
                     (unsigned(pInput[j + 1]) << 8)  |
                     (unsigned(pInput[j + 2]) << 16) |
                     (unsigned(pInput[j + 3]) << 24));
    }
}
//---------------------------------------------------------------------------
void PSS_Encoding::MD5MemCpy(char* pOutput, char* pInput, std::size_t len)
{
    ASSERT(pInput);
    ASSERT(pOutput);

    // todo -cImprovement -oJean: Replace "for loop" with standard memcpy if possible
    for (std::size_t i = 0; i < len; ++i)
        pOutput[i] = pInput[i];
}
//---------------------------------------------------------------------------
void PSS_Encoding::MD5MemSet(char* pOutput, int value, std::size_t len)
{
    ASSERT(pOutput);

    // todo -cImprovement -oJean: Replace "for loop" with standard memset if possible
    for (std::size_t i = 0; i < len; ++i)
        ((char*)pOutput)[i] = char(value);
}
//---------------------------------------------------------------------------
