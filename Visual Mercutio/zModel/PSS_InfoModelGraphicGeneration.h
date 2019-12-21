/****************************************************************************
 * ==> PSS_InfoModelGraphicGeneration --------------------------------------*
 ****************************************************************************
 * Description : Provides a graphic model info generator                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InfoModelGraphicGenerationH
#define PSS_InfoModelGraphicGenerationH

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

// class name mapping
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declaration
class PSS_ProcessGraphModelMdl;
class PSS_ProcessGraphModelController;
class PSS_Server;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Graphic model info generator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_InfoModelGraphicGeneration
{
    public:
        /**
        * Constructor
        *@param pModel - the owning model
        *@param pCtlr - the model controller
        *@param urlName - the model url name
        *@param absolutePath - the model absolute path
        *@param includeConceptor - if true, the Conceptor info should be included
        *@param includeProcessReport - if true, the process report info should be included
        *@param includeRuleBook - if true, the rule book info should be included
        *@param imageFileName - the image file name
        *@param hyperLink - the model hyperlink
        *@param pDC - the device context to draw on
        *@param pServer - the server
        */
        PSS_InfoModelGraphicGeneration(PSS_ProcessGraphModelMdl*        pModel               = NULL,
                                       PSS_ProcessGraphModelController* pCtlr                = NULL,
                                       const CString&                   urlName              = _T(""),
                                       bool                             absolutePath         = true,
                                       bool                             includeConceptor     = true,
                                       bool                             includeProcessReport = true,
                                       bool                             includeRuleBook      = true,
                                       const CString&                   imageFileName        = _T(""),
                                       const CString&                   hyperLink            = _T(""),
                                       CDC*                             pDC                  = NULL,
                                       PSS_Server*                      pServer              = NULL);

        virtual ~PSS_InfoModelGraphicGeneration();

        /**
        * Gets the model
        *@return the model
        */
        virtual inline PSS_ProcessGraphModelMdl* GetModel() const;

        /**
        * Sets the model
        *@param pModel - the model
        */
        virtual inline void SetModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Gets the controller
        *@return the controller
        */
        virtual inline PSS_ProcessGraphModelController* GetCtlr() const;

        /**
        * Sets the controller
        *@param pCtrl - the model controller
        */
        virtual inline void SetCtlr(PSS_ProcessGraphModelController* pCtrl);

        /**
        * Gets the url name
        *@return the url name
        */
        virtual inline CString GetURLName() const;

        /**
        * Sets the url name
        *@param value - the url name
        */
        virtual inline void SetURLName(const CString& value);

        /**
        * Gets the absolute path
        *@return the absolute path
        */
        virtual inline bool GetAbsolutePath() const;

        /**
        * Sets the absolute path
        *@param value - the absolute path
        */
        virtual inline void SetAbsolutePath(bool value);

        /**
        * Gets if the Conceptor info should be included
        *@return true if the Conceptor info should be included, otherwise false
        */
        virtual inline bool GetIncludeConceptor() const;

        /**
        * Sets if the Conceptor info should be included
        *@param value - if true, the Conceptor info should be included
        */
        virtual inline void SetIncludeConceptor(bool value);

        /**
        * Gets if the process report info should be included
        *@return true if the process report info should be included, otherwise false
        */
        virtual inline bool GetIncludeProcessReport() const;

        /**
        * Sets if the process report info should be included
        *@param value - if true, the process report info should be included
        */
        virtual inline void SetIncludeProcessReport(bool value);

        /**
        * Gets if the rule book info should be included
        *@return true if the rule book info should be included, otherwise false
        */
        virtual inline bool GetIncludeRuleBook() const;

        /**
        * Sets if the rule book info should be included
        *@param value - if true, the rule book info should be included
        */
        virtual inline void SetIncludeRuleBook(bool value);

        /**
        * Gets the image file name
        *@return the image file name
        */
        virtual inline CString GetImageFileName() const;

        /**
        * Sets the image file name
        *@param value - the image file name
        */
        virtual inline void SetImageFileName(const CString& value);

        /**
        * Gets the hyperlink
        *@return the hyperlink
        */
        virtual inline CString GetHyperLink() const;

        /**
        * Sets the hyperlink
        *@param value - the hyperlink
        */
        virtual inline void SetHyperLink(const CString& value);

        /**
        * Gets the device context
        *@return the device context
        */
        virtual inline CDC* GetDC() const;

        /**
        * Sets the device context
        *@param pDC - the device context
        */
        virtual inline void SetDC(CDC* pDC);

        /**
        * Gets the server
        *@return the server
        */
        virtual inline PSS_Server* GetServer() const;

        /**
        * Sets the server
        *@param pServer - the server
        */
        virtual inline void SetServer(PSS_Server* pServer);

    private:
        PSS_ProcessGraphModelMdl*        m_pModel;
        PSS_ProcessGraphModelController* m_pCtlr;
        PSS_Server*                      m_pServer;
        CDC*                             m_pDC;
        CString                          m_URLName;
        CString                          m_ImageFileName;
        CString                          m_HyperLink;
        bool                             m_AbsolutePath;
        bool                             m_IncludeConceptor;
        bool                             m_IncludeProcessReport;
        bool                             m_IncludeRuleBook;
};

