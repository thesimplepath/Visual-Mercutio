/****************************************************************************
 * ==> PSS_ModelGenerateImageFiles -----------------------------------------*
 ****************************************************************************
 * Description : Navigates through the processes and generates the images   *
 *               files                                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ModelGenerateImageFilesH
#define PSS_ModelGenerateImageFilesH

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
#include "zBaseLib\PSS_Directory.h"
#include "zBaseLib\PSS_KeepStringUsage.h"
#include "zConversion\PSS_StringTools.h"
#include "zProperty\ZBPropertyAttributes.h"
#include "zModel\ZUModelNavigation.h"
#include "zModel\ZBInfoModelGraphicGeneration.h"
#include "zModelWeb\PSS_PublishModelGenerateDialog.h"

// forward class declaration
class PSS_BasicSymbol;
class ZIProperties;
class ZBInfoModelGraphicGeneration;
class ZBUserGroupEntity;
class ZBUserRoleEntity;
class ZBLogicalSystemEntity;
class ZBSystemEntity;
class ZBLogicalPrestationsEntity;
class ZBPrestationsEntity;
class ZBLogicalRulesEntity;
class ZBRulesEntity;
class ZBUserEntity;
class PSS_HtmlFile;

#ifdef _ZMODELWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Navigates through the processes and generates the images files
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ModelGenerateImageFiles : public ZUModelNavigation, public PSS_KeepStringUsage
{
    public:
        /**
        * Constructor
        *@param pModel - model for which images files should be generated
        *@param pClass - model class
        *@param pPropAttributes - model attributes
        */
        PSS_ModelGenerateImageFiles(ZDProcessGraphModelMdl* pModel          = NULL,
                                    void*                   pClass          = NULL,
                                    ZBPropertyAttributes*   pPropAttributes = NULL);

        virtual ~PSS_ModelGenerateImageFiles();

        /**
        * Gets the index html file name
        *@return the index html file name
        */
        virtual inline CString GetIndexHtmlFileName() const;

        /**
        * Gets the root html file name
        *@return the root html file name
        */
        virtual inline CString GetRootHtmlFileName() const;

        /**
        * Called when a navigation starts
        *@return true on success, otherwise false
        */
        virtual bool OnStart();

        /**
        * Called when a navigation ends
        *@return true on success, otherwise false
        */
        virtual bool OnFinish();

        /**
        * Called when the navigation reaches a symbol and the files should be generated for this symbol
        *@param pSymbol - found symbol
        *@return true on success, otherwise false
        */
        virtual bool OnSymbol(ZBSymbol* pSymbol);

        /**
        * Called when the navigation reaches a link and the files should be generated for this link
        *@param pSymbol - found symbol
        *@return true on success, otherwise false
        */
        virtual bool OnLink(ZBLinkSymbol* pLink);

    private:
        static std::size_t             m_IndexItem;
        ZBInfoModelGraphicGeneration*  m_pInfo;
        ZBPropertyAttributes*          m_pPropAttributes;
        PSS_PublishModelGenerateDialog m_FileGenerateWindow;
        CString                        m_RootHtmlFileName;
        CString                        m_IndexHtmlFileName;
        CString                        m_RootName;
        CString                        m_ImageDirectory;
        CString                        m_IncludeDirectory;
        CString                        m_InternalLogoFileName;

        /**
        * Generates the model files
        *@return true on success, otherwise false
        */
        bool GenerateModel(ZDProcessGraphModelMdl* pModel);

        /**
        * Builds file name and path
        *@param fileName - file name
        *@param refFileName - reference file name
        *@return file name and path
        */
        CString BuildFileNameAndPath(const CString& fileName, const CString& refFileName);

        /**
        * Replaces all the backslash found in a string by a slash
        *@param fileName - file name in which backslash should be replaced
        *@return replaced file name
        */
        CString ReplaceBackSlash(const CString& fileName);

        /**
        * Replaces all the CRLF and tab chars found in a string by space
        *@param str - file name in which special chars should be replaced
        *@return replaced file name
        */
        CString ReplaceSpecialCharInString(const CString& str);

        /**
        * Parses the model name
        *@param modelName - model name to parse
        *@return parsed model name
        */
        inline CString ParseModelName(const CString& modelName) const;

        /**
        * Creates a html page
        *@param pModel - model from which the html page should be created
        *@param imageFileName - model image file name
        *@return true on success, otherwise false
        */
        bool CreateHtmlPage(ZDProcessGraphModelMdl* pModel, const CString& imageFileName);

        /**
        * Generates the index page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateIndexPage(ZDProcessGraphModelMdl* pModel);

        /**
        * Generates the model main frame page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateFrameMainModelPage(ZDProcessGraphModelMdl* pModel, const CString& modelHtmlPage);

        /**
        * Generates the frame user page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateFrameUserPage(ZDProcessGraphModelMdl* pModel);

        /**
        * Generates the frame system page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateFrameSystemPage(ZDProcessGraphModelMdl* pModel);

        /**
        * Generates the frame prestations page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateFramePrestationsPage(ZDProcessGraphModelMdl* pModel);

        /**
        * Generates the frame empty user page
        *@return true on success, otherwise false
        */
        bool GenerateFrameEmptyUserPage();

        /**
        * Generates the frame empty system page
        *@return true on success, otherwise false
        */
        bool GenerateFrameEmptySystemPage();

        /**
        * Generates the frame empty prestations page
        *@return true on success, otherwise false
        */
        bool GenerateFrameEmptyPrestationsPage();

        /**
        * Generates the frame empty property page
        *@return true on success, otherwise false
        */
        bool GenerateEmptyPropertyPage();

        /**
        * Generates the banner page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateBannerPage(ZDProcessGraphModelMdl* pModel);

        /**
        * Generates the unit group page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateUnitGroupPage(ZDProcessGraphModelMdl* pModel);

        /**
        * Generates the logical system page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateLogicalSystemPage(ZDProcessGraphModelMdl* pModel);

        /**
        * Generates the logical prestations page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateLogicalPrestationsPage(ZDProcessGraphModelMdl* pModel);

        /**
        * Generates the unit objects
        *@param pGroupEntity - group entity for which the objects should be generated
        *@param pHtmlFile - html file to add to
        *@return true on success, otherwise false
        */
        bool GenerateUnitObjects(ZBUserGroupEntity* pGroupEntity, PSS_HtmlFile* pHtmlFile);

        /**
        * Generates the unit group objects
        *@param pGroupEntity - group entity for which the objects should be generated
        *@param pHtmlFile - html file to add to
        *@param parentID - parent identifier
        *@return true on success, otherwise false
        */
        bool GenerateUnitGroupObjects(ZBUserGroupEntity* pGroupEntity, PSS_HtmlFile* pHtmlFile, std::size_t parentID);

        /**
        * Generates the unit role objects
        *@param pRoleEntity - role entity for which the objects should be generated
        *@param pHtmlFile - html file to add to
        *@param parentID - parent identifier
        *@return true on success, otherwise false
        */
        bool GenerateUnitRoleObjects(ZBUserRoleEntity* pRoleEntity, PSS_HtmlFile* pHtmlFile, std::size_t parentID);

        /**
        * Generates the user group list
        *@param pGroupEntity - group entity for which the list should be generated
        *@return the user group list, empty string on error
        */
        CString GenerateUserGroupList(ZBUserGroupEntity* pGroupEntity);

        /**
        * Generates the logical system objects
        *@param pSystemEntity - logical system entity for which the objects should be generated
        *@param pHtmlFile - html file to add to
        *@param parentID - parent identifier
        *@return true on success, otherwise false
        */
        bool GenerateLogicalSystemObjects(ZBLogicalSystemEntity* pSystemEntity, PSS_HtmlFile* pHtmlFile);
        bool GenerateLogicalSystemObjects(ZBLogicalSystemEntity* pSystemEntity, PSS_HtmlFile* pHtmlFile, std::size_t parentID);

        /**
        * Generates the logical system list
        *@param pSystemEntity - logical system entity for which the list should be generated
        *@return the logical system list, empty string on error
        */
        CString GenerateLogicalSystemList(ZBLogicalSystemEntity* pSystemEntity);

        /**
        * Generates the logical prestations objects
        *@param pSystemEntity - logical prestations entity for which the objects should be generated
        *@param pHtmlFile - html file to add to
        *@param parentID - parent identifier
        *@return true on success, otherwise false
        */
        bool GenerateLogicalPrestationsObjects(ZBLogicalPrestationsEntity* pPrestationsEntity, PSS_HtmlFile* pHtmlFile);
        bool GenerateLogicalPrestationsObjects(ZBLogicalPrestationsEntity* pPrestationsEntity, PSS_HtmlFile* pHtmlFile, std::size_t parentID);

        /**
        * Generates the logical prestations list
        *@param pSystemEntity - logical prestations entity for which the list should be generated
        *@return the logical prestations list, empty string on error
        */
        CString GenerateLogicalPrestationsList(ZBLogicalPrestationsEntity* pPrestationsEntity);

        bool GeneratePropertyPage(ZIProperties* pPropertiesObject, const CString& htmlFileName);

        /**
        * Builds the model image file name
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        CString BuildModelImageFileName(ZDProcessGraphModelMdl* pModel) const;

        /**
        * Builds the model html file name
        *@param pModel - model owning the file for which the name should be built
        *@param prefix - file name prefix
        *@return file name
        */
        CString BuildModelHTMLFileName(ZDProcessGraphModelMdl* pModel, const CString& prefix = _T("")) const;

        /**
        * Builds the model html file name for printer
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        CString BuildModelHTMLFileNameForPrinter(ZDProcessGraphModelMdl* pModel) const;

        /**
        * Builds the main frame model html file name
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        inline CString BuildModelHTMLFileNameMainFrame(ZDProcessGraphModelMdl* pModel) const;

        /**
        * Builds the html file name for index
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        inline CString BuildModelHTMLFileNameIndex() const;
        inline CString BuildModelHTMLFileNameIndex(ZDProcessGraphModelMdl* pModel) const;

        /**
        * Builds the html file name for banner
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        inline CString BuildModelHTMLFileNameBanner() const;

        /**
        * Builds the html file name for user main frame
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        inline CString BuildModelHTMLFileNameUserMainFrame() const;

        /**
        * Builds the html file name for unit
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        inline CString BuildModelHTMLFileNameUnit(ZDProcessGraphModelMdl* pModel) const;

        /**
        * Builds the html file name for system
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        inline CString BuildModelHTMLFileNameSystem(ZDProcessGraphModelMdl* pModel) const;

        /**
        * Builds the html file name for prestations
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        inline CString BuildModelHTMLFileNamePrestations(ZDProcessGraphModelMdl* pModel) const;

        /**
        * Builds the html file name for logical system
        *@param pSystemEntity - system entity owning the file for which the name should be built
        *@return file name
        */
        CString BuildHTMLFileNameLogicalSystem(ZBSystemEntity* pSystemEntity) const;

        /**
        * Builds the html file name for logical prestations
        *@param pPrestationsEntity - prestations entity owning the file for which the name should be built
        *@return file name
        */
        CString BuildHTMLFileNameLogicalPrestations(ZBPrestationsEntity* pPrestationsEntity) const;

        /**
        * Builds the html file name for user
        *@param pUserEntity - user entity owning the file for which the name should be built
        *@return file name
        */
        CString BuildHTMLFileNameUser(ZBUserEntity* pUserEntity) const;

        /**
        * Builds the html file name for the system main frame
        *@return file name
        */
        inline CString BuildModelHTMLFileNameSystemMainFrame() const;

        /**
        * Builds the html file name for the prestations main frame
        *@return file name
        */
        inline CString BuildModelHTMLFileNamePrestationsMainFrame() const;

        /**
        * Builds the html file name for the empty user
        *@return file name
        */
        inline CString BuildModelHTMLFileNameEmptyUser() const;

        /**
        * Builds the html file name for the empty system
        *@return file name
        */
        inline CString BuildModelHTMLFileNameEmptySystem() const;

        /**
        * Builds the html file name for the empty prestations
        *@return file name
        */
        inline CString BuildModelHTMLFileNameEmptyPrestations() const;

        /**
        * Builds the html file name for the empty property page
        *@return file name
        */
        inline CString BuildModelHTMLFileNameEmptyPropertyPage() const;

        /**
        * Builds the html file name for the Conceptor page
        *@param entityName - entity name for which the file name should be built
        *@return file name
        */
        CString BuildConceptorHTMLFileName(const CString& entityName) const;

        /**
        * Builds the html file name for the process report page
        *@param processName - process report name for which the file name should be built
        *@return file name
        */
        CString BuildProcessReportHTMLFileName(const CString& processName) const;

        /**
        * Builds the html file name for the prestations report page
        *@param prestationName - prestation name for which the file name should be built
        *@return file name
        */
        CString BuildPrestationsReportHTMLFileName(const CString& prestationName) const;

        /**
        * Builds the html file name for the symbol property page
        *@param pSymbol - symbol for which the file name should be built
        *@param pModel - model for which the file name should be built
        *@param prefix - file name prefix
        *@return file name
        */
        CString BuildSymbolPropertyHTMLFileName(PSS_BasicSymbol*        pSymbol,
                                                ZDProcessGraphModelMdl* pModel,
                                                const CString&          prefix = _T("")) const;
};

