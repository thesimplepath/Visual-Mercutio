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
#include "zProperty\PSS_PropertyAttributes.h"
#include "zModel\PSS_ModelNavigation.h"
#include "zModel\PSS_InfoModelGraphicGeneration.h"
#include "zModelWeb\PSS_PublishModelGenerateDialog.h"

// old class name mapping
#ifndef PSS_UserEntity
    #define PSS_UserEntity ZBUserEntity
#endif
#ifndef PSS_UserGroupEntity
    #define PSS_UserGroupEntity ZBUserGroupEntity
#endif
#ifndef PSS_UserRoleEntity
    #define PSS_UserRoleEntity ZBUserRoleEntity
#endif
#ifndef PSS_SystemEntity
    #define PSS_SystemEntity ZBSystemEntity
#endif
#ifndef PSS_LogicalSystemEntity
    #define PSS_LogicalSystemEntity ZBLogicalSystemEntity
#endif
#ifndef PSS_PrestationsEntity
    #define PSS_PrestationsEntity ZBPrestationsEntity
#endif
#ifndef PSS_LogicalPrestationsEntity
    #define PSS_LogicalPrestationsEntity ZBLogicalPrestationsEntity
#endif
#ifndef PSS_RulesEntity
    #define PSS_RulesEntity ZBRulesEntity
#endif
#ifndef PSS_LogicalRulesEntity
    #define PSS_LogicalRulesEntity ZBLogicalRulesEntity
#endif

