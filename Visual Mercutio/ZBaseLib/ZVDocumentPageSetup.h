/****************************************************************************
 * ==> PSS_DocumentPageSetup -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a printer document page setup                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DocumentPageSetupH
#define PSS_DocumentPageSetupH

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
#include "Define.h"
#include "ZVDocumentPageSetupDlg.h"

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
* Printer document page setup
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_DocumentPageSetup
{
    public:
        PSS_DocumentPageSetup();
        virtual ~PSS_DocumentPageSetup();

        /**
        * Gets the background file name
        *@return the background file name
        */
        virtual CString GetBackgroundFileName() const;

        /**
        * Gets the default page size
        *@param margins - margins
        *@return the default page size
        */
        virtual CSize GetDefaultPageSize(const CRect& margins) const;

        /**
        * Gets the paper size
        *@return the paper size
        */
        virtual CSize GetPaperSize() const;

        /**
        * Sets the paper size
        *@param paperSize - the paper size
        */
        virtual void SetPaperSize(const CSize& paperSize);

        /**
        * Gets the standard size
        *@return the standard size
        */
        virtual short GetStandardSize();

        /**
        * Sets the standard size
        *@param standardSize - the standard size
        */
        virtual void SetStandardSize(short standardSize);

        /**
        * Gets the orientation
        *@return the orientation
        */
        virtual short GetOrientation();

        /**
        * Sets the orientation
        *@param orientation - the orientation
        */
        virtual void SetOrientation(short orientation);

        /**
        * Called when the user defines the page format
        */
        virtual void OnUserDefinePageFormat();

        /**
        * Called when the printer settings are updated
        */
        virtual void OnUpdatePrinterSettings();

        /**
        * Checks if standard size is supported
        *@param standardSize - standard size
        *@return TRUE if standard size is supported, otherwise FALSE
        */
        virtual BOOL IsSupported(short StandardSize);

        /**
        * Checks if the format is defined
        *@return TRUE if the format is defined, otherwise FALSE
        */
        virtual BOOL IsFormatDefined();

        /**
        * Checks if canceled
        *@return TRUE if canceled, otherwise FALSE
        */
        virtual BOOL IsCancelled();

        /**
        * Checks if can print
        *@return TRUE if can print, otherwise FALSE
        */
        virtual BOOL CanPrint();

    private:
        ZVDocumentPageSetupDlg m_PageSetupDlg;
        CSize                  m_PaperSize;
        CString                m_BkGndName;
        short                  m_StandardSize;
        short                  m_Orientation;
        BOOL                   m_IsFormatDefined;
        BOOL                   m_IsCancelled;
        BOOL                   m_CanPrint;
        BOOL                   m_IsChecked;

        /**
        * Gets the printer page size
        *@param[out] paperSize - paper size
        *@param[out] standardSize - standard size
        *@param[out] orientation - orientation
        *@return TRUE on success, otherwise FALSE
        */
        BOOL GetPrinterSettings(CSize& paperSize, short& standardSize, short& orientation);

        /**
        * Changes the printer page size
        *@param standardSize - standard size
        *@param orientation - orientation
        *@return TRUE on success, otherwise FALSE
        */
        void ChangePrinterSettings(short standardSize, short orientation);
};

#endif
