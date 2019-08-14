/****************************************************************************
 * ==> PSS_SoapPublishModelGenerateFiles -----------------------------------*
 ****************************************************************************
 * Description : Publish the model generated files to Messenger through a   *
 *               SOAP protocol, and check the publication validity          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SoapPublishModelGenerateFiles.h"

// processsoft
#include "zBaseLib\ZDirectory.h"
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\ZBServer.h"
#include "zBaseLib\ZILog.h"
#include "zConversion\PSS_StringTools.h"
#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ProcGraphModelVp.h"
#include "zModel\ProcGraphModelCtlr.h"
#include "zModel\ZBInfoModelGraphicGeneration.h"
#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "zModel\ZBGenericSymbolErrorLine.h"
#include "ZBPublishMessengerModelInformation.h"
#include "zSOAP\PSS_SoapData_Settings.h"
#include "zWeb\PSS_HtmlFile.h"
#include "ZBBPStartSymbol.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
const CString g_HomeImageFile   = _T("home.jpg");
const CString g_ParentImageFile = _T("parent.gif");
//---------------------------------------------------------------------------
// PSS_SoapPublishModelGenerateFiles
//---------------------------------------------------------------------------
PSS_SoapPublishModelGenerateFiles::PSS_SoapPublishModelGenerateFiles(ZDProcessGraphModelMdl*             pModel,
                                                                     void*                               pClass,
                                                                     ZBPublishMessengerModelInformation* pInfo) :
    ZUModelNavigation(pModel, pClass),
    m_pModelInfo(pInfo)
{}
//---------------------------------------------------------------------------
PSS_SoapPublishModelGenerateFiles::~PSS_SoapPublishModelGenerateFiles()
{}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelGenerateFiles::OnStart()
{
    if (!m_pClass)
        return false;

    // get class info
    m_pInfo = static_cast<ZBInfoModelGraphicGeneration*>(m_pClass);
    ASSERT(m_pInfo);

    // copy the publication address from source info
    if (m_pModelInfo)
        PSS_SoapData_Settings::m_Url = (const char*)m_pModelInfo->m_MessengerAddress;

    // create the window for file generation feedback
    m_FileGenerateWindow.Create();

    // get the temp directory
    char tempDir[512];
    ::GetWindowsDirectory(tempDir, sizeof(tempDir));
    m_TargetDirectory = ZDirectory::NormalizeDirectory(tempDir) + _T("\\tempPSS");

    // create it if still not exists
    ZDirectory::CreateDirectory(m_TargetDirectory);

    // temp dir still not exists?
    if (!ZDirectory::Exist(m_TargetDirectory))
        return false;

    // change the current directory
    if (!ZDirectory::ChangeCurrentDirectory(m_TargetDirectory))
        return false;

    // publish the home image file, if it exists
    if (PSS_File::Exist(ZDirectory::NormalizeDirectory(m_pInfo->GetpServer()->GetSystemDirectory()) + _T("\\") + g_HomeImageFile))
        if (!m_PubFile.Add(PSS_SoapData_File(PSS_SoapData_File::IE_DM_PublicFolder,
                                             1,
                                             (const char*)m_pInfo->GetpServer()->GetSystemDirectory(),
                                             (const char*)g_HomeImageFile)))
            TRACE(_T("Problem publishing the Home image file\n"));

    // publish the parent image file, if it exists
    if (PSS_File::Exist(ZDirectory::NormalizeDirectory(m_pInfo->GetpServer()->GetSystemDirectory()) + _T("\\") + g_ParentImageFile))
        if (!m_PubFile.Add(PSS_SoapData_File(PSS_SoapData_File::IE_DM_PublicFolder,
                                             1,
                                             (const char*)m_pInfo->GetpServer()->GetSystemDirectory(),
                                             (const char*)g_ParentImageFile)))
            TRACE(_T("Problem publishing the Parent image file\n"));

    // reset the generated filenames array
    ResetStringsArray();

    if (!PublishModel(m_pModel))
        return false;

    // save the root html filename
    m_RootHtmlFileName = BuildModelHTMLFilename(m_pModel);
    m_RootName         = m_pModel->GetAbsolutePath();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelGenerateFiles::OnFinish()
{
    // clean the directory used to generate the files
    ZDirectory::DeleteDirectory(m_TargetDirectory, TRUE, TRUE);

    // hide the feedback dialog
    m_FileGenerateWindow.ShowWindow(SW_HIDE);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelGenerateFiles::OnSymbol(ZBSymbol* pSymbol)
{
    if (!pSymbol)
        return false;

    ASSERT(m_pInfo);

    if (pSymbol->GetChildModel() && m_pInfo->GetpDC() && m_pInfo->GetpCtlr())
        if (!PublishModel(dynamic_cast<ZDProcessGraphModelMdl*>(pSymbol->GetChildModel())))
            return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelGenerateFiles::OnLink(ZBLinkSymbol* pLink)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelGenerateFiles::PublishModel(ZDProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return false;

    ASSERT(m_pInfo);

    ZDProcessGraphModelController* pCtrl = m_pInfo->GetpCtlr();
    CDC*                           pDC   = m_pInfo->GetpDC();

    if (!pDC || !pCtrl)
        return false;

    // get the viewport
    ZIProcessGraphModelViewport* pVp = pCtrl->BrowseModel(pModel, pModel->GetParent());

    if (!pVp)
        return false;

    // export the model to the image filename
    const CString imageFilename = BuildModelImageFilename(pModel);

    // refresh Setup Copyfile Window
    m_FileGenerateWindow.SetDestination(imageFilename);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process the remaining messages in message loop
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the image was already generated to avoid generating it twice
    if (!StringAlreadyGenerated(imageFilename))
        // generate the file
        if (pVp->ExportModelToImageFile(imageFilename, *pDC))
        {
            PSS_File file(imageFilename);

            // publish the file name
            if (!m_PubFile.Add(PSS_SoapData_File(PSS_SoapData_File::IE_DM_PublicFolder,
                                                    1,
                                                    (const char*)m_TargetDirectory,
                                                    (const char*)file.GetFileName())))
                TRACE1(_T("Problem publishing the file %s\n"), (const char*)ImageFilename);
        }
        else
            TRACE1(_T("Problem exporting the file %s\n"), (const char*)ImageFilename);

    // create the html page
    CreateHtmlPage(pModel, imageFilename);

    return true;
}
//---------------------------------------------------------------------------
CString PSS_SoapPublishModelGenerateFiles::BuildModelImageFilename(ZDProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return _T("");

    // build the filename using the full object path
    CString Filename  = ZDirectory::NormalizeDirectory(m_TargetDirectory) + _T("\\");
    Filename         += ParseModelName(pModel->GetAbsolutePath());
    Filename         += _T(".jpg");

    return Filename;
}
//---------------------------------------------------------------------------
CString PSS_SoapPublishModelGenerateFiles::BuildModelHTMLFilename(ZDProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return _T("");

    // build the filename using the full object path
    CString Filename  = ZDirectory::NormalizeDirectory(m_TargetDirectory) + _T("\\");
    Filename         += ParseModelName(pModel->GetAbsolutePath());
    Filename         += _T(".htm");

    return Filename;
}
//---------------------------------------------------------------------------
CString PSS_SoapPublishModelGenerateFiles::ParseModelName(const CString& modelName)
{
    return PSS_StringTools::ConvertSpecialChar(modelName);
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelGenerateFiles::CreateHtmlPage(ZDProcessGraphModelMdl* pModel, const CString& imageFileName)
{
    if (!pModel)
        return false;

    const CString  htmlFileName = BuildModelHTMLFilename(pModel);
          PSS_File rootHtmlFile(m_RootHtmlFileName);

    // refresh Setup Copyfile Window
    m_FileGenerateWindow.SetDestination(htmlFileName);
    m_FileGenerateWindow.UpdateWindow();

    MSG msg;

    // process the remaining messages in the message loop
    if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
        ::GetMessage(&msg, NULL, NULL, NULL);
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // check if the html file was already generated to avoid generating it twice
    if (StringAlreadyGenerated(htmlFileName))
        return true;

    PSS_HtmlFile htmlFile(htmlFileName);
    
    if (!htmlFile.OpenFileCreate())
        return false;

    CString s;

    // write header
    s.Format(IDS_SOAPMODELGENHTML_1,
             (const char*)pModel->GetAbsolutePath(),                     // model path
             (const char*)ZBDate::GetToday().GetStandardFormatedDate()); // current date

    htmlFile << s;

    s.LoadString(IDS_SOAPMODELGENHTML_14);
    htmlFile << s;

    // write the navigation table header
    s.LoadString(IDS_SOAPMODELGENHTML_6);
    htmlFile << s;

    // write the ref to root
    s.Format(IDS_SOAPMODELGENHTML_7,
             (const char*)rootHtmlFile.GetFileName(), // root filename
             (const char*)g_HomeImageFile,            // logo filename
             (const char*)rootHtmlFile.GetFileName(), // root filename
             (const char*)m_RootName);                // root name

    htmlFile << s;

    // write the parent if there is one
    if (pModel->GetParent())
    {
        // get the parent html filename and name
        const CString  parentHtmlFileName = BuildModelHTMLFilename(pModel->GetParent());
              PSS_File parentHtmlFile(parentHtmlFileName);
        const CString  ParentName         = pModel->GetParent()->GetAbsolutePath();

        s.Format(IDS_SOAPMODELGENHTML_11,
                 (const char*)parentHtmlFile.GetFileName(), // root filename
                 (const char*)g_ParentImageFile,            // logo filename
                 (const char*)parentHtmlFile.GetFileName(), // root filename
                 (const char*)ParentName);                  // root name

        htmlFile << s;
    }
    else
    {
        s.LoadString(IDS_SOAPMODELGENHTML_8);
        htmlFile << s;
    }

    // write the navigation table footer
    s.LoadString(IDS_SOAPMODELGENHTML_9);
    htmlFile << s;

    // write the break line
    s.LoadString(IDS_SOAPMODELGENHTML_10);
    htmlFile << s;

    // write the hotspot table header
    PSS_File image(imageFileName);

    s.Format(IDS_SOAPMODELGENHTML_2,
             (const char*)pModel->GetAbsolutePath(), // object name
             (const char*)image.GetFileName());      // image file

    htmlFile << s;

    // write all hot spots. Run throught the model elements and write the hotspot entities
    CString symbolHtmlFileName;
    CRect   symbolCoordinates;

    // process the model components
    CODComponentSet* pSet = pModel->GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
            continue;

        ZBSymbol* pCompSym = dynamic_cast<ZBSymbol*>(pComp);

        // has a sub-model defined?
        if (pCompSym && pCompSym->GetChildModel())
        {
            // get the html filename for the reference
            symbolHtmlFileName = BuildModelHTMLFilename(dynamic_cast<ZDProcessGraphModelMdl*>(pCompSym->GetChildModel()));

            PSS_File symbol(symbolHtmlFileName);

            // get the symbol position
            symbolCoordinates = pComp->GetBaseRgn().GetBounds();

            s.Format(IDS_SOAPMODELGENHTML_3,
                     symbolCoordinates.left,
                     symbolCoordinates.top,
                     symbolCoordinates.right,
                     symbolCoordinates.bottom,
                     (const char*)symbol.GetFileName());

            htmlFile << s;

            continue;
        }

        ZBBPStartSymbol* pStartCompSym = dynamic_cast<ZBBPStartSymbol*>(pComp);

        // if it is a start symbol, then create the hot spot for starting a new process
        if (pStartCompSym)
        {
            // get the symbol position
            symbolCoordinates = pComp->GetBaseRgn().GetBounds();

            s.Format(IDS_SOAPMODELGENHTML_17,
                        symbolCoordinates.left,
                        symbolCoordinates.top,
                        symbolCoordinates.right,
                        symbolCoordinates.bottom,
                        pStartCompSym->GetSymbolReferenceNumber());

            htmlFile << s;
        }
    }

    // write the hotspot table footer
    s.LoadString(IDS_SOAPMODELGENHTML_4);
    htmlFile << s;

    // write the footer
    s.LoadString(IDS_SOAPMODELGENHTML_5);
    htmlFile << s;

    htmlFile.CloseFile();

    #ifdef _DEBUG
        s.Format(_T(" HTML File = %s\n"), (const char*)htmlFileName);
        TRACE(s);
    #endif

    // log the published file name
    if (m_pLog && m_pLog->IsInDebugMode())
    {
        CString message;
        message.Format(IDS_AL_PUBLISHHTMLFILE, (const char*)htmlFileName);
        ZBGenericSymbolErrorLine e(message);
        m_pLog->AddLine(e);
    }

    PSS_File file(htmlFileName);

    // publish the file name
    if (!m_PubFile.Add(PSS_SoapData_File(PSS_SoapData_File::IE_DM_PublicFolder,
                                         1,
                                         (const char*)m_TargetDirectory,
                                         (const char*)file.GetFileName())))
        TRACE(_T("Problem publishing html file\n"));

    return true;
}
//---------------------------------------------------------------------------