// forward class declaration
class PSS_BasicSymbol;
class PSS_Properties;
class PSS_InfoModelGraphicGeneration;
class PSS_UserEntity;
class PSS_UserGroupEntity;
class PSS_UserRoleEntity;
class PSS_SystemEntity;
class PSS_LogicalSystemEntity;
class PSS_PrestationsEntity;
class PSS_LogicalPrestationsEntity;
class PSS_RulesEntity;
class PSS_LogicalRulesEntity;
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
class AFX_EXT_CLASS PSS_ModelGenerateImageFiles : public PSS_ModelNavigation,
                                                  public PSS_KeepStringUsage
{
    public:
        /**
        * Constructor
        *@param pModel - the model for which images files should be generated, can be NULL
        *@param pClass - the custom data class, can be NULL
        *@param pPropAttributes - the model attributes, can be NULL
        */
        PSS_ModelGenerateImageFiles(PSS_ProcessGraphModelMdl* pModel          = NULL,
                                    void*                     pClass          = NULL,
                                    PSS_PropertyAttributes*   pPropAttributes = NULL);

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
        virtual bool OnSymbol(PSS_Symbol* pSymbol);

        /**
        * Called when the navigation reaches a link and the files should be generated for this link
        *@param pSymbol - found symbol
        *@return true on success, otherwise false
        */
        virtual bool OnLink(PSS_LinkSymbol* pLink);

    private:
        static std::size_t              m_IndexItem;
        PSS_InfoModelGraphicGeneration* m_pInfo;
        PSS_PropertyAttributes*         m_pPropAttributes;
        PSS_PublishModelGenerateDialog  m_FileGenerateWindow;
        CString                         m_RootHtmlFileName;
        CString                         m_IndexHtmlFileName;
        CString                         m_RootName;
        CString                         m_ImageDirectory;
        CString                         m_IncludeDirectory;
        CString                         m_InternalLogoFileName;

        /**
        * Generates the model files
        *@return true on success, otherwise false
        */
        bool GenerateModel(PSS_ProcessGraphModelMdl* pModel);

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
        bool CreateHtmlPage(PSS_ProcessGraphModelMdl* pModel, const CString& imageFileName);

        /**
        * Generates the index page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateIndexPage(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Generates the model main frame page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateFrameMainModelPage(PSS_ProcessGraphModelMdl* pModel, const CString& modelHtmlPage);

        /**
        * Generates the frame user page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateFrameUserPage(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Generates the frame system page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateFrameSystemPage(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Generates the frame prestations page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateFramePrestationsPage(PSS_ProcessGraphModelMdl* pModel);

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
        bool GenerateBannerPage(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Generates the unit group page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateUnitGroupPage(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Generates the logical system page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateLogicalSystemPage(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Generates the logical prestations page
        *@param pModel - model for which the page should be generated
        *@return true on success, otherwise false
        */
        bool GenerateLogicalPrestationsPage(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Generates the unit objects
        *@param pGroupEntity - group entity for which the objects should be generated
        *@param pHtmlFile - html file to add to
        *@return true on success, otherwise false
        */
        bool GenerateUnitObjects(PSS_UserGroupEntity* pGroupEntity, PSS_HtmlFile* pHtmlFile);

        /**
        * Generates the unit group objects
        *@param pGroupEntity - group entity for which the objects should be generated
        *@param pHtmlFile - html file to add to
        *@param parentID - parent identifier
        *@return true on success, otherwise false
        */
        bool GenerateUnitGroupObjects(PSS_UserGroupEntity* pGroupEntity, PSS_HtmlFile* pHtmlFile, std::size_t parentID);

        /**
        * Generates the unit role objects
        *@param pRoleEntity - role entity for which the objects should be generated
        *@param pHtmlFile - html file to add to
        *@param parentID - parent identifier
        *@return true on success, otherwise false
        */
        bool GenerateUnitRoleObjects(PSS_UserRoleEntity* pRoleEntity, PSS_HtmlFile* pHtmlFile, std::size_t parentID);

        /**
        * Generates the user group list
        *@param pGroupEntity - group entity for which the list should be generated
        *@return the user group list, empty string on error
        */
        CString GenerateUserGroupList(PSS_UserGroupEntity* pGroupEntity);

        /**
        * Generates the logical system objects
        *@param pSystemEntity - logical system entity for which the objects should be generated
        *@param pHtmlFile - html file to add to
        *@param parentID - parent identifier
        *@return true on success, otherwise false
        */
        bool GenerateLogicalSystemObjects(PSS_LogicalSystemEntity* pSystemEntity, PSS_HtmlFile* pHtmlFile);
        bool GenerateLogicalSystemObjects(PSS_LogicalSystemEntity* pSystemEntity, PSS_HtmlFile* pHtmlFile, std::size_t parentID);

        /**
        * Generates the logical system list
        *@param pSystemEntity - logical system entity for which the list should be generated
        *@return the logical system list, empty string on error
        */
        CString GenerateLogicalSystemList(PSS_LogicalSystemEntity* pSystemEntity);

        /**
        * Generates the logical prestations objects
        *@param pSystemEntity - logical prestations entity for which the objects should be generated
        *@param pHtmlFile - html file to add to
        *@param parentID - parent identifier
        *@return true on success, otherwise false
        */
        bool GenerateLogicalPrestationsObjects(PSS_LogicalPrestationsEntity* pPrestationsEntity, PSS_HtmlFile* pHtmlFile);
        bool GenerateLogicalPrestationsObjects(PSS_LogicalPrestationsEntity* pPrestationsEntity, PSS_HtmlFile* pHtmlFile, std::size_t parentID);

        /**
        * Generates the logical prestations list
        *@param pSystemEntity - logical prestations entity for which the list should be generated
        *@return the logical prestations list, empty string on error
        */
        CString GenerateLogicalPrestationsList(PSS_LogicalPrestationsEntity* pPrestationsEntity);

        bool GeneratePropertyPage(PSS_Properties* pPropertiesObject, const CString& htmlFileName);

        /**
        * Builds the model image file name
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        CString BuildModelImageFileName(PSS_ProcessGraphModelMdl* pModel) const;

        /**
        * Builds the model html file name
        *@param pModel - model owning the file for which the name should be built
        *@param prefix - file name prefix
        *@return file name
        */
        CString BuildModelHTMLFileName(PSS_ProcessGraphModelMdl* pModel, const CString& prefix = _T("")) const;

        /**
        * Builds the model html file name for printer
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        CString BuildModelHTMLFileNameForPrinter(PSS_ProcessGraphModelMdl* pModel) const;

        /**
        * Builds the main frame model html file name
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        inline CString BuildModelHTMLFileNameMainFrame(PSS_ProcessGraphModelMdl* pModel) const;

        /**
        * Builds the html file name for index
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        inline CString BuildModelHTMLFileNameIndex() const;
        inline CString BuildModelHTMLFileNameIndex(PSS_ProcessGraphModelMdl* pModel) const;

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
        inline CString BuildModelHTMLFileNameUnit(PSS_ProcessGraphModelMdl* pModel) const;

        /**
        * Builds the html file name for system
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        inline CString BuildModelHTMLFileNameSystem(PSS_ProcessGraphModelMdl* pModel) const;

        /**
        * Builds the html file name for prestations
        *@param pModel - model owning the file for which the name should be built
        *@return file name
        */
        inline CString BuildModelHTMLFileNamePrestations(PSS_ProcessGraphModelMdl* pModel) const;

        /**
        * Builds the html file name for logical system
        *@param pSystemEntity - system entity owning the file for which the name should be built
        *@return file name
        */
        CString BuildHTMLFileNameLogicalSystem(PSS_SystemEntity* pSystemEntity) const;

        /**
        * Builds the html file name for logical prestations
        *@param pPrestationsEntity - prestations entity owning the file for which the name should be built
        *@return file name
        */
        CString BuildHTMLFileNameLogicalPrestations(PSS_PrestationsEntity* pPrestationsEntity) const;

        /**
        * Builds the html file name for user
        *@param pUserEntity - user entity owning the file for which the name should be built
        *@return file name
        */
        CString BuildHTMLFileNameUser(PSS_UserEntity* pUserEntity) const;

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
        CString BuildSymbolPropertyHTMLFileName(PSS_BasicSymbol*          pSymbol,
                                                PSS_ProcessGraphModelMdl* pModel,
                                                const CString&            prefix = _T("")) const;
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
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameMainFrame(PSS_ProcessGraphModelMdl* pModel) const
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
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameIndex(PSS_ProcessGraphModelMdl* pModel) const
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
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameUnit(PSS_ProcessGraphModelMdl* pModel) const
{
    return BuildModelHTMLFileName(pModel, _T("Unit_"));
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameSystem(PSS_ProcessGraphModelMdl* pModel) const
{
    return BuildModelHTMLFileName(pModel, _T("System_"));
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNamePrestations(PSS_ProcessGraphModelMdl* pModel) const
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
