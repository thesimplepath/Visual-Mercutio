/****************************************************************************
 * ==> PSS_Encoding --------------------------------------------------------*
 ****************************************************************************
 * Description : Helper for string encoding and decoding                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_EncodingH
#define PSS_EncodingH

 // change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// std
#include <string>

#ifdef _ZCONVERSIONEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Helper for string encoding and decoding
*@author Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Encoding
{
    public:
        /**
        * Base64 decodes a string
        *@param pStr - buffer containing the string to decode
        *@param len - string length in bytes
        *@return decoded string
        */
        static std::string Base64Decode(const char* pStr, std::size_t len);

        /**
        * Base64 encodes a string
        *@param pStr - buffer containing the string to encode
        *@param len - string length in bytes
        *@return base64 encoded string
        */
        static std::string Base64Encode(const char* pStr, std::size_t len);

        /**
        * MD5 encodes a string
        *@param data - string containing data to encode
        *@param len - length to encode in data, in bytes
        *@return encoded string
        */
        static std::string MD5Encode(const std::string& data, std::size_t len);

    private:
        /**
        * MD5 context
        */
        struct IMD5Context
        {
            unsigned m_State[4];   // state (ABCD)
            unsigned m_Count[2];   // number of bits, modulo 2^64 (lsb first)
            char     m_Buffer[64]; // input buffer
        };

        /**
        * MD5 initialization. Begins an MD5 operation, writing a new context
        *@param[in, out] pContext - MD5 context to initialize
        */
        static void MD5Init(IMD5Context* pContext);

        /**
        * MD5 block update operation. Continues an MD5 message-digest operation, processing another message block,
        * and updating the context
        *@param pContext - MD5 context
        *@param pStr - string to process
        *@param len - string length in bytes
        */
        static void MD5Update(IMD5Context* pContext, char* pStr, std::size_t len);

        /**
        * MD5 finalization. Ends an MD5 message-digest operation, writing the message digest and zeroizing the context
        *@param digest - MD5 digest
        *@param pContext - MD5 context
        */
        static void MD5Final(char digest[16], IMD5Context* pContext);

        /**
        * MD5 basic transformation. Transforms state based on block
        *@param state - state
        *@param block - block
        */
        static void MD5Transform(unsigned state[4], char block[64]);

        /**
        * Encodes input (UINT4) into output (unsigned char). Assumes len is a multiple of 4
        *@param pOutput - output
        *@param pInput - input
        *@param len - length in bytes
        */
        static void MD5Encode(char* pOutput, unsigned* pInput, std::size_t len);
            
        /**
        * Decodes input (unsigned char) into output (UINT4). Assumes len is a multiple of 4
        *@param pOutput - output
        *@param pInput - input
        *@param len - length in bytes
        */
        static void MD5Decode(unsigned* pOutput, char* pInput, std::size_t len);

        /**
        * Copies the memory between MD5 source and destination buffers
        *@param pOutput - destination buffer to copy to
        *@param pInput - source buffer to copy from
        *@param len - length to copy in bytes
        */
        static void MD5MemCpy(char* pOutput, char* pInput, std::size_t len);

        /**
        * Sets MD5 buffer content to an initial value
        *@param pOutput - MD5 buffer to fill with value
        *@param value - value to fill
        *@param len - MD5 buffer length in bytes
        */
        static void MD5MemSet(char* pOutput, int value, std::size_t len);
};

#endif
