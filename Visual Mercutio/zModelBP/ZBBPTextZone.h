// **********************************************************************************************************
// *                                         Classe ZBBPTextZone                                            *
// **********************************************************************************************************
// * JMR-MODIF - Le 4 avril 2006 - Ajout de la classe ZBBPTextZone.                                            *
// **********************************************************************************************************
// * Cette classe permet la gestion et l'affichage d'une zone de texte personnalisée.                        *
// **********************************************************************************************************

#if !defined(AFX_ZBBPTextZone_H__F5100AAD_5FFF_4817_BE12_0A6B0BA8A8D4__INCLUDED_)
#define AFX_ZBBPTextZone_H__F5100AAD_5FFF_4817_BE12_0A6B0BA8A8D4__INCLUDED_

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

class AFX_EXT_CLASS ZBBPTextZone : public PSS_TextZone
{
    DECLARE_SERIAL(ZBBPTextZone)

    public:
        ZBBPTextZone();
        virtual ~ZBBPTextZone();

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
