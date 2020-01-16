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
#include "zBaseLib\PSS_Directory.h"
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\PSS_Server.h"
#include "zBaseLib\PSS_Log.h"
#include "zConversion\PSS_StringTools.h"
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_ProcessGraphModelController.h"
#include "zModel\PSS_ProcessGraphModelViewport.h"
#include "zModel\PSS_InfoModelGraphicGeneration.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
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
PSS_SoapPublishModelGenerateFiles::PSS_SoapPublishModelGenerateFiles(PSS_ProcessGraphModelMdl*           pModel,
                                                                     void*                               pClass,
                                                                     ZBPublishMessengerModelInformation* pInfo) :
    PSS_ModelNavigation(pModel, pClass),
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
    m_pInfo = static_cast<PSS_InfoModelGraphicGeneration*>(m_pClass);
    ASSERT(m_pInfo);

    // copy the publication address from source info
    if (m_pModelInfo)
        PSS_SoapData_Settings::m_Url = (const char*)m_pModelInfo->m_MessengerAddress;

    // create the window for file generation feedback
    m_FileGenerateWindow.Create();

    char tempDir[512];

    // get the temp directory
    ::GetWindowsDirectory(tempDir, sizeof(tempDir));
    m_TargetDirectory = PSS_Directory::NormalizeDirectory(tempDir) + _T("\\tempPSS");

    // create it if still not exists
    PSS_Directory::CreateDirectory(m_TargetDirectory);

    // temp dir still not exists?
    if (!PSS_Directory::Exist(m_TargetDirectory))
        return false;

    // change the current directory
    if (!PSS_Directory::ChangeCurrentDirectory(m_TargetDirectory))
        return false;

    // publish the home image file, if it exists
    if (PSS_File::Exist(PSS_Directory::NormalizeDirectory(m_pInfo->GetServer()->GetSystemDirectory()) + _T("\\") + g_HomeImageFile))
        if (!m_PubFile.Add(PSS_SoapData_File(PSS_SoapData_File::IE_DM_PublicFolder,
                                             1,
                                             (const char*)m_pInfo->GetServer()->GetSystemDirectory(),
                                             (const char*)g_HomeImageFile)))
            TRACE(_T("Problem publishing the Home image file\n"));

    // publish the parent image file, if it exists
    if (PSS_File::Exist(PSS_Directory::NormalizeDirectory(m_pInfo->GetServer()->GetSystemDirectory()) + _T("\\") + g_ParentImageFile))
        if (!m_PubFile.Add(PSS_SoapData_File(PSS_SoapData_File::IE_DM_PublicFolder,
                                             1,
                                             (const char*)m_pInfo->GetServer()->GetSystemDirectory(),
                                             (const char*)g_ParentImageFile)))
            TRACE(_T("Problem publishing the Parent image file\n"));

    // reset the generated file name array
    ResetStringsArray();

    if (!PublishModel(m_pModel))
        return false;

    // save the root html file name
    m_RootHtmlFileName = BuildModelHTMLFileName(m_pModel);
    m_RootName         = m_pModel->GetAbsolutePath();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelGenerateFiles::OnFinish()
{
    // clean the directory used to generate the files
    PSS_Directory::DeleteDirectory(m_TargetDirectory, TRUE, TRUE);

    // hide the feedback dialog
    m_FileGenerateWindow.ShowWindow(SW_HIDE);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelGenerateFiles::OnSymbol(PSS_Symbol* pSymbol)
{
    if (!pSymbol)
        return false;

    ASSERT(m_pInfo);

    if (pSymbol->GetChildModel() && m_pInfo->GetDC() && m_pInfo->GetCtlr())
        if (!PublishModel(dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetChildModel())))
            return false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelGenerateFiles::OnLink(PSS_LinkSymbol* pLink)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelGenerateFiles::PublishModel(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return false;

    ASSERT(m_pInfo);

    PSS_ProcessGraphModelController* pCtrl = m_pInfo->GetCtlr();
    CDC*                             pDC   = m_pInfo->GetDC();

    if (!pDC || !pCtrl)
        return false;

    // get the viewport
    PSS_ProcessGraphModelViewport* pVp = pCtrl->BrowseModel(pModel, pModel->GetParent());

    if (!pVp)
        return false;

    // export the model to the image file name
    const CString imageFileName = BuildModelImageFileName(pModel);

    // refresh the setup copy file window
    m_FileGenerateWindow.SetDestination(imageFileName);
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
    if (!StringAlreadyGenerated(imageFileName))
        // generate the file
        if (pVp->ExportModelToImageFile(imageFileName, *pDC))
        {
            PSS_File file(imageFileName);

            // publish the file name
            if (!m_PubFile.Add(PSS_SoapData_File(PSS_SoapData_File::IE_DM_PublicFolder,
                                                 1,
                                                 (const char*)m_TargetDirectory,
                                                 (const char*)file.GetFileName())))
                TRACE1(_T("Problem publishing the file %s\n"), (const char*)imageFileName);
        }
        else
            TRACE1(_T("Problem exporting the file %s\n"), (const char*)imageFileName);

    // create the html page
    CreateHtmlPage(pModel, imageFileName);

    return true;
}
//---------------------------------------------------------------------------
CString PSS_SoapPublishModelGenerateFiles::BuildModelImageFileName(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return _T("");

    // build the file name using the full object path
    CString fileName  = PSS_Directory::NormalizeDirectory(m_TargetDirectory) + _T("\\");
    fileName         += ParseModelName(pModel->GetAbsolutePath());
    fileName         += _T(".jpg");

    return fileName;
}
//---------------------------------------------------------------------------
CString PSS_SoapPublishModelGenerateFiles::BuildModelHTMLFileName(PSS_ProcessGraphModelMdl* pModel)
{
    if (!pModel)
        return _T("");

    // build the file name using the full object path
    CString fileName  = PSS_Directory::NormalizeDirectory(m_TargetDirectory) + _T("\\");
    fileName         += ParseModelName(pModel->GetAbsolutePath());
    fileName         += _T(".htm");

    return fileName;
}
//---------------------------------------------------------------------------
CString PSS_SoapPublishModelGenerateFiles::ParseModelName(const CString& modelName)
{
    return PSS_StringTools::ConvertSpecialChar(modelName);
}
//---------------------------------------------------------------------------
bool PSS_SoapPublishModelGenerateFiles::CreateHtmlPage(PSS_ProcessGraphModelMdl* pModel, const CString& imageFileName)
{
    if (!pModel)
        return false;

    const CString  htmlFileName = BuildModelHTMLFileName(pModel);
          PSS_File rootHtmlFile(m_RootHtmlFileName);

    // refresh the setup copy file window
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
             (const char*)pModel->GetAbsolutePath(),
             (const char*)PSS_Date::GetToday().GetStandardFormattedDate());

    htmlFile << s;

    s.LoadString(IDS_SOAPMODELGENHTML_14);
    htmlFile << s;

    // write the navigation table header
    s.LoadString(IDS_SOAPMODELGENHTML_6);
    htmlFile << s;

    // write the ref to root
    s.Format(IDS_SOAPMODELGENHTML_7,
             (const char*)rootHtmlFile.GetFileName(),
             (const char*)g_HomeImageFile,
             (const char*)rootHtmlFile.GetFileName(),
             (const char*)m_RootName);

    htmlFile << s;

    // write the parent if there is one
    if (pModel->GetParent())
    {
        // get the parent html file name and name
        const CString  parentHtmlFileName = BuildModelHTMLFileName(pModel->GetParent());
              PSS_File parentHtmlFile(parentHtmlFileName);
        const CString  ParentName         = pModel->GetParent()->GetAbsolutePath();

        s.Format(IDS_SOAPMODELGENHTML_11,
                 (const char*)parentHtmlFile.GetFileName(),
                 (const char*)g_ParentImageFile,
                 (const char*)parentHtmlFile.GetFileName(),
                 (const char*)ParentName);

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

    s.Format(IDS_SOAPMODELGENHTML_2, (const char*)pModel->GetAbsolutePath(), (const char*)image.GetFileName());

    htmlFile << s;

    // write all hot spots. Iterate throught the model elements and write the hotspot entities
    CString symbolHtmlFileName;
    CRect   symbolCoordinates;

    // process the model components
    CODComponentSet* pSet = pModel->GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        if (!pComp)
            continue;

        PSS_Symbol* pCompSym = dynamic_cast<PSS_Symbol*>(pComp);

        // has a sub-model defined?
        if (pCompSym && pCompSym->GetChildModel())
        {
            // get the html file name for the reference
            symbolHtmlFileName = BuildModelHTMLFileName(dynamic_cast<PSS_ProcessGraphModelMdl*>(pCompSym->GetChildModel()));

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

        // if it's a start symbol, create the hot spot for starting a new process
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
        PSS_GenericSymbolErrorLine e(message);
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