//---------------------------------------------------------------------------
// PSS_InfoModelGraphicGeneration
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_InfoModelGraphicGeneration::GetModel() const
{
    return m_pModel;
}
//---------------------------------------------------------------------------
void PSS_InfoModelGraphicGeneration::SetModel(PSS_ProcessGraphModelMdl* value)
{
    m_pModel = value;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelController* PSS_InfoModelGraphicGeneration::GetCtlr() const
{
    return m_pCtlr;
}
//---------------------------------------------------------------------------
void PSS_InfoModelGraphicGeneration::SetCtlr(PSS_ProcessGraphModelController* value)
{
    m_pCtlr = value;
}
//---------------------------------------------------------------------------
CString PSS_InfoModelGraphicGeneration::GetURLName() const
{
    return m_URLName;
}
//---------------------------------------------------------------------------
void PSS_InfoModelGraphicGeneration::SetURLName(const CString& value)
{
    m_URLName = value;
}
//---------------------------------------------------------------------------
bool PSS_InfoModelGraphicGeneration::GetAbsolutePath() const
{
    return m_AbsolutePath;
}
//---------------------------------------------------------------------------
void PSS_InfoModelGraphicGeneration::SetAbsolutePath(bool value)
{
    m_AbsolutePath = value;
}
//---------------------------------------------------------------------------
bool PSS_InfoModelGraphicGeneration::GetIncludeConceptor() const
{
    return m_IncludeConceptor;
}
//---------------------------------------------------------------------------
void PSS_InfoModelGraphicGeneration::SetIncludeConceptor(bool value)
{
    m_IncludeConceptor = value;
}
//---------------------------------------------------------------------------
bool PSS_InfoModelGraphicGeneration::GetIncludeProcessReport() const
{
    return m_IncludeProcessReport;
}
//---------------------------------------------------------------------------
void PSS_InfoModelGraphicGeneration::SetIncludeProcessReport(bool value)
{
    m_IncludeProcessReport = value;
}
//---------------------------------------------------------------------------
bool PSS_InfoModelGraphicGeneration::GetIncludeRuleBook() const
{
    return m_IncludeRuleBook;
}
//---------------------------------------------------------------------------
void PSS_InfoModelGraphicGeneration::SetIncludeRuleBook(bool value)
{
    m_IncludeRuleBook = value;
}
//---------------------------------------------------------------------------
CString PSS_InfoModelGraphicGeneration::GetImageFileName() const
{
    return m_ImageFileName;
}
//---------------------------------------------------------------------------
void PSS_InfoModelGraphicGeneration::SetImageFileName(const CString& value)
{
    m_ImageFileName = value;
}
//---------------------------------------------------------------------------
CString PSS_InfoModelGraphicGeneration::GetHyperLink() const
{
    return m_HyperLink;
}
//---------------------------------------------------------------------------
void PSS_InfoModelGraphicGeneration::SetHyperLink(const CString& value)
{
    m_HyperLink = value;
}
//---------------------------------------------------------------------------
CDC* PSS_InfoModelGraphicGeneration::GetDC() const
{
    return m_pDC;
}
//---------------------------------------------------------------------------
void PSS_InfoModelGraphicGeneration::SetDC(CDC* value)
{
    m_pDC = value;
}
//---------------------------------------------------------------------------
PSS_Server* PSS_InfoModelGraphicGeneration::GetServer() const
{
    return m_pServer;
}
//---------------------------------------------------------------------------
void PSS_InfoModelGraphicGeneration::SetServer(PSS_Server* value)
{
    m_pServer = value;
}
//---------------------------------------------------------------------------

#endif
