/****************************************************************************
 * ==> PSS_TextZoneBP ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a text zone for banking process                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TextZoneBPH
#define PSS_TextZoneBPH

 // old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_TextZoneBP
    #define PSS_TextZoneBP ZBBPTextZone
#endif

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

// processsoft
#include "zModel\PSS_TextZone.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Text zone for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TextZoneBP : public PSS_TextZone
{
    DECLARE_SERIAL(PSS_TextZoneBP)

    public:
        PSS_TextZoneBP();
        virtual ~PSS_TextZoneBP();

        /**
        * Creates a text zone
        *@param ptLog - the log point
        *@param pDC - the device context
        */
        virtual void Create(const CPoint& ptLog, CClientDC* pDC);

        /**
        * Initializes the style
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitializeStyle();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);
};

#endif
