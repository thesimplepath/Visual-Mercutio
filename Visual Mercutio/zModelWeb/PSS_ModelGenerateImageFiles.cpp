/****************************************************************************
 * ==> PSS_ModelGenerateImageFiles -----------------------------------------*
 ****************************************************************************
 * Description : Navigates through the processes and generates the images   *
 *               files                                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ModelGenerateImageFiles.h"

// processsoft
#include "zBaseLib\PSS_Server.h"
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\PSS_StringFormatter.h"
#include "zBaseLib\PSS_Global.h"
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_ProcessGraphModelController.h"
#include "zModel\PSS_ProcessGraphModelViewport.h"
#include "zModel\ZDProcessGraphPage.h"
#include "zModel\ZUExtractModelUnitGroupAssigned.h"
#include "zModel\ZUExtractModelLogicalSystemAssigned.h"
#include "zModel\ZUExtractModelLogicalPrestationsAssigned.h"
#include "zModel\ZBSymbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\ZBUserGroupEntity.h"
#include "zModel\ZBUserRoleEntity.h"
#include "zModel\ZBLogicalSystemEntity.h"
#include "zModel\ZBLogicalPrestationsEntity.h"
#include "zModel\ZBLogicalRulesEntity.h"
#include "zModel\zModelRes.h"
#include "zWeb\PSS_HtmlFile.h"

// resources
#include "PSS_ModelResIDs.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------
const CString g_LogoImageFile               = _T("processsoft.jpg");
const CString g_HomeImageFile               = _T("home.jpg");
const CString g_ParentImageFile             = _T("parent.gif");
const CString g_PrinterImageFile            = _T("printer.jpg");
const CString g_1pTransImageFile            = _T("1ptrans.gif");
const CString g_MinusImageFile              = _T("minus.gif");
const CString g_PlusImageFile               = _T("plus.gif");
const CString g_UsersImageFile              = _T("users.gif");
const CString g_LogicalSystemImageFile      = _T("lgs.gif");
const CString g_LogicalPrestationsImageFile = _T("prest.gif");
const CString g_TreeCSSFile                 = _T("tree.css");
const CString g_TreeJSFile                  = _T("tree.js");
const CString g_AJLibJSFile                 = _T("ajlib.js");
const CString g_AJPopupJSFile               = _T("ajpopup.js");
const CString g_AJPopupCSSFile              = _T("ajpopup.css");
const CString g_White                       = _T("White");
const CString g_PSSRightTarget              = _T("_pssRightFrame");
const CString g_PSSLeftTarget               = _T("_pssLeftFrame");
const CString g_PSSMainTarget               = _T("_pssMain");
const CString g_BlankTarget                 = _T("_blank");
const CString g_TopTarget                   = _T("_top");
const CString g_BottomTarget                = _T("_bottom");
const CString g_LeftTarget                  = _T("_left");
const CString g_RightTarget                 = _T("_right");
//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
std::size_t PSS_ModelGenerateImageFiles::m_IndexItem = 0;
//---------------------------------------------------------------------------
// PSS_ModelGenerateImageFiles
//---------------------------------------------------------------------------
PSS_ModelGenerateImageFiles::PSS_ModelGenerateImageFiles(PSS_ProcessGraphModelMdl* pModel,
                                                         void*                     pClass,
                                                         ZBPropertyAttributes*     pPropAttributes) :
    ZUModelNavigation(pModel, pClass),
    m_pPropAttributes(pPropAttributes)
{}
//---------------------------------------------------------------------------
PSS_ModelGenerateImageFiles::~PSS_ModelGenerateImageFiles()
{}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::OnStart()
{
    // get info from model class
    m_pInfo = static_cast<ZBInfoModelGraphicGeneration*>(m_pClass);
    ASSERT(m_pInfo);

    // create the window for file generation feedback
    m_FileGenerateWindow.Create();

    // create the image directory
    m_ImageDirectory = PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\images");
    PSS_Directory::CreateDirectory(m_ImageDirectory);

    if (!PSS_Directory::Exist(m_ImageDirectory))
        return false;

    // create the image directory
    m_IncludeDirectory = PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\includes");
    PSS_Directory::CreateDirectory(m_IncludeDirectory);

    if (!PSS_Directory::Exist(m_IncludeDirectory))
        return false;
    
    // get the web directory
    const CString webDir = PSS_Global::GetApplicationDirectory() + _T("\\Web");

    // copy images from the system root directory
    if (m_pInfo->GetServer())
    {
        if (m_pInfo->GetImageFileName().IsEmpty())
        {
            PSS_Directory::CopyFileFromToDirectory(webDir, m_ImageDirectory, g_LogoImageFile);
            m_InternalLogoFileName.Empty();
        }
        else
        {
            PSS_File file(m_pInfo->GetImageFileName());
            m_InternalLogoFileName = file.GetFileName();
            PSS_Directory::CopyFileFromToDirectory(file.GetFilePath(), m_ImageDirectory, m_InternalLogoFileName);
        }

        PSS_Directory::CopyFileFromToDirectory(webDir, m_ImageDirectory,   g_HomeImageFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_ImageDirectory,   g_ParentImageFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_ImageDirectory,   g_PrinterImageFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_ImageDirectory,   g_1pTransImageFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_ImageDirectory,   g_MinusImageFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_ImageDirectory,   g_PlusImageFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_ImageDirectory,   g_UsersImageFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_ImageDirectory,   g_LogicalSystemImageFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_ImageDirectory,   g_LogicalPrestationsImageFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_IncludeDirectory, g_TreeCSSFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_IncludeDirectory, g_TreeJSFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_IncludeDirectory, g_AJLibJSFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_IncludeDirectory, g_AJPopupJSFile);
        PSS_Directory::CopyFileFromToDirectory(webDir, m_IncludeDirectory, g_AJPopupCSSFile);
    }

    if (!GenerateIndexPage(m_pModel))
        return false;

    if (!GenerateBannerPage(m_pModel))
        return false;

    if (!GenerateEmptyPropertyPage())
        return false;

    if (!GenerateModel(m_pModel))
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::OnFinish()
{
    // hide the feedback dialog
    m_FileGenerateWindow.ShowWindow(SW_HIDE);
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::OnSymbol(PSS_Symbol* pSymbol)
{
    if (!pSymbol)
        return false;

    ASSERT(m_pInfo);

    // get the html page owner model
    PSS_ProcessGraphModelMdl* pOwnerModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetOwnerModel());

    // build the html file name
    const CString htmlFileName = BuildSymbolPropertyHTMLFileName(pSymbol, pOwnerModel ? pOwnerModel : m_pModel);

    if (!GeneratePropertyPage(pSymbol, htmlFileName))
        return false;

    if (pSymbol->GetChildModel() && m_pInfo->GetDC() && m_pInfo->GetCtlr())
    {
        PSS_ProcessGraphModelMdl* pChildModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());

        if (!pChildModel)
            return false;

        if (!GenerateModel(pChildModel))
            return false;

        const PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pPageSet = pChildModel->GetPageSet();

        // generate the html page contained at the model root
        if (pPageSet)
        {
            PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(pPageSet);

            // iterate through pages to process
            for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
            {
                // get the page model
                PSS_ProcessGraphModelMdl* pPageModel = pPage->GetModel();

                if (!pPageModel)
                    continue;

                // do process itself?
                if (pPageModel == pChildModel)
                    continue;

                if (!GenerateModel(pPageModel))
                    return false;
            }
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::OnLink(PSS_LinkSymbol* pLink)
{
    if (!pLink)
        return false;

    ASSERT(m_pInfo);

    // get the html page owner model
    PSS_ProcessGraphModelMdl* pOwnerModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pLink->GetOwnerModel());

    // build the html FileName
    const CString htmlFileName = BuildSymbolPropertyHTMLFileName(pLink, pOwnerModel ? pOwnerModel : m_pModel);

    return GeneratePropertyPage(pLink, htmlFileName);
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateModel(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return false;

    ASSERT(m_pInfo);

    if (!m_pInfo->GetDC() || !m_pInfo->GetCtlr())
        return false;

    // get the viewport
    PSS_ProcessGraphModelViewport* pVp = m_pInfo->GetCtlr()->BrowseModel(pModel, pModel->GetParent());

    if (!pVp)
        return false;

    // get the model image file name 
    const CString imageFileName = BuildModelImageFileName(pModel);

    // refresh Setup Copyfile Window
    m_FileGenerateWindow.SetDestination(imageFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // dispatch Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the image has already been generated, to avoid to generate the same image twice
    if (!StringAlreadyGenerated(imageFileName))
        // write the file
        pVp->ExportModelToImageFile(imageFileName, *m_pInfo->GetDC());

    CreateHtmlPage(pModel, imageFileName);

    return true;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildFileNameAndPath(const CString& fileName, const CString& refFileName)
{
    if (m_pInfo->GetAbsolutePath() || fileName.IsEmpty())
        return fileName;

    // if path is relative, run through the path and replace its location
    PSS_File refFile(refFileName);
    PSS_File File(fileName);

    CString refFilePath(refFile.GetFilePath());
    LPTSTR  pRefFilePath = refFilePath.GetBuffer(refFilePath.GetLength());

    CString filePath(File.GetFilePath());
    LPTSTR  pFilePath = filePath.GetBuffer(filePath.GetLength());

    const CString shortFileName = File.GetFileName();

    // iterate through the directory till different
    while (*pRefFilePath && *pFilePath && *pRefFilePath == *pFilePath)
    {
        ++pFilePath;
        ++pRefFilePath;
    }

    // same directory? Returns the file name only
    if (!*pRefFilePath && !*pFilePath)
    {
        refFilePath.ReleaseBuffer(-1);
        filePath.ReleaseBuffer(-1);
        return shortFileName;
    }

    // the ref file is at the end? The destination is just below the initial reference file
    if (!*pRefFilePath)
    {
        const CString finalFile(pFilePath);
        refFilePath.ReleaseBuffer(-1);
        filePath.ReleaseBuffer(-1);
        return ReplaceBackSlash(finalFile + shortFileName);
    }

    // the file is at the end? The destination is upper
    if (!*pFilePath)
    {
        // count the remaining directories and replace them by .. backslash
        CString relativePath;

        for (; *pRefFilePath; ++pRefFilePath)
            if (*pRefFilePath == '\\')
                relativePath += _T("../");

        refFilePath.ReleaseBuffer(-1);
        filePath.ReleaseBuffer(-1);

        return ReplaceBackSlash(relativePath + shortFileName);
    }

    // otherwise, go back then go down
    CString relativePath;

    // go back to top by replacing directories by .. backslash
    for (; *pRefFilePath; ++pRefFilePath)
        if (*pRefFilePath == '\\')
            relativePath += _T("../");

    const CString completePath = relativePath + pFilePath;
    refFilePath.ReleaseBuffer(-1);
    filePath.ReleaseBuffer(-1);

    return ReplaceBackSlash(completePath);
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::ReplaceBackSlash(const CString& fileName)
{
    CString name = fileName;
    LPTSTR  pC   = name.GetBuffer(name.GetLength() + 1);

    try
    {
        // iterate through chars and replace each backslash by slash
        for (; *pC; ++pC)
            if (*pC == '\\')
                *pC = '/';
    }
    catch (...)
    {
        name.ReleaseBuffer(-1);
        throw;
    }

    name.ReleaseBuffer(-1);
    return name;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::ReplaceSpecialCharInString(const CString& str)
{
    CString s  = str;
    LPTSTR  pC = s.GetBuffer(s.GetLength() + 1);

    try
    {
        // iterate through chars and replace each CRLF or tab by space
        for (; *pC; ++pC)
            switch (*pC)
            {
                case '\t':
                case '\r':
                case '\n': *pC = ' ';
            }
    }
    catch (...)
    {
        s.ReleaseBuffer(-1);
        throw;
    }

    s.ReleaseBuffer(-1);
    return s;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::CreateHtmlPage(PSS_ProcessGraphModelMdl* pModel, const CString& imageFileName)
{
    if (!pModel)
        return false;

    const CString htmlFileName           = BuildModelHTMLFileName(pModel);
    const CString htmlFileNameForPrinter = BuildModelHTMLFileNameForPrinter(pModel);

    // refresh setup copy file Window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // dispatch Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        // write header
        CString s;
        s.Format(IDS_MODELGENHTML_1,
                 (const char*)pModel->GetAbsolutePath(),
                 (const char*)PSS_Date::GetToday().GetStandardFormattedDate());
        htmlFile << s;

        // build the CSS file name
        const CString ajPopupCSSFileName = m_IncludeDirectory + _T("\\") + g_AJPopupCSSFile;
        s.Format(IDS_MODELGENHTML_50,
                 (const char*)BuildFileNameAndPath(ajPopupCSSFileName, htmlFileName));
        htmlFile << s;

        // build the ajLib javascript file name
        const CString ajLibJSFileName = m_IncludeDirectory + _T("\\") + g_AJLibJSFile;
        s.Format(IDS_MODELGENHTML_52,
                 (const char*)BuildFileNameAndPath(ajLibJSFileName, htmlFileName));
        htmlFile << s;

        // build the ajPopup javascript file name
        CString ajPopupJSFileName = m_IncludeDirectory + _T("\\") + g_AJPopupJSFile;
        s.Format(IDS_MODELGENHTML_52,
                 (const char*)BuildFileNameAndPath(ajPopupJSFileName, htmlFileName));
        htmlFile << s;

        // write the JavaScript header
        s.LoadString(IDS_MODELGENHTML_79);
        htmlFile << s;

        const CODComponentSet* pSet = pModel->GetComponents();
        ASSERT(pSet);

        const int setCount      = pSet->GetSize();
              int objectCounter = 1;

        // iterate through components
        for (int i = 0; i < setCount; ++i)
        {
            // get component
            CODComponent* pComp = pSet->GetAt(i);

            if (!pComp)
                continue;

            // is a symbol or a link?
            if (ISA(pComp, PSS_Symbol) || ISA(pComp, PSS_LinkSymbol))
            {
                // write it
                s.Format(IDS_MODELGENHTML_86, objectCounter);
                htmlFile << s;
                ++objectCounter;
            }
        }

        s.LoadString(IDS_MODELGENHTML_87);
        htmlFile << s;

        objectCounter = 1;

        // iterate through components
        for (int i = 0; i < setCount; ++i)
        {
            // get component
            CODComponent* pComp = pSet->GetAt(i);

            if (!pComp)
                continue;

            // is a symbol or a link?
            if (ISA(pComp, PSS_Symbol) || ISA(pComp, PSS_LinkSymbol))
            {
                // Write it
                s.Format(IDS_MODELGENHTML_82, objectCounter, objectCounter, objectCounter);
                htmlFile << s;
                ++objectCounter;
            }
        }

        s.LoadString(IDS_MODELGENHTML_83);
        htmlFile << s;

        objectCounter = 1;

        // iterate through components
        for (int i = 0; i < setCount; ++i)
        {
            // get component
            CODComponent* pComp = pSet->GetAt(i);

            if (!pComp)
                continue;

            // is a symbol or a link?
            if (ISA(pComp, PSS_Symbol) || ISA(pComp, PSS_LinkSymbol))
            {
                PSS_BasicSymbol* pBasicSym = dynamic_cast<PSS_BasicSymbol*>(pComp);

                // if no sub-model, just the area for the popup
                PSS_ProcessGraphModelMdl* pOwnerModel =
                        dynamic_cast<PSS_ProcessGraphModelMdl*>(pBasicSym->GetOwnerModel());

                s.Format(IDS_MODELGENHTML_84, objectCounter);
                htmlFile << s;

                s.Format(IDS_MODELGENHTML_88,
                         (const char*)BuildFileNameAndPath(BuildSymbolPropertyHTMLFileName(pBasicSym,
                                                                                           pOwnerModel ? pOwnerModel : pModel),
                                                           htmlFileName));
                htmlFile << s;

                s.Format(IDS_MODELGENHTML_89,
                         objectCounter,
                         objectCounter,
                         objectCounter,
                         objectCounter);
                htmlFile << s;

                ++objectCounter;
            }
        }

        // write the JavaScript footer
        s.LoadString(IDS_MODELGENHTML_90);
        htmlFile << s;

        // end of head and body
        s.LoadString(IDS_MODELGENHTML_51);
        htmlFile << s;

        // write the navigation table header
        s.LoadString(IDS_MODELGENHTML_6);
        htmlFile << s;

        CString logoImage;

        // write the parent if there is one
        if (pModel->GetParent())
        {
            // get the parent html name, its file name, and the logo image file name
            const CString parentName         = pModel->GetParent()->GetAbsolutePath();
            const CString parentHtmlFileName = BuildModelHTMLFileName(pModel->GetParent());
                          logoImage          = m_ImageDirectory + _T("\\") + g_ParentImageFile;

            s.Format(IDS_MODELGENHTML_11,
                     (const char*)BuildFileNameAndPath(parentHtmlFileName, htmlFileName),
                     (const char*)BuildFileNameAndPath(logoImage,          htmlFileName),
                     (const char*)BuildFileNameAndPath(parentHtmlFileName, htmlFileName),
                     (const char*)parentName);
            htmlFile << s;
        }
        else
        {
            // get the parent html file name and the logo image file name
            const CString parentName = _T("Index");
                          logoImage  = m_ImageDirectory + _T("\\") + g_HomeImageFile;

            s.Format(IDS_MODELGENHTML_85,
                     (const char*)BuildFileNameAndPath(m_IndexHtmlFileName, htmlFileName),
                     (const char*)BuildFileNameAndPath(logoImage,           htmlFileName),
                     (const char*)BuildFileNameAndPath(m_IndexHtmlFileName, htmlFileName),
                     (const char*)parentName);
            htmlFile << s;
        }

        // write the print facilities
        logoImage = m_ImageDirectory + _T("\\") + g_PrinterImageFile;
        s.Format(IDS_MODELGENHTML_15,
                 (const char*)BuildFileNameAndPath(htmlFileNameForPrinter, htmlFileName),
                 (const char*)BuildFileNameAndPath(logoImage,              htmlFileName));
        htmlFile << s;

        // write the navigation table footer
        s.LoadString(IDS_MODELGENHTML_9);
        htmlFile << s;

        // write all the popups for all symbols. NOTE Javascript starts here
        s.LoadString(IDS_MODELGENHTML_53);
        htmlFile << s;

        // create a dummy object to avoid copyright on the first object
        s.Format(IDS_MODELGENHTML_55, 0); // allocate the new popup object
        htmlFile << s;
        s.Format(IDS_MODELGENHTML_57, 0, _T(""));
        htmlFile << s;
        s.Format(IDS_MODELGENHTML_58, 0, _T(""));
        htmlFile << s;
        s.Format(IDS_MODELGENHTML_61, 0); // create the new popup object
        htmlFile << s;

        objectCounter = 1;

        // iterate through components
        for (int i = 0; i < setCount; ++i)
        {
            // get component
            CODComponent* pComp = pSet->GetAt(i);

            if (!pComp)
                continue;

            PSS_Symbol*     pSymbol     = dynamic_cast<PSS_Symbol*>(pComp);
            PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pComp);

            // for all symbols, create a popup 
            if (pSymbol || pLinkSymbol)
            {
                PSS_BasicSymbol* pBasicSym = dynamic_cast<PSS_BasicSymbol*>(pComp);
                ASSERT(pBasicSym);

                // allocate the new popup object
                s.Format(IDS_MODELGENHTML_55, objectCounter);
                htmlFile << s;

                // the header is the symbol name
                s.Format(IDS_MODELGENHTML_57,
                         objectCounter,
                         (const char*)ReplaceSpecialCharInString(pBasicSym->GetSymbolName()));
                htmlFile << s;

                CString dummy;
                dummy.Format(IDS_SYMBOLDESCRIPTION_HTML, pBasicSym->GetSymbolComment());

                // the text is the symbol description
                s.Format(IDS_MODELGENHTML_58,
                         objectCounter,
                         (const char*)ReplaceSpecialCharInString(dummy));
                htmlFile << s;

                dummy.Format(IDS_SYMBOLREF_HTML, pBasicSym->GetSymbolReferenceNumber());

                // the text is the symbol description
                s.Format(IDS_MODELGENHTML_58,
                         objectCounter,
                         (const char*)dummy);
                htmlFile << s;

                // check if has an external document
                if ((pSymbol && pSymbol->AcceptExtFile()) || (pLinkSymbol && pLinkSymbol->AcceptExtFile()))
                {
                    // get external file property manager
                    const ZBExtFilePropertyMgr* pExtFilePropMgr = dynamic_cast<ZBExtFilePropertyMgr*>(pComp);
                    ASSERT(pExtFilePropMgr);

                    // get link count
                    const std::size_t linkCount = pExtFilePropMgr->GetExtFileCount();

                    // iterate through links
                    for (std::size_t idx = 0; idx < linkCount; ++idx)
                    {
                        // for each link, create a link with a blank target
                        ZBExtFileProperties* pFileProp = pExtFilePropMgr->GetExtFileProperty(idx);

                        if (!pFileProp)
                            continue;

                        dummy.Format(IDS_SYMBOLEXTFILE_HTML, idx + 1, (const char*)pFileProp->GetFileTitle());

                        s.Format(IDS_MODELGENHTML_60,
                                 objectCounter,
                                 (const char*)dummy,
                                 (const char*)ReplaceBackSlash(pFileProp->GetFileName()),
                                 (const char*)g_BlankTarget);
                        htmlFile << s;
                    }
                }

                // if has a unit defined, insert the unit link
                if ((pSymbol && pSymbol->HasUnit()) || (pLinkSymbol && pLinkSymbol->HasUnit()))
                {
                    ZBUserGroupEntity* pUserGroupEntity =
                            dynamic_cast<ZBUserGroupEntity*>
                                    (pModel->GetMainUserGroup()->FindGroupByGUID(pBasicSym->GetUnitGUID(), true));
                    ASSERT(pUserGroupEntity);

                    if (pUserGroupEntity)
                    {
                        dummy.Format(IDS_SYMBOLUNIT_HTML, (const char*)pBasicSym->GetUnitName());

                        s.Format(IDS_MODELGENHTML_59,
                                 objectCounter,
                                 (const char*)dummy,
                                 (const char*)BuildFileNameAndPath(BuildHTMLFileNameUser(pUserGroupEntity),
                                                                   htmlFileName));

                        htmlFile << s;
                    }
                }

                // if has a system defined, insert the system link
                if ((pSymbol && pLinkSymbol->AcceptExtApp()) || (pLinkSymbol && pLinkSymbol->AcceptExtApp()))
                {
                    // get external file property manager
                    const ZBExtAppPropertyMgr* pExtAppPropMgr = dynamic_cast<ZBExtAppPropertyMgr*>(pComp);
                    ASSERT(pExtAppPropMgr);

                    // get link count
                    const std::size_t appCount = pExtAppPropMgr->GetExtAppCount();

                    for (std::size_t idx = 0; idx < appCount; ++idx)
                    {
                        // for each link, create a link with a blank target
                        const ZBExtAppProperties* pAppProperty = pExtAppPropMgr->GetExtAppProperty(idx);

                        if (pAppProperty)
                        {
                            ZBLogicalSystemEntity* pLogicalSystemEntity =
                                    dynamic_cast<ZBLogicalSystemEntity*>(pModel->GetMainLogicalSystem()->FindSystemByGUID
                                            (pAppProperty->GetCommandParameters().Right(pAppProperty->GetCommandParameters().GetLength() - gLogicalSystemKey.GetLength()), true));

                            if (pLogicalSystemEntity)
                            {
                                dummy.Format(IDS_SYMBOLEXTAPP_HTML,
                                             idx + 1,
                                             (const char*)pAppProperty->GetCommandTitle());

                                s.Format(IDS_MODELGENHTML_59,
                                         objectCounter,
                                         (const char*)dummy,
                                         (const char*)BuildFileNameAndPath(BuildHTMLFileNameLogicalSystem(pLogicalSystemEntity),
                                                                           htmlFileName));
                                htmlFile << s;
                            }
                        }
                    }
                }

                // if has a sub-model defined, create a link to enter in the symbol child model
                if (pSymbol && pSymbol->GetChildModel())
                {
                    PSS_ProcessGraphModelMdl* pSubModel =
                            dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel());
                    ASSERT(pSubModel);

                    // retreive the html FileName for the reference
                    CString symbolChildModelHtmlFileName = BuildModelHTMLFileName(pSubModel);
                    dummy.Format(IDS_GOINSYMBOL_HTML, (const char*)pBasicSym->GetSymbolName());

                    s.Format(IDS_MODELGENHTML_59,
                             objectCounter,
                             (const char*)dummy,
                             (const char*)BuildFileNameAndPath(symbolChildModelHtmlFileName, htmlFileName));

                    htmlFile << s;

                    // check if the symbol has more than one page
                    if (pSubModel->GetPageSet())
                    {
                        PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(pSubModel->GetPageSet());
                        ZDProcessGraphPage*                                 pPage = it.GetFirst();

                        // skip the first page and iterate through the remaining ones
                        if (pPage)
                            for (pPage = it.GetNext(); pPage; pPage = it.GetNext())
                            {
                                // retreive the html file name for the reference
                                symbolChildModelHtmlFileName = BuildModelHTMLFileName(pPage->GetModel());
                                dummy.Format(IDS_GOINSYMBOL_HTML, (const char*)pPage->GetPageName());

                                s.Format(IDS_MODELGENHTML_59,
                                         objectCounter,
                                         (const char*)dummy,
                                         (const char*)BuildFileNameAndPath(symbolChildModelHtmlFileName, htmlFileName));
                                htmlFile << s;
                            }
                    }
                }

                // if has a process report defined, create a link to enter in the process report
                if (pSymbol && pSymbol->IsProcess() && m_pInfo->GetIncludeProcessReport())
                {
                    const CString processReportPath = BuildProcessReportHTMLFileName(pBasicSym->GetSymbolName());

                    // get the html file name for the reference
                    dummy.LoadString(IDS_GOINREPORT_HTML);

                    s.Format(IDS_MODELGENHTML_59,
                             objectCounter,
                             (const char*)dummy,
                             (const char*)processReportPath);
                    htmlFile << s;
                }

                // create the new popup object
                s.Format(IDS_MODELGENHTML_61, objectCounter);
                htmlFile << s;

                // next object
                ++objectCounter;
            }
        }

        // javascript end here
        s.LoadString(IDS_MODELGENHTML_54);
        htmlFile << s;

        // write the hotspot table header
        s.Format(IDS_MODELGENHTML_2,
                 (const char*)pModel->GetAbsolutePath(),
                 (const char*)BuildFileNameAndPath(imageFileName, htmlFileName));
        htmlFile << s;

        // write all hot spots. Run throught the model elements and write the hotspot entities
        CString symbolHtmlFileName;
        CRect   symbolCoordinates;

        objectCounter = 1;

        // iterate through components
        for (int i = 0; i < setCount; ++i)
        {
            // get component
            CODComponent* pComp = pSet->GetAt(i);

            if (!pComp)
                continue;

            PSS_Symbol*     pSymbol     = dynamic_cast<PSS_Symbol*>(pComp);
            PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pComp);

            if (pSymbol || pLinkSymbol)
            {
                // if no sub-model, just the area for the popup
                CODModel* pOwnerModel = dynamic_cast<PSS_BasicSymbol*>(pComp)->GetOwnerModel();

                // and then, retreive the symbol position
                if (pSymbol)
                    symbolCoordinates = pComp->GetBaseRgn().GetBounds();
                else
                if (pLinkSymbol->GetNumLabels() > 0)
                    symbolCoordinates = pLinkSymbol->GetLabel(0)->GetBounds();
                else
                    symbolCoordinates = pLinkSymbol->GetBaseRgn().GetBounds();

                s.Format(IDS_MODELGENHTML_91,
                         objectCounter,
                         objectCounter,
                         (const char*)g_PSSLeftTarget,
                         symbolCoordinates.left,
                         symbolCoordinates.top,
                         symbolCoordinates.right,
                         symbolCoordinates.bottom);
                htmlFile << s;

                // next object
                ++objectCounter;
            }
        }

        // write the hotspot table footer
        s.LoadString(IDS_MODELGENHTML_4);
        htmlFile << s;

        // write the footer
        s.LoadString(IDS_MODELGENHTML_5);
        htmlFile << s;

        htmlFile.CloseFile();
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileNameForPrinter))
    {
        // refresh Setup Copyfile Window
        m_FileGenerateWindow.SetDestination(htmlFileNameForPrinter);
        m_FileGenerateWindow.UpdateWindow();

        // dispatch Windows messages
        if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
        {
            ::GetMessage(&msg, NULL, NULL, NULL);
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        // create the printable HTML file
        PSS_HtmlFile printableHtmlFile(htmlFileNameForPrinter);

        if (!printableHtmlFile.OpenFileCreate())
            return false;

        CString s;

        // write header
        s.Format(IDS_MODELGENHTML_1,
                 (const char*)pModel->GetAbsolutePath(),
                 (const char*)PSS_Date::GetToday().GetStandardFormattedDate());
        printableHtmlFile << s;

        s.Format(IDS_MODELGENHTML_16, (const char*)BuildFileNameAndPath(imageFileName, htmlFileName));
        printableHtmlFile << s;

        // write the footer
        s.LoadString(IDS_MODELGENHTML_5);
        printableHtmlFile << s;

        printableHtmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateIndexPage(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return false;

    // get the root html file name
    m_RootHtmlFileName = BuildModelHTMLFileName(pModel, _T("Index_"));
    m_RootName = pModel->GetAbsolutePath();

    // get the main index.htm pages
    m_IndexHtmlFileName = BuildModelHTMLFileNameIndex();

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(m_IndexHtmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process message loop
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(m_IndexHtmlFileName))
    {
        PSS_HtmlFile htmlFile(m_IndexHtmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        CString s;

        // write the complete html file with reference to the main banner and the main index pages
        s.Format(IDS_MODELGENHTML_66,
                 (const char*)BuildFileNameAndPath(BuildModelHTMLFileNameBanner(), m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(m_RootHtmlFileName, m_RootHtmlFileName));
        htmlFile << s;

        htmlFile.CloseFile();
    }

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(m_RootHtmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    // process message loop
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(m_RootHtmlFileName))
    {
        PSS_HtmlFile htmlFile(m_RootHtmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        CString s;

        // write header
        s.Format(IDS_MODELGENHTML_1,
                 (const char*)pModel->GetAbsolutePath(),
                 (const char*)PSS_Date::GetToday().GetStandardFormattedDate());
        htmlFile << s;

        s.Format(IDS_MODELGENHTML_68, (const char*)g_White);
        htmlFile << s;

        // write the model name table header
        s.LoadString(IDS_MODELGENHTML_18a);
        htmlFile << s;

        // write the model name
        htmlFile << pModel->GetModelName();

        // write the model name table footer
        s.LoadString(IDS_MODELGENHTML_22);
        htmlFile << s;

        // write the table header
        s.LoadString(IDS_MODELGENHTML_19);
        htmlFile << s;

        CString subModelHtmlFileName;

        // write all links to all root pages
        if (pModel->GetPageSet())
        {
            PSS_ProcessGraphModelMdl::IProcessGraphPageIterator it(pModel->GetPageSet());

            // iterate through all pages if there are
            for (ZDProcessGraphPage* pPage = it.GetFirst(); pPage; pPage = it.GetNext())
                if (pPage->GetModel())
                {
                    // get page model
                    PSS_ProcessGraphModelMdl* pPageModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pPage->GetModel());
                    ASSERT(pPageModel);

                    GenerateModel(pPageModel);

                    // get the html file name for the reference
                    subModelHtmlFileName = BuildModelHTMLFileName(pPageModel);

                    s.LoadString(IDS_MODELGENHTML_20);
                    htmlFile << s;

                    s.LoadString(IDS_MODELGENHTML_24);
                    htmlFile << s;

                    if (!GenerateFrameMainModelPage(pPageModel, subModelHtmlFileName))
                        return false;

                    s.Format(IDS_MODELGENHTML_25,
                             (const char*)BuildFileNameAndPath(BuildModelHTMLFileNameMainFrame(pPageModel),
                             m_RootHtmlFileName),
                             (const char*)pPage->GetPageName());
                    htmlFile << s;
                }
        }

        // write blank lines
        s.LoadString(IDS_MODELGENHTML_75);
        htmlFile << s;

        // if a main user group is defined, generate the user group page
        if (pModel->GetMainUserGroup())
        {
            // generate the frame for the system page
            if (!GenerateFrameEmptyUserPage())
                return false;

            if (!GenerateFrameUserPage(pModel))
                return false;

            s.LoadString(IDS_MODELGENHTML_28);
            htmlFile << s;

            s.LoadString(IDS_MODELGENHTML_20);
            htmlFile << s;

            s.LoadString(IDS_MODELGENHTML_24);
            htmlFile << s;

            // get the html FileName for the reference
            const CString htmlFileName = BuildModelHTMLFileNameUserMainFrame();

            s.Format(IDS_MODELGENHTML_25,
                     (const char*)BuildFileNameAndPath(htmlFileName, m_RootHtmlFileName),
                     (const char*)pModel->GetMainUserGroup()->GetEntityName());
            htmlFile << s;

            if (!GenerateUnitGroupPage(pModel))
                return false;
        }

        // write blank lines
        s.LoadString(IDS_MODELGENHTML_75);
        htmlFile << s;

        // if a main logical system is defined, generate the logical system page
        if (pModel->GetMainLogicalSystem())
        {
            // generate the frame for the system page
            if (!GenerateFrameEmptySystemPage())
                return false;

            if (!GenerateFrameSystemPage(pModel))
                return false;

            s.LoadString(IDS_MODELGENHTML_29);
            htmlFile << s;

            s.LoadString(IDS_MODELGENHTML_20);
            htmlFile << s;

            s.LoadString(IDS_MODELGENHTML_24);
            htmlFile << s;

            // get the html FileName for the reference
            const CString htmlFileName = BuildModelHTMLFileNameSystemMainFrame();

            s.Format(IDS_MODELGENHTML_25,
                     (const char*)BuildFileNameAndPath(htmlFileName, m_RootHtmlFileName),
                     (const char*)pModel->GetMainLogicalSystem()->GetEntityName());
            htmlFile << s;

            if (!GenerateLogicalSystemPage(pModel))
                return false;
        }

        // write blank lines
        s.LoadString(IDS_MODELGENHTML_75);
        htmlFile << s;

        // if a main logical prestations is defined, generate the logical prestations page
        if (pModel->GetMainLogicalPrestations())
        {
            // generate the frame for the prestations page
            if (!GenerateFrameEmptyPrestationsPage())
                return false;

            if (!GenerateFramePrestationsPage(pModel))
                return false;

            s.LoadString(IDS_MODELGENHTML_80);
            htmlFile << s;

            s.LoadString(IDS_MODELGENHTML_20);
            htmlFile << s;

            s.LoadString(IDS_MODELGENHTML_24);
            htmlFile << s;

            // get the html FileName for the reference
            const CString htmlFileName = BuildModelHTMLFileNamePrestationsMainFrame();

            s.Format(IDS_MODELGENHTML_25,
                     (const char*)BuildFileNameAndPath(htmlFileName, m_RootHtmlFileName),
                     (const char*)pModel->GetMainLogicalPrestations()->GetEntityName());
            htmlFile << s;

            if (!GenerateLogicalPrestationsPage(pModel))
                return false;
        }

        // write blank lines
        s.LoadString(IDS_MODELGENHTML_75);
        htmlFile << s;

        // if a main logical rule is defined, generate the rule book
        if (pModel->GetMainLogicalRules() && m_pInfo->GetIncludeRuleBook())
        {
            s.LoadString(IDS_RULEBOOK_MTL_HTML_1);
            htmlFile << s;

            s.LoadString(IDS_MODELGENHTML_20);
            htmlFile << s;

            s.LoadString(IDS_MODELGENHTML_24);
            htmlFile << s;

            s.Format(IDS_MODELGENHTML_25,
                     _T("RuleBook.htm"),
                     (const char*)pModel->GetMainLogicalRules()->GetEntityName());
            htmlFile << s;

            s.LoadString(IDS_MODELGENHTML_20);
            htmlFile << s;

            s.LoadString(IDS_MODELGENHTML_24);
            htmlFile << s;

            CString ruleBookDetailsTitle = _T("");
            ruleBookDetailsTitle.LoadString(IDS_RULEBOOKDETAILS_MTL_HTML_6);

            s.Format(IDS_MODELGENHTML_25,
                     _T("RuleBookDetails.htm"),
                     (const char*)ruleBookDetailsTitle);
            htmlFile << s;
        }

        // write blank lines
        s.LoadString(IDS_MODELGENHTML_75);
        htmlFile << s;

        // write the table footer and end of html file
        s.LoadString(IDS_MODELGENHTML_21);
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateFrameMainModelPage(PSS_ProcessGraphModelMdl* pModel,
                                                             const CString&            modelHtmlPage)
{
    if (!pModel)
        return false;

    // generate the main frame html page for the model
    const CString htmlFileName = BuildModelHTMLFileNameMainFrame(pModel);

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        CString s;

        // write header
        s.Format(IDS_MODELGENHTML_69,
                 (const char*)BuildFileNameAndPath(BuildModelHTMLFileNameEmptyPropertyPage(), m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(modelHtmlPage, m_RootHtmlFileName));
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateFrameUserPage(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return false;

    // generate the main banner.htm pages
    const CString htmlFileName = BuildModelHTMLFileNameUserMainFrame();

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process the Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating twice it
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        CString s;

        // write header
        s.Format(IDS_MODELGENHTML_69,
                 (const char*)BuildFileNameAndPath(BuildModelHTMLFileNameUnit(pModel), m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(BuildModelHTMLFileNameEmptyUser(), m_RootHtmlFileName));
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateFrameSystemPage(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return false;

    // generate the main banner.htm pages
    const CString htmlFileName = BuildModelHTMLFileNameSystemMainFrame();

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        CString s;

        // write header
        s.Format(IDS_MODELGENHTML_69,
                 (const char*)BuildFileNameAndPath(BuildModelHTMLFileNameSystem(pModel), m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(BuildModelHTMLFileNameEmptySystem(), m_RootHtmlFileName));
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateFramePrestationsPage(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return false;

    // generate the main banner.htm pages
    const CString htmlFileName = BuildModelHTMLFileNamePrestationsMainFrame();

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        CString s;

        // write header
        s.Format(IDS_MODELGENHTML_78,
                 (const char*)BuildFileNameAndPath(BuildModelHTMLFileNamePrestations(pModel), m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(BuildModelHTMLFileNameEmptyPrestations(), m_RootHtmlFileName));
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateFrameEmptyUserPage()
{
    // generate the empty user page
    const CString htmlFileName = BuildModelHTMLFileNameEmptyUser();

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        CString s;

        // write header
        s.LoadString(IDS_MODELGENHTML_70);
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateFrameEmptySystemPage()
{
    // generate the empty user page
    const CString htmlFileName = BuildModelHTMLFileNameEmptySystem();

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        CString s;

        // write header
        s.LoadString(IDS_MODELGENHTML_71);
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateFrameEmptyPrestationsPage()
{
    // generate the empty user page
    const CString htmlFileName = BuildModelHTMLFileNameEmptyPrestations();

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        CString s;

        // write header
        s.LoadString(IDS_MODELGENHTML_81);
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateEmptyPropertyPage()
{
    // generate the empty user page
    const CString htmlFileName = BuildModelHTMLFileNameEmptyPropertyPage();

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        CString s;

        // write header
        s.LoadString(IDS_MODELGENHTML_72);
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateBannerPage(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return false;

    // generate the main banner.htm pages
    const CString bannerHtmlFileName = BuildModelHTMLFileNameBanner();

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(bannerHtmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(bannerHtmlFileName))
    {
        PSS_HtmlFile htmlFile(bannerHtmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        CString s;

        // write header
        s.Format(IDS_MODELGENHTML_1,
                 (const char*)pModel->GetAbsolutePath(),
                 (const char*)PSS_Date::GetToday().GetStandardFormattedDate());
        htmlFile << s;

        s.Format(IDS_MODELGENHTML_68, (const char*)g_White);
        htmlFile << s;

        // write the copyright table with the processsoft image jpg
        s.LoadString(IDS_MODELGENHTML_12);
        htmlFile << s;

        // build the logo image file name
        CString logoImage  = m_ImageDirectory + _T("\\");
                logoImage += m_InternalLogoFileName.IsEmpty() ? g_LogoImageFile : m_InternalLogoFileName;

        const CString ref = m_pInfo->GetHyperLink().IsEmpty() ? _T("http://www.processsoft.com") : m_pInfo->GetHyperLink();

        s.Format(IDS_MODELGENHTML_13,
                 (const char*)ref,
                 (const char*)BuildFileNameAndPath(logoImage, m_RootHtmlFileName));
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_14);
        htmlFile << s;

        // write the navigation table header
        s.LoadString(IDS_MODELGENHTML_6);
        htmlFile << s;

        // write the ref to root
        logoImage = m_ImageDirectory + _T("\\") + g_HomeImageFile;

        CString dummy;
        dummy.LoadString(IDS_INDEXPAGE_HTML);

        s.Format(IDS_MODELGENHTML_7,
                 (const char*)BuildFileNameAndPath(m_RootHtmlFileName, m_RootHtmlFileName),
                 (const char*)g_PSSMainTarget,
                 (const char*)BuildFileNameAndPath(logoImage, m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(m_RootHtmlFileName, m_RootHtmlFileName),
                 (const char*)g_PSSMainTarget,
                 (const char*)dummy);
        htmlFile << s;

        // write the navigation table header
        s.LoadString(IDS_MODELGENHTML_8);
        htmlFile << s;

        // write the model name table footer
        s.LoadString(IDS_MODELGENHTML_9);
        htmlFile << s;

        // write the table footer and end of html file
        s.LoadString(IDS_MODELGENHTML_21);
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateUnitGroupPage(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return false;

    // build the html FileName
    const CString htmlFileName = BuildModelHTMLFileNameUnit(pModel);

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        // get the style and the javascript FileNames
        const CString cssHtmlFileName = m_IncludeDirectory + _T("\\") + g_TreeCSSFile;
        const CString jsHtmlFileName  = m_IncludeDirectory + _T("\\") + g_TreeJSFile;

        CString s;

        // write header
        s.Format(IDS_MODELGENHTML_23,
                 (const char*)BuildFileNameAndPath(cssHtmlFileName, m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(jsHtmlFileName,  m_RootHtmlFileName));
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_26);
        htmlFile << s;

        // add the style to the menu
        const CString plusHtmlFileName  = m_ImageDirectory + _T("\\") + g_PlusImageFile;
        const CString minusHtmlFileName = m_ImageDirectory + _T("\\") + g_MinusImageFile;
        const CString userHtmlFileName  = m_ImageDirectory + _T("\\") + g_UsersImageFile;

        s.Format(IDS_MODELGENHTML_64,
                 (const char*)BuildFileNameAndPath(userHtmlFileName,  m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(minusHtmlFileName, m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(plusHtmlFileName,  m_RootHtmlFileName),
                 (const char*)g_PSSRightTarget);
        htmlFile << s;

        if (!GenerateUnitObjects(pModel->GetMainUserGroup(), &htmlFile))
        {
            htmlFile.CloseFile();
            return false;
        }

        // body and end of html
        s.Format(IDS_MODELGENHTML_27, (const char*)g_White);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_53);
        htmlFile << s;

        // generate the tree control
        s.LoadString(IDS_MODELGENHTML_67);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_54);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_65);
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateLogicalSystemPage(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return false;

    // build the html FileName
    const CString htmlFileName = BuildModelHTMLFileNameSystem(pModel);

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        // get the style and the javascript file names
        const CString cssHtmlFileName = m_IncludeDirectory + _T("\\") + g_TreeCSSFile;
        const CString jsHtmlFileName  = m_IncludeDirectory + _T("\\") + g_TreeJSFile;

        CString s;

        // write header
        s.Format(IDS_MODELGENHTML_23,
                 (const char*)BuildFileNameAndPath(cssHtmlFileName, m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(jsHtmlFileName, m_RootHtmlFileName));
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_26);
        htmlFile << s;

        const CString plusHtmlFileName   = m_ImageDirectory + _T("\\") + g_PlusImageFile;
        const CString minusHtmlFileName  = m_ImageDirectory + _T("\\") + g_MinusImageFile;
        const CString systemHtmlFileName = m_ImageDirectory + _T("\\") + g_LogicalSystemImageFile;

        s.Format(IDS_MODELGENHTML_64,
                 (const char*)BuildFileNameAndPath(systemHtmlFileName, m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(minusHtmlFileName,  m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(plusHtmlFileName,   m_RootHtmlFileName),
                 (const char*)g_PSSRightTarget);
        htmlFile << s;

        if (!GenerateLogicalSystemObjects(pModel->GetMainLogicalSystem(), &htmlFile))
        {
            htmlFile.CloseFile();
            return false;
        }

        // body and end of html
        s.Format(IDS_MODELGENHTML_27, (const char*)g_White);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_53);
        htmlFile << s;

        // generate the tree control
        s.LoadString(IDS_MODELGENHTML_67);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_54);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_65);
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateLogicalPrestationsPage(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return false;

    // build the html FileName
    const CString htmlFileName = BuildModelHTMLFileNamePrestations(pModel);

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        // retreive the style and the javascript FileNames
        const CString cssHtmlFileName = m_IncludeDirectory + _T("\\") + g_TreeCSSFile;
        const CString jsHtmlFileName  = m_IncludeDirectory + _T("\\") + g_TreeJSFile;

        CString s;

        // write header
        s.Format(IDS_MODELGENHTML_23,
                 (const char*)BuildFileNameAndPath(cssHtmlFileName, m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(jsHtmlFileName,  m_RootHtmlFileName));
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_26);
        htmlFile << s;

        const CString plusHtmlFileName        = m_ImageDirectory + _T("\\") + g_PlusImageFile;
        const CString minusHtmlFileName       = m_ImageDirectory + _T("\\") + g_MinusImageFile;
        const CString prestationsHtmlFileName = m_ImageDirectory + _T("\\") + g_LogicalPrestationsImageFile;

        s.Format(IDS_MODELGENHTML_64,
                 (const char*)BuildFileNameAndPath(prestationsHtmlFileName, m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(minusHtmlFileName,       m_RootHtmlFileName),
                 (const char*)BuildFileNameAndPath(plusHtmlFileName,        m_RootHtmlFileName),
                 (const char*)g_PSSRightTarget);
        htmlFile << s;

        if (!GenerateLogicalPrestationsObjects(pModel->GetMainLogicalPrestations(), &htmlFile))
        {
            htmlFile.CloseFile();
            return false;
        }

        // body and end of html
        s.Format(IDS_MODELGENHTML_27, (const char*)g_White);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_53);
        htmlFile << s;

        // generate the tree control
        s.LoadString(IDS_MODELGENHTML_67);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_54);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_65);
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateUnitObjects(ZBUserGroupEntity* pGroupEntity, PSS_HtmlFile* pHtmlFile)
{
    if (!pGroupEntity || !pHtmlFile)
        return false;

    m_IndexItem = 0;

    return GenerateUnitGroupObjects(pGroupEntity, pHtmlFile, m_IndexItem);
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateUnitGroupObjects(ZBUserGroupEntity* pGroupEntity,
                                                           PSS_HtmlFile*      pHtmlFile,
                                                           std::size_t        parentID)
{
    ++m_IndexItem;

    const std::size_t currentItem = m_IndexItem;
    const CString     refFile     = GenerateUserGroupList(pGroupEntity);

    CString s;

    s.Format(IDS_MODELGENHTML_30,
             m_IndexItem,
             parentID,
             (const char*)pGroupEntity->GetEntityName(),
             refFile.IsEmpty() ? _T("null") : (const char*)BuildFileNameAndPath(refFile, m_RootHtmlFileName));

    *pHtmlFile << s;

    if (pGroupEntity->ContainEntity())
    {
        const int count = pGroupEntity->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            ZBUserEntity* pEntity = pGroupEntity->GetEntityAt(i);

            if (!pEntity)
                continue;

            ZBUserGroupEntity* pUserGroupEntity = dynamic_cast<ZBUserGroupEntity*>(pEntity);

            if (pUserGroupEntity)
                GenerateUnitGroupObjects(pUserGroupEntity, pHtmlFile, currentItem);

            ZBUserRoleEntity* pUserRoleEntity = dynamic_cast<ZBUserRoleEntity*>(pEntity);

            if (pUserRoleEntity)
                GenerateUnitRoleObjects(pUserRoleEntity, pHtmlFile, currentItem);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateUnitRoleObjects(ZBUserRoleEntity* pRoleEntity,
                                                          PSS_HtmlFile*     pHtmlFile,
                                                          std::size_t       parentID)
{
    ++m_IndexItem;

    CString s;

    s.Format(IDS_MODELGENHTML_30,
             m_IndexItem,
             parentID,
             (const char*)pRoleEntity->GetEntityName(),
             _T("null"));
    *pHtmlFile << s;

    return true;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::GenerateUserGroupList(ZBUserGroupEntity* pGroupEntity)
{
    if (!pGroupEntity)
        return _T("");

    // extract the symbols for which this user group is assigned to
    ZUExtractModelUnitGroupAssigned extract(m_pModel, pGroupEntity);
    extract.Navigate();

    // build the html FileName
    CString htmlFileName = BuildHTMLFileNameUser(pGroupEntity);

    // refresh setup copy file window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return _T("");

        CString s;
        CString s1;

        // write the header and the document title
        s1.LoadString(IDS_USERGROUP_HTML);
        s.Format(IDS_MODELGENHTML_31, (const char*)s1);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_36);
        htmlFile << s;

        s.Format(IDS_MODELGENHTML_37, (const char*)s1);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_38);
        htmlFile << s;

        const CString entityname = (const char*)pGroupEntity->GetEntityName();

        // build Conceptor file name
        if (m_pInfo->GetIncludeConceptor())
        {
            const CString fileName = BuildConceptorHTMLFileName(entityname);

            htmlFile << _T("<a href=\"") + fileName + _T("\">");
            htmlFile << entityname;
            htmlFile << _T("</a>");
        }
        else
            // write the unit name
            htmlFile << pGroupEntity->GetEntityName();

        s.LoadString(IDS_MODELGENHTML_76);
        htmlFile << s;

        // Write the model name
        htmlFile << m_pModel->GetAbsolutePath();

        s.LoadString(IDS_MODELGENHTML_32);
        htmlFile << s;

        CODComponentIterator it(&extract.GetComponentSet());

        // iterate through the symbol list and build the page
        for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
        {
            if (ISA(pComp, PSS_Symbol) || ISA(pComp, PSS_LinkSymbol))
            {
                PSS_BasicSymbol* pBasicSym = dynamic_cast<PSS_BasicSymbol*>(pComp);
                ASSERT(pBasicSym);

                CString                   htmlFileNameOwnerModel;
                CString                   symbolPath(_T("#NA"));
                PSS_ProcessGraphModelMdl* pOwnerModel =
                        dynamic_cast<PSS_ProcessGraphModelMdl*>(pBasicSym->GetOwnerModel());

                if (pOwnerModel)
                {
                    htmlFileNameOwnerModel = BuildModelHTMLFileName(pOwnerModel);
                    symbolPath             = pOwnerModel->GetAbsolutePath();
                }

                // if no reference
                if (htmlFileNameOwnerModel.IsEmpty())
                    s.Format(IDS_MODELGENHTML_35,
                             (const char*)pBasicSym->GetSymbolName(),
                             (const char*)symbolPath);
                else
                    s.Format(IDS_MODELGENHTML_33,
                             (const char*)BuildFileNameAndPath(htmlFileNameOwnerModel, m_RootHtmlFileName),
                             (const char*)pBasicSym->GetSymbolName(),
                             (const char*)symbolPath);

                htmlFile << s;
            }
        }

        s.LoadString(IDS_MODELGENHTML_34);
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return htmlFileName;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateLogicalSystemObjects(ZBLogicalSystemEntity* pSystemEntity, PSS_HtmlFile* pHtmlFile)
{
    if (!pSystemEntity || !pHtmlFile)
        return false;

    m_IndexItem = 0;

    return GenerateLogicalSystemObjects(pSystemEntity, pHtmlFile, m_IndexItem);
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateLogicalSystemObjects(ZBLogicalSystemEntity* pSystemEntity,
                                                               PSS_HtmlFile*          pHtmlFile,
                                                               std::size_t            parentID)
{
    if (!pSystemEntity || !pHtmlFile)
        return false;

    ++m_IndexItem;

    const std::size_t currentItem = m_IndexItem;
    const CString     refFile     = GenerateLogicalSystemList(pSystemEntity);

    CString s;
    s.Format(IDS_MODELGENHTML_30,
             m_IndexItem,
             parentID,
             (const char*)pSystemEntity->GetEntityName(),
             refFile.IsEmpty() ? _T("null") : (const char*)BuildFileNameAndPath(refFile, m_RootHtmlFileName));

    *pHtmlFile << s;

    if (pSystemEntity->ContainEntity())
    {
        const int count = pSystemEntity->GetEntityCount();

        // iterate through entities
        for (int i = 0; i < count; ++i)
        {
            // get entity
            ZBSystemEntity* pEntity = pSystemEntity->GetEntityAt(i);

            if (!pEntity)
                continue;

            ZBLogicalSystemEntity* pLogicalEntity = dynamic_cast<ZBLogicalSystemEntity*>(pEntity);

            if (pLogicalEntity)
                GenerateLogicalSystemObjects(pLogicalEntity, pHtmlFile, currentItem);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::GenerateLogicalSystemList(ZBLogicalSystemEntity* pSystemEntity)
{
    if (!pSystemEntity)
        return _T("");

    // extract the symbols for which this logical system is assigned to
    ZUExtractModelLogicalSystemAssigned extract(m_pModel, pSystemEntity);
    extract.Navigate();

    // build the html FileName
    const CString htmlFileName = BuildHTMLFileNameLogicalSystem(pSystemEntity);

    // refresh Setup Copyfile Window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return _T("");

        CString s;
        CString s1;

        // write the header and the document title
        s1.LoadString(IDS_LOGICALSYSTEM_HTML);
        s.Format(IDS_MODELGENHTML_31, (const char*)s1);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_36);
        htmlFile << s;

        s.Format(IDS_MODELGENHTML_37, (const char*)s1);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_38);
        htmlFile << s;

        // write the unit name
        htmlFile << pSystemEntity->GetEntityName();
        s.LoadString(IDS_MODELGENHTML_76);
        htmlFile << s;

        // write the model name
        htmlFile << m_pModel->GetAbsolutePath();

        s.LoadString(IDS_MODELGENHTML_32);
        htmlFile << s;

        CODComponentIterator it(&extract.GetComponentSet());

        // iterate through the list of symbols and build the page
        for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
        {
            if (ISA(pComp, PSS_Symbol) || ISA(pComp, PSS_LinkSymbol))
            {
                PSS_BasicSymbol* pBasicSym = dynamic_cast<PSS_BasicSymbol*>(pComp);
                ASSERT(pBasicSym);

                CString                   htmlFileNameOwnerModel;
                CString                   symbolPath(_T("#NA"));
                PSS_ProcessGraphModelMdl* pOwnerModel =
                        dynamic_cast<PSS_ProcessGraphModelMdl*>(pBasicSym->GetOwnerModel());

                if (pOwnerModel)
                {
                    htmlFileNameOwnerModel = BuildModelHTMLFileName(pOwnerModel);
                    symbolPath             = pOwnerModel->GetAbsolutePath();
                }

                // if no reference
                if (htmlFileNameOwnerModel.IsEmpty())
                    s.Format(IDS_MODELGENHTML_35,
                             (const char*)pBasicSym->GetSymbolName(),
                             (const char*)symbolPath);
                else
                    s.Format(IDS_MODELGENHTML_33,
                             (const char*)BuildFileNameAndPath(htmlFileNameOwnerModel, m_RootHtmlFileName),
                             (const char*)pBasicSym->GetSymbolName(),
                             (const char*)symbolPath);

                htmlFile << s;
            }
        }

        s.LoadString(IDS_MODELGENHTML_34);
        htmlFile << s;

        htmlFile.CloseFile();

    }

    return htmlFileName;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateLogicalPrestationsObjects(ZBLogicalPrestationsEntity* pPrestationsEntity,
                                                                    PSS_HtmlFile*               pHtmlFile)
{
    if (!pPrestationsEntity || !pHtmlFile)
        return false;

    m_IndexItem = 0;

    return GenerateLogicalPrestationsObjects(pPrestationsEntity, pHtmlFile, m_IndexItem);
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GenerateLogicalPrestationsObjects(ZBLogicalPrestationsEntity* pPrestationsEntity,
                                                                    PSS_HtmlFile*               pHtmlFile,
                                                                    std::size_t                 parentID)
{
    if (!pPrestationsEntity || !pHtmlFile)
        return false;

    ++m_IndexItem;

    const std::size_t currentItem = m_IndexItem;
    const CString     refFile     = GenerateLogicalPrestationsList(pPrestationsEntity);

    CString s;
    s.Format(IDS_MODELGENHTML_30, m_IndexItem,
             parentID,
             (const char*)pPrestationsEntity->GetEntityName(),
             refFile.IsEmpty() ? _T("null") : (const char*)BuildFileNameAndPath(refFile, m_RootHtmlFileName));

    *pHtmlFile << s;

    if (pPrestationsEntity->ContainEntity())
    {
        const int count = pPrestationsEntity->GetEntityCount();

        // iterate through entities
        for (int i = 0; i < count; ++i)
        {
            // get entity
            ZBPrestationsEntity* pEntity = pPrestationsEntity->GetEntityAt(i);

            if (!pEntity)
                continue;

            ZBLogicalPrestationsEntity* pLogicalEntity = dynamic_cast<ZBLogicalPrestationsEntity*>(pEntity);

            if (pLogicalEntity)
                GenerateLogicalPrestationsObjects(pLogicalEntity, pHtmlFile, currentItem);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::GenerateLogicalPrestationsList(ZBLogicalPrestationsEntity* pPrestationsEntity)
{
    if (!pPrestationsEntity)
        return _T("");

    // get the symbols for which this prestation is assigned
    ZUExtractModelLogicalPrestationsAssigned extract(m_pModel, pPrestationsEntity);
    extract.Navigate();

    // build the html file name
    const CString htmlFileName = BuildHTMLFileNameLogicalPrestations(pPrestationsEntity);

    // refresh the info window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating it twice
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return _T("");

        CString s;
        CString s1;

        // write the header and the document title
        s1.LoadString(IDS_LOGICALPRESTATIONS_HTML);
        s.Format(IDS_MODELGENHTML_31, (const char*)s1);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_36);
        htmlFile << s;

        s.Format(IDS_MODELGENHTML_37, (const char*)s1);
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_38);
        htmlFile << s;

        // write the prestation name
        s.Format(IDS_MODELGENHTML_92,
                 BuildPrestationsReportHTMLFileName(pPrestationsEntity->GetEntityName()),
                 pPrestationsEntity->GetEntityName());
        htmlFile << s;

        s.LoadString(IDS_MODELGENHTML_76);
        htmlFile << s;

        // write the model name
        htmlFile << m_pModel->GetAbsolutePath();

        s.LoadString(IDS_MODELGENHTML_32);
        htmlFile << s;

        CODComponentIterator it(&extract.GetComponentSet());

        // iterate through the symbols and build the page
        for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
        {
            if (ISA(pComp, PSS_Symbol) || ISA(pComp, PSS_LinkSymbol))
            {
                PSS_BasicSymbol* pBasicSym = dynamic_cast<PSS_BasicSymbol*>(pComp);
                ASSERT(pBasicSym);

                CString                   htmlFileNameOwnerModel;
                CString                   symbolPath(_T("#NA"));
                PSS_ProcessGraphModelMdl* pOwnerModel =
                        dynamic_cast<PSS_ProcessGraphModelMdl*>(pBasicSym->GetOwnerModel());

                if (pOwnerModel)
                {
                    htmlFileNameOwnerModel = BuildModelHTMLFileName(pOwnerModel);
                    symbolPath             = pOwnerModel->GetAbsolutePath();
                }

                // no referential defined?
                if (htmlFileNameOwnerModel.IsEmpty())
                    s.Format(IDS_MODELGENHTML_35,
                             (const char*)pBasicSym->GetSymbolName(),
                             (const char*)symbolPath);
                else
                    s.Format(IDS_MODELGENHTML_33,
                             (const char*)BuildFileNameAndPath(htmlFileNameOwnerModel, m_RootHtmlFileName),
                             (const char*)pBasicSym->GetSymbolName(),
                             (const char*)symbolPath);

                htmlFile << s;
            }
        }

        s.LoadString(IDS_MODELGENHTML_34);
        htmlFile << s;

        htmlFile.CloseFile();
    }

    return htmlFileName;
}
//---------------------------------------------------------------------------
bool PSS_ModelGenerateImageFiles::GeneratePropertyPage(ZIProperties* pPropertiesObject, const CString& htmlFileName)
{
    if (!pPropertiesObject)
        return false;

    // refresh Setup Copyfile Window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process Windows messages
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file has already been generated, to avoid generating twice the same html file
    if (!StringAlreadyGenerated(htmlFileName))
    {
        PSS_HtmlFile htmlFile(htmlFileName);

        if (!htmlFile.OpenFileCreate())
            return false;

        // get the property set from object
        ZBPropertySet propSet;
        pPropertiesObject->FillProperties(propSet);

        CString s;
        CString s1;

        // write the header and the document title
        s1.LoadString(IDS_SYMBOLPROPERTY_HTML);
        s.Format(IDS_MODELGENHTML_39, (const char*)s1);
        htmlFile << s;

        bool oneAtLeast = false;

        ZBPropertyIterator it(&propSet);
        CString            previousCategory;

        // iterate through the property set
        for (ZBProperty* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        {
            if (!pProp->GetEnable())
                continue;

            // check if property attributes to show should be filtered
            if (m_pPropAttributes)
                // check if defined
                if (!m_pPropAttributes->FindAttribute(pProp->GetCategoryID(), pProp->GetItemID()))
                    continue;

            // flag for closing properly the html
            oneAtLeast = true;

            CString value;
            CString format;

            if (pProp->GetCategory() != previousCategory)
            {
                // previous section? Close the table section
                if (!previousCategory.IsEmpty())
                {
                    s.LoadString(IDS_MODELGENHTML_43);
                    htmlFile << s;
                }

                // add the section name
                s.LoadString(IDS_MODELGENHTML_40);
                htmlFile << s;

                s.Format(IDS_MODELGENHTML_41, (const char*)pProp->GetCategory());
                htmlFile << s;

                s.LoadString(IDS_MODELGENHTML_42);
                htmlFile << s;

                // save the category for checking changes in categories
                previousCategory = pProp->GetCategory();
            }

            // get the formatted value
            switch (pProp->GetPTValueType())
            {
                case ZBProperty::PT_DOUBLE:   value = PSS_StringFormatter::GetFormattedBuffer(pProp->GetValueDouble(),                  pProp->GetStringFormat()); break;
                case ZBProperty::PT_FLOAT:    value = PSS_StringFormatter::GetFormattedBuffer(pProp->GetValueFloat(),                   pProp->GetStringFormat()); break;
                case ZBProperty::PT_DATE:     value = PSS_StringFormatter::GetFormattedBuffer((PSS_Date&)pProp->GetValueDate(),         pProp->GetStringFormat()); break;
                case ZBProperty::PT_TIMESPAN: value = PSS_StringFormatter::GetFormattedBuffer((PSS_TimeSpan&)pProp->GetValueTimeSpan(), pProp->GetStringFormat()); break;
                case ZBProperty::PT_DURATION: value = PSS_StringFormatter::GetFormattedBuffer((PSS_Duration&)pProp->GetValueDuration(), pProp->GetStringFormat()); break;
                case ZBProperty::PT_STRING:   value = pProp->GetValueString();                                                                                     break;
                default:                                                                                                                                           break;
            }

            // remove empty spaces from properties
            if (!value.IsEmpty())
            {
                // add the label
                s.LoadString(IDS_MODELGENHTML_44);
                htmlFile << s;

                s.Format(IDS_MODELGENHTML_45, (const char*)pProp->GetLabel());
                htmlFile << s;

                // add the value
                s.LoadString(IDS_MODELGENHTML_46);
                htmlFile << s;

                s.Format(IDS_MODELGENHTML_47, (const char*)value);
                htmlFile << s;
            }
        }

        // close the table if once have been opened
        if (oneAtLeast)
        {
            s.LoadString(IDS_MODELGENHTML_43);
            htmlFile << s;
        }

        // end of HTML
        s.LoadString(IDS_MODELGENHTML_49);
        htmlFile << s;

        htmlFile.CloseFile();

        // delete all properties
        ZBPropertyIterator itDel(&propSet);

        for (ZBProperty* pProp = itDel.GetFirst(); pProp; pProp = itDel.GetNext())
            delete pProp;

        propSet.RemoveAll();
    }

    return true;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelImageFileName(PSS_ProcessGraphModelMdl* pModel) const
{
    if (!pModel)
        return _T("");

    // build the FileName using the full object path
    CString fileName  = PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\");
            fileName += ParseModelName(pModel->GetAbsolutePath());
            fileName += _T(".jpg");

    return fileName;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileName(PSS_ProcessGraphModelMdl* pModel, const CString& prefix) const
{
    if (!pModel)
        return _T("");

    // build the FileName using the full object path
    CString fileName = PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\");

    if (!prefix.IsEmpty())
        fileName += prefix;

    fileName += ParseModelName(pModel->GetAbsolutePath());
    fileName += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildModelHTMLFileNameForPrinter(PSS_ProcessGraphModelMdl* pModel) const
{
    if (!pModel)
        return _T("");

    // build the FileName using the full object path
    CString fileName  = PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\");
            fileName += ParseModelName(pModel->GetAbsolutePath());
            fileName += _T("_prt");
            fileName += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildHTMLFileNameLogicalSystem(ZBSystemEntity* pSystemEntity) const
{
    if (!pSystemEntity)
        return _T("");

    CString fileName = PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\");
    CString entityString;

    do
    {
        entityString += pSystemEntity->GetEntityName();
        entityString += _T("_");

        // get the parent
        pSystemEntity = pSystemEntity->GetParent();
    }
    while (pSystemEntity);

    fileName += ParseModelName(entityString);
    fileName += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildHTMLFileNameLogicalPrestations(ZBPrestationsEntity* pPrestationsEntity) const
{
    if (!pPrestationsEntity)
        return _T("");

    CString fileName = PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\");
    CString entityString;

    do
    {
        entityString += pPrestationsEntity->GetEntityName();
        entityString += _T("_");

        // retreive the parent
        pPrestationsEntity = pPrestationsEntity->GetParent();
    }
    while (pPrestationsEntity);

    fileName += ParseModelName(entityString);
    fileName += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildHTMLFileNameUser(ZBUserEntity* pUserEntity) const
{
    if (!pUserEntity)
        return _T("");

    CString fileName = PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\");
    CString entityString;

    do
    {
        entityString += pUserEntity->GetEntityName();
        entityString += _T( "_" );

        // get the parent
        pUserEntity = pUserEntity->GetParent();
    }
    while (pUserEntity);

    fileName += ParseModelName(entityString);
    fileName += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildConceptorHTMLFileName(const CString& entityName) const
{
    CString fileName  = _T("Conceptor_");
            fileName += ParseModelName(entityName);
            fileName += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildProcessReportHTMLFileName(const CString& processName) const
{
    CString fileName  = _T("ProcessReport_");
    fileName         += ParseModelName(processName);
    fileName         += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildPrestationsReportHTMLFileName(const CString& prestationName) const
{
    CString fileName  = _T("PrestationsReport_");
    fileName         += ParseModelName(prestationName);
    fileName         += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
CString PSS_ModelGenerateImageFiles::BuildSymbolPropertyHTMLFileName(PSS_BasicSymbol*          pSymbol,
                                                                     PSS_ProcessGraphModelMdl* pModel,
                                                                     const CString&            prefix) const
{
    if (!pSymbol)
        return _T("");

    if (!pModel)
        return _T("");

    ASSERT(m_pInfo);

    // build the file name using the full object path + the symbol name and the reference number to avoid collision
    CString fileName  = PSS_Directory::NormalizeDirectory(m_pInfo->GetURLName()) + _T("\\");
            fileName += _T("prp_");

    if (!prefix.IsEmpty())
        fileName += prefix;

    fileName += ParseModelName(pModel->GetAbsolutePath());
    fileName += _T("_");
    fileName += ParseModelName(pSymbol->GetSymbolName() + pSymbol->GetSymbolReferenceNumberStr());
    fileName += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
