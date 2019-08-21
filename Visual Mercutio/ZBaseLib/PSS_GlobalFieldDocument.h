/****************************************************************************
 * ==> PSS_GlobalFieldDocument ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a global field document                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GlobalFieldDocumentH
#define PSS_GlobalFieldDocumentH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_GlobalFieldDocument
    //#define PSS_GlobalFieldDocument ZDGlobalFieldDocument
#endif

// processsoft
#include "PSS_GlobalFieldManager.h"
#include "HistFMng.h"
#include "Stamp.h"
#include "PSS_BaseDocument.h"

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
* Global field document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GlobalFieldDocument : public PSS_BaseDocument
{
    DECLARE_SERIAL(PSS_GlobalFieldDocument)

    public:
        typedef PSS_BaseDocument inherited;

        PSS_GlobalFieldDocument();
        virtual ~PSS_GlobalFieldDocument();

        /**
        * Initializes the class
        *@param fileName - file name
        *@param pGlobalFieldManager - global field manager
        *@param pHistoryValueManager - history value manager
        */
        virtual void Initialize(const CString&          fileName,
                                PSS_GlobalFieldManager* pGlobalFieldManager,
                                ZAHistoryFieldManager*  pHistoryValueManager);

        /**
        * Initializes the class
        *@param pGlobalFieldManager - global field manager
        *@param pHistoryValueManager - history value manager
        */
        virtual void Initialize(PSS_GlobalFieldManager* pGlobalFieldManager, ZAHistoryFieldManager* pHistoryValueManager);

        /**
        * Reads the document
        *@param fileName - file name
        *@param pGlobalFieldManager - global field manager
        *@param pHistoryValueManager - history value manager
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ReadDocument(const CString&          fileName,
                                  PSS_GlobalFieldManager* pGlobalFieldManager,
                                  ZAHistoryFieldManager*  pHistoryValueManager);

        /**
        * Reads the document
        *@param fileName - file name
        *@param pGlobalFieldManager - global field manager
        *@param pHistoryValueManager - history value manager
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ReadDocument(const CString& fileName);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        /// Additional Protected Declarations
        //{{AFX_MSG(ZDGlobalFieldDocument)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_GlobalFieldManager* m_pGlobalFieldManager;
        ZAHistoryFieldManager*  m_pHistoryValueManager;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_GlobalFieldDocument(const PSS_GlobalFieldDocument& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_GlobalFieldDocument& operator = (const PSS_GlobalFieldDocument& other);
};

#endif