//---------------------------------------------------------------------------
// PSS_ModelGenerateImageFiles
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::GetIndexHtmlFileName() const
{
    return m_IndexHtmlFileName;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::GetRootHtmlFileName() const
{
    return m_RootHtmlFileName;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::ParseModelName(const CString& modelName) const
{
    return PSS_StringTools::ConvertSpecialChar(modelName);
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameMainFrame(ZDProcessGraphModelMdl* pModel) const
{
    return BuildModelHTMLFileName(pModel, _T("mainfrm_"));
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameIndex() const
{
    // build the main index html FileName 
    return PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\index.htm");
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameIndex(ZDProcessGraphModelMdl* pModel) const
{
    return BuildModelHTMLFileName(pModel, _T("Index_"));
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameBanner() const
{
    // build the main banner html FileName 
    return PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\banner.htm");
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameUserMainFrame() const
{
    // build the main index html FileName 
    return PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\users_mainframe.htm");
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameUnit(ZDProcessGraphModelMdl* pModel) const
{
    return BuildModelHTMLFileName(pModel, _T("Unit_"));
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameSystem(ZDProcessGraphModelMdl* pModel) const
{
    return BuildModelHTMLFileName(pModel, _T("System_"));
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNamePrestations(ZDProcessGraphModelMdl* pModel) const
{
    return BuildModelHTMLFileName(pModel, _T("Prestations_"));
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameSystemMainFrame() const
{
    // build the main index html FileName 
    return PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\system_mainframe.htm");
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNamePrestationsMainFrame() const
{
    return PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\prestations_mainframe.htm");
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameEmptyUser() const
{
    // build the main index html FileName 
    return PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\empty_users.htm");
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameEmptySystem() const
{
    // build the main index html FileName 
    return PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\empty_system.htm");
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameEmptyPrestations() const
{
    return PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\empty_prestations.htm");
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameEmptyPropertyPage() const
{
    // Build the main index html FileName 
    return PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\empty_prp.htm");
}
//---------------------------------------------------------------------------

#endif
